#pragma bank 255

#include "platforms.h"
#include "global.h"
#include "commonSprites.h"

uint8_t platform_moving_count = 0;
platform_moving_t platforms_moving[PLATFORM_MOVING_MAX];

uint8_t platform_falling_count = 0;
platform_falling_t platforms_falling[PLATFORM_FALLING_MAX];

// Frame index of the falling platform sprite in commonSprites.
#define PLATFORM_FALLING_FRAME 9

void platform_moving_new(uint16_t x, uint16_t y,
                         platform_direction_t platform_direction, uint8_t range,
                         uint8_t width) BANKED {
  //EMU_printf("new platform at %d:%d", x, y);
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

void platform_moving_update(void) NONBANKED {
  uint8_t index_platform_moving = 0;
  while (index_platform_moving < platform_moving_count) {
    platform_moving_t *platform = &platforms_moving[index_platform_moving];

    platform->x += platform->vel_x;
    platform->y += platform->vel_y;

    platform->draw_x = (platform->x - camera_x_upscaled) >> 4;
    platform->draw_y = platform->y >> 4;

    platform->range_current++;
    if (platform->range_current >= 14 * TILE_SIZE) {
      platform->vel_x = -platform->vel_x;
      platform->vel_y = -platform->vel_y;
      platform->range_current = 0;
    }

    if (platform->x <= camera_x_upscaled - DEVICE_SCREEN_PX_WIDTH) {
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

uint8_t platform_moving_draw(uint8_t base_sprite) NONBANKED {
  uint8_t _saved_bank = _current_bank;
  SWITCH_ROM(BANK(commonSprites));

  uint8_t draw_index = 4;
  const metasprite_t *commonSprites_metasprite =
      commonSprites_metasprites[draw_index];

  for (uint8_t index_platform_moving = 0;
       index_platform_moving < platform_moving_count; index_platform_moving++) {
    platform_moving_t *platform = &platforms_moving[index_platform_moving];
    // The metasprite origin is the sprite center, so offset by half a tile.
    uint8_t draw_y = platform->draw_y + DEVICE_SPRITE_PX_OFFSET_Y +
                     MARGIN_TOP_PX + (TILE_SIZE / 2);

    for (uint8_t i = 0; i < PLATFORMS_MOVING_SIZE; i++) {
      base_sprite += move_metasprite_ex(
          commonSprites_metasprite, commonSprites_TILE_ORIGIN, 0, base_sprite,
          platform->draw_x + i * commonSprites_TILE_W +
              DEVICE_SPRITE_PX_OFFSET_X + (TILE_SIZE / 2),
          draw_y);
    }
  }
  SWITCH_ROM(_saved_bank);

  return base_sprite;
}

void platform_falling_new(uint16_t x, uint16_t y) BANKED {
  if (platform_falling_count < PLATFORM_FALLING_MAX) {
    platform_falling_t *platform =
        &platforms_falling[platform_falling_count];

    platform->x = x << 4;
    platform->y = y << 4;
    platform->is_falling = FALSE;
    platform->draw_x = (platform->x - camera_x_upscaled) >> 4;
    platform->draw_y = platform->y >> 4;

    platform_falling_count++;
  }
}

void platform_falling_update(void) NONBANKED {
  uint8_t index_platform_falling = 0;

  while (index_platform_falling < platform_falling_count) {
    platform_falling_t *platform =
        &platforms_falling[index_platform_falling];

    // Once Mario has stepped on it, the platform drops at a constant speed and
    // keeps falling even if he jumps off.
    if (platform->is_falling) {
      platform->y += PLATFORM_FALLING_SPEED;
    }

    platform->draw_x = (platform->x - camera_x_upscaled) >> 4;
    platform->draw_y = platform->y >> 4;

    if (platform->x + (DEVICE_SCREEN_PX_WIDTH << 4) <= camera_x_upscaled ||
        (platform->is_falling &&
         platform->draw_y > DEVICE_SCREEN_PX_HEIGHT)) {
      for (uint8_t j = index_platform_falling;
           j < platform_falling_count - 1; j++) {
        platforms_falling[j] = platforms_falling[j + 1];
      }
      platform_falling_count--;
      hide_sprites_range(1, MAX_HARDWARE_SPRITES);
      continue;
    }

    index_platform_falling++;
  }
}

uint8_t platform_falling_draw(uint8_t base_sprite) NONBANKED {
  uint8_t _saved_bank = _current_bank;
  SWITCH_ROM(BANK(commonSprites));

  const metasprite_t *commonSprites_metasprite =
      commonSprites_metasprites[PLATFORM_FALLING_FRAME];

  for (uint8_t index_platform_falling = 0;
       index_platform_falling < platform_falling_count;
       index_platform_falling++) {
    platform_falling_t *platform =
        &platforms_falling[index_platform_falling];
    // The metasprite origin is the sprite center, so offset by half a tile.
    uint8_t draw_y = platform->draw_y + DEVICE_SPRITE_PX_OFFSET_Y +
                     MARGIN_TOP_PX + (TILE_SIZE / 2);

    base_sprite += move_metasprite_ex(
        commonSprites_metasprite, commonSprites_TILE_ORIGIN, 0, base_sprite,
        platform->draw_x + DEVICE_SPRITE_PX_OFFSET_X + (TILE_SIZE / 2),
        draw_y);
  }
  SWITCH_ROM(_saved_bank);

  return base_sprite;
}
