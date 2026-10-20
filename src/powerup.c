#pragma bank 255

#include "powerup.h"
#include "entity_movement.h"
#include "level.h"

#define POWERUP_MUSHROOM_SPEED 4

// frame index of the flower in commonSprites
#define POWERUP_FLOWER_FRAME 2

// The star hops: it first moves one tile up and one tile right, then one tile
// down and one tile right, then it falls without any background collision.
#define POWERUP_STAR_SPEED 8
#define POWERUP_STAR_GRAVITY 16
#define POWERUP_STAR_MAX_FALL_SPEED 48
#define POWERUP_STAR_RISE_HEIGHT (TILE_SIZE << 4)

#define STAR_STATE_RISING 0
#define STAR_STATE_DESCENDING 1
#define STAR_STATE_FALLING 2

BANKREF(powerup)

bool powerup_active = FALSE;
powerup_t powerup;

void powerup_new(uint16_t x, uint16_t y, uint8_t type) BANKED {
  powerup.x = x;
  powerup.y = y;

  powerup.type = type;
  powerup.flip = FALSE;

  switch (powerup.type) {
  case POWERUP_MUSHROOM:
    powerup.current_frame = 0;
    powerup.vel_x = POWERUP_MUSHROOM_SPEED;
    powerup.vel_y = 0;
    break;
  case POWERUP_STAR:
    powerup.current_frame = 5;
    powerup.vel_x = POWERUP_STAR_SPEED;
    powerup.vel_y = -POWERUP_STAR_SPEED;
    powerup.y_origin = y;
    powerup.move_state = STAR_STATE_RISING;
    break;
  case POWERUP_FLOWER:
    // the flower is static: it stays where it spawned
    powerup.current_frame = POWERUP_FLOWER_FRAME;
    powerup.vel_x = 0;
    powerup.vel_y = 0;
    break;
  }

  powerup_active = TRUE;
}

static void powerup_move_star(void) {
  // The star follows a fixed trajectory, ignoring the background completely:
  // rise diagonally up-right by one tile, then descend diagonally down-right
  // by one tile, then free fall while still drifting right.
  int16_t rise_target = (int16_t)powerup.y_origin - POWERUP_STAR_RISE_HEIGHT;

  if (rise_target < 0) {
    rise_target = 0;
  }

  switch (powerup.move_state) {
  case STAR_STATE_RISING:
    powerup.x += powerup.vel_x;

    if ((int16_t)powerup.y + powerup.vel_y <= rise_target) {
      powerup.y = (uint16_t)rise_target;
      powerup.vel_y = POWERUP_STAR_SPEED;
      powerup.move_state = STAR_STATE_DESCENDING;
    } else {
      powerup.y += powerup.vel_y;
    }
    break;

  case STAR_STATE_DESCENDING:
    powerup.x += powerup.vel_x;
    powerup.y += powerup.vel_y;

    if (powerup.y >= powerup.y_origin) {
      powerup.y = powerup.y_origin;
      powerup.vel_y = 0;
      powerup.move_state = STAR_STATE_FALLING;
    }
    break;

  case STAR_STATE_FALLING:
    powerup.x += powerup.vel_x;
    powerup.vel_y += POWERUP_STAR_GRAVITY;

    if (powerup.vel_y > POWERUP_STAR_MAX_FALL_SPEED) {
      powerup.vel_y = POWERUP_STAR_MAX_FALL_SPEED;
    }

    powerup.y += powerup.vel_y;
    break;
  }
}

void powerup_update(void) BANKED {
  // the mushroom walks like a goomba: it moves horizontally, bounces off walls
  // and falls with gravity. It shares the enemy movement code, which lives in
  // a bank (see entity_movement.c) because ROM bank 0 is limited.
  if (powerup.type == POWERUP_MUSHROOM) {
    if (powerup.vel_x == 0) {
      powerup.vel_x = POWERUP_MUSHROOM_SPEED;
    }

    entity_apply_horizontal_movement(
        &powerup.x, powerup.y, &powerup.vel_x, &powerup.flip, TILE_SIZE,
        TILE_SIZE, 0, FALSE);
    entity_apply_vertical_movement(
        powerup.x, &powerup.y, &powerup.vel_y, TILE_SIZE, TILE_SIZE, 0, 0,
        entity_has_ground(powerup.x, powerup.y, TILE_SIZE, TILE_SIZE));
  } else if (powerup.type == POWERUP_STAR) {
    powerup_move_star();
  }

  powerup.draw_x =
      ((powerup.x - camera_x_upscaled) >> 4) + DEVICE_SPRITE_PX_OFFSET_X + 4;
  powerup.draw_y = (powerup.y >> 4) + DEVICE_SPRITE_PX_OFFSET_Y + 2 * TILE_SIZE + 4;

  if (powerup.draw_x >= DEVICE_SCREEN_PX_WIDTH + 8 * TILE_SIZE) {
    powerup_active = FALSE;
  }

  if ((powerup.y >> 4) > DEVICE_SCREEN_PX_HEIGHT + 2 * TILE_SIZE) {
    powerup_active = FALSE;
  }
}

uint8_t powerup_draw(uint8_t base_sprite) NONBANKED {
  uint8_t _saved_bank = _current_bank;
  SWITCH_ROM(BANK(commonSprites));

  //EMU_printf("frame %d \n", powerup.current_frame);

  const metasprite_t *commonSprites_metasprite =
      commonSprites_metasprites[powerup.current_frame];

  // EMU_printf("DRAW OBJECT %d at %d %d\n", powerup.type, powerup.draw_x,
  //            powerup.draw_y);

#ifdef SEGA
  base_sprite += move_metasprite_ex(commonSprites_metasprite,
                                    commonSprites_TILE_ORIGIN, 0, base_sprite,
                                    powerup.draw_x, powerup.draw_y);
#else
  if (powerup.flip) {
    base_sprite += move_metasprite_flipx(commonSprites_metasprite,
                                         commonSprites_TILE_ORIGIN, 0,
                                         base_sprite, powerup.draw_x,
                                         powerup.draw_y);
  } else {
    base_sprite += move_metasprite_ex(commonSprites_metasprite,
                                      commonSprites_TILE_ORIGIN, 0, base_sprite,
                                      powerup.draw_x, powerup.draw_y);
  }
#endif

  SWITCH_ROM(_saved_bank);

  return base_sprite;
}
