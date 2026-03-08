#pragma bank 255
#include "lookup_table_3_3.h"
BANKREF(level_3_3_lookup)

static const level_object level_3_3_page_00_lookup[] = {{0}};
static const level_object level_3_3_page_01_lookup[] = {
    {.x = 3,  .y = 10, .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
    {.x = 12, .y = 11, .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
    {.x = 16, .y = 2,  .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
};
static const level_object level_3_3_page_02_lookup[] = {
    {.x = 5,  .y = 3,  .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
};
static const level_object level_3_3_page_03_lookup[] = {
    {.x = 16, .y = 14, .type = OBJECT_TYPE_PLATFORM_MOVING,  .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
    {.x = 18, .y = 6,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 19, .y = 6,  .type = OBJECT_TYPE_PLATFORM_FALLING},
};
static const level_object level_3_3_page_04_lookup[] = {
    {.x = 0,  .y = 11, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 1,  .y = 3,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
};
static const level_object level_3_3_page_05_lookup[] = {
    {.x = 6,  .y = 14, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KUMO}},
    {.x = 9,  .y = 5,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 14, .y = 14, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KUMO}},
    {.x = 19, .y = 12, .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
};
static const level_object level_3_3_page_06_lookup[] = {{0}};
static const level_object level_3_3_page_07_lookup[] = {{0}};
static const level_object level_3_3_page_08_lookup[] = {{0}};
static const level_object level_3_3_page_09_lookup[] = {
    {.x = 1,  .y = 14, .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
    {.x = 6,  .y = 14, .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
};
static const level_object level_3_3_page_10_lookup[] = {{0}};
static const level_object level_3_3_page_11_lookup[] = {
    {.x = 2,  .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BATADON}},
    {.x = 8,  .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_TOKOTOKO}},
};
static const level_object level_3_3_page_12_lookup[] = {{0}};
static const level_object level_3_3_page_13_lookup[] = {
    {.x = 13, .y = 5,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BATADON}},
};
static const level_object level_3_3_page_14_lookup[] = {
    {.x = 13, .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_HIYOIHOI}},
};
static const level_object level_3_3_page_15_lookup[] = {{0}};

const page_lookup_t level_3_3_lookup[] = {
    {level_3_3_page_00_lookup, BANK(level_3_3_lookup), 0},
    {level_3_3_page_01_lookup, BANK(level_3_3_lookup), 3},
    {level_3_3_page_02_lookup, BANK(level_3_3_lookup), 1},
    {level_3_3_page_03_lookup, BANK(level_3_3_lookup), 3},
    {level_3_3_page_04_lookup, BANK(level_3_3_lookup), 2},
    {level_3_3_page_05_lookup, BANK(level_3_3_lookup), 4},
    {level_3_3_page_06_lookup, BANK(level_3_3_lookup), 0},
    {level_3_3_page_07_lookup, BANK(level_3_3_lookup), 0},
    {level_3_3_page_08_lookup, BANK(level_3_3_lookup), 0},
    {level_3_3_page_09_lookup, BANK(level_3_3_lookup), 2},
    {level_3_3_page_10_lookup, BANK(level_3_3_lookup), 0},
    {level_3_3_page_11_lookup, BANK(level_3_3_lookup), 2},
    {level_3_3_page_12_lookup, BANK(level_3_3_lookup), 0},
    {level_3_3_page_13_lookup, BANK(level_3_3_lookup), 1},
    {level_3_3_page_14_lookup, BANK(level_3_3_lookup), 1},
    {level_3_3_page_15_lookup, BANK(level_3_3_lookup), 0},
};