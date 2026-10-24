#pragma bank 255

#include "lookup_table_1_3.h"

BANKREF(level_1_3_lookup)

const level_object level_1_3_lookup[] = {
    {.x = 153,
     .y = 11,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GAO}},
    {.x = 210,
     .y = 10,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 206,
     .y = 11,
     .type = OBJECT_TYPE_POWERUP,
     .data.enemy = {.type = POWERUP_MUSHROOM}},
    {.x = 276,
     .y = 11,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GAO}},
    {.x = 292,
     .y = 11,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GAO}},
    {.x = 312,
     .y = 11,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_BOSS_BIRABUTO}}
};
