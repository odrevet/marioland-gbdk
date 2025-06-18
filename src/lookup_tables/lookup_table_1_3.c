#pragma bank 255

#include "lookup_table_1_3.h"

BANKREF(level_1_3_lookup_bank)

const level_object level_1_3_lookup[] = {
    {.x = 155,
     .y = 11,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GAO}},
    {.x = 187,
     .y = 10,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 251,
     .y = 12,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GAO}},
    {.x = 276,
     .y = 11,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GAO}},
    {.x = 292,
     .y = 11,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GAO}},
};

const size_t level_1_3_lookup_size =
    sizeof(level_1_3_lookup) / sizeof(level_1_3_lookup[0]);