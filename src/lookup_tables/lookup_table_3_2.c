#pragma bank 255
#include "lookup_table_3_2.h"
BANKREF(level_3_2_lookup)

static const level_object level_3_2_page_00_lookup[] = {
    {.x = 7,  .y = 3,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_SUU}},
    {.x = 11, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
};
static const level_object level_3_2_page_01_lookup[] = {
    {.x = 18, .y = 3,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_SUU}},
};
static const level_object level_3_2_page_02_lookup[] = {
    {.x = 5,  .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 11, .y = 5,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_SUU}},
    {.x = 13, .y = 5,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_SUU}},
    {.x = 18, .y = 11, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
};
static const level_object level_3_2_page_03_lookup[] = {
    {.x = 0,  .y = 2,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_SUU}},
    {.x = 7,  .y = 1,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
};
static const level_object level_3_2_page_04_lookup[] = {
    {.x = 0,  .y = 4,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_SUU}},
    {.x = 1,  .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KUMO}},
    {.x = 12, .y = 3,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_SUU}},
};
static const level_object level_3_2_page_05_lookup[] = {
    {.x = 3,  .y = 0,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 12, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
};
static const level_object level_3_2_page_06_lookup[] = {
    {.x = 5,  .y = 10, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 16, .y = 3,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_SUU}},
    {.x = 18, .y = 9,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KUMO}},
};
static const level_object level_3_2_page_07_lookup[] = {
    {.x = 0,  .y = 5,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_SUU}},
    {.x = 7,  .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 19, .y = 6,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KUMO}},
};
static const level_object level_3_2_page_08_lookup[] = {
    {.x = 3,  .y = 11, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BULLET}},
    {.x = 6,  .y = 2,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_SUU}},
    {.x = 13, .y = 10, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
};
static const level_object level_3_2_page_09_lookup[] = {
    {.x = 18, .y = 9,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KUMO}},
};
static const level_object level_3_2_page_10_lookup[] = {{0}};
static const level_object level_3_2_page_11_lookup[] = {{0}};
static const level_object level_3_2_page_12_lookup[] = {
    {.x = 7,  .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BULLET}},
    {.x = 9,  .y = 5,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_SUU}},
    {.x = 12, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KUMO}},
    {.x = 18, .y = 11, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
};
static const level_object level_3_2_page_13_lookup[] = {
    {.x = 4,  .y = 6,  .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
    {.x = 12, .y = 11, .type = OBJECT_TYPE_ENEMY,           .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 15, .y = 5,  .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
};
static const level_object level_3_2_page_14_lookup[] = {
    {.x = 1,  .y = 8,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 2,  .y = 8,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 5,  .y = 7,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 6,  .y = 7,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 13, .y = 8,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 16, .y = 9,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 17, .y = 9,  .type = OBJECT_TYPE_PLATFORM_FALLING},
};
static const level_object level_3_2_page_15_lookup[] = {
    {.x = 1,  .y = 9,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 4,  .y = 8,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 7,  .y = 7,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 10, .y = 6,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 13, .y = 5,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 16, .y = 3,  .type = OBJECT_TYPE_PLATFORM_FALLING},
};

const page_lookup_t level_3_2_lookup[] = {
    {level_3_2_page_00_lookup, BANK(level_3_2_lookup), 2},
    {level_3_2_page_01_lookup, BANK(level_3_2_lookup), 1},
    {level_3_2_page_02_lookup, BANK(level_3_2_lookup), 4},
    {level_3_2_page_03_lookup, BANK(level_3_2_lookup), 2},
    {level_3_2_page_04_lookup, BANK(level_3_2_lookup), 3},
    {level_3_2_page_05_lookup, BANK(level_3_2_lookup), 2},
    {level_3_2_page_06_lookup, BANK(level_3_2_lookup), 3},
    {level_3_2_page_07_lookup, BANK(level_3_2_lookup), 3},
    {level_3_2_page_08_lookup, BANK(level_3_2_lookup), 3},
    {level_3_2_page_09_lookup, BANK(level_3_2_lookup), 1},
    {level_3_2_page_10_lookup, BANK(level_3_2_lookup), 0},
    {level_3_2_page_11_lookup, BANK(level_3_2_lookup), 0},
    {level_3_2_page_12_lookup, BANK(level_3_2_lookup), 4},
    {level_3_2_page_13_lookup, BANK(level_3_2_lookup), 3},
    {level_3_2_page_14_lookup, BANK(level_3_2_lookup), 7},
    {level_3_2_page_15_lookup, BANK(level_3_2_lookup), 6},
};