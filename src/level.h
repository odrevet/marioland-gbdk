#ifndef LEVEL_H
#define LEVEL_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <gb/gb.h>
#include <gb/metasprites.h>
#include <gbdk/platform.h>

#include "global.h"
#include "hud.h"

// tilesets
#include "graphics/common.h"
#include "graphics/birabuto.h"
#include "graphics/muda.h"
#include "graphics/chai.h"
#include "graphics/easton.h"

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

extern const unsigned char* current_map;
extern int current_map_tile_origin;
extern const unsigned char*  current_map_tiles;
extern size_t current_map_size;
extern size_t current_map_width;
extern uint8_t level_bank;


enum tileset_index {
  TILE_EMPTY = 0x27,
  TILE_INTEROGATION_BLOCK = 0x28,
  TILE_EMPTIED = 0x29,
  BREAKABLE_BLOCK = 0x2A,
  TILE_UNBREAKABLE = 0x2B,
  TILE_COIN = 0x33,
  PIPE_TOP_LEFT = 0x30,
  PIPE_TOP_RIGHT = 0x31,
  PIPE_CENTER_LEFT = 0x3A,
  PIPE_CENTER_RIGHT = 0x3B,
  TILE_FLOOR = 0x65,
  TILE_METALIC_LEFT = 0x4A,
  TILE_METALIC_RIGHT = 0x4B,
  PALM_PLATEFORM_LEFT = 0x69,
  PALM_PLATEFORM_CENTER = 0X6A,
  PALM_PLATEFORM_RIGHT = 0x6B,
  STONE_TILE_LEFT = 0x7F,
  STONE_TILE_MIDDLE_LEFT = 0x89,
  STONE_TILE_MIDDLE_RIGHT = 0x8A,
  STONE_TILE_RIGHT = 0x80,
  STONE_BAR = 0x81,
  STONE_TILE_FLOOR = 0x8B,
};

inline uint8_t get_tile(uint8_t x, uint8_t y) {
  if(y <= 16){
    return TILE_EMPTY;
  }

  uint8_t tile_x = ((x + camera_x) / TILE_SIZE) % DEVICE_SCREEN_BUFFER_WIDTH;
  uint8_t tile_y = (y / TILE_SIZE) - DEVICE_SPRITE_OFFSET_Y;
  return map_buffer[tile_y][tile_x];
}

#define MAX_TILE 255

static inline bool is_tile_solid(uint8_t tile) {
    static const bool solid_tiles[MAX_TILE + 1] = {
        [TILE_FLOOR] = true,
        [TILE_INTEROGATION_BLOCK] = true,
        [BREAKABLE_BLOCK] = true,
        [TILE_UNBREAKABLE] = true,
        [PIPE_TOP_LEFT] = true,
        [PIPE_TOP_RIGHT] = true,
        [PIPE_CENTER_LEFT] = true,
        [PIPE_CENTER_RIGHT] = true,
        [TILE_METALIC_LEFT] = true,
        [TILE_METALIC_RIGHT] = true,
        [TILE_EMPTIED] = true,
        [PALM_PLATEFORM_LEFT] = true,
        [PALM_PLATEFORM_CENTER] = true,
        [PALM_PLATEFORM_RIGHT] = true,
        [STONE_TILE_LEFT] = true,
        [STONE_TILE_RIGHT] = true,
        [STONE_BAR] = true,
        [STONE_TILE_FLOOR] = true
    };
    return tile <= MAX_TILE && solid_tiles[tile];
}

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