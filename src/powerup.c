#pragma bank 255

#include "powerup.h"
#include "level.h"

#include <gbdk/emu_debug.h>

#define POWERUP_MUSHROOM_SPEED 4

BANKREF(powerup)

bool powerup_active = FALSE;
powerup_t powerup;

void powerup_new(uint16_t x, uint16_t y, uint8_t type) BANKED {
  powerup.x = x;
  powerup.y = y;

  powerup.type = type;

  switch (powerup.type) {
  case POWERUP_MUSHROOM:
    powerup.current_frame = 0;
    powerup.vel_x = POWERUP_MUSHROOM_SPEED;
    powerup.vel_y = 0;
    EMU_printf("SPAWN MUSH x=%d y=%d\n", powerup.x, powerup.y);
    break;
  case POWERUP_STAR:
    powerup.current_frame = 5;
    //EMU_printf("SPWAN STAR WITH FRAME %d \n", powerup.current_frame);
    break;
  }

  powerup_active = TRUE;
}

void powerup_update(void) BANKED {
  powerup.draw_x =
      ((powerup.x - camera_x_upscaled) >> 4) + DEVICE_SPRITE_PX_OFFSET_X + 4;
  //powerup.draw_y = (powerup.y >> 4) + DEVICE_SPRITE_PX_OFFSET_Y + TILE_SIZE + 4;
  powerup.draw_y = (powerup.y >> 4) + DEVICE_SPRITE_PX_OFFSET_Y + 2 * TILE_SIZE + 4;

  if (powerup.type == POWERUP_MUSHROOM) {
    if (powerup.vel_x == 0) {
      powerup.vel_x = POWERUP_MUSHROOM_SPEED;
    }

    uint16_t current_x = powerup.x >> 4;
    uint16_t current_y = powerup.y >> 4;

    uint16_t next_x_upscaled = powerup.x + powerup.vel_x;
    uint16_t next_x = next_x_upscaled >> 4;

    uint8_t hit_wall = FALSE;
    if (powerup.vel_x > 0) {
      uint8_t tile_right_top = get_tile(next_x + TILE_SIZE - 1 - camera_x, current_y);
      uint8_t tile_right_bottom = get_tile(next_x + TILE_SIZE - 1 - camera_x, current_y + TILE_SIZE - 1);
      hit_wall = is_tile_solid(tile_right_top) || is_tile_solid(tile_right_bottom);
    } else if (powerup.vel_x < 0) {
      uint8_t tile_left_top = get_tile(next_x - camera_x, current_y);
      uint8_t tile_left_bottom = get_tile(next_x - camera_x, current_y + TILE_SIZE - 1);
      hit_wall = is_tile_solid(tile_left_top) || is_tile_solid(tile_left_bottom);
    }

    if (hit_wall) {
      powerup.vel_x = -powerup.vel_x;
    } else {
      powerup.x = next_x_upscaled;
    }

    uint16_t ground_check_x = powerup.x >> 4;
    uint16_t ground_check_y = (powerup.y >> 4) + TILE_SIZE;

    uint8_t tile_ground_left = get_tile(ground_check_x - camera_x, ground_check_y);
    uint8_t tile_ground_right = get_tile(ground_check_x + TILE_SIZE - 1 - camera_x, ground_check_y);
    uint8_t on_ground = is_tile_solid(tile_ground_left) || is_tile_solid(tile_ground_right) ||
                        is_tile_passthought(tile_ground_left, tile_ground_right);

    if (!on_ground) {
      powerup.vel_y += 32;
    }

    if (powerup.vel_y != 0) {
      uint16_t next_y_upscaled = powerup.y + powerup.vel_y;
      uint16_t next_y = next_y_upscaled >> 4;

      if (powerup.vel_y > 0) {
        uint8_t tile_bottom_left = get_tile(ground_check_x - camera_x, next_y + TILE_SIZE);
        uint8_t tile_bottom_right = get_tile(ground_check_x + TILE_SIZE - 1 - camera_x, next_y + TILE_SIZE);
        if (is_tile_solid(tile_bottom_left) || is_tile_solid(tile_bottom_right) ||
            is_tile_passthought(tile_bottom_left, tile_bottom_right)) {
          powerup.vel_y = 0;
          powerup.y = (TILE_ALIGN(next_y + TILE_SIZE) - TILE_SIZE) << 4;
        } else {
          powerup.y = next_y_upscaled;
        }
      } else if (powerup.vel_y < 0) {
        uint8_t tile_top_left = get_tile(ground_check_x - camera_x, next_y);
        uint8_t tile_top_right = get_tile(ground_check_x + TILE_SIZE - 1 - camera_x, next_y);
        if (is_tile_solid(tile_top_left) || is_tile_solid(tile_top_right)) {
          powerup.vel_y = 0;
        } else {
          powerup.y = next_y_upscaled;
        }
      }
    }
  }

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

  base_sprite +=
      move_metasprite_ex(commonSprites_metasprite, commonSprites_TILE_ORIGIN, 0,
                         base_sprite, powerup.draw_x, powerup.draw_y);

  SWITCH_ROM(_saved_bank);

  return base_sprite;
}
