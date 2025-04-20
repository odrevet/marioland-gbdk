#ifndef PLAYER_H
#define PLAYER_H

#include <gb/gb.h>
#include <gbdk/platform.h>

#include <string.h>

#include "global.h"
#include "game.h"
#include "level.h"
#include "text.h"

#include "graphics/enemies.h"
#include "graphics/text.h"
#include "graphics/mario.h"

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

void player_move() BANKED;

#endif 
