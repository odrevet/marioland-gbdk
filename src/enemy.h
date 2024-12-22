#ifndef ENEMY_H
#define ENEMY_H

#include <gb/gb.h>
#include <gb/metasprites.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"

#define ENEMY_MAX 4
#define ENEMY_LOOP_PER_ANIMATION_FRAME 15

enum enemy_type { ENEMY_TYPE_GOOMBA, ENEMY_TYPE_KOOPA };

typedef struct enemy_t {
  uint16_t x;
  uint16_t y;
  uint16_t draw_x;
  uint16_t draw_y;
  uint16_t vel_x;
  uint16_t vel_y;
  uint8_t type;
  uint8_t frame_counter;
  uint8_t current_frame;
  bool flip;
} enemy_t;

extern uint8_t enemy_count;
extern enemy_t enemies[ENEMY_MAX];

void enemy_new(uint16_t x, uint16_t y, uint8_t type);
void enemy_update();
void enemy_draw(int start);

#endif