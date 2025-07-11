#pragma bank 255

#include "lookup_table_4_2.h"

BANKREF(level_4_2_lookup)

const level_object level_4_2_lookup[] = {
    {.x = 29,
     .y = 10,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 41,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 49,
     .y = 10,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 52,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_PONPON}},
    {.x = 62,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_BULLET}},
    {.x = 70,
     .y = 12,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 98,
     .y = 9,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_NYOLOLIN}},
    {.x = 105,
     .y = 12,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 110,
     .y = 7,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 111,
     .y = 12,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 117,
     .y = 11,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 125,
     .y = 12,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 131,
     .y = 12,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 134,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_BULLET}},
    {.x = 137,
     .y = 11,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 143,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 144,
     .y = 7,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 152,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_PONPON}},
    {.x = 168,
     .y = 9,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 179,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 209,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 223,
     .y = 11,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.range = 6,
                              .platform_direction = DIRECTION_VERTICAL}},
    {.x = 226,
     .y = 9,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.range = 6,
                              .platform_direction = DIRECTION_VERTICAL}},
    {.x = 243,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 262,
     .y = 12,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.range = 6,
                              .platform_direction = DIRECTION_VERTICAL}},
    {.x = 267,
     .y = 11,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.range = 6,
                              .platform_direction = DIRECTION_VERTICAL}},
    {.x = 285,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 290,
     .y = 10,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_PIONPI}},
    {.x = 298,
     .y = 8,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 315,
     .y = 12,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 326,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_PIONPI}},
    {.x = 331,
     .y = 10,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 338,
     .y = 8,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 362,
     .y = 11,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_PLANT}},
    {.x = 366,
     .y = 4,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.range = 6,
                              .platform_direction = DIRECTION_VERTICAL}},
    {
        .x = 376,
        .y = 4,
        .type = OBJECT_TYPE_PLATFORM_FALLING,
    },
    {
        .x = 382,
        .y = 12,
        .type = OBJECT_TYPE_PLATFORM_FALLING,
    },
    {
        .x = 384,
        .y = 9,
        .type = OBJECT_TYPE_PLATFORM_FALLING,
    },
    {
        .x = 385,
        .y = 6,
        .type = OBJECT_TYPE_PLATFORM_FALLING,
    },
    {
        .x = 386,
        .y = 4,
        .type = OBJECT_TYPE_PLATFORM_FALLING,
    }};
