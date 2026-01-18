#ifndef MISSILE_H
#define MISSILE_H

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "level.h"

#include "graphics/sprite_common.h"


#define MISSILE_MAX 3

typedef struct missile_t {
  uint16_t x;
  uint16_t y;
  uint16_t draw_x;
  uint16_t draw_y;
  int8_t vel_x;
  int8_t vel_y;
  bool active;
} missile_t;

extern uint8_t missile_count;
extern missile_t missiles[MISSILE_MAX];

void missile_new(uint16_t x, uint16_t y);
void missile_update(void);
uint8_t missile_draw(uint8_t base_sprite);

#endif
