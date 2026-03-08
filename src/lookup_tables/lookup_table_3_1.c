#pragma bank 255
#include "lookup_table_3_1.h"
BANKREF(level_3_1_lookup)

static const level_object level_3_1_page_00_lookup[] = {{0}};
static const level_object level_3_1_page_01_lookup[] = {
    {.x = 10, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BATADON}},
};
static const level_object level_3_1_page_02_lookup[] = {
    {.x = 0,  .y = 13, .type = OBJECT_TYPE_ENEMY,            .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 8,  .y = 13, .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 9,  .y = 13, .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 10, .y = 13, .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 11, .y = 13, .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 12, .y = 13, .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 13, .y = 13, .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 19, .y = 13, .type = OBJECT_TYPE_ENEMY,            .data.enemy = {.type = ENEMY_KOOPA}},
};
static const level_object level_3_1_page_03_lookup[] = {
    {.x = 12, .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BULLET}},
};
static const level_object level_3_1_page_04_lookup[] = {
    {.x = 16, .y = 1,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BATADON}},
    {.x = 19, .y = 2,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
};
static const level_object level_3_1_page_05_lookup[] = {
    {.x = 5,  .y = 4,  .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
    {.x = 9,  .y = 10, .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
    {.x = 17, .y = 12, .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
};
static const level_object level_3_1_page_06_lookup[] = {
    {.x = 0, .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 5, .y = 9,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
};
static const level_object level_3_1_page_07_lookup[] = {
    {.x = 2,  .y = 11, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 12, .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BULLET}},
};
static const level_object level_3_1_page_08_lookup[] = {
    {.x = 2,  .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 15, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_TOKOTOKO}},
    {.x = 18, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
};
static const level_object level_3_1_page_09_lookup[] = {
    {.x = 10, .y = 8,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_TOKOTOKO}},
    {.x = 18, .y = 2,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BATADON}},
};
static const level_object level_3_1_page_10_lookup[] = {
    {.x = 13, .y = 6,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 18, .y = 2,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BATADON}},
};
static const level_object level_3_1_page_11_lookup[] = {
    {.x = 0,  .y = 14, .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
    {.x = 9,  .y = 4,  .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
    {.x = 11, .y = 3,  .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
};
static const level_object level_3_1_page_12_lookup[] = {
    {.x = 2,  .y = 11, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BULLET}},
    {.x = 12, .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BULLET}},
};
static const level_object level_3_1_page_13_lookup[] = {
    {.x = 8,  .y = 7,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 10, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_TOKOTOKO}},
    {.x = 12, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_TOKOTOKO}},
    {.x = 14, .y = 3,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BATADON}},
    {.x = 14, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_TOKOTOKO}},
};
static const level_object level_3_1_page_14_lookup[] = {
    {.x = 5,  .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BATADON}},
    {.x = 8,  .y = 7,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BULLET}},
    {.x = 18, .y = 9,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_TOKOTOKO}},
};
static const level_object level_3_1_page_15_lookup[] = {{0}};
static const level_object level_3_1_page_16_lookup[] = {{0}};
static const level_object level_3_1_page_17_lookup[] = {
    {.x = 17, .y = 11, .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
};
static const level_object level_3_1_page_18_lookup[] = {{0}};
static const level_object level_3_1_page_19_lookup[] = {{0}};
static const level_object level_3_1_page_20_lookup[] = {{0}};
static const level_object level_3_1_page_21_lookup[] = {{0}};
static const level_object level_3_1_page_22_lookup[] = {
    {.x = 4,  .y = 7,  .type = OBJECT_TYPE_PLATFORM_MOVING,  .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
    {.x = 13, .y = 5,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 16, .y = 3,  .type = OBJECT_TYPE_PLATFORM_FALLING},
};

const page_lookup_t level_3_1_lookup[] = {
    {level_3_1_page_00_lookup, BANK(level_3_1_lookup), 0},
    {level_3_1_page_01_lookup, BANK(level_3_1_lookup), 1},
    {level_3_1_page_02_lookup, BANK(level_3_1_lookup), 8},
    {level_3_1_page_03_lookup, BANK(level_3_1_lookup), 1},
    {level_3_1_page_04_lookup, BANK(level_3_1_lookup), 2},
    {level_3_1_page_05_lookup, BANK(level_3_1_lookup), 3},
    {level_3_1_page_06_lookup, BANK(level_3_1_lookup), 2},
    {level_3_1_page_07_lookup, BANK(level_3_1_lookup), 2},
    {level_3_1_page_08_lookup, BANK(level_3_1_lookup), 3},
    {level_3_1_page_09_lookup, BANK(level_3_1_lookup), 2},
    {level_3_1_page_10_lookup, BANK(level_3_1_lookup), 2},
    {level_3_1_page_11_lookup, BANK(level_3_1_lookup), 3},
    {level_3_1_page_12_lookup, BANK(level_3_1_lookup), 2},
    {level_3_1_page_13_lookup, BANK(level_3_1_lookup), 5},
    {level_3_1_page_14_lookup, BANK(level_3_1_lookup), 3},
    {level_3_1_page_15_lookup, BANK(level_3_1_lookup), 0},
    {level_3_1_page_16_lookup, BANK(level_3_1_lookup), 0},
    {level_3_1_page_17_lookup, BANK(level_3_1_lookup), 1},
    {level_3_1_page_18_lookup, BANK(level_3_1_lookup), 0},
    {level_3_1_page_19_lookup, BANK(level_3_1_lookup), 0},
    {level_3_1_page_20_lookup, BANK(level_3_1_lookup), 0},
    {level_3_1_page_21_lookup, BANK(level_3_1_lookup), 0},
    {level_3_1_page_22_lookup, BANK(level_3_1_lookup), 3},
};