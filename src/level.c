#include "level.h"
#include "global.h"
#include "graphics/birabuto.h"
#include <stddef.h>

uint16_t camera_x;
uint16_t camera_x_subpixel;
uint16_t next_col_chunk_load;
const unsigned char *current_map;
uint8_t map_buffer[LEVEL_HEIGHT][DEVICE_SCREEN_BUFFER_WIDTH];
uint8_t coldata[MAP_BUFFER_HEIGHT];
uint8_t set_column_at;
bool level_end_reached;
uint8_t current_level;

int current_map_tile_origin;
const unsigned char *current_map_tiles;
size_t current_map_size;
size_t current_map_width;
uint8_t level_bank;

uint8_t level_load_column(uint16_t start_at, uint8_t nb) NONBANKED {
  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(level_bank);

  uint8_t col = 0;
  while (col < nb) {
    uint8_t map_column = (col + start_at) & (DEVICE_SCREEN_BUFFER_WIDTH - 1);

    for (int row = 0; row < LEVEL_HEIGHT; row++) {
      int pos = (row * (current_map_width / TILE_SIZE)) + col + start_at;
      map_buffer[row][map_column] = current_map[pos];
      coldata[row] = current_map[pos];
    }

    // Draw current column
    set_bkg_tiles(map_column, 0, 1, LEVEL_HEIGHT, coldata);

    col++;
  };

  SWITCH_ROM(previous_bank);
  return col;
}

void level_set_current() NONBANKED {
  switch (current_level) {
  case 0:
    set_level_1_1();
    break;
  case 1:
    set_level_1_2();
    break;
  case 2:
    set_level_1_3();
    break;
  case 3:
    set_level_2_1();
    break;
  case 4:
    set_level_2_2();
    break;
  case 5:
    set_level_2_3();
    break;
  }
  load_current_level();
}

void load_current_level() NONBANKED {
  set_column_at = 0;
  camera_x = 0;
  camera_x_subpixel = 0;
  level_end_reached = false;

  level_load_column(0, MAP_BUFFER_WIDTH);

  next_col_chunk_load = COLUMN_CHUNK_SIZE;
}

void level_load_tileset_birabuto() NONBANKED {
  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(birabuto));

  current_map_tiles = birabuto_tiles;
  current_map_tile_origin = birabuto_TILE_ORIGIN;
  current_map_size = birabuto_TILE_COUNT;
  set_bkg_data(current_map_tile_origin, current_map_size, current_map_tiles);

  SWITCH_ROM(previous_bank);
}

void level_load_tileset_muda() NONBANKED {
  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(muda));

  current_map_tiles = muda_tiles;
  current_map_tile_origin = muda_TILE_ORIGIN;
  current_map_size = muda_TILE_COUNT;
  set_bkg_data(current_map_tile_origin, current_map_size, current_map_tiles);

  SWITCH_ROM(previous_bank);
}

void set_level_1_1() NONBANKED {
  level_load_tileset_birabuto();

  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(level_1_1));

  current_map = level_1_1_map;
  current_map_width = level_1_1_WIDTH;
  level_bank = BANK(level_1_1);

  SWITCH_ROM(previous_bank);
}

void set_level_1_2() NONBANKED {
  level_load_tileset_birabuto();

  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(level_1_2));

  current_map = level_1_2_map;
  current_map_width = level_1_2_WIDTH;
  level_bank = BANK(level_1_2);

  SWITCH_ROM(previous_bank);
}

void set_level_1_3() NONBANKED {
  level_load_tileset_birabuto();

  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(level_1_3));

  current_map = level_1_3_map;
  current_map_width = level_1_3_WIDTH;
  level_bank = BANK(level_1_3);

  SWITCH_ROM(previous_bank);
}

void set_level_2_1() NONBANKED {
  level_load_tileset_muda();

  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(level_2_1));

  current_map = level_2_1_map;
  current_map_width = level_2_1_WIDTH;
  level_bank = BANK(level_2_1);

  SWITCH_ROM(previous_bank);
}

void set_level_2_2() NONBANKED {
  level_load_tileset_muda();

  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(level_2_2));

  current_map = level_2_2_map;
  current_map_width = level_2_2_WIDTH;
  level_bank = BANK(level_2_2);

  SWITCH_ROM(previous_bank);
}

void set_level_2_3() NONBANKED {
  level_load_tileset_muda();

  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(level_2_3));

  current_map = level_2_3_map;
  current_map_width = level_2_3_WIDTH;
  level_bank = BANK(level_2_3);

  SWITCH_ROM(previous_bank);
}
