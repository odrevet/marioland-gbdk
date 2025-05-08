#ifndef PLATFORMS_H
#define PLATFORMS_H

#include <gb/gb.h>
#include <gbdk/metasprites.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct platform_moving_t {
  uint16_t x;
  uint16_t y;
  uint8_t draw_x;
  uint8_t draw_y;

  int8_t vel_x;
  int8_t vel_y;
  uint8_t size;
  uint8_t range;
} platform_moving_t;

typedef struct platform_falling_t{
  uint16_t x;
  uint16_t y;
  uint8_t draw_x;
  uint8_t draw_y;

  bool is_falling;
  uint8_t ttl;
} platform_falling_t;

void platform_moving_new(uint16_t x, uint16_t y, uint8_t size, uint8_t range);
void platform_falling_new(uint16_t x, uint16_t y);


#endif
