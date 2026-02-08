#ifndef PLAYER_H
#define PLAYER_H

#include <gbdk/platform.h>
#include <gbdk/platform.h>

#include <stdint.h>

#include "global.h"
#include "level.h"
#include "platforms.h"
#include "text.h"
#include "level.h"

#ifdef GAMEBOY
#include "musicmanager.h"
#include "sfxplayer.h"
#include "sounds/sound_bump.h"
#include "sounds/sound_jump_small.h"
#include "sounds/sound_pause.h"
#include "sounds/sound_pipe.h"
#include "musics/musics.h"
#endif 

#include "graphics/mario.h"
#include "graphics/text.h"

#include "level_object.h"

//#include "lookup_tables/lookup_table_underground.h"

BANKREF_EXTERN(player)

#define MARIO_HEIGHT_SMALL 8
#define MARIO_HEIGHT_BIG 16

#define MARIO_WIDTH 8
#define PLAYER_HORIZONTAL_MARGIN 2
#define PLAYER_TOP_MARGIN TILE_SIZE

extern uint8_t coins;
extern uint16_t score;
extern uint8_t joy;
extern uint16_t time;
extern uint8_t lives;
extern uint8_t level_index;
extern uint8_t joypad_previous, joypad_current;

extern uint16_t scroll_limit;

// player coords and movements
extern uint16_t player_x_upscaled;
extern uint16_t player_y_upscaled;
extern uint16_t player_x_next_upscaled;
extern uint16_t player_y_next_upscaled;
extern uint16_t player_x;
extern uint16_t player_y;
extern uint16_t player_x_next;
extern uint16_t player_y_next;
extern uint8_t player_draw_x;
extern uint8_t player_draw_y;
extern int8_t vel_x;
extern int8_t vel_y;
extern bool is_jumping;

extern bool display_jump_frame;
extern bool display_slide_frame;
extern bool display_walk_animation;

extern bool touch_ground;
extern uint16_t current_jump;

extern uint8_t player_frame;
extern uint8_t frame_counter;
extern bool mario_flip;
extern uint16_t scroll_limit;

extern uint8_t current_gravity;

extern uint8_t tile_next_1;
extern uint8_t tile_next_2;

extern uint8_t scroll;
extern bool plane_mode;

void update_frame_counter(void) NONBANKED;
uint8_t player_draw(uint8_t base_sprite) NONBANKED;
void player_move(void) BANKED;
void player_on_touch_ground(void) NONBANKED;
bool player_is_on_platform(void) NONBANKED;
bool player_check_pipe_entry(void) NONBANKED;
void player_enter_pipe(const unsigned char* destination, uint8_t destination_bank) NONBANKED;

#endif
