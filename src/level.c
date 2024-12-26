#include "level.h"
#include "global.h"
#include "graphics/birabuto.h"
#include <stddef.h>

uint16_t camera_x;
uint16_t camera_x_subpixel;
uint16_t next_col_chunk_load;
const unsigned char* current_map;
uint8_t map_buffer[MAP_BUFFER_SIZE];
uint8_t coldata[LEVEL_HEIGHT];
uint8_t set_column_at;
bool level_end_reached;
uint8_t current_level;

int current_map_tile_origin;
const unsigned char*  current_map_tiles;
size_t current_map_size;
size_t current_map_width;

uint8_t level_load_column(uint8_t start_at, uint8_t nb)
{
  uint8_t col = start_at;    
  while (col < nb) {
    for (int i = 0; i < LEVEL_HEIGHT; i++) {
        int pos = (i * (current_map_width / TILE_SIZE)) + col;
        map_buffer[i] = current_map[pos];
        coldata[i] = current_map[pos];
    }

    // Get hardware map tile X column
    uint8_t map_x_column = (col + start_at) & (DEVICE_SCREEN_BUFFER_WIDTH - 1);

    // Draw current column
    set_bkg_tiles(map_x_column, 0, 1, LEVEL_HEIGHT, coldata);

    col++;
  };

  return col;
}

void level_set_current()
{
  switch(current_level){
    case 0: 
      set_level_1_1_0();
      break;
    case 1: 
      set_level_1_2_0();
      break;
    case 2: 
      set_level_1_3_0();
      break;
  }
  load_current_level();
}

void load_current_level()
{
  set_column_at = 0;
  camera_x = 0;
  camera_x_subpixel = 0;
  level_end_reached = false;

  level_load_column(0, DEVICE_SCREEN_WIDTH + COLUMN_CHUNK_SIZE);
  next_col_chunk_load = COLUMN_CHUNK_SIZE;
}

void level_load_tileset_birabuto() NONBANKED
{
  uint8_t _current_bank = CURRENT_BANK;
  SWITCH_ROM(BANK(birabuto));

  current_map_tiles = birabuto_tiles;
  current_map_tile_origin = birabuto_TILE_ORIGIN;
  current_map_size = birabuto_TILE_COUNT;
  set_bkg_data(current_map_tile_origin, current_map_size, current_map_tiles);

  SWITCH_ROM(_current_bank);
}

void level_load_tileset_muda() NONBANKED
{
  uint8_t _current_bank = CURRENT_BANK;
  SWITCH_ROM(BANK(birabuto));

  current_map_tiles = muda_tiles;
  current_map_tile_origin = muda_TILE_ORIGIN;
  current_map_size = birabuto_TILE_COUNT;
  set_bkg_data(current_map_tile_origin, current_map_size, current_map_tiles);
  
  SWITCH_ROM(_current_bank);
}

void set_level_1_1_0() NONBANKED
{
  level_load_tileset_birabuto();

  uint8_t _current_bank = CURRENT_BANK;
  SWITCH_ROM(BANK(level_1_1_0));

  current_map = level_1_1_0_map;
  current_map_width = level_1_1_0_WIDTH;

  SWITCH_ROM(_current_bank);
}

void set_level_1_1_1() NONBANKED
{
  level_load_tileset_birabuto();

  uint8_t _current_bank = CURRENT_BANK;
  SWITCH_ROM(BANK(level_1_1_1));

  current_map = level_1_1_1_map;
  current_map_width = level_1_1_1_WIDTH;

  SWITCH_ROM(_current_bank);
}

void set_level_1_2_0() NONBANKED
{
  level_load_tileset_birabuto();

  uint8_t _current_bank = CURRENT_BANK;
  SWITCH_ROM(BANK(level_1_1_0));

  current_map = level_1_1_0_map;
  current_map_width = level_1_1_0_WIDTH;

  SWITCH_ROM(_current_bank);
}

void set_level_1_3_0() NONBANKED
{
  level_load_tileset_birabuto();

  uint8_t _current_bank = CURRENT_BANK;
  SWITCH_ROM(BANK(level_1_3_0));

  current_map = level_1_3_0_map;
  current_map_width = level_1_3_0_WIDTH;

  SWITCH_ROM(_current_bank);
}

