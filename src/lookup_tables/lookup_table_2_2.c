#pragma bank 255
#include "lookup_table_2_2.h"
BANKREF(level_2_2_lookup)

static const level_object level_2_2_page_00_lookup[] = {{0}};
static const level_object level_2_2_page_01_lookup[] = {
    {.x = 2, .y = 10, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
};
static const level_object level_2_2_page_02_lookup[] = {
    {.x = 4, .y = 9, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 6, .y = 5, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
};
static const level_object level_2_2_page_03_lookup[] = {
    {.x = 2,  .y = 4, .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_HORIZONTAL}},
    {.x = 13, .y = 4, .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_HORIZONTAL}},
};
static const level_object level_2_2_page_04_lookup[] = {
    {.x = 5,  .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 16, .y = 7,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
};
static const level_object level_2_2_page_05_lookup[] = {
    {.x = 4,  .y = 7,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 14, .y = 7,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 19, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
};
static const level_object level_2_2_page_06_lookup[] = {{0}};
static const level_object level_2_2_page_07_lookup[] = {
    {.x = 1,  .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 3,  .y = 7,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_MEKABON}},
    {.x = 14, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
};
static const level_object level_2_2_page_08_lookup[] = {
    {.x = 12, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 18, .y = 10, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
};
static const level_object level_2_2_page_09_lookup[] = {
    {.x = 3,  .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 13, .y = 13, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_MEKABON}},
};
static const level_object level_2_2_page_10_lookup[] = {
    {.x = 3, .y = 6, .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
    {.x = 7, .y = 9, .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_HORIZONTAL}},
};
static const level_object level_2_2_page_11_lookup[] = {
    {.x = 5,  .y = 11, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 11, .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_YURARIN}},
    {.x = 18, .y = 8,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
};
static const level_object level_2_2_page_12_lookup[] = {
    {.x = 4,  .y = 9, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 5,  .y = 6, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 11, .y = 3, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
};
static const level_object level_2_2_page_13_lookup[] = {
    {.x = 6,  .y = 1,  .type = OBJECT_TYPE_PLATFORM_MOVING,  .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
    {.x = 11, .y = 3,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 13, .y = 7,  .type = OBJECT_TYPE_PLATFORM_FALLING},
    {.x = 15, .y = 11, .type = OBJECT_TYPE_PLATFORM_FALLING},
};

const page_lookup_t level_2_2_lookup[] = {
    {level_2_2_page_00_lookup, BANK(level_2_2_lookup), 0},
    {level_2_2_page_01_lookup, BANK(level_2_2_lookup), 1},
    {level_2_2_page_02_lookup, BANK(level_2_2_lookup), 2},
    {level_2_2_page_03_lookup, BANK(level_2_2_lookup), 2},
    {level_2_2_page_04_lookup, BANK(level_2_2_lookup), 2},
    {level_2_2_page_05_lookup, BANK(level_2_2_lookup), 3},
    {level_2_2_page_06_lookup, BANK(level_2_2_lookup), 0},
    {level_2_2_page_07_lookup, BANK(level_2_2_lookup), 3},
    {level_2_2_page_08_lookup, BANK(level_2_2_lookup), 2},
    {level_2_2_page_09_lookup, BANK(level_2_2_lookup), 2},
    {level_2_2_page_10_lookup, BANK(level_2_2_lookup), 2},
    {level_2_2_page_11_lookup, BANK(level_2_2_lookup), 3},
    {level_2_2_page_12_lookup, BANK(level_2_2_lookup), 3},
    {level_2_2_page_13_lookup, BANK(level_2_2_lookup), 4},
};