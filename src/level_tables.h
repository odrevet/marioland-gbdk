#ifndef LEVEL_TABLES_H
#define LEVEL_TABLES_H

#include <gbdk/platform.h>

// Level 1_1
#define level_table_1_1_ENTRY_COUNT 15
#include <level_1_1_00.h>
#include <level_1_1_01.h>
#include <level_1_1_02.h>
#include <level_1_1_03.h>
#include <level_1_1_04.h>
#include <level_1_1_05.h>
#include <level_1_1_06.h>

// Level 1_2
#define level_table_1_2_ENTRY_COUNT 14
#include <level_1_2_00.h>
#include <level_1_2_01.h>
#include <level_1_2_02.h>
#include <level_1_2_03.h>
#include <level_1_2_04.h>
#include <level_1_2_05.h>
#include <level_1_2_06.h>

// Level 1_3
#define level_table_1_3_ENTRY_COUNT 17
#include <level_1_3_00.h>
#include <level_1_3_01.h>
#include <level_1_3_02.h>
#include <level_1_3_03.h>
#include <level_1_3_04.h>
#include <level_1_3_05.h>
#include <level_1_3_06.h>
#include <level_1_3_07.h>
#include <level_1_3_08.h>
#include <level_1_3_09.h>
#include <level_1_3_10.h>

// Level 2_1
#define level_table_2_1_ENTRY_COUNT 16
#include <level_2_1_00.h>
#include <level_2_1_01.h>
#include <level_2_1_02.h>
#include <level_2_1_03.h>
#include <level_2_1_04.h>
#include <level_2_1_05.h>
#include <level_2_1_06.h>
#include <level_2_1_07.h>

// Level 2_2
#define level_table_2_2_ENTRY_COUNT 12
#include <level_2_2_00.h>
#include <level_2_2_01.h>
#include <level_2_2_02.h>
#include <level_2_2_03.h>
#include <level_2_2_04.h>
#include <level_2_2_05.h>
#include <level_2_2_06.h>
#include <level_2_2_07.h>

// Level 2_3
#define level_table_2_3_ENTRY_COUNT 19
#include <level_2_3_00.h>
#include <level_2_3_01.h>
#include <level_2_3_02.h>
#include <level_2_3_03.h>
#include <level_2_3_04.h>
#include <level_2_3_05.h>

// Level 3_1
#define level_table_3_1_ENTRY_COUNT 23
#include <level_3_1_00.h>
#include <level_3_1_01.h>
#include <level_3_1_02.h>
#include <level_3_1_03.h>
#include <level_3_1_04.h>
#include <level_3_1_05.h>
#include <level_3_1_06.h>
#include <level_3_1_07.h>
#include <level_3_1_08.h>
#include <level_3_1_09.h>
#include <level_3_1_10.h>
#include <level_3_1_11.h>

// Level 3_2
#define level_table_3_2_ENTRY_COUNT 16
#include <level_3_2_00.h>
#include <level_3_2_01.h>
#include <level_3_2_02.h>
#include <level_3_2_03.h>
#include <level_3_2_04.h>
#include <level_3_2_05.h>
#include <level_3_2_06.h>
#include <level_3_2_07.h>
#include <level_3_2_08.h>
#include <level_3_2_09.h>
#include <level_3_2_10.h>

// Level 3_3
#define level_table_3_3_ENTRY_COUNT 16
#include <level_3_3_00.h>
#include <level_3_3_01.h>
#include <level_3_3_02.h>
#include <level_3_3_03.h>
#include <level_3_3_04.h>
#include <level_3_3_05.h>
#include <level_3_3_06.h>
#include <level_3_3_07.h>
#include <level_3_3_08.h>

// Level 4_1
#define level_table_4_1_ENTRY_COUNT 23
#include <level_4_1_00.h>
#include <level_4_1_01.h>
#include <level_4_1_02.h>
#include <level_4_1_03.h>
#include <level_4_1_04.h>
#include <level_4_1_05.h>
#include <level_4_1_06.h>
#include <level_4_1_07.h>
#include <level_4_1_08.h>
#include <level_4_1_09.h>

// Level 4_2
#define level_table_4_2_ENTRY_COUNT 20
#include <level_4_2_00.h>
#include <level_4_2_01.h>
#include <level_4_2_02.h>
#include <level_4_2_03.h>
#include <level_4_2_04.h>
#include <level_4_2_05.h>
#include <level_4_2_06.h>
#include <level_4_2_07.h>
#include <level_4_2_08.h>
#include <level_4_2_09.h>
#include <level_4_2_10.h>
#include <level_4_2_11.h>

// Level 4_3
#define level_table_4_3_ENTRY_COUNT 24
#include <level_4_3_00.h>
#include <level_4_3_01.h>
#include <level_4_3_02.h>
#include <level_4_3_03.h>
#include <level_4_3_04.h>
#include <level_4_3_05.h>
#include <level_4_3_06.h>
#include <level_4_3_07.h>
#include <level_4_3_08.h>
#include <level_4_3_09.h>

#include <level_gates.h>
#include <stage_end.h>

typedef struct {
    const unsigned char* map;
    uint8_t bank;
} banked_map_t;

// Level table declarations
extern const banked_map_t level_1_1_map[level_table_1_1_ENTRY_COUNT];
extern const banked_map_t level_1_2_map[level_table_1_2_ENTRY_COUNT];
extern const banked_map_t level_1_3_map[level_table_1_3_ENTRY_COUNT];
extern const banked_map_t level_2_1_map[level_table_2_1_ENTRY_COUNT];
extern const banked_map_t level_2_2_map[level_table_2_2_ENTRY_COUNT];
extern const banked_map_t level_2_3_map[level_table_2_3_ENTRY_COUNT];
extern const banked_map_t level_3_1_map[level_table_3_1_ENTRY_COUNT];
extern const banked_map_t level_3_2_map[level_table_3_2_ENTRY_COUNT];
extern const banked_map_t level_3_3_map[level_table_3_3_ENTRY_COUNT];
extern const banked_map_t level_4_1_map[level_table_4_1_ENTRY_COUNT];
extern const banked_map_t level_4_2_map[level_table_4_2_ENTRY_COUNT];
extern const banked_map_t level_4_3_map[level_table_4_3_ENTRY_COUNT];

#endif