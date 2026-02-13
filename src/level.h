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
#include "sounds/sound_coin.h"
#include "sounds/sound_oneup.h"

// musics
#include "musicmanager.h"
#include "musics/musics.h"
#endif 

// tilesets
#include "graphics/birabuto.h"
#include "graphics/chai.h"
#include "graphics/common.h"
#include "graphics/easton.h"
#include "graphics/muda.h"

// lookup tables
#include "level_object.h"
#include "lookup_tables/lookup_table_1_1.h"
#include "lookup_tables/lookup_table_1_2.h"
#include "lookup_tables/lookup_table_1_3.h"
#include "lookup_tables/lookup_table_2_1.h"
#include "lookup_tables/lookup_table_2_2.h"
#include "lookup_tables/lookup_table_2_3.h"
#include "lookup_tables/lookup_table_3_1.h"
#include "lookup_tables/lookup_table_3_2.h"
#include "lookup_tables/lookup_table_3_3.h"
#include "lookup_tables/lookup_table_4_1.h"
#include "lookup_tables/lookup_table_4_2.h"
#include "lookup_tables/lookup_table_4_3.h"
#include "lookup_tables/lookup_table_underground.h"

#include "level_tables.h"

#define NB_LEVELS 12
#define LEVEL_HEIGHT 16
#define COLUMN_CHUNK_SIZE 1 // how many map columns to load at a time
#define PAGE_SIZE 20

// buffer worth of one column to hold map data when loading/scrolling
extern uint8_t coldata[LEVEL_HEIGHT];
// map buffer in RAM to check collision without access VRAM
#if defined(GAMEBOY)
#define MAP_BUFFER_WIDTH (DEVICE_SCREEN_WIDTH + 7)
#elif defined(NINTENDO_NES)
#define MAP_BUFFER_WIDTH (DEVICE_SCREEN_WIDTH + 1)
#else
#define MAP_BUFFER_WIDTH (DEVICE_SCREEN_WIDTH)
#endif

#define MAP_BUFFER_HEIGHT LEVEL_HEIGHT

extern uint8_t map_buffer[MAP_BUFFER_HEIGHT * DEVICE_SCREEN_BUFFER_WIDTH];

extern uint16_t camera_x;
extern uint16_t camera_x_upscaled;
extern uint16_t next_col_chunk_load;
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

extern uint8_t level_lookup_bank;
extern const level_object *level_lookup;
extern size_t level_lookup_size;

extern uint8_t current_page;

extern uint8_t cached_page_index;

#ifdef USE_COMPRESSED_LEVELS
#define DECOMPRESSED_PAGE_SIZE 320
extern uint8_t decompression_buffer[DECOMPRESSED_PAGE_SIZE];
#endif 

typedef struct level_t {
  char major;
  char minor;

  const banked_map_t *map_pages;
  uint8_t page_count;

  size_t map_width;
  size_t map_width_in_tiles;

  uint8_t map_tiles_bank;
  unsigned char *map_tiles;
  uint8_t map_tile_origin;
  size_t map_tiles_count;

  uint8_t lookup_bank;
  level_object *lookup;
  const size_t lookup_size;
#ifdef GAMEBOY
  uint8_t music_bank;
  hUGESong_t *music;
#endif
} level;

extern const level levels[NB_LEVELS];
extern const level undergrounds[1];

#define TILE_INDEX_X(x, camera_x)                                              \
  ((((x) + (camera_x)) >> 3) % DEVICE_SCREEN_BUFFER_WIDTH)
#define TILE_INDEX_Y(y) ((y) >> 3)

// Common tiles (shared across all worlds)
enum tileset_index_common {
  TILE_EMPTY = 0x27,
  TILE_INTEROGATION_BLOCK = 0x28,
  TILE_EMPTIED = 0x29,
  BREAKABLE_BLOCK = 0x2A,
  TILE_UNBREAKABLE = 0x2B,
  TILE_COIN = 0x37,
  PIPE_TOP_LEFT = 0x30,
  PIPE_TOP_RIGHT = 0x31,
  PIPE_CENTER_LEFT = 0x3E,
  PIPE_CENTER_RIGHT = 0x3F,
  SWITCH = 0x3D,
  METAL_GATE = 0x3C,
  PIPE_HORIZONTAL_1 = 0x4A,
  PIPE_HORIZONTAL_2 = 0x4B,
  PIPE_HORIZONTAL_3 = 0x4C,
  PIPE_HORIZONTAL_4 = 0x4D,
  PIPE_HORIZONTAL_5 = 0x58,
  PIPE_HORIZONTAL_6 = 0x59,
  PIPE_HORIZONTAL_7 = 0x5A,
  PIPE_HORIZONTAL_8 = 0x5B,
  METAL_BLOCK_LEFT = 0x56,
  METAL_BLOCK_RIGHT = 0x57
};

// Birabuto world tiles
enum tileset_index_birabuto {
  GREY_BLOCK = 0x61,
  TILE_TORCH = 0x72,
  TILE_FLOOR = 0x75,
  TILE_FLOOR_BIS = 0x7F,
  OBLIC_LINE_LEFT = 0x68,
  OBLIC_LINE_RIGHT = 0x69,
  STONE_LEFT = 0x5C,
  STONE_RIGHT = 0x5D,
  TILED_FLOOR = 0x91,
  STONE_BIS_LEFT = 0x99,
  STONE_BIS_RIGHT = 0x9A,
  BRICK_BLOCK = 0x9B,
  PALM_TREE_LEFT = 0x79,
  PALM_TREE_CENTER = 0x7A,
  PALM_TREE_RIGHT = 0x7B
};

// Muda world tiles
enum tileset_index_muda {
  MUDA_PLATEFORM_LEFT = 0x83,
  MUDA_PLATEFORM_CENTER = 0x84,
  MUDA_PLATEFORM_RIGHT = 0x85,
  BIG_BLOCK_TOP_LEFT = 0x86,
  BIG_BLOCK_TOP_RIGHT = 0X87,
  BIG_BLOCK_BOTTOM_LEFT = 0X90,
  BIG_BLOCK_BOTTOM_RIGHT = 0X91,
  OCEAN_FLOOR_LEFT = 0x88,
  OCEAN_FLOOR_RIGHT = 0x89,
  MUDA_BRIDGE = 0x99,
  HALF_BIG_BLOCK_TOP_LEFT = 0x9A,
  HALF_BIG_BLOCK_TOP_RIGHT = 0X9B
};

// Easton world tiles
enum tileset_index_easton {
  EASTON_FLOOR_1 = 0x9D,
  EASTON_FLOOR_2 = 0x9C,
  EASTON_STONE_PLATEFORM_1 = 0x87,
  EASTON_STONE_PLATEFORM_2 = 0x91,
  EASTON_STONE_PLATEFORM_3 = 0x9E,
  EASTON_STONE_PLATEFORM_4 = 0x9F,
  EASTON_STONE_PLATEFORM_BOTTOM = 0x9B,
  EASTON_LARGE_BLACK_BLOCK_TOP_LEFT = 0X72,
  EASTON_LARGE_BLACK_BLOCK_TOP_RIGHT = 0X73,
  EASTON_LARGE_BLACK_BLOCK_BOTOM_LEFT = 0X7C,
  EASTON_LARGE_BLACK_BLOCK_BOTTOM_RIGHT = 0X7D,
  EASTON_BLOCK = 0xA0,
  EASTON_STONE_PLATEFORM_LEFT = 0xA1,
  EASTON_STONE_PLATEFORM_RIGHT = 0xA2,
};

enum tileset_index_chai {
  CHAI_FLOOR_LEFT = 0x88,
  CHAI_FLOOR_MIDDLE_1 = 0x89,
  CHAI_FLOOR_MIDDLE_2 = 0x8A,
  CHAI_FLOOR_MIDDLE_RIGHT = 0x8B,
  CHAI_GREY_BLOCK = 0x93,
  CHAI_PIPE = 0xAF,
  CHAI_PIPE_LEFT = 0xB6,
  CHAI_PIPE_RIGHT = 0xB7,
  CHAI_PIPE_BOTTOM_LEFT = 0xB8,
  CHAI_PIPE_BOTTOM_RIGHT = 0xB9,
  CHAI_BLOCK = 0x63,
  CHAI_BRICK_BLOCK = 0x83,
  CHAI_BLACK_BLOCK_LEFT = 0x96,
  CHAI_BLACK_BLOCK_RIGHT = 0x97,
  CHAI_FIRE_BLOCK = 0x9C
};

uint8_t get_tile(uint8_t x, uint8_t y);
bool is_tile_passthought(uint8_t tile_left_bottom, uint8_t tile_right_bottom);
bool is_tile_solid(uint8_t tile);

bool is_coin(uint8_t tile);

/**
 * when a background tile is a coin, replace it with a blank tile and call
 * on_get_coin
 */
void on_get_coin_background(uint8_t x, uint8_t y);

/**
 * play sfx. increment coin counter.
 * check if 100 coins reached and give a bonus life if so.
 * update score.
 * update HUD
 */
void on_get_coin();
void on_interogation_block_hit(uint8_t x, uint8_t y);

void level_load_objects(uint16_t col) NONBANKED;
uint8_t level_load_column(uint16_t start_at, uint8_t nb, level *level_to_load) NONBANKED;
                         
void level_set_current(void) NONBANKED;
void load_current_level(void) NONBANKED;

void set_level(uint8_t level_index) NONBANKED;

#endif
