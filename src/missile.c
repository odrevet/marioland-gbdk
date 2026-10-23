#pragma bank 255

#include "missile.h"

#include <gbdk/platform.h>

#include "commonSprites.h"
#include "enemy.h"
#include "global.h"
#include "level.h"

#ifdef GAMEBOY
#include "sound_squish.h"
#endif

BANKREF(missile)

missile_t missiles[NB_MISSILE];

// Projectile sprite: frame 11 of the common sprite sheet (the torpedo).
// That frame is a single 8x8 tile, so it can be drawn with the direct sprite
// API using its tile index instead of reading the metasprite from another ROM
// bank (which is not safe from this banked file).
#define MISSILE_FRAME 11
#define MISSILE_TILE (commonSprites_TILE_ORIGIN + MISSILE_FRAME)
#define MISSILE_SIZE TILE_SIZE
// Horizontal speed, in pixels per frame. Kept below one tile per frame so the
// pre-move tile test below can never skip a block.
#define MISSILE_SPEED 4
// Safety net: the missile is also dropped when it leaves the screen, so this
// only has to outlive the widest possible flight.
#define MISSILE_TTL 90

void missile_fire(uint16_t world_x, uint16_t world_y) BANKED {
  for (uint8_t i = 0; i < NB_MISSILE; i++) {
    if (missiles[i].ttl != 0) {
      continue;
    }

    missiles[i].x = (int16_t)world_x;
    missiles[i].y = (int16_t)world_y;
    missiles[i].ttl = MISSILE_TTL;

    // Hide the slot until the next draw so a recycled slot never shows the
    // sprite left over from the previous missile.
    hide_sprite(MISSILE_HW_SPRITE_BASE + i);
    return;
  }
}

// Kill the first enemy the missile overlaps. Returns TRUE on a hit.
// enemy_stomp lives in another bank: the compiler emits the banked call, so
// no manual bank switch (which would be fatal in this banked function).
static bool missile_hit_enemy(const missile_t *missile) {
  int16_t missile_left = missile->x;
  int16_t missile_right = (int16_t)(missile->x + MISSILE_SIZE);
  int16_t missile_top = missile->y;
  int16_t missile_bottom = (int16_t)(missile->y + MISSILE_SIZE);

  for (uint8_t index_enemy = 0; index_enemy < ENEMY_MAX; index_enemy++) {
    enemy_t *enemy = &enemies[index_enemy];

    if (!enemy->active || enemy->stomped) {
      continue;
    }

    int16_t enemy_left = (int16_t)(enemy->x >> 4);
    int16_t enemy_right = (int16_t)((enemy->x >> 4) + TILE_SIZE);
    int16_t enemy_top = (int16_t)(enemy->y >> 4);
    int16_t enemy_bottom = (int16_t)((enemy->y >> 4) + enemiesSprites_HEIGHT);

    if (missile_left < enemy_right && missile_right > enemy_left &&
        missile_top < enemy_bottom && missile_bottom > enemy_top) {
      enemy_stomp(index_enemy);

#ifdef GAMEBOY
      music_play_sfx(BANK(sound_squish), sound_squish,
                     SFX_MUTE_MASK(sound_squish), MUSIC_SFX_PRIORITY_NORMAL);
#endif
      return TRUE;
    }
  }

  return FALSE;
}

void missile_update(void) BANKED {
  for (uint8_t i = 0; i < NB_MISSILE; i++) {
    missile_t *missile = &missiles[i];

    if (missile->ttl == 0) {
      continue;
    }

    missile->ttl--;

    // The leading edge of the missile (its right side) is what hits the
    // background. It is tested before the move so a missile sitting on the
    // tile grid cannot enter a solid tile on the frame it starts touching it.
    // Kept signed so the comparison against the (up to 256 pixel wide) screen
    // stays meaningful on every target.
    int16_t front =
        (int16_t)(missile->x + MISSILE_SIZE - 1 - (int16_t)camera_x);

    // Past the right edge of the screen the level columns ahead are not
    // loaded, so the flight ends there.
    if (front >= DEVICE_SCREEN_PX_WIDTH) {
      missile->ttl = 0;
      hide_sprite(MISSILE_HW_SPRITE_BASE + i);
      continue;
    }

    if (missile_hit_enemy(missile)) {
      missile->ttl = 0;
      hide_sprite(MISSILE_HW_SPRITE_BASE + i);
      continue;
    }

    // Test the two tiles the leading edge can touch (the missile is one tile
    // tall but may straddle two rows).
    uint8_t tile_x = (uint8_t)front;
    uint8_t tile_top = get_tile(tile_x, (uint8_t)missile->y);
    uint8_t tile_bottom =
        get_tile(tile_x, (uint8_t)(missile->y + MISSILE_SIZE - 1));

    if (tile_top == BREAKABLE_BLOCK || tile_bottom == BREAKABLE_BLOCK) {
      uint8_t hit_y = (tile_top == BREAKABLE_BLOCK)
                          ? (uint8_t)missile->y
                          : (uint8_t)(missile->y + MISSILE_SIZE - 1);
      on_break_tile(tile_x, hit_y);
      missile->ttl = 0;
      hide_sprite(MISSILE_HW_SPRITE_BASE + i);
      continue;
    }

    if (is_tile_solid(tile_top) || is_tile_solid(tile_bottom)) {
      missile->ttl = 0;
      hide_sprite(MISSILE_HW_SPRITE_BASE + i);
      continue;
    }

    // Nothing in the way, the missile moves on.
    missile->x = (int16_t)(missile->x + MISSILE_SPEED);
  }
}

// Draw the torpedo with the common sheet's frame 11. The missile positions are
// in world space so they scroll with the level.
uint8_t missile_draw(uint8_t base_sprite) BANKED {
  for (uint8_t i = 0; i < NB_MISSILE; i++) {
    uint8_t slot = MISSILE_HW_SPRITE_BASE + i;
    missile_t *missile = &missiles[i];

    if (missile->ttl == 0) {
      continue;
    }

    int16_t screen_x = (int16_t)(missile->x - (int16_t)camera_x);
    int16_t screen_y = (int16_t)(missile->y + MARGIN_TOP_PX);

    if (screen_x < -MISSILE_SIZE || screen_x > DEVICE_SCREEN_PX_WIDTH ||
        screen_y < -MISSILE_SIZE || screen_y > DEVICE_SCREEN_PX_HEIGHT) {
      hide_sprite(slot);
      continue;
    }

    // The torpedo tile is pivoted on its center, so offset the sprite position
    // by half a tile.
    set_sprite_tile(slot, MISSILE_TILE);
    set_sprite_prop(slot, S_PAL(0));
    move_sprite(slot,
                (uint8_t)(screen_x + DEVICE_SPRITE_PX_OFFSET_X +
                          (MISSILE_SIZE / 2)),
                (uint8_t)(screen_y + DEVICE_SPRITE_PX_OFFSET_Y +
                          (MISSILE_SIZE / 2)));
  }

  return base_sprite;
}

void missile_reset(void) BANKED {
  for (uint8_t i = 0; i < NB_MISSILE; i++) {
    missiles[i].ttl = 0;
    missiles[i].x = 0;
    missiles[i].y = 0;
    hide_sprite(MISSILE_HW_SPRITE_BASE + i);
  }
}
