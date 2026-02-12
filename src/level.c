#include "level.h"
#include "coin_animated.h"
#include <gbdk/platform.h>

#include "global.h"
#include "graphics/enemies.h"
#include "level_object.h"
#include "level_tables.h"
#include "lookup_tables/lookup_table_underground.h"

#ifdef GAMEBOY
#include "musics/musics.h"
#endif

#include "platforms.h"
#include "player.h"
#include <stdint.h>

// Camera and scrolling
uint16_t camera_x;
uint16_t camera_x_upscaled;
uint16_t next_col_chunk_load;
const unsigned char *current_map;

// Map buffer for rendering
uint8_t map_buffer[MAP_BUFFER_HEIGHT * DEVICE_SCREEN_BUFFER_WIDTH] = {TILE_EMPTY};
uint8_t coldata[MAP_BUFFER_HEIGHT];
uint8_t set_column_at;
bool level_end_reached;
uint8_t current_level;
uint8_t map_column;

#ifdef USE_COMPRESSED_LEVELS
#include <gbdk/gbdecompress.h>
// Decompression buffer - sized for a single page
uint8_t decompression_buffer[DECOMPRESSED_PAGE_SIZE];
#endif

// Current level tile data
int current_map_tile_origin;
const unsigned char *current_map_tiles;
size_t current_map_tile_count;
size_t current_map_width;
size_t current_map_width_in_tiles;
uint8_t level_bank;

// Level object lookup data
uint8_t level_lookup_bank;
const level_object *level_lookup;
size_t level_lookup_size;

// Map page tracking
uint8_t current_page = 0;
uint8_t map_column_in_page = 0;

// Cache for currently decompressed page to avoid repeated decompression
uint8_t cached_page_index = 0xFF;  // Invalid page initially

#define PAGE_SIZE 20 

// Level definitions
const level levels[NB_LEVELS] = {
  {
    .major = '1',
    .minor = '1',
    #ifdef GAMEBOY
    .music_bank = BANK(music_overworld),
    .music = &music_overworld,
    #endif
    .map_pages = level_1_1_map,
    .page_count = level_table_1_1_ENTRY_COUNT,
    .map_tiles_bank = BANK(birabuto),
    .map_tile_origin = birabuto_TILE_ORIGIN,
    .map_tiles = birabuto_tiles,
    .map_tiles_count = birabuto_TILE_COUNT,
    .map_width = level_table_1_1_ENTRY_COUNT * PAGE_SIZE * 8,
    .map_width_in_tiles = level_table_1_1_ENTRY_COUNT * PAGE_SIZE,
    .lookup_bank = BANK(level_1_1_lookup),
    .lookup = level_1_1_lookup,
    .lookup_size = level_1_1_lookup_ENTRY_COUNT
  },
  {
  .major = '1',
  .minor = '2',
  #ifdef GAMEBOY
  .music_bank = BANK(music_overworld),
  .music = &music_overworld,
  #endif
  .map_pages = level_1_2_map,
  .page_count = level_table_1_2_ENTRY_COUNT,
  .map_tiles_bank = BANK(birabuto),
  .map_tile_origin = birabuto_TILE_ORIGIN,
  .map_tiles = birabuto_tiles,
  .map_tiles_count = birabuto_TILE_COUNT,
  .map_width = level_table_1_2_ENTRY_COUNT * PAGE_SIZE * 8,
  .map_width_in_tiles = level_table_1_2_ENTRY_COUNT * PAGE_SIZE,
  .lookup_bank = BANK(level_1_2_lookup),
  .lookup = level_1_2_lookup,
  .lookup_size = level_1_2_lookup_ENTRY_COUNT
  },
  {
  .major = '1',
  .minor = '3',
  #ifdef GAMEBOY
  .music_bank = BANK(music_castle),
  .music = &music_castle,
  #endif
  .map_pages = level_1_3_map,
  .page_count = level_table_1_3_ENTRY_COUNT,
  .map_tiles_bank = BANK(birabuto),
  .map_tile_origin = birabuto_TILE_ORIGIN,
  .map_tiles = birabuto_tiles,
  .map_tiles_count = birabuto_TILE_COUNT,
  .map_width = level_table_1_3_ENTRY_COUNT * PAGE_SIZE * 8,
  .map_width_in_tiles = level_table_1_3_ENTRY_COUNT * PAGE_SIZE,
  .lookup_bank = BANK(level_1_3_lookup),
  .lookup = level_1_3_lookup,
  .lookup_size = level_1_3_lookup_ENTRY_COUNT
  },
  {
  .major = '2',
  .minor = '1',
  #ifdef GAMEBOY
  .music_bank = BANK(music_overworld),
  .music = &music_overworld,
  #endif
  .map_pages = level_2_1_map,
  .page_count = level_table_2_1_ENTRY_COUNT,
  .map_tiles_bank = BANK(muda),
  .map_tile_origin = muda_TILE_ORIGIN,
  .map_tiles = muda_tiles,
  .map_tiles_count = muda_TILE_COUNT,
  .map_width = level_table_2_1_ENTRY_COUNT * PAGE_SIZE * 8,
  .map_width_in_tiles = level_table_2_1_ENTRY_COUNT * PAGE_SIZE,
  .lookup_bank = BANK(level_2_1_lookup),
  .lookup = level_2_1_lookup,
  .lookup_size = level_2_1_lookup_ENTRY_COUNT
  },
  {
  .major = '2',
  .minor = '2',
  #ifdef GAMEBOY
  .music_bank = BANK(music_overworld),
  .music = &music_overworld,
  #endif
  .map_pages = level_2_2_map,
  .page_count = level_table_2_2_ENTRY_COUNT,
  .map_tiles_bank = BANK(muda),
  .map_tile_origin = muda_TILE_ORIGIN,
  .map_tiles = muda_tiles,
  .map_tiles_count = muda_TILE_COUNT,
  .map_width = level_table_2_2_ENTRY_COUNT * PAGE_SIZE * 8,
  .map_width_in_tiles = level_table_2_2_ENTRY_COUNT * PAGE_SIZE,
  .lookup_bank = BANK(level_2_2_lookup),
  .lookup = level_2_2_lookup,
  .lookup_size = level_2_2_lookup_ENTRY_COUNT
  },
  {
  .major = '2',
  .minor = '3',
  #ifdef GAMEBOY
  .music_bank = BANK(music_underwater),
  .music = &music_underwater,
  #endif
  .map_pages = level_2_3_map,
  .page_count = level_table_2_3_ENTRY_COUNT,
  .map_tiles_bank = BANK(muda),
  .map_tile_origin = muda_TILE_ORIGIN,
  .map_tiles = muda_tiles,
  .map_tiles_count = muda_TILE_COUNT,
  .map_width = level_table_2_3_ENTRY_COUNT * PAGE_SIZE * 8,
  .map_width_in_tiles = level_table_2_3_ENTRY_COUNT * PAGE_SIZE,
  .lookup_bank = BANK(level_2_3_lookup),
  .lookup = level_2_3_lookup,
  .lookup_size = level_2_3_lookup_ENTRY_COUNT
  },
  {
  .major = '3',
  .minor = '1',
  #ifdef GAMEBOY
  .music_bank = BANK(music_overworld),
  .music = &music_overworld,
  #endif
  .map_pages = level_3_1_map,
  .page_count = level_table_3_1_ENTRY_COUNT,
  .map_tiles_bank = BANK(easton),
  .map_tile_origin = easton_TILE_ORIGIN,
  .map_tiles = easton_tiles,
  .map_tiles_count = easton_TILE_COUNT,
  .map_width = level_table_3_1_ENTRY_COUNT * PAGE_SIZE * 8,
  .map_width_in_tiles = level_table_3_1_ENTRY_COUNT * PAGE_SIZE,
  .lookup_bank = BANK(level_3_1_lookup),
  .lookup = level_3_1_lookup,
  .lookup_size = level_3_1_lookup_ENTRY_COUNT
  },
  {
  .major = '3',
  .minor = '2',
  #ifdef GAMEBOY
  .music_bank = BANK(music_overworld),
  .music = &music_overworld,
  #endif
  .map_pages = level_3_2_map,
  .page_count = level_table_3_2_ENTRY_COUNT,
  .map_tiles_bank = BANK(easton),
  .map_tile_origin = easton_TILE_ORIGIN,
  .map_tiles = easton_tiles,
  .map_tiles_count = easton_TILE_COUNT,
  .map_width = level_table_3_2_ENTRY_COUNT * PAGE_SIZE * 8,
  .map_width_in_tiles = level_table_3_2_ENTRY_COUNT * PAGE_SIZE,
  .lookup_bank = BANK(level_3_2_lookup),
  .lookup = level_3_2_lookup,
  .lookup_size = level_3_2_lookup_ENTRY_COUNT
  },
  {
  .major = '3',
  .minor = '3',
  #ifdef GAMEBOY
  .music_bank = BANK(music_castle),
  .music = &music_castle,
  #endif
  .map_pages = level_3_3_map,
  .page_count = level_table_3_3_ENTRY_COUNT,
  .map_tiles_bank = BANK(easton),
  .map_tile_origin = easton_TILE_ORIGIN,
  .map_tiles = easton_tiles,
  .map_tiles_count = easton_TILE_COUNT,
  .map_width = level_table_3_3_ENTRY_COUNT * PAGE_SIZE * 8,
  .map_width_in_tiles = level_table_3_3_ENTRY_COUNT * PAGE_SIZE,
  .lookup_bank = BANK(level_3_3_lookup),
  .lookup = level_3_3_lookup,
  .lookup_size = level_3_3_lookup_ENTRY_COUNT
  },
  {
  .major = '4',
  .minor = '1',
  #ifdef GAMEBOY
  .music_bank = BANK(music_overworld),
  .music = &music_overworld,
  #endif
  .map_pages = level_4_1_map,
  .page_count = level_table_4_1_ENTRY_COUNT,
  .map_tiles_bank = BANK(chai),
  .map_tile_origin = chai_TILE_ORIGIN,
  .map_tiles = chai_tiles,
  .map_tiles_count = chai_TILE_COUNT,
  .map_width = level_table_4_1_ENTRY_COUNT * PAGE_SIZE * 8,
  .map_width_in_tiles = level_table_4_1_ENTRY_COUNT * PAGE_SIZE,
  .lookup_bank = BANK(level_4_1_lookup),
  .lookup = level_4_1_lookup,
  .lookup_size = level_4_1_lookup_ENTRY_COUNT
  },
  {
  .major = '4',
  .minor = '2',
  #ifdef GAMEBOY
  .music_bank = BANK(music_overworld),
  .music = &music_overworld,
  #endif
  .map_pages = level_4_2_map,
  .page_count = level_table_4_2_ENTRY_COUNT,
  .map_tiles_bank = BANK(chai),
  .map_tile_origin = chai_TILE_ORIGIN,
  .map_tiles = chai_tiles,
  .map_tiles_count = chai_TILE_COUNT,
  .map_width = level_table_4_2_ENTRY_COUNT * PAGE_SIZE * 8,
  .map_width_in_tiles = level_table_4_2_ENTRY_COUNT * PAGE_SIZE,
  .lookup_bank = BANK(level_4_2_lookup),
  .lookup = level_4_2_lookup,
  .lookup_size = level_4_2_lookup_ENTRY_COUNT
  },
  {
  .major = '4',
  .minor = '3',
  #ifdef GAMEBOY
  .music_bank = BANK(music_underwater),
  .music = &music_underwater,
  #endif
  .map_pages = level_4_3_map,
  .page_count = level_table_4_3_ENTRY_COUNT,
  .map_tiles_bank = BANK(chai),
  .map_tile_origin = chai_TILE_ORIGIN,
  .map_tiles = chai_tiles,
  .map_tiles_count = chai_TILE_COUNT,
  .map_width = level_table_4_3_ENTRY_COUNT * PAGE_SIZE * 8,
  .map_width_in_tiles = level_table_4_3_ENTRY_COUNT * PAGE_SIZE,
  .lookup_bank = BANK(level_4_3_lookup),
  .lookup = level_4_3_lookup,
  .lookup_size = level_4_3_lookup_ENTRY_COUNT
  }
};

const level undergrounds[1] = {
  {
    .major = '1',
    .minor = '1',
    #ifdef GAMEBOY
    .music_bank = BANK(music_underground),
    .music = &music_underground,
    #endif
    .map_pages = underground_0_map_pages,
    .page_count = 1,
    .map_tiles_bank = NULL,
    .map_tile_origin = NULL,
    .map_tiles = NULL,
    .map_tiles_count = 0,
    .map_width = 1 * PAGE_SIZE * 8,
    .map_width_in_tiles = 1 * PAGE_SIZE,
    .lookup_bank = BANK(underground_lookup),
    .lookup = underground_0_lookup,
    .lookup_size = underground_lookup_ENTRY_COUNT
  }
};

/**
 * Get tile at world coordinates
 */
uint8_t get_tile(uint8_t x, uint8_t y) {
  if (y >> 3 < 2 || y >> 3 > MAP_BUFFER_HEIGHT + 1) {
    return TILE_EMPTY;
  }

  uint8_t tile_x = TILE_INDEX_X(x, camera_x);
  uint8_t tile_y = TILE_INDEX_Y(y);
  return map_buffer[tile_y * DEVICE_SCREEN_BUFFER_WIDTH + tile_x];
}

/**
 * Check if a tile is solid (blocks player movement)
 */
bool is_tile_solid(uint8_t tile) {
  // Check common solid tiles
  switch (tile) {
    case TILE_INTEROGATION_BLOCK:
    case BREAKABLE_BLOCK:
    case TILE_UNBREAKABLE:
    case PIPE_TOP_LEFT:
    case PIPE_TOP_RIGHT:
    case PIPE_CENTER_LEFT:
    case PIPE_CENTER_RIGHT:
    case PIPE_HORIZONTAL_1:
    case PIPE_HORIZONTAL_2:
    case PIPE_HORIZONTAL_3:
    case PIPE_HORIZONTAL_4:
    case PIPE_HORIZONTAL_5:
    case PIPE_HORIZONTAL_6:
    case PIPE_HORIZONTAL_7:
    case PIPE_HORIZONTAL_8:
    case TILE_EMPTIED:
    case METAL_GATE:
    case METAL_BLOCK_LEFT:
    case METAL_BLOCK_RIGHT:
      return true;
  }

  // Check world-specific tiles
  if (current_level >= 0 && current_level <= 2) {
    // Birabuto world
    return ((tile == TILE_FLOOR) || (tile == TILE_FLOOR_BIS) ||
            (tile == STONE_LEFT) || (tile == STONE_RIGHT) ||
            (tile == TILED_FLOOR) || (tile == STONE_BIS_LEFT) ||
            (tile == STONE_BIS_RIGHT) || (tile == BRICK_BLOCK) || 
            (tile == GREY_BLOCK));
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

/**
 * Check if tiles can be passed through from below (semi-solid platforms)
 */
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

/**
 * Check if tile is a coin
 */
bool is_coin(uint8_t tile) { 
  return tile == TILE_COIN; 
}

/**
 * Handle coin collection from background tile
 */
void on_get_coin_background(uint8_t x, uint8_t y) {
  uint8_t index_x = TILE_INDEX_X(x, camera_x);
  uint8_t index_y = TILE_INDEX_Y(y);

  map_buffer[index_y * DEVICE_SCREEN_BUFFER_WIDTH + index_x] = TILE_EMPTY;
  set_bkg_tile_xy(index_x, index_y, TILE_EMPTY);

  on_get_coin();
}

/**
 * Handle coin collection logic
 */
void on_get_coin() {
  #ifdef GAMEBOY
  music_play_sfx(BANK(sound_coin), sound_coin, SFX_MUTE_MASK(sound_coin),
                 MUSIC_SFX_PRIORITY_NORMAL);
  #endif

  coins++;
  score += 10;

  if (coins == 100) {
    lives++;
    hud_update_lives();
    coins = 0;
    #ifdef GAMEBOY
    music_play_sfx(BANK(sound_oneup), sound_oneup, SFX_MUTE_MASK(sound_oneup),
                   MUSIC_SFX_PRIORITY_NORMAL);
    #endif
  }

  hud_update_coins();
  hud_update_score();
}

/**
 * Handle interrogation block being hit
 */
void on_interogation_block_hit(uint8_t x, uint8_t y) {
  // Get buffer indices for rendering
  uint8_t index_x = TILE_INDEX_X(x, camera_x);
  uint8_t index_y = TILE_INDEX_Y(y);

  // Get actual world tile coordinates for lookup
  uint8_t world_tile_x = (x + camera_x) >> 3;

  // Update map buffer and VRAM with an emptied block
  map_buffer[index_y * DEVICE_SCREEN_BUFFER_WIDTH + index_x] = TILE_EMPTIED;

  #if defined(GAMEBOY)
  set_bkg_tile_xy(index_x, index_y, TILE_EMPTIED);
  #elif defined(NINTENDO_NES)
  set_bkg_tile_xy(index_x, index_y + 2, TILE_EMPTIED);
  #endif

  // Switch to lookup table bank to check block contents
  uint8_t _saved_bank = _current_bank;
  SWITCH_ROM(level_lookup_bank);

  // Check block content in lookup table using WORLD coordinates
  bool lookup_found = FALSE;
  for (uint16_t i = 0; i < level_lookup_size && !lookup_found; i++) {
    level_object *obj = &level_lookup[i];
    
    if (obj->x == world_tile_x && obj->y == index_y) {
      lookup_found = TRUE;
      powerup_new((index_x << 3) << 4, (index_y << 3) << 4, obj->data.enemy.type);
    }
  }

  SWITCH_ROM(_saved_bank);

  // Coin by default, if block coord not found in lookup table
  if (lookup_found == FALSE) {
    on_get_coin();
    coin_animated_new(index_x, index_y);
  }
}

uint16_t col_from = 0;

/**
 * Load level objects (enemies, platforms, etc.) at a specific column
 */
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
        // Powerups handled by interrogation blocks
      } else if (obj->type == OBJECT_TYPE_PLATFORM_MOVING) {
        platform_moving_new(
            obj->x * TILE_SIZE, (obj->y + MARGIN_TOP) * TILE_SIZE,
            obj->data.platform_moving.platform_direction,
            obj->data.platform_moving.range, obj->data.platform_moving.width);
      } else if (obj->type == OBJECT_TYPE_PLATFORM_FALLING) {
        platform_falling_new(obj->x * TILE_SIZE,
                             (obj->y + MARGIN_TOP) * TILE_SIZE);
      }
      else if (obj->type == OBJECT_TYPE_PIPE_VERTICAL) {
        // Pipes are rendered as part of the background tiles
        // They are checked in player_check_pipe_entry() when player presses down
        // No special loading needed here - just skip
      }
    } else if (obj->x > col) {
      col_from = i;
      break;
    }
  }
  
  SWITCH_ROM(_saved_bank);
}


/**
 * Load columns from compressed map pages with proper bank switching and decompression
 * This is the critical function that switches banks when loading map data
 */
uint8_t level_load_column(uint16_t start_at, uint8_t nb) NONBANKED {
  uint8_t _saved_bank = _current_bank;
  
  uint8_t col = 0;
  while (col < nb) {
    // Calculate which page we need and the column within that page
    uint16_t global_column = col + start_at;
    uint8_t page_index = global_column / 20;  // Each page is 20 tiles wide
    uint8_t column_in_page = global_column % 20;
    
    // Check if we've exceeded the number of pages
    if (page_index >= levels[current_level].page_count) {
      SWITCH_ROM(_saved_bank);
      return col;  // Return how many we actually loaded
    }
    
    // Get the banked map entry for the current page
    const banked_map_t *page_entry = &levels[current_level].map_pages[page_index];
    
    // CRITICAL: Switch to the bank containing this page's data
    SWITCH_ROM(page_entry->bank);
    const unsigned char* current_page_data;

    #ifdef USE_COMPRESSED_LEVELS
    // Decompress the page data if we haven't already cached it
    if (cached_page_index != page_index) {
      // Decompress the compressed map data into our buffer
      gb_decompress(page_entry->map, decompression_buffer);
      current_page_data = decompression_buffer;
      cached_page_index = page_index;
    } else {
      // Use cached decompressed data
      current_page_data = decompression_buffer;
    }
    #else
    current_page_data = page_entry->map;
    #endif
    
    // Calculate buffer position for this column
    map_column = (col + start_at) & (DEVICE_SCREEN_BUFFER_WIDTH - 1);

    // Load the column from the decompressed page
    for (int row = 0; row < LEVEL_HEIGHT; row++) {
      int pos = (row * 20) + column_in_page;  // 20 = page width
      uint8_t tile = current_page_data[pos];
      map_buffer[row * DEVICE_SCREEN_BUFFER_WIDTH + map_column] = tile;
      coldata[row] = tile;
    }

    // Draw current column to background
    #if defined(GAMEBOY)
      #define TILE_Y 0
    #elif defined(NINTENDO_NES)
      #define TILE_Y 2
    #else
      #define TILE_Y 0
    #endif
    set_bkg_tiles(map_column, TILE_Y, 1, LEVEL_HEIGHT, coldata);

    col++;
  }

  // Restore original bank
  SWITCH_ROM(_saved_bank);
  return col;
}

/**
 * Set up the current level and initialize player position
 */
void level_set_current(void) NONBANKED {
  set_level(current_level);
  scroll_limit = DEVICE_SCREEN_PX_WIDTH_HALF;
  enemy_count = 0;
  platform_moving_count = 0;
  col_from = 0;
  hide_sprites_range(1, MAX_HARDWARE_SPRITES);
  load_current_level();
}

/**
 * Load the current level's initial state
 */
void load_current_level(void) NONBANKED {
  set_column_at = 0;
  camera_x = 0;
  move_bkg(0, -16);
  camera_x_upscaled = 0;
  level_end_reached = false;
  current_page = 0;
  map_column_in_page = 0;
  cached_page_index = 0xFF;  // Invalidate page cache

  // Load initial map columns
  level_load_column(0, MAP_BUFFER_WIDTH);

  next_col_chunk_load = COLUMN_CHUNK_SIZE;
}

/**
 * Set up a specific level (tiles, music, lookup tables, etc.)
 */
void set_level(uint8_t level_index) NONBANKED {
  hud_set_level(levels[level_index].major, levels[level_index].minor);

  #ifdef GAMEBOY
  music_load(levels[level_index].music_bank, levels[level_index].music);
  #endif

  uint8_t _saved_bank = _current_bank;

  // Load level tiles
  SWITCH_ROM(levels[level_index].map_tiles_bank);
  current_map_tiles = levels[level_index].map_tiles;
  current_map_tile_origin = levels[level_index].map_tile_origin;
  current_map_tile_count = levels[level_index].map_tiles_count;
  set_bkg_data(current_map_tile_origin, current_map_tile_count,
               current_map_tiles);

  // Set level dimensions
  current_map_width = levels[level_index].map_width;
  current_map_width_in_tiles = levels[level_index].map_width_in_tiles;

  // Set up lookup table for level objects
  SWITCH_ROM(levels[level_index].lookup_bank);
  level_lookup_bank = levels[level_index].lookup_bank;
  level_lookup = levels[level_index].lookup;
  level_lookup_size = levels[level_index].lookup_size;

  SWITCH_ROM(_saved_bank);
}