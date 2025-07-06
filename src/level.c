#include "level.h"
#include "coin_animated.h"
#include "gb/gb.h"
#include "global.h"
#include "graphics/enemies.h"
#include "levels/level_1_1.h"
#include "lookup_tables.h"
#include "lookup_tables/lookup_table_1_1.h"
#include "musics/musics.h"
#include "platforms.h"
#include "player.h"
#include <stdint.h>

uint16_t camera_x;
uint16_t camera_x_upscaled;
uint16_t next_col_chunk_load;
const unsigned char *current_map;

uint8_t map_buffer[MAP_BUFFER_HEIGHT * DEVICE_SCREEN_BUFFER_WIDTH] = {
    TILE_EMPTY};
uint8_t coldata[MAP_BUFFER_HEIGHT];
uint8_t set_column_at;
bool level_end_reached;
uint8_t current_level;
uint8_t map_column;

int current_map_tile_origin;
const unsigned char *current_map_tiles;
size_t current_map_tile_count;
size_t current_map_width;
size_t current_map_width_in_tiles;
uint8_t level_bank;

uint8_t level_lookup_bank;
const level_object *level_lookup;
size_t level_lookup_size;

const level levels[NB_LEVELS] = {{.major = '1',
                                  .minor = '1',
                                  .bank = BANK(level_1_1),
                                  .music_bank = BANK(music_overworld),
                                  .music = &music_overworld,
                                  .map = level_1_1_map,
                                  .map_tiles_bank = BANK(birabuto),
                                  .map_tile_origin = birabuto_TILE_ORIGIN,
                                  .map_tiles = birabuto_tiles,
                                  .map_tiles_count = birabuto_TILE_COUNT,
                                  .map_width = level_1_1_WIDTH,
                                  .map_width_in_tiles = level_1_1_WIDTH >> 3,
                                  .lookup_bank = BANK(level_1_1_lookup_bank),
                                  .lookup = level_1_1_lookup,
                                  .lookup_size = 15},

                                 {.major = '1',
                                  .minor = '2',
                                  .bank = BANK(level_1_2),
                                  .music_bank = BANK(music_overworld),
                                  .music = &music_overworld,
                                  .map = level_1_2_map,
                                  .map_tiles_bank = BANK(birabuto),
                                  .map_tile_origin = birabuto_TILE_ORIGIN,
                                  .map_tiles = birabuto_tiles,
                                  .map_tiles_count = birabuto_TILE_COUNT,
                                  .map_width = level_1_2_WIDTH,
                                  .map_width_in_tiles = level_1_2_WIDTH >> 3,
                                  .lookup_bank = BANK(level_1_2_lookup_bank),
                                  .lookup = level_1_2_lookup,
                                  .lookup_size = 0},

                                 {.major = '1',
                                  .minor = '3',
                                  .bank = BANK(level_1_3),
                                  .map = level_1_3_map,
                                  .map_tiles_bank = BANK(birabuto),
                                  .map_tile_origin = birabuto_TILE_ORIGIN,
                                  .music_bank = BANK(music_castle),
                                  .music = &music_castle,
                                  .map_tiles = birabuto_tiles,
                                  .map_tiles_count = birabuto_TILE_COUNT,
                                  .map_width = level_1_3_WIDTH,
                                  .map_width_in_tiles = level_1_3_WIDTH >> 3,
                                  .lookup_bank = BANK(level_1_3_lookup_bank),
                                  .lookup = level_1_3_lookup,
                                  .lookup_size = 0},

                                 {.major = '2',
                                  .minor = '1',
                                  .bank = BANK(level_2_1),
                                  .music_bank = BANK(music_overworld),
                                  .music = &music_overworld,
                                  .map = level_2_1_map,
                                  .map_tiles_bank = BANK(muda),
                                  .map_tile_origin = muda_TILE_ORIGIN,
                                  .map_tiles = muda_tiles,
                                  .map_tiles_count = muda_TILE_COUNT,
                                  .map_width = level_2_1_WIDTH,
                                  .map_width_in_tiles = level_2_1_WIDTH >> 3,
                                  .lookup_bank = BANK(level_2_1_lookup_bank),
                                  .lookup = level_2_1_lookup,
                                  .lookup_size = 0},

                                 {.major = '2',
                                  .minor = '2',
                                  .bank = BANK(level_2_2),
                                  .music_bank = BANK(music_overworld),
                                  .music = &music_overworld,
                                  .map = level_2_2_map,
                                  .map_tiles_bank = BANK(muda),
                                  .map_tile_origin = muda_TILE_ORIGIN,
                                  .map_tiles = muda_tiles,
                                  .map_tiles_count = muda_TILE_COUNT,
                                  .map_width = level_2_2_WIDTH,
                                  .map_width_in_tiles = level_2_2_WIDTH >> 3,
                                  .lookup_bank = BANK(level_2_2_lookup_bank),
                                  .lookup = level_2_2_lookup,
                                  .lookup_size = 0},

                                 {.major = '2',
                                  .minor = '3',
                                  .bank = BANK(level_2_3),
                                  .music_bank = BANK(music_overworld),
                                  .music = &music_overworld,
                                  .map = level_2_3_map,
                                  .map_tiles_bank = BANK(muda),
                                  .map_tile_origin = muda_TILE_ORIGIN,
                                  .map_tiles = muda_tiles,
                                  .map_tiles_count = muda_TILE_COUNT,
                                  .map_width = level_2_3_WIDTH,
                                  .map_width_in_tiles = level_2_3_WIDTH >> 3,
                                  .lookup_bank = BANK(level_2_3_lookup_bank),
                                  .lookup = level_2_3_lookup,
                                  .lookup_size = 0},

                                 {.major = '3',
                                  .minor = '1',
                                  .bank = BANK(level_3_1),
                                  .music_bank = BANK(music_overworld),
                                  .music = &music_overworld,
                                  .map = level_3_1_map,
                                  .map_tiles_bank = BANK(easton),
                                  .map_tile_origin = easton_TILE_ORIGIN,
                                  .map_tiles = easton_tiles,
                                  .map_tiles_count = easton_TILE_COUNT,
                                  .map_width = level_3_1_WIDTH,
                                  .map_width_in_tiles = level_3_1_WIDTH >> 3,
                                  .lookup_bank = BANK(level_3_1_lookup_bank),
                                  .lookup = level_3_1_lookup,
                                  .lookup_size = 0},

                                 {.major = '3',
                                  .minor = '2',
                                  .bank = BANK(level_3_2),
                                  .music_bank = BANK(music_overworld),
                                  .music = &music_overworld,
                                  .map = level_3_2_map,
                                  .map_tiles_bank = BANK(easton),
                                  .map_tile_origin = easton_TILE_ORIGIN,
                                  .map_tiles = easton_tiles,
                                  .map_tiles_count = easton_TILE_COUNT,
                                  .map_width = level_3_2_WIDTH,
                                  .map_width_in_tiles = level_3_2_WIDTH >> 3,
                                  .lookup_bank = BANK(level_3_2_lookup_bank),
                                  .lookup = level_3_2_lookup,
                                  .lookup_size = 0},

                                 {.major = '3',
                                  .minor = '3',
                                  .bank = BANK(level_3_3),
                                  .music_bank = BANK(music_overworld),
                                  .music = &music_overworld,
                                  .map = level_3_3_map,
                                  .map_tiles_bank = BANK(easton),
                                  .map_tile_origin = easton_TILE_ORIGIN,
                                  .map_tiles = easton_tiles,
                                  .map_tiles_count = easton_TILE_COUNT,
                                  .map_width = level_3_3_WIDTH,
                                  .map_width_in_tiles = level_3_3_WIDTH >> 3,
                                  .lookup_bank = BANK(level_3_3_lookup_bank),
                                  .lookup = level_3_3_lookup,
                                  .lookup_size = 0},

                                 {.major = '4',
                                  .minor = '1',
                                  .bank = BANK(level_4_1),
                                  .music_bank = BANK(music_overworld),
                                  .music = &music_overworld,
                                  .map = level_4_1_map,
                                  .map_tile_origin = chai_TILE_ORIGIN,
                                  .map_tiles_bank = BANK(chai),
                                  .map_tiles = chai_tiles,
                                  .map_tiles_count = chai_TILE_COUNT,
                                  .map_width = level_4_1_WIDTH,
                                  .map_width_in_tiles = level_4_1_WIDTH >> 3,
                                  .lookup_bank = BANK(level_4_1_lookup_bank),
                                  .lookup = level_4_1_lookup,
                                  .lookup_size = 0},

                                 {.major = '4',
                                  .minor = '2',
                                  .bank = BANK(level_4_2),
                                  .music_bank = BANK(music_overworld),
                                  .music = &music_overworld,
                                  .map_tiles_bank = BANK(chai),
                                  .map = level_4_2_map,
                                  .map_tile_origin = chai_TILE_ORIGIN,
                                  .map_tiles = chai_tiles,
                                  .map_tiles_count = chai_TILE_COUNT,
                                  .map_width = level_4_2_WIDTH,
                                  .map_width_in_tiles = level_4_2_WIDTH >> 3,
                                  .lookup_bank = BANK(level_4_2_lookup_bank),
                                  .lookup = level_4_2_lookup,
                                  .lookup_size = 0},

                                 {.major = '4',
                                  .minor = '3',
                                  .bank = BANK(level_4_3),
                                  .music_bank = BANK(music_overworld),
                                  .music = &music_overworld,
                                  .map = level_4_3_map,
                                  .map_tiles_bank = BANK(chai),
                                  .map_tile_origin = chai_TILE_ORIGIN,
                                  .map_tiles = chai_tiles,
                                  .map_tiles_count = chai_TILE_COUNT,
                                  .map_width = level_4_3_WIDTH,
                                  .map_width_in_tiles = level_4_3_WIDTH >> 3,
                                  .lookup_bank = BANK(level_4_3_lookup_bank),
                                  .lookup = level_4_3_lookup,
                                  .lookup_size = 0}};

uint8_t get_tile(uint8_t x, uint8_t y) {
  if (y >> 3 < 2 || y >> 3 > MAP_BUFFER_HEIGHT + 1) {
    return TILE_EMPTY;
  }

  uint8_t tile_x = TILE_INDEX_X(x, camera_x);
  uint8_t tile_y = TILE_INDEX_Y(y);
  return map_buffer[tile_y * DEVICE_SCREEN_BUFFER_WIDTH + tile_x];
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
            (tile == STONE_BIS_RIGHT) || (tile == BRICK_BLOCK));
  } else if (current_level >= 3 && current_level <= 5) {
    // Muda world
    return ((tile == BIG_BLOCK_TOP_LEFT) || (tile == BIG_BLOCK_TOP_RIGHT) ||
            (tile == BIG_BLOCK_BOTTOM_LEFT) ||
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

bool is_tile_passthought(uint8_t tile_left_bottom, uint8_t tile_right_bottom) {
  return (current_level == 1 && ((tile_left_bottom == PALM_TREE_LEFT) ||
                                 (tile_left_bottom == PALM_TREE_CENTER) ||
                                 (tile_left_bottom == PALM_TREE_RIGHT) ||
                                 (tile_right_bottom == PALM_TREE_LEFT) ||
                                 (tile_right_bottom == PALM_TREE_CENTER) ||
                                 (tile_right_bottom == PALM_TREE_RIGHT))) ||
         (current_level == 3 && ((tile_left_bottom == MUDA_PLATEFORM_LEFT) ||
                                 (tile_left_bottom == MUDA_PLATEFORM_CENTER) ||
                                 (tile_left_bottom == MUDA_PLATEFORM_RIGHT) ||
                                 (tile_right_bottom == MUDA_PLATEFORM_LEFT) ||
                                 (tile_right_bottom == MUDA_PLATEFORM_CENTER) ||
                                 (tile_right_bottom == MUDA_PLATEFORM_RIGHT)));
}

bool is_coin(uint8_t tile) { return tile == TILE_COIN; }

void on_get_coin_background(uint8_t x, uint8_t y) {
  uint8_t index_x = TILE_INDEX_X(x, camera_x);
  uint8_t index_y = TILE_INDEX_Y(y);

  map_buffer[index_y * DEVICE_SCREEN_BUFFER_WIDTH + index_x] = TILE_EMPTY;
  set_bkg_tile_xy(index_x, index_y, TILE_EMPTY);

  on_get_coin();
}

void on_get_coin() {
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

void on_interogation_block_hit(uint8_t x, uint8_t y) {
  uint8_t index_x = TILE_INDEX_X(x, camera_x);
  uint8_t index_y = TILE_INDEX_Y(y);

  // update map buffer and vram with an emptied block
  map_buffer[index_y * DEVICE_SCREEN_BUFFER_WIDTH + index_x] = TILE_EMPTIED;
  set_bkg_tile_xy(index_x, index_y, TILE_EMPTIED);

  // check block content in lookup table
  bool lookup_found = FALSE;
  /*for (int i = 0; i < level_block_lookup_size && !lookup_found; i++) {
    level_block_object *obj = level_block_lookup + i;
    if (obj->x == index_x && obj->y == index_y) {
      lookup_found = TRUE;
      powerup_new((obj->x << 3) << 4, (obj->y << 3) << 4, obj->id);
    }
  }*/

  // coin by default, if block coord not found in lookup table
  if (lookup_found == FALSE) {
    on_get_coin();
    coin_animated_new(index_x, index_y);
  }
}

uint16_t col_from = 0;
void level_load_objects(uint16_t col) NONBANKED {
  uint8_t _saved_bank = _current_bank;
  SWITCH_ROM(level_lookup_bank);

  for (uint16_t i = col_from; i < level_lookup_size; i++) {
    level_object *obj = &level_lookup[i];
    if (obj->x == col) {
      if (obj->type == OBJECT_TYPE_ENEMY) {
        enemy_new(obj->x * TILE_SIZE,
                  (obj->y + MARGIN_TOP) * TILE_SIZE - enemies_HEIGHT,
                  obj->data.enemy.type);
      } else if (obj->type == OBJECT_TYPE_POWERUP) {
      } else if (obj->type == OBJECT_TYPE_PLATFORM_MOVING) {
        platform_moving_new(
            obj->x * TILE_SIZE, (obj->y + MARGIN_TOP) * TILE_SIZE,
            obj->data.platform_moving.platform_direction,
            obj->data.platform_moving.range, obj->data.platform_moving.width);
      } else if (obj->type == OBJECT_TYPE_PLATFORM_FALLING) {
        platform_falling_new(obj->x * TILE_SIZE,
                             (obj->y + MARGIN_TOP) * TILE_SIZE);
      }
    } else if (obj->x > col) {
      col_from = i;
      break;
    }
  }
  SWITCH_ROM(_saved_bank);
}

uint8_t level_load_column(uint16_t start_at, uint8_t nb) NONBANKED {
  uint8_t _saved_bank = _current_bank;
  SWITCH_ROM(level_bank);

  uint8_t col = 0;
  while (col < nb) {
    map_column = (col + start_at) & (DEVICE_SCREEN_BUFFER_WIDTH - 1);

    for (int row = 0; row < LEVEL_HEIGHT; row++) {
      int pos = (row * current_map_width_in_tiles) + col + start_at;
      uint8_t tile = current_map[pos];
      map_buffer[row * DEVICE_SCREEN_BUFFER_WIDTH + map_column] = tile;
      coldata[row] = tile;
    }

    // Draw current column
    set_bkg_tiles(map_column, 0, 1, LEVEL_HEIGHT, coldata);

    col++;
  };

  SWITCH_ROM(_saved_bank);
  return col;
}

void level_set_current(void) NONBANKED {
  set_level(current_level);

  player_x_upscaled = (4 << 3) << 4;
  player_y_upscaled = 80 << 4;
  player_x_next_upscaled = player_x_upscaled;
  player_y_next_upscaled = player_y_upscaled;

  player_draw_x =
      player_x + DEVICE_SPRITE_PX_OFFSET_X + PLAYER_DRAW_OFFSET_X - camera_x;
  player_draw_y = player_y + DEVICE_SPRITE_PX_OFFSET_Y + MARGIN_TOP_PX +
                  PLAYER_DRAW_OFFSET_Y;

  scroll_limit = DEVICE_SCREEN_PX_WIDTH_HALF;
  enemy_count = 0;
  platform_moving_count = 0;
  col_from = 0;
  hide_sprites_range(1, MAX_HARDWARE_SPRITES);
  load_current_level();
}

void load_current_level(void) NONBANKED {
  set_column_at = 0;
  camera_x = 0;
  camera_x_upscaled = 0;
  level_end_reached = false;

  level_load_column(0, MAP_BUFFER_WIDTH);

  next_col_chunk_load = COLUMN_CHUNK_SIZE;
}

void set_level(uint8_t level_index) NONBANKED {
  hud_set_level(levels[level_index].major, levels[level_index].minor);

  music_load(levels[level_index].music_bank, levels[level_index].music);

  uint8_t _saved_bank = _current_bank;

  SWITCH_ROM(levels[level_index].map_tiles_bank);
  current_map_tiles = levels[level_index].map_tiles;
  current_map_tile_origin = levels[level_index].map_tile_origin;
  current_map_tile_count = levels[level_index].map_tiles_count;
  set_bkg_data(current_map_tile_origin, current_map_tile_count,
               current_map_tiles);

  SWITCH_ROM(levels[level_index].bank);
  current_map = levels[level_index].map;
  current_map_width = levels[level_index].map_width;
  current_map_width_in_tiles = levels[level_index].map_width_in_tiles;
  level_bank = levels[level_index].bank;

  // SWITCH_ROM(levels[level_index].lookup_bank);
  level_lookup_bank = levels[level_index].lookup_bank;
  level_lookup = level_1_1_lookup;           // levels[level_index].lookup;
  level_lookup_size = level_1_1_lookup_size; // levels[level_index].lookup_size;
  // level_block_lookup = NULL;
  // level_block_lookup_size = 0;

  SWITCH_ROM(_saved_bank);
}
