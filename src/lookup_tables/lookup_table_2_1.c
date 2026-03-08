#pragma bank 255
#include "lookup_table_2_1.h"
BANKREF(level_2_1_lookup)

static const level_object level_2_1_page_00_lookup[] = {{0}};
static const level_object level_2_1_page_01_lookup[] = {
    {.x = 8,  .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 12, .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_HONEN}},
};
static const level_object level_2_1_page_02_lookup[] = {
    {.x = 13, .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 17, .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_HONEN}},
};
static const level_object level_2_1_page_03_lookup[] = {
    {.x = 3, .y = 10, .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.platform_direction = DIRECTION_HORIZONTAL}},
    {.x = 5, .y = 6,  .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.platform_direction = DIRECTION_HORIZONTAL}},
};
static const level_object level_2_1_page_04_lookup[] = {{0}};
static const level_object level_2_1_page_05_lookup[] = {
    {.x = 4,  .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 11, .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_HONEN}},
};
static const level_object level_2_1_page_06_lookup[] = {
    {.x = 2,  .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 9,  .y = 6,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 9,  .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 11, .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 14, .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_HONEN}},
};
static const level_object level_2_1_page_07_lookup[] = {
    {.x = 3,  .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 7,  .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 16, .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_HONEN}},
};
static const level_object level_2_1_page_08_lookup[] = {
    {.x = 1,  .y = 5,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 3,  .y = 5,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 14, .y = 2,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 16, .y = 2,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 18, .y = 2,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
};
static const level_object level_2_1_page_09_lookup[] = {
    {.x = 5,  .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 9,  .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 13, .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 18, .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_HONEN}},
};
static const level_object level_2_1_page_10_lookup[] = {
    {.x = 9,  .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 14, .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
};
static const level_object level_2_1_page_11_lookup[] = {
    {.x = 2,  .y = 11, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
};
static const level_object level_2_1_page_12_lookup[] = {
    {.x = 14, .y = 2,  .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
};
static const level_object level_2_1_page_13_lookup[] = {
    {.x = 11, .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
};
static const level_object level_2_1_page_14_lookup[] = {
    {.x = 0, .y = 15, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 8, .y = 5,  .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},
};
static const level_object level_2_1_page_15_lookup[] = {
    {.x = 4,  .y = 5, .type = OBJECT_TYPE_PLATFORM_MOVING, .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},
    {.x = 13, .y = 3, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 14, .y = 3, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},
};

const page_lookup_t level_2_1_lookup[] = {
    {level_2_1_page_00_lookup, BANK(level_2_1_lookup), 0},
    {level_2_1_page_01_lookup, BANK(level_2_1_lookup), 2},
    {level_2_1_page_02_lookup, BANK(level_2_1_lookup), 2},
    {level_2_1_page_03_lookup, BANK(level_2_1_lookup), 2},
    {level_2_1_page_04_lookup, BANK(level_2_1_lookup), 0},
    {level_2_1_page_05_lookup, BANK(level_2_1_lookup), 2},
    {level_2_1_page_06_lookup, BANK(level_2_1_lookup), 5},
    {level_2_1_page_07_lookup, BANK(level_2_1_lookup), 3},
    {level_2_1_page_08_lookup, BANK(level_2_1_lookup), 5},
    {level_2_1_page_09_lookup, BANK(level_2_1_lookup), 4},
    {level_2_1_page_10_lookup, BANK(level_2_1_lookup), 2},
    {level_2_1_page_11_lookup, BANK(level_2_1_lookup), 1},
    {level_2_1_page_12_lookup, BANK(level_2_1_lookup), 1},
    {level_2_1_page_13_lookup, BANK(level_2_1_lookup), 1},
    {level_2_1_page_14_lookup, BANK(level_2_1_lookup), 2},
    {level_2_1_page_15_lookup, BANK(level_2_1_lookup), 3},
};