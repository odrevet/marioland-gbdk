#include "level.h"

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

uint8_t get_tile(uint8_t x, uint8_t y) {
  if (y <= 16) {
    return TILE_EMPTY;
  }

  uint8_t tile_x = ((x + camera_x) / TILE_SIZE) % DEVICE_SCREEN_BUFFER_WIDTH;
  uint8_t tile_y = (y / TILE_SIZE) - DEVICE_SPRITE_OFFSET_Y;
  return map_buffer[tile_y][tile_x];
}

bool is_tile_solid(uint8_t tile) {
  // check common solid tiles
  switch (tile) {
  case TILE_INTEROGATION_BLOCK:
  case BREAKABLE_BLOCK:
  case TILE_UNBREAKABLE:
  case PIPE_TOP_LEFT:
  case PIPE_TOP_RIGHT:
  case PIPE_CENTER_LEFT:
  case PIPE_CENTER_RIGHT:
  case TILE_EMPTIED:
  case METAL_GATE:
  case METAL_BLOCK_LEFT:
  case METAL_BLOCK_RIGHT:
    return true;
  }

  // check world specific tiles
  if (current_level >= 0 && current_level <= 2) {
    // Birabuto world
    return ((tile == TILE_FLOOR) || (tile == TILE_FLOOR_BIS) ||
            (tile == STONE_LEFT) || (tile == STONE_RIGHT) ||
            (tile == TILED_FLOOR) || (tile == STONE_BIS_LEFT) ||
            (tile == STONE_BIS_RIGHT) || (tile == BRICK_BLOCK) ||
            (tile == PALM_TREE_LEFT) || (tile == PALM_TREE_CENTER) ||
            (tile == PALM_TREE_RIGHT));
  } else if (current_level >= 3 && current_level <= 5) {
    // Muda world
    return ((tile == MUDA_PLATEFORM_LEFT) || (tile == MUDA_PLATEFORM_CENTER) ||
            (tile == MUDA_PLATEFORM_RIGHT) || (tile == BIG_BLOCK_TOP_LEFT) ||
            (tile == BIG_BLOCK_TOP_RIGHT) || (tile == BIG_BLOCK_BOTTOM_LEFT) ||
            (tile == BIG_BLOCK_BOTTOM_RIGHT) || (tile == OCEAN_FLOOR_LEFT) ||
            (tile == OCEAN_FLOOR_RIGHT) || (tile == MUDA_BRIDGE) ||
            (tile == HALF_BIG_BLOCK_TOP_LEFT) ||
            (tile == HALF_BIG_BLOCK_TOP_RIGHT));
  } else if (current_level >= 6 && current_level <= 8) {
    // Easton world
    return ((tile == EASTON_FLOOR_1) || (tile == EASTON_FLOOR_2) ||
            (tile == EASTON_STONE_PLATEFORM_1) ||
            (tile == EASTON_STONE_PLATEFORM_2) ||
            (tile == EASTON_STONE_PLATEFORM_3) ||
            (tile == EASTON_STONE_PLATEFORM_4) ||
            (tile == EASTON_STONE_PLATEFORM_BOTTOM) ||
            (tile == EASTON_LARGE_BLACK_BLOCK_TOP_LEFT) ||
            (tile == EASTON_LARGE_BLACK_BLOCK_TOP_RIGHT) ||
            (tile == EASTON_LARGE_BLACK_BLOCK_BOTOM_LEFT) ||
            (tile == EASTON_LARGE_BLACK_BLOCK_BOTTOM_RIGHT) ||
            (tile == EASTON_BLOCK) || (tile == EASTON_STONE_PLATEFORM_LEFT) ||
            (tile == EASTON_STONE_PLATEFORM_RIGHT));
  } else if (current_level >= 9 && current_level <= 12) {
    // Chai world
    return ((tile == CHAI_FLOOR_LEFT) || (tile == CHAI_FLOOR_MIDDLE_1) ||
            (tile == CHAI_FLOOR_MIDDLE_2) ||
            (tile == CHAI_FLOOR_MIDDLE_RIGHT) || (tile == CHAI_GREY_BLOCK) ||
            (tile == CHAI_PIPE) || (tile == CHAI_PIPE_LEFT) ||
            (tile == CHAI_PIPE_RIGHT) || (tile == CHAI_PIPE_BOTTOM_LEFT) ||
            (tile == CHAI_PIPE_BOTTOM_RIGHT) || (tile == CHAI_BLOCK) ||
            (tile == CHAI_BRICK_BLOCK) || (tile == CHAI_BLACK_BLOCK_LEFT) ||
            (tile == CHAI_BLACK_BLOCK_RIGHT) || (tile == CHAI_FIRE_BLOCK));
  }

  return false;
}

bool is_coin(uint8_t tile) { return tile == TILE_COIN; }

void on_get_coin(uint8_t x, uint8_t y) {
  uint8_t index_x = ((x + camera_x) / TILE_SIZE) % DEVICE_SCREEN_BUFFER_WIDTH;
  uint8_t index_y = y / TILE_SIZE - DEVICE_SPRITE_OFFSET_Y;

  map_buffer[index_y][index_x] = TILE_EMPTY;

  set_bkg_tile_xy(index_x, index_y, TILE_EMPTY);

  music_play_sfx(BANK(sound_coin), sound_coin, SFX_MUTE_MASK(sound_coin),
                 MUSIC_SFX_PRIORITY_NORMAL);

  coins++;
  score += 10;

  if (coins == 100) {
    lives++;
    hud_update_lives();
    coins = 0;
    music_play_sfx(BANK(sound_oneup), sound_oneup, SFX_MUTE_MASK(sound_oneup),
                   MUSIC_SFX_PRIORITY_NORMAL);
  }

  hud_update_coins();
  hud_update_score();
}

void level_load_objects(uint16_t col) NONBANKED {
  for (int i = 0; i < level_1_1_lookup_size; i++) {
    level_object *obj = level_1_1_lookup+i;
    if (obj->x == col) {
      EMU_printf("SPAWN OBJECT %d at %d %d\n", obj->type, obj->x, obj->y);
      if (obj->type == OBJECT_TYPE_ENEMY) {
      } else if (obj->type == OBJECT_TYPE_POWERUP) {
      }
    }
  }
}

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
    music_load(BANK(music_overworld), &music_overworld);
    break;
  case 1:
    set_level_1_2();
    hud_set_level('1', '2');
    music_load(BANK(music_overworld), &music_overworld);
    break;
  case 2:
    set_level_1_3();
    hud_set_level('1', '3');
    music_load(BANK(music_castle), &music_castle);
    break;
  case 3:
    set_level_2_1();
    hud_set_level('2', '1');
    music_load(BANK(music_overworld), &music_overworld);
    break;
  case 4:
    set_level_2_2();
    hud_set_level('2', '2');
    music_load(BANK(music_overworld), &music_overworld);
    break;
  case 5:
    set_level_2_3();
    hud_set_level('2', '3');
    music_load(BANK(music_castle), &music_castle);
    break;
  case 6:
    set_level_3_1();
    hud_set_level('3', '1');
    music_load(BANK(music_overworld), &music_overworld);
    break;
  case 7:
    set_level_3_2();
    hud_set_level('3', '2');
    music_load(BANK(music_overworld), &music_overworld);
    break;
  case 8:
    set_level_3_3();
    hud_set_level('3', '3');
    music_load(BANK(music_castle), &music_castle);
    break;
  case 9:
    set_level_4_1();
    hud_set_level('4', '1');
    music_load(BANK(music_overworld), &music_overworld);
    break;
  case 10:
    set_level_4_2();
    hud_set_level('4', '2');
    music_load(BANK(music_overworld), &music_overworld);
    break;
  case 11:
    set_level_4_3();
    hud_set_level('4', '3');
    music_load(BANK(music_castle), &music_castle);
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
