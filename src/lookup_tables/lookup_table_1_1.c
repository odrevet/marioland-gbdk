#pragma bank 255
#include "lookup_table_1_1.h"
BANKREF(level_1_1_lookup)

static const level_object level_1_1_page_00_lookup[1] = {{0}};

static const level_object level_1_1_page_01_lookup[] = {
    {.x = 2,  .y = 9,  .type = OBJECT_TYPE_POWERUP, .data.enemy = {.type = POWERUP_MUSHROOM}},
    {.x = 3,  .y = 13, .type = OBJECT_TYPE_ENEMY,   .data.enemy = {.type = ENEMY_GOOMBO}},
};

static const level_object level_1_1_page_02_lookup[] = {
    {.x = 1,  .y = 12, .type = OBJECT_TYPE_PIPE_VERTICAL,
     .data.pipe = {.destination_level = undergrounds + 0,
                   .destination_page = 0,
                   .destination_x = 2,
                   .destination_y = 2}},
};

static const level_object level_1_1_page_03_lookup[] = {
    {.x = 6,  .y = 10, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
};

static const level_object level_1_1_page_04_lookup[] = {
    {.x = 0,  .y = 4,  .type = OBJECT_TYPE_ENEMY,   .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 2,  .y = 4,  .type = OBJECT_TYPE_ENEMY,   .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 15, .y = 6,  .type = OBJECT_TYPE_POWERUP, .data.enemy = {.type = POWERUP_MUSHROOM}},
};

static const level_object level_1_1_page_05_lookup[] = {
    {.x = 17, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
};

static const level_object level_1_1_page_06_lookup[1] = {{0}};

static const level_object level_1_1_page_07_lookup[] = {
    {.x = 16, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
};

static const level_object level_1_1_page_08_lookup[] = {
    {.x = 6,  .y = 13, .type = OBJECT_TYPE_ENEMY,   .data.enemy = {.type = ENEMY_FLY}},
    {.x = 9,  .y = 13, .type = OBJECT_TYPE_ENEMY,   .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 14, .y = 6,  .type = OBJECT_TYPE_POWERUP, .data.enemy = {.type = POWERUP_STAR}},
};

static const level_object level_1_1_page_09_lookup[] = {
    {.x = 6,  .y = 10, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 15, .y = 10, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
};

static const level_object level_1_1_page_10_lookup[] = {
    {.x = 5,  .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 10, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
};

static const level_object level_1_1_page_11_lookup[] = {
    {.x = 14, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_FLY}},
};

static const level_object level_1_1_page_12_lookup[] = {
    {.x = 5,  .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_FLY}},
};

static const level_object level_1_1_page_13_lookup[1] = {{0}};

static const level_object level_1_1_page_14_lookup[] = {
    {.x = 1, .y = 3, .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
    {.x = 3, .y = 1, .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_HORIZONTAL}},
};

const page_lookup_t level_1_1_lookup[] = {
    {level_1_1_page_00_lookup, BANK(level_1_1_lookup), 0},
    {level_1_1_page_01_lookup, BANK(level_1_1_lookup), 2},
    {level_1_1_page_02_lookup, BANK(level_1_1_lookup), 1},
    {level_1_1_page_03_lookup, BANK(level_1_1_lookup), 1},
    {level_1_1_page_04_lookup, BANK(level_1_1_lookup), 3},
    {level_1_1_page_05_lookup, BANK(level_1_1_lookup), 1},
    {level_1_1_page_06_lookup, BANK(level_1_1_lookup), 0},
    {level_1_1_page_07_lookup, BANK(level_1_1_lookup), 1},
    {level_1_1_page_08_lookup, BANK(level_1_1_lookup), 3},
    {level_1_1_page_09_lookup, BANK(level_1_1_lookup), 2},
    {level_1_1_page_10_lookup, BANK(level_1_1_lookup), 2},
    {level_1_1_page_11_lookup, BANK(level_1_1_lookup), 1},
    {level_1_1_page_12_lookup, BANK(level_1_1_lookup), 1},
    {level_1_1_page_13_lookup, BANK(level_1_1_lookup), 0},
    {level_1_1_page_14_lookup, BANK(level_1_1_lookup), 2},
};