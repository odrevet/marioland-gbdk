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
#include "sound.h"

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

#define MAX_TILE 255

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
  SWITCH = 0x3D
};

static const bool solid_tiles_common[MAX_TILE] = {
    [TILE_INTEROGATION_BLOCK] = true, [BREAKABLE_BLOCK] = true,
    [TILE_UNBREAKABLE] = true,        [PIPE_TOP_LEFT] = true,
    [PIPE_TOP_RIGHT] = true,          [PIPE_CENTER_LEFT] = true,
    [PIPE_CENTER_RIGHT] = true,       [TILE_EMPTIED] = true};

enum tileset_index_birabuto {
  TILE_FLOOR = 0x75,
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

static const bool solid_tiles_birabuto[MAX_TILE] = {
    [TILE_FLOOR] = true,     [STONE_LEFT] = true,     [STONE_RIGHT] = true,
    [TILED_FLOOR] = true,    [STONE_BIS_LEFT] = true, [STONE_BIS_RIGHT] = true,
    [BRICK_BLOCK] = true,    [PALM_TREE_LEFT] = true, [PALM_TREE_CENTER] = true,
    [PALM_TREE_RIGHT] = true};

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

static const bool solid_tiles_muda[MAX_TILE] = {
    [MUDA_PLATEFORM_LEFT] = true,     [MUDA_PLATEFORM_CENTER] = true,
    [MUDA_PLATEFORM_RIGHT] = true,    [BIG_BLOCK_TOP_LEFT] = true,
    [BIG_BLOCK_TOP_RIGHT] = true,     [BIG_BLOCK_BOTTOM_LEFT] = true,
    [BIG_BLOCK_BOTTOM_RIGHT] = true,  [OCEAN_FLOOR_LEFT] = true,
    [OCEAN_FLOOR_RIGHT] = true,       [MUDA_BRIDGE] = true,
    [HALF_BIG_BLOCK_TOP_LEFT] = true, [HALF_BIG_BLOCK_TOP_RIGHT] = true};

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

static const bool solid_tiles_easton[MAX_TILE] = {
    [EASTON_FLOOR_1] = true,
    [EASTON_FLOOR_2] = true,
    [EASTON_STONE_PLATEFORM_1] = true,
    [EASTON_STONE_PLATEFORM_2] = true,
    [EASTON_STONE_PLATEFORM_3] = true,
    [EASTON_STONE_PLATEFORM_4] = true,
    [EASTON_STONE_PLATEFORM_BOTTOM] = true,
    [EASTON_LARGE_BLACK_BLOCK_TOP_LEFT] = true,
    [EASTON_LARGE_BLACK_BLOCK_TOP_RIGHT] = true,
    [EASTON_LARGE_BLACK_BLOCK_BOTOM_LEFT] = true,
    [EASTON_LARGE_BLACK_BLOCK_BOTTOM_RIGHT] = true, 
    [EASTON_BLOCK] = true,
    [EASTON_STONE_PLATEFORM_LEFT] = true,
    [EASTON_STONE_PLATEFORM_RIGHT] = true, 
};
/*
enum tileset_index_chai {
  CHAI_FLOOR_LEFT = 0x88,
  CHAI_FLOOR_MIDDLE_1 = 0x89,
  CHAI_FLOOR_MIDDLE_2 = 0x8A,
  CHAI_FLOOR_MIDDLE_RIGHT = 0x8B,
  CHAI_GREY_BLOCK = 0x93,
  CHAI_PIPE = 0xAF,
  CHAI_BLOCK = 0x63
};

static const bool solid_tiles_chai[MAX_TILE] = {
    [CHAI_FLOOR_LEFT] = true,
    [CHAI_FLOOR_MIDDLE_1] = true,
    [CHAI_FLOOR_MIDDLE_2] = true,
    [CHAI_FLOOR_MIDDLE_RIGHT] = true,
    [CHAI_GREY_BLOCK] = true,
    [CHAI_PIPE] = true,
    [CHAI_BLOCK] = true
};
*/
inline uint8_t get_tile(uint8_t x, uint8_t y) {
  if (y <= 16) {
    return TILE_EMPTY;
  }

  uint8_t tile_x = ((x + camera_x) / TILE_SIZE) % DEVICE_SCREEN_BUFFER_WIDTH;
  uint8_t tile_y = (y / TILE_SIZE) - DEVICE_SPRITE_OFFSET_Y;
  return map_buffer[tile_y][tile_x];
}

static inline bool is_tile_solid(uint8_t tile) {
  return solid_tiles_common[tile] ||
         (((current_level >= 0 && current_level <= 2) &&
           solid_tiles_birabuto[tile]) ||
          ((current_level >= 3 && current_level <= 5) &&
           solid_tiles_muda[tile]) ||
          ((current_level >= 6 && current_level <= 8) &&
          solid_tiles_easton[tile])/* ||
          ((current_level >= 9 && current_level <= 12) &&
          solid_tiles_chai[tile])*/);
}

bool is_coin(uint8_t tile);

void on_get_coin(uint8_t x, uint8_t y);
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