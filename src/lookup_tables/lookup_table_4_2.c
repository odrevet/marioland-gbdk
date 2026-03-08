#pragma bank 255
#include "lookup_table_4_2.h"
BANKREF(level_4_2_lookup)

static const level_object level_4_2_page_00_lookup[] = {{0}};
static const level_object level_4_2_page_01_lookup[] = {
    {.x = 9,  .y = 10, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
};
static const level_object level_4_2_page_02_lookup[] = {
    {.x = 1,  .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 9,  .y = 10, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 12, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PONPON}},
};
static const level_object level_4_2_page_03_lookup[] = {
    {.x = 2,  .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BULLET}},
    {.x = 10, .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
};
static const level_object level_4_2_page_04_lookup[] = {
    {.x = 18, .y = 9,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_NYOLOLIN}},
};
static const level_object level_4_2_page_05_lookup[] = {
    {.x = 5,  .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 10, .y = 7,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 11, .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 17, .y = 11, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
};
static const level_object level_4_2_page_06_lookup[] = {
    {.x = 5,  .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 11, .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 14, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BULLET}},
    {.x = 17, .y = 11, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
};
static const level_object level_4_2_page_07_lookup[] = {
    {.x = 3,  .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 4,  .y = 7,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 12, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PONPON}},
};
static const level_object level_4_2_page_08_lookup[] = {
    {.x = 8,  .y = 9,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 19, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
};
static const level_object level_4_2_page_09_lookup[] = {{0}};
static const level_object level_4_2_page_10_lookup[] = {
    {.x = 9,  .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
};
static const level_object level_4_2_page_11_lookup[] = {
    {.x = 3,  .y = 11, .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
    {.x = 6,  .y = 9,  .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
};
static const level_object level_4_2_page_12_lookup[] = {
    {.x = 3,  .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
};
static const level_object level_4_2_page_13_lookup[] = {
    {.x = 2,  .y = 12, .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
    {.x = 7,  .y = 11, .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
};
static const level_object level_4_2_page_14_lookup[] = {
    {.x = 5,  .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 10, .y = 10, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PIONPI}},
    {.x = 18, .y = 8,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
};
static const level_object level_4_2_page_15_lookup[] = {
    {.x = 15, .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
};
static const level_object level_4_2_page_16_lookup[] = {
    {.x = 6,  .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PIONPI}},
    {.x = 11, .y = 10, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 18, .y = 8,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
};
static const level_object level_4_2_page_17_lookup[] = {{0}};
static const level_object level_4_2_page_18_lookup[] = {
    {.x = 2,  .y = 11, .type = OBJECT_TYPE_ENEMY,           .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 6,  .y = 4,  .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
    {.x = 16, .y = 4,  .type = OBJECT_TYPE_PLATFORM_FALLING},
};
static const level_object level_4_2_page_19_lookup[] = {
    {.x = 2,  .y = 12, .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 4,  .y = 9,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 5,  .y = 6,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 6,  .y = 4,  .type = OBJECT_TYPE_PLATFORM_FALLING},
};

const page_lookup_t level_4_2_lookup[] = {
    {level_4_2_page_00_lookup, BANK(level_4_2_lookup), 0},
    {level_4_2_page_01_lookup, BANK(level_4_2_lookup), 1},
    {level_4_2_page_02_lookup, BANK(level_4_2_lookup), 3},
    {level_4_2_page_03_lookup, BANK(level_4_2_lookup), 2},
    {level_4_2_page_04_lookup, BANK(level_4_2_lookup), 1},
    {level_4_2_page_05_lookup, BANK(level_4_2_lookup), 4},
    {level_4_2_page_06_lookup, BANK(level_4_2_lookup), 4},
    {level_4_2_page_07_lookup, BANK(level_4_2_lookup), 3},
    {level_4_2_page_08_lookup, BANK(level_4_2_lookup), 2},
    {level_4_2_page_09_lookup, BANK(level_4_2_lookup), 0},
    {level_4_2_page_10_lookup, BANK(level_4_2_lookup), 1},
    {level_4_2_page_11_lookup, BANK(level_4_2_lookup), 2},
    {level_4_2_page_12_lookup, BANK(level_4_2_lookup), 1},
    {level_4_2_page_13_lookup, BANK(level_4_2_lookup), 2},
    {level_4_2_page_14_lookup, BANK(level_4_2_lookup), 3},
    {level_4_2_page_15_lookup, BANK(level_4_2_lookup), 1},
    {level_4_2_page_16_lookup, BANK(level_4_2_lookup), 3},
    {level_4_2_page_17_lookup, BANK(level_4_2_lookup), 0},
    {level_4_2_page_18_lookup, BANK(level_4_2_lookup), 3},
    {level_4_2_page_19_lookup, BANK(level_4_2_lookup), 4},
};