#ifndef PLAYER_H
#define PLAYER_H

#include <gb/gb.h>
#include <gbdk/platform.h>

#include <string.h>

#include "global.h"
#include "level.h"
#include "text.h"

#include "graphics/enemies.h"
#include "graphics/text.h"
#include "graphics/mario.h"

extern uint8_t coins;
extern uint16_t score;
extern uint8_t joy;
extern uint16_t time;
extern uint8_t lives;
extern uint8_t level_index;
extern uint8_t joypad_previous, joypad_current;
extern uint8_t nb_col;

// player coords and movements
extern uint16_t player_x_subpixel;
extern uint16_t player_y_subpixel;
extern uint16_t player_x_subpixel_next;
extern uint16_t player_y_subpixel_next;
extern uint8_t player_draw_x;
extern uint8_t player_draw_y;
extern uint8_t player_draw_x_next;
extern uint8_t player_draw_y_next;
extern int8_t vel_x;
extern int8_t vel_y;
extern bool is_jumping;
extern bool display_jump_frame;
extern bool display_slide_frame;
extern bool touch_ground;
extern uint8_t current_jump;
extern int8_t player_max_speed;
extern uint8_t player_frame;
extern uint8_t frame_counter;
extern bool mario_flip;
extern uint8_t current_gravity;


extern uint8_t next_pos;
extern uint8_t tile_next_1;
extern uint8_t tile_next_2;

extern uint8_t scroll;

void update_frame_counter();

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

void player_move() BANKED;

#endif 
