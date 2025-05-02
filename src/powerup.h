#ifndef POWERUP_H
#define POWERUP_H

#include <gb/gb.h>
#include <gbdk/metasprites.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"
//#include "graphics/powerups.h"

enum powerup_type {
  POWERUP_MUSHROOM,
  POWERUP_FLOWER,
  POWERUP_STAR,
  POWERUP_HEART
};

typedef struct powerup_t {
  uint16_t x;
  uint16_t y;
  uint8_t draw_x;
  uint8_t draw_y;
  int8_t vel_x;
  int8_t vel_y;
  uint8_t type;
} powerup_t;

// a single power up at a time available
extern powerup_t powerup;

void powerup_new(uint16_t x, uint16_t y, uint8_t type);
void powerup_update(void);
uint8_t powerup_draw(uint8_t base_sprite);

#endif
