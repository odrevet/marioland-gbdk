#pragma bank 255
#include "lookup_table_underground.h"

BANKREF(underground_lookup)

const level_object underground_0_lookup[] = {
    {.x = 16,
     .y = 11,
     .type = OBJECT_TYPE_PIPE_VERTICAL,
     .data.pipe = {.destination = level_1_1_00_map,
                   .destination_bank = BANK(level_1_1_00)}}};
