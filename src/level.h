#ifndef LEVEL_H
#define LEVEL_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <gb/gb.h>
#include <gb/metasprites.h>
#include <gbdk/incbin.h>
#include <gbdk/platform.h>
#include <gbdk/rledecompress.h>

#include "global.h"

// tilesets
#include "../res/common.h"
INCBIN_EXTERN(common_tiles_bin)

#include "../res/birabuto.h"
INCBIN_EXTERN(birabuto_tiles_bin)


// maps
#include "../res/level_1_1.h"
INCBIN_EXTERN(map_1_1)

//#include "../res/level_1_2.h"
//INCBIN_EXTERN(map_1_2)

//#include "../res/level_1_3.h"
//INCBIN_EXTERN(map_1_3)

#define NB_LEVELS 3
#define LEVEL_HEIGHT 16
#define COLUMN_CHUNK_SIZE 1 // how many map columns to decompress at a time

// buffer worth of one column to hold map data when decrompressing
extern uint8_t coldata[LEVEL_HEIGHT];
// map buffer in RAM to check collision without access VRAM
#define MAP_BUFFER_WIDTH (DEVICE_SCREEN_WIDTH + COLUMN_CHUNK_SIZE)
#define MAP_BUFFER_HEIGHT (LEVEL_HEIGHT)
#define MAP_BUFFER_SIZE (MAP_BUFFER_WIDTH * MAP_BUFFER_HEIGHT)


extern uint8_t map_buffer[MAP_BUFFER_SIZE];

extern uint16_t camera_x;
extern uint16_t camera_x_subpixel;
extern uint16_t next_col_chunk_load;
extern uint8_t set_column_at;
extern bool level_end_reached;
extern uint8_t current_level;

extern const unsigned char* current_map;
extern int current_map_tile_origin;
extern const unsigned char*  current_map_tiles_bin;
extern size_t current_map_size;
extern size_t current_map_width;


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
  uint16_t index = ((y / TILE_SIZE - DEVICE_SPRITE_OFFSET_Y) * MAP_BUFFER_WIDTH) + 
                   (((x + camera_x) / TILE_SIZE) % MAP_BUFFER_WIDTH);
  return map_buffer[index];
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


inline uint8_t bkg_load_column(uint8_t start_at, uint8_t nb) {
  uint8_t col = 0;

  while (col < nb && rle_decompress(coldata, LEVEL_HEIGHT)) {
    // Copy column to map_buffer
    for (uint8_t row = 0; row < LEVEL_HEIGHT; row++) {
      uint16_t index = (row * MAP_BUFFER_WIDTH) + set_column_at;
      map_buffer[index] = coldata[row];
    }

    set_column_at = (set_column_at + 1) % MAP_BUFFER_WIDTH;

    // Get hardware map tile X column
    uint8_t map_x_column = (col + start_at) & (DEVICE_SCREEN_BUFFER_WIDTH - 1);

    // Draw current column
    set_bkg_tiles(map_x_column, 0, 1, LEVEL_HEIGHT, coldata);

    col++;
  }

  return col;
}


void next_level();
void load_current_level();
void set_level_1_1();
void set_level_1_2();
void set_level_1_3();

#endif