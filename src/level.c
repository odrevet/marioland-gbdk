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

void level_set_current(void) NONBANKED {
  switch (current_level) {
      case 0:
          set_level_1_1();
          hud_set_level('1', '1');
          break;
      case 1:
          set_level_1_2();
          hud_set_level('1', '2');
          break;
      case 2:
          set_level_1_3();
          hud_set_level('1', '3');
          break;
      case 3:
          set_level_2_1();
          hud_set_level('2', '1');
          break;
      case 4:
          set_level_2_2();
          hud_set_level('2', '2');
          break;
      case 5:
          set_level_2_3();
          hud_set_level('2', '3');
          break;
      case 6:
          set_level_3_1();
          hud_set_level('3', '1');
          break;
      case 7:
          set_level_3_2();
          hud_set_level('3', '2');
          break;
      case 8:
          set_level_3_3();
          hud_set_level('3', '3');
          break;
      case 9:
          set_level_4_1();
          hud_set_level('4', '1');
          break;
      case 10:
          set_level_4_2();
          hud_set_level('4', '2');
          break;
      case 11:
          set_level_4_3();
          hud_set_level('4', '3');
          break;
  }
  load_current_level();
}

void load_current_level(void) NONBANKED {
  set_column_at = 0;
  camera_x = 0;
  camera_x_subpixel = 0;
  level_end_reached = false;

  level_load_column(0, MAP_BUFFER_WIDTH);

  next_col_chunk_load = COLUMN_CHUNK_SIZE;
}

void level_load_tileset_birabuto(void) NONBANKED {
  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(birabuto));

  current_map_tiles = birabuto_tiles;
  current_map_tile_origin = birabuto_TILE_ORIGIN;
  current_map_size = birabuto_TILE_COUNT;
  set_bkg_data(current_map_tile_origin, current_map_size, current_map_tiles);

  SWITCH_ROM(previous_bank);
}

void level_load_tileset_muda(void) NONBANKED {
  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(muda));

  current_map_tiles = muda_tiles;
  current_map_tile_origin = muda_TILE_ORIGIN;
  current_map_size = muda_TILE_COUNT;
  set_bkg_data(current_map_tile_origin, current_map_size, current_map_tiles);

  SWITCH_ROM(previous_bank);
}

void level_load_tileset_chai(void) NONBANKED {
  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(chai));

  current_map_tiles = chai_tiles;
  current_map_tile_origin = chai_TILE_ORIGIN;
  current_map_size = chai_TILE_COUNT;
  set_bkg_data(current_map_tile_origin, current_map_size, current_map_tiles);

  SWITCH_ROM(previous_bank);
}

void level_load_tileset_easton(void) NONBANKED {
  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(easton));

  current_map_tiles = easton_tiles;
  current_map_tile_origin = easton_TILE_ORIGIN;
  current_map_size = easton_TILE_COUNT;
  set_bkg_data(current_map_tile_origin, current_map_size, current_map_tiles);

  SWITCH_ROM(previous_bank);
}

void set_level_1_1(void) NONBANKED {
  level_load_tileset_birabuto();

  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(level_1_1));

  current_map = level_1_1_map;
  current_map_width = level_1_1_WIDTH;
  level_bank = BANK(level_1_1);

  SWITCH_ROM(previous_bank);
}

void set_level_1_2(void) NONBANKED {
  level_load_tileset_birabuto();

  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(level_1_2));

  current_map = level_1_2_map;
  current_map_width = level_1_2_WIDTH;
  level_bank = BANK(level_1_2);

  SWITCH_ROM(previous_bank);
}

void set_level_1_3(void) NONBANKED {
  level_load_tileset_birabuto();

  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(level_1_3));

  current_map = level_1_3_map;
  current_map_width = level_1_3_WIDTH;
  level_bank = BANK(level_1_3);

  SWITCH_ROM(previous_bank);
}

void set_level_2_1(void) NONBANKED {
  level_load_tileset_muda();

  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(level_2_1));

  current_map = level_2_1_map;
  current_map_width = level_2_1_WIDTH;
  level_bank = BANK(level_2_1);

  SWITCH_ROM(previous_bank);
}

void set_level_2_2(void) NONBANKED {
  level_load_tileset_muda();

  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(level_2_2));

  current_map = level_2_2_map;
  current_map_width = level_2_2_WIDTH;
  level_bank = BANK(level_2_2);

  SWITCH_ROM(previous_bank);
}

void set_level_2_3(void) NONBANKED {
  level_load_tileset_muda();

  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(level_2_3));

  current_map = level_2_3_map;
  current_map_width = level_2_3_WIDTH;
  level_bank = BANK(level_2_3);

  SWITCH_ROM(previous_bank);
}

void set_level_3_1(void) NONBANKED {
  level_load_tileset_easton();
  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(level_3_1));
  current_map = level_3_1_map;
  current_map_width = level_3_1_WIDTH;
  level_bank = BANK(level_3_1);
  SWITCH_ROM(previous_bank);
}

void set_level_3_2(void) NONBANKED {
  level_load_tileset_easton();

  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(level_3_2));

  current_map = level_3_2_map;
  current_map_width = level_3_2_WIDTH;
  level_bank = BANK(level_3_2);

  SWITCH_ROM(previous_bank);
}

void set_level_3_3(void) NONBANKED {
  level_load_tileset_easton();

  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(level_3_3));

  current_map = level_3_3_map;
  current_map_width = level_3_3_WIDTH;
  level_bank = BANK(level_3_3);

  SWITCH_ROM(previous_bank);
}

void set_level_4_1(void) NONBANKED {
  level_load_tileset_chai();
  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(level_4_1));
  current_map = level_4_1_map;
  current_map_width = level_4_1_WIDTH;
  level_bank = BANK(level_4_1);
  SWITCH_ROM(previous_bank);
}

void set_level_4_2(void) NONBANKED {
  level_load_tileset_chai();
  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(level_4_2));
  current_map = level_4_2_map;
  current_map_width = level_4_2_WIDTH;
  level_bank = BANK(level_4_2);
  SWITCH_ROM(previous_bank);
}

void set_level_4_3(void) NONBANKED {
  level_load_tileset_chai();
  uint8_t previous_bank = _current_bank;
  SWITCH_ROM(BANK(level_4_3));
  current_map = level_4_3_map;
  current_map_width = level_4_3_WIDTH;
  level_bank = BANK(level_4_3);
  SWITCH_ROM(previous_bank);
}
