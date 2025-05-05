#ifndef COIN_ANIMATED_H
#define COIN_ANIMATED_H

#include <gb/gb.h>
#include <gbdk/metasprites.h>

#include <stdint.h>
#include "global.h"

#include "graphics/sprite_common.h"

typedef struct coin_animated {
  uint8_t draw_x;
  uint8_t draw_y;
  uint8_t ttl;
  uint8_t hw_sprite_index;
} coin_animated_t;

#define NB_COIN_ANIMATED 3
extern coin_animated_t coin_animated_array[NB_COIN_ANIMATED];
extern uint8_t coin_index;

void coin_animated_update(void);
uint8_t coin_animated_draw(uint8_t base_sprite);


#endif