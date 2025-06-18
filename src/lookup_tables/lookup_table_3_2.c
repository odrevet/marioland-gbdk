#pragma bank 255

#include "lookup_table_3_2.h"

BANKREF(level_3_2_lookup_bank)

const level_object level_3_2_lookup[] = {{.x = 7,
                                    .y = 3,
                                    .type = OBJECT_TYPE_ENEMY,
                                    .data.enemy = {.type = ENEMY_SUU}}};

const size_t level_3_2_lookup_size =
    sizeof(level_3_2_lookup) / sizeof(level_3_2_lookup[0]);