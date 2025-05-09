#ifndef PLATFORMS_H
#define PLATFORMS_H

#include <gb/gb.h>
#include <gbdk/metasprites.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gbdk/emu_debug.h>

typedef enum {
  DIRECTION_VERTICAL,
  DIRECTION_HORIZONTAL,
  DIRECTION_BOTH
} plateform_direction_t;

typedef struct {
  uint16_t x;
  uint16_t y;
  uint8_t draw_x;
  uint8_t draw_y;

  int8_t vel_x;
  int8_t vel_y;
  uint8_t size;
  uint8_t range;
} platform_moving_t;

typedef struct {
  uint16_t x;
  uint16_t y;
  uint8_t draw_x;
  uint8_t draw_y;

  bool is_falling;
} platform_falling_t;

void platform_moving_new(uint16_t x, uint16_t y, plateform_direction_t direction, uint8_t range);
void platform_falling_new(uint16_t x, uint16_t y);


#endif
