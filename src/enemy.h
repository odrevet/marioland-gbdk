#ifndef ENEMY_H
#define ENEMY_H

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "graphics/enemies.h"
#include "graphics/enemies_large.h"

BANKREF_EXTERN(enemy)

#define ENEMY_MAX 4
#define ENEMY_LOOP_PER_ANIMATION_FRAME 15
#define ENEMY_STOMPED_DISPLAY_FRAMES 30  // How long to show crushed sprite

enum enemy_type {
  ENEMY_GOOMBO,
  ENEMY_KOOPA,
  ENEMY_FLY,
  ENEMY_PLANT,
  ENEMY_BUNBUN,
  ENEMY_GAO,
  ENEMY_HONEN,
  ENEMY_MEKABON,
  ENEMY_YURARIN,
  ENEMY_BATADON,
  ENEMY_BULLET,
  ENEMY_TOKOTOKO,
  ENEMY_SUU,
  ENEMY_KUMO,
  ENEMY_HIYOIHOI,
  ENEMY_PIONPI,
  ENEMY_PONPON,
  ENEMY_NYOLOLIN
};

typedef struct {
  uint16_t x;
  uint16_t y;
  uint8_t draw_x;
  uint8_t draw_y;
  int8_t vel_x;
  int8_t vel_y;
  uint8_t type;
  uint8_t frame_counter;
  uint8_t current_frame;
  uint8_t hp; // how many super ball / missile hits the enemy can takes
  bool flip;
  bool stomped;  // Is enemy stomped/crushed
  uint8_t stomped_timer;  // Countdown timer for stomped display
  bool active;
} enemy_t;

extern uint8_t enemy_count;
extern enemy_t enemies[ENEMY_MAX];

void enemy_new(uint16_t x, uint16_t y, uint8_t type) NONBANKED;
void enemy_remove(uint8_t index_enemy) NONBANKED;
void enemy_stomp(uint8_t index_enemy) NONBANKED;
void enemy_update(void) NONBANKED;
uint8_t enemy_draw(uint8_t base_sprite) NONBANKED;

void enemy_move_goomba(uint8_t index) BANKED;
void enemy_move_koopa(uint8_t index) BANKED;
void enemy_move_fly(uint8_t index) BANKED;

#endif