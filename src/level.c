#include "level.h"
#include "coin_animated.h"
#include <gbdk/platform.h>
#include <gbdk/emu_debug.h>

#include "global.h"
#include "enemiesSprites.h"
#include "level_object.h"
#include "level_tables.h"
#include "lookup_table_underground.h"

#ifdef NINTENDO
#include "musicmanager.h"
#include "musics.h"
#endif

#include "platforms.h"
#include "player.h"
#include <stdint.h>

#include "enemiesBirabutoSprites.h"
#include "enemiesMudaSprites.h"
#include "enemiesEastonSprites.h"
#include "enemiesChaiSprites.h"

#if defined(SEGA) || defined(NINTENDO_NES)
#define STREAM_FULL_WIDTH
#endif

uint16_t camera_x;
uint16_t camera_x_upscaled;
uint16_t load_col_at;
const unsigned char *current_map;

uint8_t map_buffer[MAP_BUFFER_HEIGHT * DEVICE_SCREEN_BUFFER_WIDTH] = {TILE_EMPTY};
uint8_t coldata[MAP_BUFFER_HEIGHT];
bool level_end_reached;
uint8_t current_level;
uint8_t map_column = 0;
uint8_t current_column_in_page = 0;

uint16_t level_page_x_offset = 0;
uint16_t world_col_loaded = 0;

typedef struct {
  uint8_t bg_bank;
  uint8_t bg_tile_origin;
  unsigned char *bg_tiles;
  size_t bg_tile_count;

  uint8_t enemy_bank;
  uint8_t enemy_tile_origin;
  const uint8_t *enemy_tiles;
  size_t enemy_tile_count;
} world_assets;

const world_assets world_assets_table[4] = {
  { BANK(birabutoTileset), birabutoTileset_TILE_ORIGIN, birabutoTileset_tiles, birabutoTileset_TILE_COUNT,
    BANK(enemiesBirabutoSprites), enemiesBirabutoSprites_TILE_ORIGIN, enemiesBirabutoSprites_tiles, enemiesBirabutoSprites_TILE_COUNT },
  { BANK(mudaTileset), mudaTileset_TILE_ORIGIN, mudaTileset_tiles, mudaTileset_TILE_COUNT,
    BANK(enemiesMudaSprites), enemiesMudaSprites_TILE_ORIGIN, enemiesMudaSprites_tiles, enemiesMudaSprites_TILE_COUNT },
  { BANK(eastonTileset), eastonTileset_TILE_ORIGIN, eastonTileset_tiles, eastonTileset_TILE_COUNT,
    BANK(enemiesEastonSprites), enemiesEastonSprites_TILE_ORIGIN, enemiesEastonSprites_tiles, enemiesEastonSprites_TILE_COUNT },
  { BANK(chaiTileset), chaiTileset_TILE_ORIGIN, chaiTileset_tiles, chaiTileset_TILE_COUNT,
    BANK(enemiesChaiSprites), enemiesChaiSprites_TILE_ORIGIN, enemiesChaiSprites_tiles, enemiesChaiSprites_TILE_COUNT }
};

#ifdef USE_COMPRESSED_LEVELS
#include <gbdk/gbdecompress.h>
uint8_t decompression_buffer[DECOMPRESSED_PAGE_SIZE];
#endif

int current_map_tile_origin;
const unsigned char *current_map_tiles;
size_t current_map_tile_count;
size_t current_map_width;
size_t current_map_width_in_tiles;
uint8_t level_bank;

uint8_t level_lookup_bank;
const level_object *level_lookup;
size_t level_lookup_size;

uint8_t current_page = 0;

#ifdef USE_COMPRESSED_LEVELS
uint8_t cached_page_index = 0xFF;
#endif

const level levels[NB_LEVELS] = {
  {
    #ifdef GAMEBOY
    .music_bank = BANK(music_world_1),
    .music = &music_world_1,
    #endif
    .map_pages = level_1_1_map,
    .page_count = level_table_1_1_ENTRY_COUNT,
    .lookup_bank = BANK(level_1_1_lookup),
    .lookup = level_1_1_lookup,
    .lookup_size = level_1_1_lookup_ENTRY_COUNT
  },
  {
  #ifdef GAMEBOY
  .music_bank = BANK(music_world_1),
  .music = &music_world_1,
  #endif
  .map_pages = level_1_2_map,
  .page_count = level_table_1_2_ENTRY_COUNT,
  .lookup_bank = BANK(level_1_2_lookup),
  .lookup = level_1_2_lookup,
  .lookup_size = level_1_2_lookup_ENTRY_COUNT
  },
  {
  #ifdef GAMEBOY
  .music_bank = BANK(music_castle),
  .music = &music_castle,
  #endif
  .map_pages = level_1_3_map,
  .page_count = level_table_1_3_ENTRY_COUNT,
  .lookup_bank = BANK(level_1_3_lookup),
  .lookup = level_1_3_lookup,
  .lookup_size = level_1_3_lookup_ENTRY_COUNT
  },
  {
  #ifdef GAMEBOY
  .music_bank = BANK(music_world_2),
  .music = &music_world_2,
  #endif
  .map_pages = level_2_1_map,
  .page_count = level_table_2_1_ENTRY_COUNT,
  .lookup_bank = BANK(level_2_1_lookup),
  .lookup = level_2_1_lookup,
  .lookup_size = level_2_1_lookup_ENTRY_COUNT
  },
  {
  #ifdef GAMEBOY
  .music_bank = BANK(music_world_2),
  .music = &music_world_2,
  #endif
  .map_pages = level_2_2_map,
  .page_count = level_table_2_2_ENTRY_COUNT,
  .lookup_bank = BANK(level_2_2_lookup),
  .lookup = level_2_2_lookup,
  .lookup_size = level_2_2_lookup_ENTRY_COUNT
  },
  {
  #ifdef GAMEBOY
  .music_bank = BANK(music_underwater),
  .music = &music_underwater,
  #endif
  .map_pages = level_2_3_map,
  .page_count = level_table_2_3_ENTRY_COUNT,
  .lookup_bank = BANK(level_2_3_lookup),
  .lookup = level_2_3_lookup,
  .lookup_size = level_2_3_lookup_ENTRY_COUNT
  },
  {
  #ifdef GAMEBOY
  .music_bank = BANK(music_world_3),
  .music = &music_world_3,
  #endif
  .map_pages = level_3_1_map,
  .page_count = level_table_3_1_ENTRY_COUNT,
  .lookup_bank = BANK(level_3_1_lookup),
  .lookup = level_3_1_lookup,
  .lookup_size = level_3_1_lookup_ENTRY_COUNT
  },
  {
  #ifdef GAMEBOY
  .music_bank = BANK(music_castle),
  .music = &music_castle,
  #endif
  .map_pages = level_3_2_map,
  .page_count = level_table_3_2_ENTRY_COUNT,
  .lookup_bank = BANK(level_3_2_lookup),
  .lookup = level_3_2_lookup,
  .lookup_size = level_3_2_lookup_ENTRY_COUNT
  },
  {
  #ifdef GAMEBOY
  .music_bank = BANK(music_castle),
  .music = &music_castle,
  #endif
  .map_pages = level_3_3_map,
  .page_count = level_table_3_3_ENTRY_COUNT,
  .lookup_bank = BANK(level_3_3_lookup),
  .lookup = level_3_3_lookup,
  .lookup_size = level_3_3_lookup_ENTRY_COUNT
  },
  {
  #ifdef GAMEBOY
  .music_bank = BANK(music_world_4),
  .music = &music_world_4,
  #endif
  .map_pages = level_4_1_map,
  .page_count = level_table_4_1_ENTRY_COUNT,
  .lookup_bank = BANK(level_4_1_lookup),
  .lookup = level_4_1_lookup,
  .lookup_size = level_4_1_lookup_ENTRY_COUNT
  },
  {
  #ifdef GAMEBOY
  .music_bank = BANK(music_world_4),
  .music = &music_world_4,
  #endif
  .map_pages = level_4_2_map,
  .page_count = level_table_4_2_ENTRY_COUNT,
  .lookup_bank = BANK(level_4_2_lookup),
  .lookup = level_4_2_lookup,
  .lookup_size = level_4_2_lookup_ENTRY_COUNT
  },
  {
  #ifdef GAMEBOY
  .music_bank = BANK(music_underwater),
  .music = &music_underwater,
  #endif
  .map_pages = level_4_3_map,
  .page_count = level_table_4_3_ENTRY_COUNT,
  .lookup_bank = BANK(level_4_3_lookup),
  .lookup = level_4_3_lookup,
  .lookup_size = level_4_3_lookup_ENTRY_COUNT
  }
};

const level undergrounds[1] = {
  {
    #ifdef GAMEBOY
    .music_bank = BANK(music_underground),
    .music = &music_underground,
    #endif
    .map_pages = underground_0_map_pages,
    .page_count = 1,
    .lookup_bank = BANK(underground_lookup),
    .lookup = underground_0_lookup,
    .lookup_size = underground_lookup_ENTRY_COUNT
  }
};

uint8_t get_tile(uint8_t x, uint8_t y) {
  if (y >> 3 < 2 || y >> 3 > MAP_BUFFER_HEIGHT + 1) {
    return TILE_EMPTY;
  }

  uint8_t tile_x = TILE_INDEX_X(x, camera_x);
  uint8_t tile_y = TILE_INDEX_Y(y);
  uint8_t tile = map_buffer[tile_y * DEVICE_SCREEN_BUFFER_WIDTH + tile_x];

  if (current_level == 0 && tile_y == 0 && tile == GREY_BLOCK) {
    return TILE_EMPTY;
  }

  return tile;
}

bool is_tile_solid(uint8_t tile) {
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

  if (current_level <= LEVEL_WORLD1_END) {
    return ((tile == TILE_FLOOR) || (tile == TILE_FLOOR_BIS) ||
            (tile == STONE_LEFT) || (tile == STONE_RIGHT) ||
            (tile == TILED_FLOOR) || (tile == STONE_BIS_LEFT) ||
            (tile == STONE_BIS_RIGHT) || (tile == BRICK_BLOCK) || 
            (tile == GREY_BLOCK));
  } else if (current_level <= LEVEL_WORLD2_END) {
    return ((tile == BIG_BLOCK_TOP_LEFT) || (tile == BIG_BLOCK_TOP_RIGHT) ||
            (tile == BIG_BLOCK_BOTTOM_LEFT) ||
            (tile == BIG_BLOCK_BOTTOM_RIGHT) || (tile == OCEAN_FLOOR_LEFT) ||
            (tile == OCEAN_FLOOR_RIGHT) || (tile == MUDA_BRIDGE) ||
            (tile == HALF_BIG_BLOCK_TOP_LEFT) ||
            (tile == HALF_BIG_BLOCK_TOP_RIGHT));
  } else if (current_level <= LEVEL_WORLD3_END) {
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
  } else {
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
  return (current_level == LEVEL_1_2 && ((tile_left_bottom == PALM_TREE_LEFT) ||
                                 (tile_left_bottom == PALM_TREE_CENTER) ||
                                 (tile_left_bottom == PALM_TREE_RIGHT) ||
                                 (tile_right_bottom == PALM_TREE_LEFT) ||
                                 (tile_right_bottom == PALM_TREE_CENTER) ||
                                 (tile_right_bottom == PALM_TREE_RIGHT))) ||
         (current_level == LEVEL_2_1 && ((tile_left_bottom == MUDA_PLATEFORM_LEFT) ||
                                 (tile_left_bottom == MUDA_PLATEFORM_CENTER) ||
                                 (tile_left_bottom == MUDA_PLATEFORM_RIGHT) ||
                                 (tile_right_bottom == MUDA_PLATEFORM_LEFT) ||
                                 (tile_right_bottom == MUDA_PLATEFORM_CENTER) ||
                                 (tile_right_bottom == MUDA_PLATEFORM_RIGHT)));
}

bool is_coin(uint8_t tile) { 
  return tile == TILE_COIN; 
}

void on_get_coin_background(uint8_t x, uint8_t y) {
  uint8_t index_x = TILE_INDEX_X(x, camera_x);
  uint8_t index_y = TILE_INDEX_Y(y);

  map_buffer[index_y * DEVICE_SCREEN_BUFFER_WIDTH + index_x] = TILE_EMPTY;
  set_bkg_tile_xy(index_x, index_y, TILE_EMPTY);

  on_get_coin();
}

void on_break_tile(uint8_t x, uint8_t y) {
  uint8_t index_x = TILE_INDEX_X(x, camera_x);
  uint8_t index_y = TILE_INDEX_Y(y);

  map_buffer[index_y * DEVICE_SCREEN_BUFFER_WIDTH + index_x] = TILE_EMPTY;
  set_bkg_tile_xy(index_x, index_y, TILE_EMPTY);

  #ifdef GAMEBOY
  music_play_sfx(BANK(sound_destroyed), sound_destroyed, SFX_MUTE_MASK(sound_destroyed),
                 MUSIC_SFX_PRIORITY_NORMAL);
  #endif
}

#define BLOCK_BUMP_FRAMES 12
#define BLOCK_BUMP_RISE 6

static struct {
  bool active;
  uint8_t timer;
  uint8_t screen_x;
  uint8_t screen_y_base;
  uint8_t index_x;
  uint8_t index_y;
  uint8_t hw_sprite;
} block_bump_state;

void on_block_bump(uint8_t x, uint8_t y) BANKED {
  uint8_t index_x = TILE_INDEX_X(x, camera_x);
  uint8_t index_y = TILE_INDEX_Y(y);

  map_buffer[index_y * DEVICE_SCREEN_BUFFER_WIDTH + index_x] = TILE_EMPTY;
  set_bkg_tile_xy(index_x, index_y, TILE_EMPTY);

#ifdef GAMEBOY
  music_play_sfx(BANK(sound_bump), sound_bump, SFX_MUTE_MASK(sound_bump),
                 MUSIC_SFX_PRIORITY_NORMAL);

  uint8_t _saved_bank = _current_bank;
  SWITCH_ROM(BANK(commonTileset));
  set_sprite_data(90, 1, commonTileset_tiles + ((BREAKABLE_BLOCK - commonTileset_TILE_ORIGIN) * 16));
  SWITCH_ROM(_saved_bank);

  block_bump_state.active = true;
  block_bump_state.timer = 0;
  block_bump_state.screen_x = (index_x << 3) + DEVICE_SPRITE_PX_OFFSET_X - (uint8_t)camera_x;
  block_bump_state.screen_y_base = (index_y << 3) + 5 * TILE_SIZE;
  block_bump_state.index_x = index_x;
  block_bump_state.index_y = index_y;
#endif
}

void block_bump_update(void) BANKED {
  if (!block_bump_state.active) return;

  block_bump_state.timer++;
  if (block_bump_state.timer >= BLOCK_BUMP_FRAMES) {
    block_bump_state.active = false;
    hide_sprite(block_bump_state.hw_sprite);
    map_buffer[block_bump_state.index_y * DEVICE_SCREEN_BUFFER_WIDTH + block_bump_state.index_x] = BREAKABLE_BLOCK;
    set_bkg_tile_xy(block_bump_state.index_x, block_bump_state.index_y, BREAKABLE_BLOCK);
  }
}

uint8_t block_bump_draw(uint8_t base_sprite) BANKED {
  if (!block_bump_state.active) return base_sprite;

  block_bump_state.hw_sprite = base_sprite;

  int8_t y_offset;
  if (block_bump_state.timer < BLOCK_BUMP_RISE) {
    y_offset = -(block_bump_state.timer + 1) * 2;
  } else {
    y_offset = -((BLOCK_BUMP_FRAMES - 1) - block_bump_state.timer) * 2;
  }

  move_sprite(base_sprite, block_bump_state.screen_x, block_bump_state.screen_y_base + y_offset);
  set_sprite_tile(base_sprite, 90);

  return base_sprite + 1;
}

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

  #ifdef GAMEBOY
  hud_update_coins();
  hud_update_score();
  #endif
}

void on_interogation_block_hit(uint8_t x, uint8_t y) {
  uint8_t index_x = TILE_INDEX_X(x, camera_x);
  uint8_t index_y = TILE_INDEX_Y(y);

  uint8_t world_tile_x = (x + camera_x) >> 3;

  map_buffer[index_y * DEVICE_SCREEN_BUFFER_WIDTH + index_x] = TILE_EMPTIED;

  #if defined(GAMEBOY) || defined(SEGA)
  set_bkg_tile_xy(index_x, index_y, TILE_EMPTIED);
  #elif defined(NINTENDO_NES)
  set_bkg_tile_xy(index_x, index_y + 2, TILE_EMPTIED);
  #endif

  uint8_t _saved_bank = _current_bank;
  SWITCH_ROM(level_lookup_bank);

  bool lookup_found = FALSE;
  for (uint16_t i = 0; i < level_lookup_size && !lookup_found; i++) {
    level_object *obj = &level_lookup[i];
    
    if (obj->x == world_tile_x && obj->y == index_y) {
      lookup_found = TRUE;
      powerup_new((index_x << 3) << 4, (index_y << 3) << 4, obj->data.enemy.type);
    }
  }

  SWITCH_ROM(_saved_bank);

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
                  (obj->y + MARGIN_TOP) * TILE_SIZE - enemiesSprites_HEIGHT,
                  obj->data.enemy.type);
        SWITCH_ROM(level_lookup_bank);
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
      else if (obj->type == OBJECT_TYPE_PIPE_VERTICAL) {
          pipe_new((uint8_t)obj->x, (uint8_t)obj->y, PIPE_DIRECTION_VERTICAL, &obj->data.pipe);
      }
      else if (obj->type == OBJECT_TYPE_PIPE_HORIZONTAL) {
          pipe_new((uint8_t)obj->x, (uint8_t)obj->y, PIPE_DIRECTION_HORIZONTAL, &obj->data.pipe);
      }
    } else if (obj->x > col) {
      col_from = i;
      break;
    }
  }
  
  SWITCH_ROM(_saved_bank);
}

uint8_t level_load_column(uint8_t nb, level *level_to_load) NONBANKED {
  uint8_t _saved_bank = _current_bank;
  uint8_t col = 0;

  while (col < nb) {
    if (current_column_in_page == PAGE_SIZE) {
      current_column_in_page = 0;
      current_page++;
      #ifdef USE_COMPRESSED_LEVELS
      cached_page_index = 0xFF;
      #endif
    }

    if (current_page >= level_to_load->page_count) {
      SWITCH_ROM(_saved_bank);
      return col;
    }

    const banked_map_t *page_entry = level_to_load->map_pages + current_page;

    SWITCH_ROM(page_entry->bank);
    const unsigned char *current_page_data;

    #ifdef USE_COMPRESSED_LEVELS
    if (cached_page_index != current_page) {
      gb_decompress(page_entry->map, decompression_buffer);
      current_page_data = decompression_buffer;
      cached_page_index = current_page;
    } else {
      current_page_data = decompression_buffer;
    }
    #else
    current_page_data = page_entry->map;
    #endif

    for (int row = 0; row < LEVEL_HEIGHT; row++) {
      uint8_t tile = current_page_data[(row * PAGE_SIZE) + current_column_in_page];
      map_buffer[row * DEVICE_SCREEN_BUFFER_WIDTH + map_column] = tile;
      coldata[row] = tile;
    }

    #if defined(GAMEBOY)
      #define TILE_Y 0
    #elif defined(NINTENDO_NES)
      #define TILE_Y 2
    #else
      #define TILE_Y 0
    #endif
    set_bkg_tiles(map_column, TILE_Y, 1, LEVEL_HEIGHT, coldata);

    current_column_in_page++;
    col++;
    map_column = (map_column + 1) % 32;
  }

  SWITCH_ROM(_saved_bank);
  return col;
}

#ifdef STREAM_FULL_WIDTH
static bool level_load_next_column(void) NONBANKED {
  if (level_load_column(1, levels + current_level) == 0) {
    return false;
  }
  level_load_objects(world_col_loaded);
  world_col_loaded++;
  return true;
}

void level_stream_columns(void) NONBANKED {
  uint16_t target = ((camera_x + 7) >> 3) + DEVICE_SCREEN_BUFFER_WIDTH;
  while (world_col_loaded < target) {
    if (!level_load_next_column()) {
      break;
    }
  }
}
#endif

void level_set_current(void) NONBANKED {
  set_level(current_level);
  scroll_limit = DEVICE_SCREEN_PX_WIDTH_HALF;
  enemy_count = 0;
  platform_moving_count = 0;
  col_from = 0;
  hide_sprites_range(1, MAX_HARDWARE_SPRITES);
  load_current_level();
}

void load_current_level(void) NONBANKED {
  camera_x = 0;
  move_camera(camera_x);
  camera_x_upscaled = 0;
  level_end_reached = false;
  current_page = 0;
  current_column_in_page = 0;
  map_column = 0;
  level_page_x_offset = 0;
  world_col_loaded = 0;
  col_from = 0;

#ifdef USE_COMPRESSED_LEVELS
  cached_page_index = 0xFF;
#endif

  pipe_clear();

#ifdef STREAM_FULL_WIDTH
#ifdef SEGA
  HIDE_LEFT_COLUMN;
#endif
  level_stream_columns();
#else
  level_load_column(MAP_BUFFER_WIDTH, levels + current_level);
  load_col_at = COLUMN_SIZE;
#endif
}

#if defined(SEGA)
#define set_sprite_data set_sprite_native_data
#endif

void set_level(uint8_t level_index) NONBANKED {
  uint8_t world = level_index / 3;
  char major = '1' + world;
  char minor = '1' + level_index % 3;

  hud_set_level(major, minor);

  #ifdef GAMEBOY
  //EMU_printf("SET_LEVEL idx=%d music_bank=%d\n", level_index,
  //           levels[level_index].music_bank);
  music_load(levels[level_index].music_bank, levels[level_index].music);
  #endif

  uint8_t _saved_bank = _current_bank;

  current_map_width = levels[level_index].page_count * PAGE_SIZE * 8;
  current_map_width_in_tiles = levels[level_index].page_count * PAGE_SIZE;

  SWITCH_ROM(levels[level_index].lookup_bank);
  level_lookup_bank = levels[level_index].lookup_bank;
  level_lookup = levels[level_index].lookup;
  level_lookup_size = levels[level_index].lookup_size;

  const world_assets *assets = &world_assets_table[world];

  SWITCH_ROM(assets->bg_bank);
  current_map_tiles = assets->bg_tiles;
  current_map_tile_origin = assets->bg_tile_origin;
  current_map_tile_count = assets->bg_tile_count;
  set_bkg_native_data(current_map_tile_origin, current_map_tile_count, current_map_tiles);

  SWITCH_ROM(assets->enemy_bank);
  set_sprite_data(assets->enemy_tile_origin, assets->enemy_tile_count, assets->enemy_tiles);

  SWITCH_ROM(_saved_bank);
}

void move_camera(uint16_t x) NONBANKED {
#ifdef SEGA
  move_bkg(x, 224 + SCROLL_TOP_OFFSET);
#else
  move_bkg(x, SCROLL_TOP_OFFSET);
#endif
}