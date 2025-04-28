#ifndef LEVEL_H
#define LEVEL_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <gb/gb.h>
#include <gbdk/metasprites.h>
#include <gbdk/platform.h>

#include "global.h"
#include "hud.h"
#include "lookup_tables.h"

// sounds
#include "sfxplayer.h"
#include "sounds/sound_coin.h"
#include "sounds/sound_oneup.h"

// musics
#include "musicmanager.h"
#include "musics/music_overworld.h"
#include "musics/music_castle.h"

// tilesets
#include "graphics/birabuto.h"
#include "graphics/chai.h"
#include "graphics/common.h"
#include "graphics/easton.h"
#include "graphics/muda.h"

// maps
#include "levels/level_1_1.h"
#include "levels/level_1_2.h"
#include "levels/level_1_3.h"
#include "levels/level_2_1.h"
#include "levels/level_2_2.h"
#include "levels/level_2_3.h"
#include "levels/level_3_1.h"
#include "levels/level_3_2.h"
#include "levels/level_3_3.h"
#include "levels/level_4_1.h"
#include "levels/level_4_2.h"
#include "levels/level_4_3.h"

#include <gbdk/emu_debug.h>

#define NB_LEVELS 12
#define LEVEL_HEIGHT 16
#define COLUMN_CHUNK_SIZE 1 // how many map columns to load at a time

// buffer worth of one column to hold map data when loading/scrolling
extern uint8_t coldata[LEVEL_HEIGHT];
// map buffer in RAM to check collision without access VRAM
#define MAP_BUFFER_WIDTH (DEVICE_SCREEN_WIDTH + 7)
#define MAP_BUFFER_HEIGHT LEVEL_HEIGHT

extern uint8_t map_buffer[MAP_BUFFER_HEIGHT][DEVICE_SCREEN_BUFFER_WIDTH];

extern uint16_t camera_x;
extern uint16_t camera_x_subpixel;
extern uint16_t next_col_chunk_load;
extern uint8_t set_column_at;
extern bool level_end_reached;
extern uint8_t current_level;

extern const unsigned char *current_map;
extern int current_map_tile_origin;
extern const unsigned char *current_map_tiles;
extern size_t current_map_size;
extern size_t current_map_width;
extern uint8_t level_bank;
extern uint8_t map_column; // the index where to load next map column

extern level_object* level_lookup;
extern size_t level_lookup_size;

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
  METAL_BLOCK_LEFT = 0x56,
  METAL_BLOCK_RIGHT = 0x57
};

// Birabuto world tiles
enum tileset_index_birabuto {
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
bool is_tile_solid(uint8_t tile);

bool is_coin(uint8_t tile);

void on_get_coin(uint8_t x, uint8_t y);

void level_load_objects(uint16_t col)NONBANKED;
uint8_t level_load_column(uint16_t start_at, uint8_t nb) NONBANKED;

void level_set_current(void) NONBANKED;
void load_current_level(void) NONBANKED;

void level_load_tileset_birabuto(void) NONBANKED;
void level_load_tileset_muda(void) NONBANKED;
void level_load_tileset_easton(void) NONBANKED;
void level_load_tileset_chai(void) NONBANKED;

void set_level_1_1(void) NONBANKED;
void set_level_1_2(void) NONBANKED;
void set_level_1_3(void) NONBANKED;
void set_level_2_1(void) NONBANKED;
void set_level_2_2(void) NONBANKED;
void set_level_2_3(void) NONBANKED;
void set_level_3_1(void) NONBANKED;
void set_level_3_2(void) NONBANKED;
void set_level_3_3(void) NONBANKED;
void set_level_4_1(void) NONBANKED;
void set_level_4_2(void) NONBANKED;
void set_level_4_3(void) NONBANKED;

#endif