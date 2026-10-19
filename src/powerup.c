#pragma bank 255

#include "powerup.h"
#include "entity_movement.h"
#include "level.h"

#define POWERUP_MUSHROOM_SPEED 4

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
    //EMU_printf("SPWAN STAR WITH FRAME %d \n", powerup.current_frame);
    break;
  }

  powerup_active = TRUE;
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
  }

  powerup.draw_x =
      ((powerup.x - camera_x_upscaled) >> 4) + DEVICE_SPRITE_PX_OFFSET_X + 4;
  powerup.draw_y = (powerup.y >> 4) + DEVICE_SPRITE_PX_OFFSET_Y + 2 * TILE_SIZE + 4;

  if (powerup.draw_x >= DEVICE_SCREEN_PX_WIDTH + 8 * TILE_SIZE &&
      powerup.draw_x <= 255) {
    powerup_active = FALSE;
  }
}

uint8_t powerup_draw(uint8_t base_sprite) NONBANKED {
  uint8_t _saved_bank = _current_bank;
  SWITCH_ROM(BANK(commonSprites));

  //EMU_printf("frame %d \n", powerup.current_frame);

  metasprite_t *commonSprites_metasprite =
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
