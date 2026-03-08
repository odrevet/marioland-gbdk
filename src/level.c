#include "level.h"
#include "coin_animated.h"
#include <gbdk/platform.h>

#include "global.h"
#include "graphics/enemies.h"
#include "level_object.h"
#include "level_tables.h"
#include "lookup_tables/lookup_table_1_1.h"
#include "lookup_tables/lookup_table_1_2.h"
#include "lookup_tables/lookup_table_1_3.h"
#include "lookup_tables/lookup_table_2_1.h"
#include "lookup_tables/lookup_table_2_2.h"
#include "lookup_tables/lookup_table_2_3.h"
#include "lookup_tables/lookup_table_3_1.h"
#include "lookup_tables/lookup_table_3_2.h"
#include "lookup_tables/lookup_table_3_3.h"
#include "lookup_tables/lookup_table_4_1.h"
#include "lookup_tables/lookup_table_4_2.h"
#include "lookup_tables/lookup_table_4_3.h"
#include "lookup_tables/lookup_table_underground.h"

#ifdef GAMEBOY
#include "musics/musics.h"
#endif

#include "platforms.h"
#include "player.h"
#include <stdint.h>

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

int current_map_tile_origin;
const unsigned char *current_map_tiles;
size_t current_map_tile_count;
size_t current_map_width;
size_t current_map_width_in_tiles;
uint8_t level_bank;

uint8_t current_page = 0;
uint16_t col_from = 0;
uint32_t level_page_loaded_cols = 0;

const level *current_level_ptr = NULL;

#ifdef USE_COMPRESSED_LEVELS
#include <gbdk/gbdecompress.h>
uint8_t decompression_buffer[DECOMPRESSED_PAGE_SIZE];
uint8_t cached_page_index = 0xFF;
#endif

const level levels[NB_LEVELS] = {
    {
        .major = '1', .minor = '1',
        #ifdef GAMEBOY
        .music_bank = BANK(music_overworld), .music = &music_overworld,
        #endif
        .map_pages = level_1_1_map, .page_count = level_table_1_1_ENTRY_COUNT,
        .map_tiles_bank = BANK(birabuto), .map_tile_origin = birabuto_TILE_ORIGIN,
        .map_tiles = birabuto_tiles, .map_tiles_count = birabuto_TILE_COUNT,
        .map_width = level_table_1_1_ENTRY_COUNT * PAGE_SIZE * 8,
        .map_width_in_tiles = level_table_1_1_ENTRY_COUNT * PAGE_SIZE,
        .page_lookups = level_1_1_lookup,
        .page_lookups_bank = BANK(level_1_1_lookup),
    },
    {
        .major = '1', .minor = '2',
        #ifdef GAMEBOY
        .music_bank = BANK(music_overworld), .music = &music_overworld,
        #endif
        .map_pages = level_1_2_map, .page_count = level_table_1_2_ENTRY_COUNT,
        .map_tiles_bank = BANK(birabuto), .map_tile_origin = birabuto_TILE_ORIGIN,
        .map_tiles = birabuto_tiles, .map_tiles_count = birabuto_TILE_COUNT,
        .map_width = level_table_1_2_ENTRY_COUNT * PAGE_SIZE * 8,
        .map_width_in_tiles = level_table_1_2_ENTRY_COUNT * PAGE_SIZE,
        .page_lookups = level_1_2_lookup,
        .page_lookups_bank = BANK(level_1_2_lookup),
    },
    {
        .major = '1', .minor = '3',
        #ifdef GAMEBOY
        .music_bank = BANK(music_castle), .music = &music_castle,
        #endif
        .map_pages = level_1_3_map, .page_count = level_table_1_3_ENTRY_COUNT,
        .map_tiles_bank = BANK(birabuto), .map_tile_origin = birabuto_TILE_ORIGIN,
        .map_tiles = birabuto_tiles, .map_tiles_count = birabuto_TILE_COUNT,
        .map_width = level_table_1_3_ENTRY_COUNT * PAGE_SIZE * 8,
        .map_width_in_tiles = level_table_1_3_ENTRY_COUNT * PAGE_SIZE,
        .page_lookups = level_1_3_lookup,
        .page_lookups_bank = BANK(level_1_3_lookup),
    },
    {
        .major = '2', .minor = '1',
        #ifdef GAMEBOY
        .music_bank = BANK(music_overworld), .music = &music_overworld,
        #endif
        .map_pages = level_2_1_map, .page_count = level_table_2_1_ENTRY_COUNT,
        .map_tiles_bank = BANK(muda), .map_tile_origin = muda_TILE_ORIGIN,
        .map_tiles = muda_tiles, .map_tiles_count = muda_TILE_COUNT,
        .map_width = level_table_2_1_ENTRY_COUNT * PAGE_SIZE * 8,
        .map_width_in_tiles = level_table_2_1_ENTRY_COUNT * PAGE_SIZE,
        .page_lookups = level_2_1_lookup,
        .page_lookups_bank = BANK(level_2_1_lookup),
    },
    {
        .major = '2', .minor = '2',
        #ifdef GAMEBOY
        .music_bank = BANK(music_overworld), .music = &music_overworld,
        #endif
        .map_pages = level_2_2_map, .page_count = level_table_2_2_ENTRY_COUNT,
        .map_tiles_bank = BANK(muda), .map_tile_origin = muda_TILE_ORIGIN,
        .map_tiles = muda_tiles, .map_tiles_count = muda_TILE_COUNT,
        .map_width = level_table_2_2_ENTRY_COUNT * PAGE_SIZE * 8,
        .map_width_in_tiles = level_table_2_2_ENTRY_COUNT * PAGE_SIZE,
        .page_lookups = level_2_2_lookup,
        .page_lookups_bank = BANK(level_2_2_lookup),
    },
    {
        .major = '2', .minor = '3',
        #ifdef GAMEBOY
        .music_bank = BANK(music_underwater), .music = &music_underwater,
        #endif
        .map_pages = level_2_3_map, .page_count = level_table_2_3_ENTRY_COUNT,
        .map_tiles_bank = BANK(muda), .map_tile_origin = muda_TILE_ORIGIN,
        .map_tiles = muda_tiles, .map_tiles_count = muda_TILE_COUNT,
        .map_width = level_table_2_3_ENTRY_COUNT * PAGE_SIZE * 8,
        .map_width_in_tiles = level_table_2_3_ENTRY_COUNT * PAGE_SIZE,
        .page_lookups = level_2_3_lookup,
        .page_lookups_bank = BANK(level_2_3_lookup),
    },
    {
        .major = '3', .minor = '1',
        #ifdef GAMEBOY
        .music_bank = BANK(music_overworld), .music = &music_overworld,
        #endif
        .map_pages = level_3_1_map, .page_count = level_table_3_1_ENTRY_COUNT,
        .map_tiles_bank = BANK(easton), .map_tile_origin = easton_TILE_ORIGIN,
        .map_tiles = easton_tiles, .map_tiles_count = easton_TILE_COUNT,
        .map_width = level_table_3_1_ENTRY_COUNT * PAGE_SIZE * 8,
        .map_width_in_tiles = level_table_3_1_ENTRY_COUNT * PAGE_SIZE,
        .page_lookups = level_3_1_lookup,
        .page_lookups_bank = BANK(level_3_1_lookup),
    },
    {
        .major = '3', .minor = '2',
        #ifdef GAMEBOY
        .music_bank = BANK(music_overworld), .music = &music_overworld,
        #endif
        .map_pages = level_3_2_map, .page_count = level_table_3_2_ENTRY_COUNT,
        .map_tiles_bank = BANK(easton), .map_tile_origin = easton_TILE_ORIGIN,
        .map_tiles = easton_tiles, .map_tiles_count = easton_TILE_COUNT,
        .map_width = level_table_3_2_ENTRY_COUNT * PAGE_SIZE * 8,
        .map_width_in_tiles = level_table_3_2_ENTRY_COUNT * PAGE_SIZE,
        .page_lookups = level_3_2_lookup,
        .page_lookups_bank = BANK(level_3_2_lookup),
    },
    {
        .major = '3', .minor = '3',
        #ifdef GAMEBOY
        .music_bank = BANK(music_castle), .music = &music_castle,
        #endif
        .map_pages = level_3_3_map, .page_count = level_table_3_3_ENTRY_COUNT,
        .map_tiles_bank = BANK(easton), .map_tile_origin = easton_TILE_ORIGIN,
        .map_tiles = easton_tiles, .map_tiles_count = easton_TILE_COUNT,
        .map_width = level_table_3_3_ENTRY_COUNT * PAGE_SIZE * 8,
        .map_width_in_tiles = level_table_3_3_ENTRY_COUNT * PAGE_SIZE,
        .page_lookups = level_3_3_lookup,
        .page_lookups_bank = BANK(level_3_3_lookup),
    },
    {
        .major = '4', .minor = '1',
        #ifdef GAMEBOY
        .music_bank = BANK(music_overworld), .music = &music_overworld,
        #endif
        .map_pages = level_4_1_map, .page_count = level_table_4_1_ENTRY_COUNT,
        .map_tiles_bank = BANK(chai), .map_tile_origin = chai_TILE_ORIGIN,
        .map_tiles = chai_tiles, .map_tiles_count = chai_TILE_COUNT,
        .map_width = level_table_4_1_ENTRY_COUNT * PAGE_SIZE * 8,
        .map_width_in_tiles = level_table_4_1_ENTRY_COUNT * PAGE_SIZE,
        .page_lookups = level_4_1_lookup,
        .page_lookups_bank = BANK(level_4_1_lookup),
    },
    {
        .major = '4', .minor = '2',
        #ifdef GAMEBOY
        .music_bank = BANK(music_overworld), .music = &music_overworld,
        #endif
        .map_pages = level_4_2_map, .page_count = level_table_4_2_ENTRY_COUNT,
        .map_tiles_bank = BANK(chai), .map_tile_origin = chai_TILE_ORIGIN,
        .map_tiles = chai_tiles, .map_tiles_count = chai_TILE_COUNT,
        .map_width = level_table_4_2_ENTRY_COUNT * PAGE_SIZE * 8,
        .map_width_in_tiles = level_table_4_2_ENTRY_COUNT * PAGE_SIZE,
        .page_lookups = level_4_2_lookup,
        .page_lookups_bank = BANK(level_4_2_lookup),
    },
    {
        .major = '4', .minor = '3',
        #ifdef GAMEBOY
        .music_bank = BANK(music_underwater), .music = &music_underwater,
        #endif
        .map_pages = level_4_3_map, .page_count = level_table_4_3_ENTRY_COUNT,
        .map_tiles_bank = BANK(chai), .map_tile_origin = chai_TILE_ORIGIN,
        .map_tiles = chai_tiles, .map_tiles_count = chai_TILE_COUNT,
        .map_width = level_table_4_3_ENTRY_COUNT * PAGE_SIZE * 8,
        .map_width_in_tiles = level_table_4_3_ENTRY_COUNT * PAGE_SIZE,
        .page_lookups = level_4_3_lookup,
        .page_lookups_bank = BANK(level_4_3_lookup),
    },
};

const level undergrounds[1] = {
    {
        .major = '1', .minor = '1',
        #ifdef GAMEBOY
        .music_bank = BANK(music_underground), .music = &music_underground,
        #endif
        .map_pages = underground_0_map_pages, .page_count = 1,
        .map_tiles_bank = NULL, .map_tile_origin = NULL,
        .map_tiles = NULL, .map_tiles_count = 0,
        .map_width = 1 * PAGE_SIZE * 8,
        .map_width_in_tiles = 1 * PAGE_SIZE,
        .page_lookups = underground_0_lookup,
        .page_lookups_bank = BANK(underground_lookup),
    }
};

uint8_t get_tile(uint8_t x, uint8_t y) {
    if (y >> 3 < 2 || y >> 3 > MAP_BUFFER_HEIGHT + 1) return TILE_EMPTY;
    uint8_t tile_x = TILE_INDEX_X(x, camera_x);
    uint8_t tile_y = TILE_INDEX_Y(y);
    return map_buffer[tile_y * DEVICE_SCREEN_BUFFER_WIDTH + tile_x];
}

bool is_tile_solid(uint8_t tile) {
    switch (tile) {
        case TILE_INTEROGATION_BLOCK: case BREAKABLE_BLOCK: case TILE_UNBREAKABLE:
        case PIPE_TOP_LEFT: case PIPE_TOP_RIGHT: case PIPE_CENTER_LEFT:
        case PIPE_CENTER_RIGHT: case PIPE_HORIZONTAL_1: case PIPE_HORIZONTAL_2:
        case PIPE_HORIZONTAL_3: case PIPE_HORIZONTAL_4: case PIPE_HORIZONTAL_5:
        case PIPE_HORIZONTAL_6: case PIPE_HORIZONTAL_7: case PIPE_HORIZONTAL_8:
        case TILE_EMPTIED: case METAL_GATE: case METAL_BLOCK_LEFT: case METAL_BLOCK_RIGHT:
            return true;
    }
    if (current_level >= 0 && current_level <= 2) {
        return ((tile == TILE_FLOOR) || (tile == TILE_FLOOR_BIS) ||
                (tile == STONE_LEFT) || (tile == STONE_RIGHT) ||
                (tile == TILED_FLOOR) || (tile == STONE_BIS_LEFT) ||
                (tile == STONE_BIS_RIGHT) || (tile == BRICK_BLOCK) ||
                (tile == GREY_BLOCK));
    } else if (current_level >= 3 && current_level <= 5) {
        return ((tile == BIG_BLOCK_TOP_LEFT) || (tile == BIG_BLOCK_TOP_RIGHT) ||
                (tile == BIG_BLOCK_BOTTOM_LEFT) || (tile == BIG_BLOCK_BOTTOM_RIGHT) ||
                (tile == OCEAN_FLOOR_LEFT) || (tile == OCEAN_FLOOR_RIGHT) ||
                (tile == MUDA_BRIDGE) || (tile == HALF_BIG_BLOCK_TOP_LEFT) ||
                (tile == HALF_BIG_BLOCK_TOP_RIGHT));
    } else if (current_level >= 6 && current_level <= 8) {
        return ((tile == EASTON_FLOOR_1) || (tile == EASTON_FLOOR_2) ||
                (tile == EASTON_STONE_PLATEFORM_1) || (tile == EASTON_STONE_PLATEFORM_2) ||
                (tile == EASTON_STONE_PLATEFORM_3) || (tile == EASTON_STONE_PLATEFORM_4) ||
                (tile == EASTON_STONE_PLATEFORM_BOTTOM) ||
                (tile == EASTON_LARGE_BLACK_BLOCK_TOP_LEFT) ||
                (tile == EASTON_LARGE_BLACK_BLOCK_TOP_RIGHT) ||
                (tile == EASTON_LARGE_BLACK_BLOCK_BOTOM_LEFT) ||
                (tile == EASTON_LARGE_BLACK_BLOCK_BOTTOM_RIGHT) ||
                (tile == EASTON_BLOCK) || (tile == EASTON_STONE_PLATEFORM_LEFT) ||
                (tile == EASTON_STONE_PLATEFORM_RIGHT));
    } else if (current_level >= 9 && current_level <= 12) {
        return ((tile == CHAI_FLOOR_LEFT) || (tile == CHAI_FLOOR_MIDDLE_1) ||
                (tile == CHAI_FLOOR_MIDDLE_2) || (tile == CHAI_FLOOR_MIDDLE_RIGHT) ||
                (tile == CHAI_GREY_BLOCK) || (tile == CHAI_PIPE) ||
                (tile == CHAI_PIPE_LEFT) || (tile == CHAI_PIPE_RIGHT) ||
                (tile == CHAI_PIPE_BOTTOM_LEFT) || (tile == CHAI_PIPE_BOTTOM_RIGHT) ||
                (tile == CHAI_BLOCK) || (tile == CHAI_BRICK_BLOCK) ||
                (tile == CHAI_BLACK_BLOCK_LEFT) || (tile == CHAI_BLACK_BLOCK_RIGHT) ||
                (tile == CHAI_FIRE_BLOCK));
    }
    return false;
}

bool is_tile_passthought(uint8_t tile_left_bottom, uint8_t tile_right_bottom) {
    return (current_level == 1 &&
            ((tile_left_bottom == PALM_TREE_LEFT) || (tile_left_bottom == PALM_TREE_CENTER) ||
             (tile_left_bottom == PALM_TREE_RIGHT) || (tile_right_bottom == PALM_TREE_LEFT) ||
             (tile_right_bottom == PALM_TREE_CENTER) || (tile_right_bottom == PALM_TREE_RIGHT))) ||
           (current_level == 3 &&
            ((tile_left_bottom == MUDA_PLATEFORM_LEFT) || (tile_left_bottom == MUDA_PLATEFORM_CENTER) ||
             (tile_left_bottom == MUDA_PLATEFORM_RIGHT) || (tile_right_bottom == MUDA_PLATEFORM_LEFT) ||
             (tile_right_bottom == MUDA_PLATEFORM_CENTER) || (tile_right_bottom == MUDA_PLATEFORM_RIGHT)));
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

void on_get_coin() {
    #ifdef GAMEBOY
    music_play_sfx(BANK(sound_coin), sound_coin, SFX_MUTE_MASK(sound_coin), MUSIC_SFX_PRIORITY_NORMAL);
    #endif
    coins++;
    score += 10;
    if (coins == 100) {
        lives++;
        hud_update_lives();
        coins = 0;
        #ifdef GAMEBOY
        music_play_sfx(BANK(sound_oneup), sound_oneup, SFX_MUTE_MASK(sound_oneup), MUSIC_SFX_PRIORITY_NORMAL);
        #endif
    }
    hud_update_coins();
    hud_update_score();
}

void on_interogation_block_hit(uint8_t x, uint8_t y) {
    uint8_t index_x = TILE_INDEX_X(x, camera_x);
    uint8_t index_y = TILE_INDEX_Y(y);
    uint8_t page_local_x = ((x + camera_x) >> 3) - (current_page * PAGE_SIZE);

    map_buffer[index_y * DEVICE_SCREEN_BUFFER_WIDTH + index_x] = TILE_EMPTIED;
    #if defined(GAMEBOY)
    set_bkg_tile_xy(index_x, index_y, TILE_EMPTIED);
    #elif defined(NINTENDO_NES)
    set_bkg_tile_xy(index_x, index_y + 2, TILE_EMPTIED);
    #endif

    uint8_t _saved_bank = _current_bank;

    // Switch to page_lookups_bank first to safely read the page_lookup_t entry
    SWITCH_ROM(current_level_ptr->page_lookups_bank);
    const page_lookup_t *page_lk = &current_level_ptr->page_lookups[current_page];
    uint8_t count     = page_lk->count;
    uint8_t obj_bank  = page_lk->bank;
    const level_object *objects = page_lk->objects;

    bool lookup_found = FALSE;

    if (count > 0) {
        SWITCH_ROM(obj_bank);
        for (uint8_t i = 0; i < count && !lookup_found; i++) {
            const level_object *obj = &objects[i];
            if (obj->x == page_local_x && obj->y == index_y) {
                lookup_found = TRUE;
                uint8_t powerup_type = obj->data.enemy.type;
                SWITCH_ROM(_saved_bank);
                powerup_new((index_x << 3) << 4, (index_y << 3) << 4, powerup_type);
            }
        }
    }

    SWITCH_ROM(_saved_bank);

    if (!lookup_found) {
        on_get_coin();
        coin_animated_new(index_x, index_y);
    }
}

#include <gbdk/emu_debug.h>

void level_load_objects(uint8_t col) NONBANKED {
    if (!current_level_ptr || current_page >= current_level_ptr->page_count) return;

    if (level_page_loaded_cols & (1UL << col)) return;
    level_page_loaded_cols |= (1UL << col);

    uint8_t _saved_bank = _current_bank;

    // Switch to page_lookups_bank first to safely read the page_lookup_t entry
    SWITCH_ROM(current_level_ptr->page_lookups_bank);
    const page_lookup_t *page_lk = &current_level_ptr->page_lookups[current_page];
    uint8_t count    = page_lk->count;
    uint8_t obj_bank = page_lk->bank;
    const level_object *objects = page_lk->objects;

    EMU_printf("load_objects col=%d page=%d count=%d\n", col, current_page, count);

    if (count == 0) {
        SWITCH_ROM(_saved_bank);
        return;
    }

    SWITCH_ROM(obj_bank);

    for (uint8_t i = 0; i < count; i++) {
        const level_object *obj = &objects[i];
        if (obj->x == col) {
            uint16_t world_x  = (current_page * PAGE_SIZE + col) * TILE_SIZE;
            uint8_t  obj_type = obj->type;
            uint8_t  obj_y    = obj->y;

            if (obj_type == OBJECT_TYPE_ENEMY) {
                uint8_t enemy_type = obj->data.enemy.type;
                SWITCH_ROM(_saved_bank);
                enemy_new(world_x, (obj_y + MARGIN_TOP) * TILE_SIZE - enemies_HEIGHT, enemy_type);
                EMU_printf("ENEMY NEW X=%d Y=%d\n", world_x / TILE_SIZE, obj_y);
                SWITCH_ROM(obj_bank);
            } else if (obj_type == OBJECT_TYPE_PLATFORM_MOVING) {
                uint8_t direction = obj->data.platform_moving.platform_direction;
                uint8_t range     = obj->data.platform_moving.range;
                uint8_t width     = obj->data.platform_moving.width;
                SWITCH_ROM(_saved_bank);
                platform_moving_new(world_x, (obj_y + MARGIN_TOP) * TILE_SIZE, direction, range, width);
                SWITCH_ROM(obj_bank);
            } else if (obj_type == OBJECT_TYPE_PLATFORM_FALLING) {
                SWITCH_ROM(_saved_bank);
                platform_falling_new(world_x, (obj_y + MARGIN_TOP) * TILE_SIZE);
                SWITCH_ROM(obj_bank);
            }
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
            level_page_loaded_cols = 0;
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
    move_bkg(0, -16);
    camera_x_upscaled = 0;
    level_end_reached = false;
    current_page = 0;
    current_column_in_page = 0;
    map_column = 0;
    current_level_ptr = levels + current_level;
    level_page_loaded_cols = 0;

    #ifdef USE_COMPRESSED_LEVELS
    cached_page_index = 0xFF;
    #endif

    level_load_column(MAP_BUFFER_WIDTH, levels + current_level);
    load_col_at = COLUMN_SIZE;
}

void set_level(uint8_t level_index) NONBANKED {
    hud_set_level(levels[level_index].major, levels[level_index].minor);

    #ifdef GAMEBOY
    music_load(levels[level_index].music_bank, levels[level_index].music);
    #endif

    uint8_t _saved_bank = _current_bank;

    SWITCH_ROM(levels[level_index].map_tiles_bank);
    current_map_tiles = levels[level_index].map_tiles;
    current_map_tile_origin = levels[level_index].map_tile_origin;
    current_map_tile_count = levels[level_index].map_tiles_count;
    set_bkg_data(current_map_tile_origin, current_map_tile_count, current_map_tiles);

    current_map_width = levels[level_index].map_width;
    current_map_width_in_tiles = levels[level_index].map_width_in_tiles;

    SWITCH_ROM(_saved_bank);
}