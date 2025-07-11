#pragma bank 255

#include "lookup_table_1_2.h"

BANKREF(level_1_2_lookup)

const level_object level_1_2_lookup[] = {
    {.x = 38,
     .y = 6,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 42,
     .y = 6,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_BUNBUN}},
    {.x = 51,
     .y = 4,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_BUNBUN}},
    {.x = 65,
     .y = 6,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 71,
     .y = 8,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 93,
     .y = 2,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 95,
     .y = 4,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 106,
     .y = 6,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},
    {.x = 112,
     .y = 8,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},
    {.x = 135,
     .y = 2,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_BUNBUN}},
    {.x = 138,
     .y = 2,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_BUNBUN}},
    {.x = 150,
     .y = 2,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_BUNBUN}},
    {.x = 154,
     .y = 6,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_BUNBUN}},
    {.x = 175,
     .y = 2,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 179,
     .y = 2,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 188,
     .y = 8,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},
    {.x = 193,
     .y = 8,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},
    {.x = 198,
     .y = 8,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},
    {.x = 205,
     .y = 12,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 208,
     .y = 2,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_BUNBUN}},
    {.x = 226,
     .y = 10,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_HORIZONTAL}},
    {.x = 263,
     .y = 8,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}}};
