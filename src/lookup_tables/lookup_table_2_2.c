#pragma bank 255

#include "lookup_table_2_2.h"

BANKREF(level_2_2_lookup)

const level_object level_2_2_lookup[] = {
    {.x = 22,
     .y = 10,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 44,
     .y = 9,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 46,
     .y = 5,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 62,
     .y = 4,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.range = 6,
                              .platform_direction = DIRECTION_HORIZONTAL}},
    {.x = 73,
     .y = 4,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.range = 6,
                              .platform_direction = DIRECTION_HORIZONTAL}},
    {.x = 85,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 96,
     .y = 7,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 104,
     .y = 7,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 114,
     .y = 7,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 119,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 141,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 143,
     .y = 7,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_MEKABON}},
    {.x = 154,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 172,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 178,
     .y = 10,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 183,
     .y = 15,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 193,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_MEKABON}},
    {.x = 203,
     .y = 6,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.range = 6,
                              .platform_direction = DIRECTION_VERTICAL}},
    {.x = 207,
     .y = 9,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.range = 6,
                              .platform_direction = DIRECTION_HORIZONTAL}},
    {.x = 225,
     .y = 11,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 231,
     .y = 15,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_YURARIN}},
    {.x = 238,
     .y = 8,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 244,
     .y = 9,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 245,
     .y = 6,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 251,
     .y = 3,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 266,
     .y = 1,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.range = 6,
                              .platform_direction = DIRECTION_VERTICAL}},
    {
        .x = 271,
        .y = 3,
        .type = OBJECT_TYPE_PLATFORM_FALLING,
    },
    {
        .x = 273,
        .y = 7,
        .type = OBJECT_TYPE_PLATFORM_FALLING,
    },
    {
        .x = 275,
        .y = 11,
        .type = OBJECT_TYPE_PLATFORM_FALLING,
    }};
