#include "platforms.h"
#include "graphics/common.h"

uint8_t platform_moving_count = 0;
platform_moving_t platforms_moving[PLATFORM_MOVING_MAX];

void platform_moving_new(uint16_t x, uint16_t y,
                         platform_direction_t platform_direction,
                         uint8_t range) {
  if (platform_moving_count < PLATFORM_MOVING_MAX) {
    platform_moving_t platform_moving = {.x = x << 4,
                                         .y = y << 4,
                                         .platform_direction =
                                             platform_direction,
                                         .range = range};
    platforms_moving[platform_moving_count] = platform_moving;
    platform_moving_count++;
  }
}

void platform_moving_update() {
  uint8_t index_platform_moving = 0;
  while (index_platform_moving < platform_moving_count) {
    platforms_moving[index_platform_moving].x +=
        platforms_moving[index_platform_moving].vel_x;
    platforms_moving[index_platform_moving].draw_x =
        (platforms_moving[index_platform_moving].x - camera_x_subpixel) >> 4;
    platforms_moving[index_platform_moving].draw_y =
        platforms_moving[index_platform_moving].y >> 4;

    if (platforms_moving[index_platform_moving].x <= camera_x_subpixel - DEVICE_SCREEN_PX_WIDTH) {
      //EMU_printf("REMOVE PLATFORM\n");
      for (uint8_t j = index_platform_moving; j < platform_moving_count - 1; j++) {
        platforms_moving[j] = platforms_moving[j + 1];
      }
      platform_moving_count--;
      hide_sprites_range(1, MAX_HARDWARE_SPRITES);
      continue;
    }


    index_platform_moving++;
  }
}

uint8_t platform_moving_draw(uint8_t base_sprite) {
  uint8_t _saved_bank = _current_bank;
  SWITCH_ROM(BANK(sprite_common));

  uint8_t draw_index = 4;
  metasprite_t *sprite_common_metasprite =
      sprite_common_metasprites[draw_index];

  for (int index_platform_moving = 0;
       index_platform_moving < platform_moving_count; index_platform_moving++) {
    for (int i = 0; i < PLATFORMS_MOVING_SIZE; i++) {
      base_sprite += move_metasprite_ex(
          sprite_common_metasprite, sprite_common_TILE_ORIGIN, 0, base_sprite,
          platforms_moving[index_platform_moving].draw_x + i * common_TILE_W,
          platforms_moving[index_platform_moving].draw_y);
    }
  }
  SWITCH_ROM(_saved_bank);

  return base_sprite;
}

void platform_falling_new(uint16_t x, uint16_t y) {}
