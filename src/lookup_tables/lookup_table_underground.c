#pragma bank 255
#include "lookup_table_underground.h"

BANKREF(underground_lookup)

const level_object underground_0_lookup[] = {
    {.x = 16,
     .y = 12,
     .type = OBJECT_TYPE_PIPE_VERTICAL,
     .data.pipe = {.destination_page = 0,
                   .map_pages = level_1_1_map}}};
