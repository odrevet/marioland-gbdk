#include "platforms.h"
#include "global.h"
#include "graphics/common.h"

uint8_t platform_moving_count = 0;
platform_moving_t platforms_moving[PLATFORM_MOVING_MAX];

void platform_moving_new(uint16_t x, uint16_t y,
                         platform_direction_t platform_direction, uint8_t range,
                         uint8_t width) {
  EMU_printf("new platform at %d:%d", x, y);
  if (platform_moving_count < PLATFORM_MOVING_MAX) {
    platform_moving_t platform_moving = {
        .x = x << 4,
        .y = y << 4,
        .platform_direction = platform_direction,
        .range_max = range * TILE_SIZE,
        .width = ((width == 0) ? PLATFORMS_MOVING_SIZE : width) * TILE_SIZE,
        .vel_x = platform_direction == DIRECTION_HORIZONTAL ? 8 : 0,
        .vel_y = platform_direction == DIRECTION_VERTICAL ? 8 : 0};

    platforms_moving[platform_moving_count] = platform_moving;
    platform_moving_count++;
  }
}

void platform_moving_update() {
  uint8_t index_platform_moving = 0;
  while (index_platform_moving < platform_moving_count) {
    platforms_moving[index_platform_moving].x +=
        platforms_moving[index_platform_moving].vel_x;
    platforms_moving[index_platform_moving].y +=
        platforms_moving[index_platform_moving].vel_y;

    platforms_moving[index_platform_moving].draw_x =
        (platforms_moving[index_platform_moving].x - camera_x_upscaled) >> 4;
    platforms_moving[index_platform_moving].draw_y =
        platforms_moving[index_platform_moving].y >> 4;

    platforms_moving[index_platform_moving].range_current++;
    if (platforms_moving[index_platform_moving].range_current >=
        14 * TILE_SIZE /*platforms_moving[index_platform_moving].range_max*/) {
      platforms_moving[index_platform_moving].vel_x =
          -platforms_moving[index_platform_moving].vel_x;
      platforms_moving[index_platform_moving].vel_y =
          -platforms_moving[index_platform_moving].vel_y;

      platforms_moving[index_platform_moving].range_current = 0;
    }

    if (platforms_moving[index_platform_moving].x <=
        camera_x_upscaled - DEVICE_SCREEN_PX_WIDTH) {
      // EMU_printf("REMOVE PLATFORM\n");
      for (uint8_t j = index_platform_moving; j < platform_moving_count - 1;
           j++) {
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

  for (uint8_t index_platform_moving = 0;
       index_platform_moving < platform_moving_count; index_platform_moving++) {
    for (uint8_t i = 0; i < PLATFORMS_MOVING_SIZE; i++) {
      base_sprite += move_metasprite_ex(
          sprite_common_metasprite, sprite_common_TILE_ORIGIN, 0, base_sprite,
          platforms_moving[index_platform_moving].draw_x + i * common_TILE_W +
              DEVICE_SPRITE_PX_OFFSET_X,
          platforms_moving[index_platform_moving].draw_y +
              +DEVICE_SPRITE_PX_OFFSET_Y + MARGIN_TOP_PX + TILE_SIZE);
    }
  }
  SWITCH_ROM(_saved_bank);

  return base_sprite;
}

void platform_falling_new(uint16_t x, uint16_t y) {}
