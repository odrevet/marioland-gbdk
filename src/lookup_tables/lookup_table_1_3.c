#pragma bank 255
#include "lookup_table_1_3.h"
BANKREF(level_1_3_lookup)

static const level_object level_1_3_page_00_lookup[] = {{0}};
static const level_object level_1_3_page_01_lookup[] = {{0}};
static const level_object level_1_3_page_02_lookup[] = {{0}};
static const level_object level_1_3_page_03_lookup[] = {{0}};
static const level_object level_1_3_page_04_lookup[] = {{0}};
static const level_object level_1_3_page_05_lookup[] = {{0}};
static const level_object level_1_3_page_06_lookup[] = {{0}};
static const level_object level_1_3_page_07_lookup[] = {
    {.x = 15, .y = 11, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GAO}},
};
static const level_object level_1_3_page_08_lookup[] = {{0}};
static const level_object level_1_3_page_09_lookup[] = {
    {.x = 7, .y = 10, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},
};
static const level_object level_1_3_page_10_lookup[] = {{0}};
static const level_object level_1_3_page_11_lookup[] = {{0}};
static const level_object level_1_3_page_12_lookup[] = {
    {.x = 11, .y = 12, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GAO}},
};
static const level_object level_1_3_page_13_lookup[] = {
    {.x = 16, .y = 11, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GAO}},
};
static const level_object level_1_3_page_14_lookup[] = {
    {.x = 12, .y = 11, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GAO}},
};
static const level_object level_1_3_page_15_lookup[] = {{0}};
static const level_object level_1_3_page_16_lookup[] = {{0}};

const page_lookup_t level_1_3_lookup[] = {
    {level_1_3_page_00_lookup, BANK(level_1_3_lookup), 0},
    {level_1_3_page_01_lookup, BANK(level_1_3_lookup), 0},
    {level_1_3_page_02_lookup, BANK(level_1_3_lookup), 0},
    {level_1_3_page_03_lookup, BANK(level_1_3_lookup), 0},
    {level_1_3_page_04_lookup, BANK(level_1_3_lookup), 0},
    {level_1_3_page_05_lookup, BANK(level_1_3_lookup), 0},
    {level_1_3_page_06_lookup, BANK(level_1_3_lookup), 0},
    {level_1_3_page_07_lookup, BANK(level_1_3_lookup), 1},
    {level_1_3_page_08_lookup, BANK(level_1_3_lookup), 0},
    {level_1_3_page_09_lookup, BANK(level_1_3_lookup), 1},
    {level_1_3_page_10_lookup, BANK(level_1_3_lookup), 0},
    {level_1_3_page_11_lookup, BANK(level_1_3_lookup), 0},
    {level_1_3_page_12_lookup, BANK(level_1_3_lookup), 1},
    {level_1_3_page_13_lookup, BANK(level_1_3_lookup), 1},
    {level_1_3_page_14_lookup, BANK(level_1_3_lookup), 1},
    {level_1_3_page_15_lookup, BANK(level_1_3_lookup), 0},
    {level_1_3_page_16_lookup, BANK(level_1_3_lookup), 0},
};