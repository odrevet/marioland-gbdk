#pragma bank 255
#include "lookup_table_4_1.h"
BANKREF(level_4_1_lookup)

static const level_object level_4_1_page_00_lookup[] = {{0}};
static const level_object level_4_1_page_01_lookup[] = {
    {.x = 11, .y = 11, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 15, .y = 14, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
};
static const level_object level_4_1_page_02_lookup[] = {
    {.x = 10, .y = 14, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 15, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PIONPI}},
};
static const level_object level_4_1_page_03_lookup[] = {
    {.x = 3,  .y = 5,  .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
    {.x = 9,  .y = 4,  .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
};
static const level_object level_4_1_page_04_lookup[] = {
    {.x = 10, .y = 14, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BULLET}},
    {.x = 15, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PIONPI}},
};
static const level_object level_4_1_page_05_lookup[] = {
    {.x = 13, .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 18, .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PIONPI}},
};
static const level_object level_4_1_page_06_lookup[] = {
    {.x = 9,  .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PIONPI}},
    {.x = 10, .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 14, .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
};
static const level_object level_4_1_page_07_lookup[] = {
    {.x = 7,  .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PIONPI}},
    {.x = 10, .y = 14, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 14, .y = 9,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PIONPI}},
};
static const level_object level_4_1_page_08_lookup[] = {
    {.x = 6,  .y = 14, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 8,  .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 11, .y = 10, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BULLET}},
};
static const level_object level_4_1_page_09_lookup[] = {
    {.x = 2,  .y = 11, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 8,  .y = 8,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PIONPI}},
    {.x = 9,  .y = 8,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 16, .y = 10, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
};
static const level_object level_4_1_page_10_lookup[] = {
    {.x = 0,  .y = 7,  .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
    {.x = 9,  .y = 12, .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
};
static const level_object level_4_1_page_11_lookup[] = {
    {.x = 3,  .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 7,  .y = 11, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 11, .y = 11, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 15, .y = 14, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
};
static const level_object level_4_1_page_12_lookup[] = {
    {.x = 3,  .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BULLET}},
    {.x = 7,  .y = 11, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 10, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
};
static const level_object level_4_1_page_13_lookup[] = {{0}};
static const level_object level_4_1_page_14_lookup[] = {
    {.x = 19, .y = 3,  .type = OBJECT_TYPE_PLATFORM_FALLING},
};
static const level_object level_4_1_page_15_lookup[] = {
    {.x = 0,  .y = 3,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 4,  .y = 3,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 5,  .y = 3,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 8,  .y = 4,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 9,  .y = 4,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 14, .y = 5,  .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
};
static const level_object level_4_1_page_16_lookup[] = {
    {.x = 4,  .y = 14, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BULLET}},
    {.x = 16, .y = 8,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PIONPI}},
};
static const level_object level_4_1_page_17_lookup[] = {
    {.x = 6,  .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PIONPI}},
    {.x = 14, .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 16, .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PIONPI}},
    {.x = 18, .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
};
static const level_object level_4_1_page_18_lookup[] = {
    {.x = 0,  .y = 6,  .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
};
static const level_object level_4_1_page_19_lookup[] = {
    {.x = 9,  .y = 14, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BULLET}},
    {.x = 13, .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BULLET}},
    {.x = 16, .y = 8,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 17, .y = 6,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BULLET}},
};
static const level_object level_4_1_page_20_lookup[] = {
    {.x = 15, .y = 11, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PIONPI}},
    {.x = 15, .y = 6,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PIONPI}},
    {.x = 15, .y = 3,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PIONPI}},
};
static const level_object level_4_1_page_21_lookup[] = {
    {.x = 11, .y = 14, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BULLET}},
    {.x = 13, .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BULLET}},
    {.x = 15, .y = 9,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BULLET}},
};
static const level_object level_4_1_page_22_lookup[] = {
    {.x = 0,  .y = 1,  .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
};

const page_lookup_t level_4_1_lookup[] = {
    {level_4_1_page_00_lookup, BANK(level_4_1_lookup), 0},
    {level_4_1_page_01_lookup, BANK(level_4_1_lookup), 2},
    {level_4_1_page_02_lookup, BANK(level_4_1_lookup), 2},
    {level_4_1_page_03_lookup, BANK(level_4_1_lookup), 2},
    {level_4_1_page_04_lookup, BANK(level_4_1_lookup), 2},
    {level_4_1_page_05_lookup, BANK(level_4_1_lookup), 2},
    {level_4_1_page_06_lookup, BANK(level_4_1_lookup), 3},
    {level_4_1_page_07_lookup, BANK(level_4_1_lookup), 3},
    {level_4_1_page_08_lookup, BANK(level_4_1_lookup), 3},
    {level_4_1_page_09_lookup, BANK(level_4_1_lookup), 4},
    {level_4_1_page_10_lookup, BANK(level_4_1_lookup), 2},
    {level_4_1_page_11_lookup, BANK(level_4_1_lookup), 4},
    {level_4_1_page_12_lookup, BANK(level_4_1_lookup), 3},
    {level_4_1_page_13_lookup, BANK(level_4_1_lookup), 0},
    {level_4_1_page_14_lookup, BANK(level_4_1_lookup), 1},
    {level_4_1_page_15_lookup, BANK(level_4_1_lookup), 6},
    {level_4_1_page_16_lookup, BANK(level_4_1_lookup), 2},
    {level_4_1_page_17_lookup, BANK(level_4_1_lookup), 4},
    {level_4_1_page_18_lookup, BANK(level_4_1_lookup), 1},
    {level_4_1_page_19_lookup, BANK(level_4_1_lookup), 4},
    {level_4_1_page_20_lookup, BANK(level_4_1_lookup), 3},
    {level_4_1_page_21_lookup, BANK(level_4_1_lookup), 3},
    {level_4_1_page_22_lookup, BANK(level_4_1_lookup), 1},
};