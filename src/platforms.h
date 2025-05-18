#ifndef PLATFORMS_H
#define PLATFORMS_H

#include <gb/gb.h>
#include <gbdk/metasprites.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "level.h"

#include "graphics/sprite_common.h"

typedef enum {
  DIRECTION_VERTICAL,
  DIRECTION_HORIZONTAL,
  DIRECTION_BOTH
} platform_direction_t;

#define PLATFORMS_MOVING_SIZE 3
#define PLATFORMS_MOVING_RANGE 6

typedef struct {
  uint16_t x;
  uint16_t y;
  uint8_t draw_x;
  uint8_t draw_y;

  int8_t vel_x;
  int8_t vel_y;
  platform_direction_t platform_direction;
  uint8_t range;
  uint8_t width;
} platform_moving_t;

typedef struct {
  uint16_t x;
  uint16_t y;
  uint8_t draw_x;
  uint8_t draw_y;

  bool is_falling;
} platform_falling_t;

#define PLATFORM_MOVING_MAX 3
extern uint8_t platform_moving_count;
extern platform_moving_t platforms_moving[PLATFORM_MOVING_MAX];

void platform_moving_new(uint16_t x, uint16_t y,
                         platform_direction_t plateform_direction,
                         uint8_t range, uint8_t width);
void platform_moving_update();
uint8_t platform_moving_draw(uint8_t base_sprite);

void platform_falling_new(uint16_t x, uint16_t y);

#endif
