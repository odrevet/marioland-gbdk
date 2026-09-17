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
#include "enemiesSprites.h"
#include "enemiesBirabutoSprites.h"

BANKREF_EXTERN(enemy)

#define ENEMY_MAX 4
#define ENEMY_LOOP_PER_ANIMATION_FRAME 15
#define ENEMY_STOMPED_DISPLAY_FRAMES 30

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
  uint16_t x_origin;
  uint16_t y_origin;
  uint8_t draw_x;
  uint8_t draw_y;
  int8_t vel_x;
  int8_t vel_y;
  uint8_t type;
  uint8_t frame_counter;
  uint8_t anim_counter;
  uint8_t current_frame;
  uint8_t hp;
  uint8_t move_state;
  bool flip;
  bool stomped;
  uint8_t stomped_timer;
  bool active;
} enemy_t;

extern uint8_t enemy_count;
extern enemy_t enemies[ENEMY_MAX];

void enemy_new(uint16_t x, uint16_t y, uint8_t type) BANKED;
void enemy_remove(uint8_t index_enemy) NONBANKED;
void enemy_reset_all(void) BANKED;
void enemy_stomp(uint8_t index_enemy) BANKED;
void enemy_update(void) BANKED;
uint8_t enemy_draw(uint8_t base_sprite) NONBANKED;

void enemy_move_goomba(uint8_t index) BANKED;
void enemy_move_koopa(uint8_t index) BANKED;
void enemy_move_fly(uint8_t index) BANKED;
void enemy_move_bunbun(uint8_t index) BANKED;
void enemy_move_gao(uint8_t index) BANKED;
void enemy_move_honen(uint8_t index) BANKED;
void enemy_move_mekabon(uint8_t index) BANKED;
void enemy_move_yurarin(uint8_t index) BANKED;
void enemy_move_batadon(uint8_t index) BANKED;
void enemy_move_bullet(uint8_t index) BANKED;
void enemy_move_tokotoko(uint8_t index) BANKED;
void enemy_move_suu(uint8_t index) BANKED;
void enemy_move_kumo(uint8_t index) BANKED;
void enemy_move_hiyoihoi(uint8_t index) BANKED;
void enemy_move_pionpi(uint8_t index) BANKED;
void enemy_move_ponpon(uint8_t index) BANKED;
void enemy_move_plant(uint8_t index) BANKED;
void enemy_move_stub(uint8_t index) BANKED;

#endif