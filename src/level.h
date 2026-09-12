#ifndef LEVEL_H
#define LEVEL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include <gbdk/platform.h>

#include "coin_animated.h"
#include "global.h"
#include "hud.h"

#ifdef GAMEBOY
// sounds
#include "sfxplayer.h"
#include "sound_coin.h"
#include "sound_oneup.h"
#include "sound_destroyed.h"
#include "sound_bump.h"
#include "musicmanager.h"
#include "musics.h"
#endif

#include "tileset_index.h"

// tilesets
#include "birabutoTileset.h"
#include "chaiTileset.h"
#include "commonTileset.h"
#include "eastonTileset.h"
#include "mudaTileset.h"

// lookup tables
#include "level_object.h"
#include "lookup_table_1_1.h"
#include "lookup_table_1_2.h"
#include "lookup_table_1_3.h"
#include "lookup_table_2_1.h"
#include "lookup_table_2_2.h"
#include "lookup_table_2_3.h"
#include "lookup_table_3_1.h"
#include "lookup_table_3_2.h"
#include "lookup_table_3_3.h"
#include "lookup_table_4_1.h"
#include "lookup_table_4_2.h"
#include "lookup_table_4_3.h"
#include "lookup_table_underground.h"

#include "level_tables.h"

#define NB_LEVELS 12
#define LEVEL_HEIGHT 16
#define COLUMN_SIZE 1 // how many map columns to load at a time
#define PAGE_SIZE 20

// buffer worth of one column to hold map data when loading/scrolling
extern uint8_t coldata[LEVEL_HEIGHT];
// map buffer in RAM to check collision without access VRAM
#ifdef GAMEBOY
#define MAP_BUFFER_WIDTH (DEVICE_SCREEN_WIDTH + 7)
#elif defined(NINTENDO_NES)
#define MAP_BUFFER_WIDTH (DEVICE_SCREEN_WIDTH + 1)
#elif defined(SEGA)
#define MAP_BUFFER_WIDTH (DEVICE_SCREEN_WIDTH + 8)
#else
#define MAP_BUFFER_WIDTH (DEVICE_SCREEN_WIDTH)
#endif

#define MAP_BUFFER_HEIGHT LEVEL_HEIGHT

extern uint8_t map_buffer[MAP_BUFFER_HEIGHT * DEVICE_SCREEN_BUFFER_WIDTH];

extern uint16_t camera_x;
extern uint16_t camera_x_upscaled;
extern uint16_t load_col_at;
extern bool level_end_reached;
extern uint8_t current_level;

extern const unsigned char *current_map;
extern int current_map_tile_origin;
extern const unsigned char *current_map_tiles;
extern size_t current_map_tile_count;
extern size_t current_map_width;
extern size_t current_map_width_in_tiles;
extern uint8_t level_bank;
extern uint8_t map_column; // the index where to load next map column
extern uint8_t current_column_in_page;

extern uint8_t level_lookup_bank;
extern const level_object *level_lookup;
extern size_t level_lookup_size;

extern uint8_t current_page;

extern uint8_t cached_page_index;

extern uint16_t col_from;
extern uint16_t level_page_x_offset;

#ifdef USE_COMPRESSED_LEVELS
#define DECOMPRESSED_PAGE_SIZE 320
extern uint8_t decompression_buffer[DECOMPRESSED_PAGE_SIZE];
#endif 

typedef struct level_t {
  const banked_map_t *map_pages;
  uint8_t page_count;

  uint8_t lookup_bank;
  level_object *lookup;
  const size_t lookup_size;
#ifdef GAMEBOY
  uint8_t music_bank;
  hUGESong_t *music;
#endif
} level;

typedef struct {
  uint8_t bank;
  uint8_t tile_origin;
  unsigned char *tiles;
  size_t tile_count;
} world_tileset;

extern const level levels[NB_LEVELS];
extern const level undergrounds[1];

#define TILE_INDEX_X(x, camera_x)                                              \
  ((((x) + (camera_x)) >> 3) % DEVICE_SCREEN_BUFFER_WIDTH)
#define TILE_INDEX_Y(y) ((y) >> 3)


uint8_t get_tile(uint8_t x, uint8_t y);
bool is_tile_passthought(uint8_t tile_left_bottom, uint8_t tile_right_bottom);
bool is_tile_solid(uint8_t tile);

bool is_coin(uint8_t tile);

/**
 * when a background tile is a coin, replace it with a blank tile and call
 * on_get_coin
 */
void on_get_coin_background(uint8_t x, uint8_t y);

void on_break_tile(uint8_t x, uint8_t y);
void on_block_bump(uint8_t x, uint8_t y) BANKED;
void block_bump_update(void) BANKED;
uint8_t block_bump_draw(uint8_t base_sprite) BANKED;

/**
 * play sfx. increment coin counter.
 * check if 100 coins reached and give a bonus life if so.
 * update score.
 * update HUD
 */
void on_get_coin();
void on_interogation_block_hit(uint8_t x, uint8_t y);

void level_load_objects(uint16_t col) NONBANKED;
uint8_t level_load_column(uint8_t nb, level *level_to_load) NONBANKED;
                         
void level_set_current(void) NONBANKED;
void load_current_level(void) NONBANKED;

void set_level(uint8_t level_index) NONBANKED;

void move_camera(uint16_t x) NONBANKED;
#endif
