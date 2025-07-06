#pragma bank 255
#include "lookup_table_1_1.h"

BANKREF(level_1_1_lookup_bank)

const level_object level_1_1_lookup[] = {
    {.x = 23,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 66,
     .y = 10,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 80,
     .y = 4,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 82,
     .y = 4,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 117,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 156,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 166,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_FLY}},
    {.x = 169,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 186,
     .y = 10,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 195,
     .y = 10,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 205,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 210,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 234,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_FLY}},
    {.x = 245,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_FLY}},
    {.x = 281,
     .y = 3,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.range = 6,
                              .platform_direction = DIRECTION_VERTICAL}},
    {.x = 283,
     .y = 1,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.range = 6,
                              .platform_direction = DIRECTION_HORIZONTAL}}};

const size_t level_1_1_lookup_size =
    sizeof(level_1_1_lookup) / sizeof(level_1_1_lookup[0]);

level_block_object const level_1_1_blocks_lookup[] = {
    {22, 9, POWERUP_MUSHROOM}};

const size_t level_1_1_blocks_lookup_size =
    sizeof(level_1_1_blocks_lookup) / sizeof(level_block_object);
