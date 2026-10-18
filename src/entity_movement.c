#pragma bank 255

#include "entity_movement.h"
#include "level.h"

#define ENTITY_GRAVITY 32

uint8_t entity_has_ground(uint16_t x, uint16_t y, uint8_t width,
                          uint8_t height) BANKED {
  uint16_t ground_check_x = x >> 4;
  uint16_t ground_check_y = (y >> 4) + height;

  uint8_t tile_ground_left = get_tile(ground_check_x - camera_x, ground_check_y);
  uint8_t tile_ground_right =
      get_tile(ground_check_x + width - 1 - camera_x, ground_check_y);

  return is_tile_solid(tile_ground_left) || is_tile_solid(tile_ground_right) ||
         is_tile_passthought(tile_ground_left, tile_ground_right);
}

uint8_t entity_has_ground_ahead(uint16_t x, uint16_t y, int8_t vel_x,
                                uint8_t width, uint8_t height) BANKED {
  uint16_t current_x = x >> 4;
  uint16_t current_y = y >> 4;

  if (vel_x > 0) {
    uint8_t tile = get_tile(current_x + width - camera_x, current_y + height);
    return is_tile_solid(tile) || is_tile_passthought(tile, tile);
  } else if (vel_x < 0) {
    uint8_t tile = get_tile(current_x - 1 - camera_x, current_y + height);
    return is_tile_solid(tile) || is_tile_passthought(tile, tile);
  }
  return FALSE;
}

void entity_apply_horizontal_movement(uint16_t *x, uint16_t y, int8_t *vel_x,
                                      bool *flip, uint8_t width, uint8_t height,
                                      uint8_t top_margin,
                                      uint8_t check_cliffs) BANKED {
  if (*vel_x == 0) {
    return;
  }

  uint16_t next_x_upscaled = *x + *vel_x;
  uint16_t next_x = next_x_upscaled >> 4;
  uint16_t current_y = y >> 4;

  uint8_t hit_wall = FALSE;
  uint8_t hit_cliff = FALSE;

  if (*vel_x > 0) {
    uint8_t tile_right_top =
        get_tile(next_x + width - 1 - camera_x, current_y + top_margin);
    uint8_t tile_right_bottom =
        get_tile(next_x + width - 1 - camera_x, current_y + height - 1);

    hit_wall = is_tile_solid(tile_right_top) || is_tile_solid(tile_right_bottom);

    if (check_cliffs && !hit_wall) {
      hit_cliff = !entity_has_ground_ahead(*x, y, *vel_x, width, height);
    }
  } else if (*vel_x < 0) {
    uint8_t tile_left_top =
        get_tile(next_x - camera_x, current_y + top_margin);
    uint8_t tile_left_bottom =
        get_tile(next_x - camera_x, current_y + height - 1);

    hit_wall = is_tile_solid(tile_left_top) || is_tile_solid(tile_left_bottom);

    if (check_cliffs && !hit_wall) {
      hit_cliff = !entity_has_ground_ahead(*x, y, *vel_x, width, height);
    }
  }

  if (hit_wall || hit_cliff) {
    *vel_x = -*vel_x;
    *flip = !*flip;
  } else {
    *x = next_x_upscaled;
  }
}

void entity_apply_vertical_movement(uint16_t x, uint16_t *y, int8_t *vel_y,
                                    uint8_t width, uint8_t height,
                                    uint8_t top_margin, uint8_t gravity_shift,
                                    uint8_t on_ground) BANKED {
  uint16_t ground_check_x = x >> 4;

  if (!on_ground) {
    if (gravity_shift == 0) {
      *vel_y = ENTITY_GRAVITY;
    } else {
      *vel_y += ENTITY_GRAVITY >> gravity_shift;
    }
  }

  if (*vel_y != 0) {
    uint16_t next_y_upscaled = *y + *vel_y;
    uint16_t next_y = next_y_upscaled >> 4;

    if (*vel_y > 0) {
      uint8_t tile_bottom_left =
          get_tile(ground_check_x - camera_x, next_y + height);
      uint8_t tile_bottom_right =
          get_tile(ground_check_x + width - 1 - camera_x, next_y + height);

      if (is_tile_solid(tile_bottom_left) || is_tile_solid(tile_bottom_right) ||
          is_tile_passthought(tile_bottom_left, tile_bottom_right)) {
        *vel_y = 0;
        *y = (TILE_ALIGN(next_y + height) - height) << 4;
      } else {
        *y = next_y_upscaled;
      }
    } else if (*vel_y < 0) {
      uint8_t tile_top_left =
          get_tile(ground_check_x - camera_x, next_y + top_margin);
      uint8_t tile_top_right =
          get_tile(ground_check_x + width - 1 - camera_x, next_y + top_margin);

      if (is_tile_solid(tile_top_left) || is_tile_solid(tile_top_right)) {
        *vel_y = 0;
      } else {
        *y = next_y_upscaled;
      }
    }
  }
}
