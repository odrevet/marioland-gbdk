#ifndef GAME_H
#define GAME_H

#include <gb/gb.h>
#include <gb/metasprites.h>
#include <gbdk/platform.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphics/enemies.h"
#include "graphics/text.h"
#include "graphics/mario.h"

#include "enemy.h"
#include "global.h"
#include "hUGEDriver.h"
#include "sound.h"
#include "text.h"
#include "player.h"
#include "level.h"

extern uint8_t coins;
extern uint16_t score;
extern uint8_t joy;
extern uint16_t time;
extern uint8_t lives;
extern uint8_t level_index;
extern uint8_t joypad_previous, joypad_current;
extern uint8_t nb_col;

void hud_update_coins();
void hud_update_score();
void hud_update_time();
void hud_update_lives();

inline bool is_coin(uint8_t tile) { return tile == TILE_COIN; }

inline void on_get_coin(uint8_t x, uint8_t y) {
  uint16_t index = ((y / TILE_SIZE - DEVICE_SPRITE_OFFSET_Y) * MAP_BUFFER_WIDTH) + 
                   (((x + camera_x) / TILE_SIZE) % MAP_BUFFER_WIDTH);
  //map_buffer[index] = TILE_EMPTY;

  set_bkg_tile_xy(((x + camera_x) / TILE_SIZE) % DEVICE_SCREEN_BUFFER_WIDTH,
                  y / TILE_SIZE - DEVICE_SPRITE_OFFSET_Y, TILE_EMPTY);

  sound_play_coin();

  coins++;
  score += 100;

  if (coins == 100) {
    lives++;
    coins = 0;
  }

  hud_update_coins();
  hud_update_score();
}

void init();
void pause(); 
void die();

#endif