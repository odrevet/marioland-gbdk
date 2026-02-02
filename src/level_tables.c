#include "level_tables.h"


// Level 1_1 map declarations
extern const unsigned char level_1_1_00_map[];
extern const unsigned char level_1_1_01_map[];
extern const unsigned char level_1_1_02_map[];
extern const unsigned char level_1_1_03_map[];
extern const unsigned char level_1_1_04_map[];
extern const unsigned char level_1_1_05_map[];
extern const unsigned char level_1_1_06_map[];

// Level 1_2 map declarations
extern const unsigned char level_1_2_00_map[];
extern const unsigned char level_1_2_01_map[];
extern const unsigned char level_1_2_02_map[];
extern const unsigned char level_1_2_03_map[];
extern const unsigned char level_1_2_04_map[];
extern const unsigned char level_1_2_05_map[];
extern const unsigned char level_1_2_06_map[];

// Level 1_3 map declarations
extern const unsigned char level_1_3_00_map[];
extern const unsigned char level_1_3_01_map[];
extern const unsigned char level_1_3_02_map[];
extern const unsigned char level_1_3_03_map[];
extern const unsigned char level_1_3_04_map[];
extern const unsigned char level_1_3_05_map[];
extern const unsigned char level_1_3_06_map[];
extern const unsigned char level_1_3_07_map[];
extern const unsigned char level_1_3_08_map[];
extern const unsigned char level_1_3_09_map[];
extern const unsigned char level_1_3_10_map[];

// Level 2_1 map declarations
extern const unsigned char level_2_1_00_map[];
extern const unsigned char level_2_1_01_map[];
extern const unsigned char level_2_1_02_map[];
extern const unsigned char level_2_1_03_map[];
extern const unsigned char level_2_1_04_map[];
extern const unsigned char level_2_1_05_map[];
extern const unsigned char level_2_1_06_map[];
extern const unsigned char level_2_1_07_map[];

// Level 2_2 map declarations
extern const unsigned char level_2_2_00_map[];
extern const unsigned char level_2_2_01_map[];
extern const unsigned char level_2_2_02_map[];
extern const unsigned char level_2_2_03_map[];
extern const unsigned char level_2_2_04_map[];
extern const unsigned char level_2_2_05_map[];
extern const unsigned char level_2_2_06_map[];
extern const unsigned char level_2_2_07_map[];

// Level 2_3 map declarations
extern const unsigned char level_2_3_00_map[];
extern const unsigned char level_2_3_01_map[];
extern const unsigned char level_2_3_02_map[];
extern const unsigned char level_2_3_03_map[];
extern const unsigned char level_2_3_04_map[];
extern const unsigned char level_2_3_05_map[];

// Level 3_1 map declarations
extern const unsigned char level_3_1_00_map[];
extern const unsigned char level_3_1_01_map[];
extern const unsigned char level_3_1_02_map[];
extern const unsigned char level_3_1_03_map[];
extern const unsigned char level_3_1_04_map[];
extern const unsigned char level_3_1_05_map[];
extern const unsigned char level_3_1_06_map[];
extern const unsigned char level_3_1_07_map[];
extern const unsigned char level_3_1_08_map[];
extern const unsigned char level_3_1_09_map[];
extern const unsigned char level_3_1_10_map[];
extern const unsigned char level_3_1_11_map[];

// Level 3_2 map declarations
extern const unsigned char level_3_2_00_map[];
extern const unsigned char level_3_2_01_map[];
extern const unsigned char level_3_2_02_map[];
extern const unsigned char level_3_2_03_map[];
extern const unsigned char level_3_2_04_map[];
extern const unsigned char level_3_2_05_map[];
extern const unsigned char level_3_2_06_map[];
extern const unsigned char level_3_2_07_map[];
extern const unsigned char level_3_2_08_map[];
extern const unsigned char level_3_2_09_map[];
extern const unsigned char level_3_2_10_map[];

// Level 3_3 map declarations
extern const unsigned char level_3_3_00_map[];
extern const unsigned char level_3_3_01_map[];
extern const unsigned char level_3_3_02_map[];
extern const unsigned char level_3_3_03_map[];
extern const unsigned char level_3_3_04_map[];
extern const unsigned char level_3_3_05_map[];
extern const unsigned char level_3_3_06_map[];
extern const unsigned char level_3_3_07_map[];
extern const unsigned char level_3_3_08_map[];

// Level 4_1 map declarations
extern const unsigned char level_4_1_00_map[];
extern const unsigned char level_4_1_01_map[];
extern const unsigned char level_4_1_02_map[];
extern const unsigned char level_4_1_03_map[];
extern const unsigned char level_4_1_04_map[];
extern const unsigned char level_4_1_05_map[];
extern const unsigned char level_4_1_06_map[];
extern const unsigned char level_4_1_07_map[];
extern const unsigned char level_4_1_08_map[];
extern const unsigned char level_4_1_09_map[];

// Level 4_2 map declarations
extern const unsigned char level_4_2_00_map[];
extern const unsigned char level_4_2_01_map[];
extern const unsigned char level_4_2_02_map[];
extern const unsigned char level_4_2_03_map[];
extern const unsigned char level_4_2_04_map[];
extern const unsigned char level_4_2_05_map[];
extern const unsigned char level_4_2_06_map[];
extern const unsigned char level_4_2_07_map[];
extern const unsigned char level_4_2_08_map[];
extern const unsigned char level_4_2_09_map[];
extern const unsigned char level_4_2_10_map[];
extern const unsigned char level_4_2_11_map[];

// Level 4_3 map declarations
extern const unsigned char level_4_3_00_map[];
extern const unsigned char level_4_3_01_map[];
extern const unsigned char level_4_3_02_map[];
extern const unsigned char level_4_3_03_map[];
extern const unsigned char level_4_3_04_map[];
extern const unsigned char level_4_3_05_map[];
extern const unsigned char level_4_3_06_map[];
extern const unsigned char level_4_3_07_map[];
extern const unsigned char level_4_3_08_map[];
extern const unsigned char level_4_3_09_map[];

extern const unsigned char level_gates_map[];
extern const unsigned char stage_end_map[];

const banked_map_t level_1_1_map[level_table_1_1_ENTRY_COUNT] = {
    {level_1_1_00_map, BANK(level_1_1_00)},
    {level_1_1_01_map, BANK(level_1_1_01)},
    {level_1_1_00_map, BANK(level_1_1_00)},
    {level_1_1_02_map, BANK(level_1_1_02)},
    {level_1_1_03_map, BANK(level_1_1_03)},
    {level_1_1_00_map, BANK(level_1_1_00)},
    {level_1_1_04_map, BANK(level_1_1_04)},
    {level_1_1_00_map, BANK(level_1_1_00)},
    {level_1_1_01_map, BANK(level_1_1_01)},
    {level_1_1_02_map, BANK(level_1_1_02)},
    {level_1_1_01_map, BANK(level_1_1_01)},
    {level_1_1_00_map, BANK(level_1_1_00)},
    {level_1_1_05_map, BANK(level_1_1_05)},
    {level_1_1_06_map, BANK(level_1_1_06)},
    {level_gates_map, BANK(level_gates)},
};

// Level 1_2 table
const banked_map_t level_1_2_map[level_table_1_2_ENTRY_COUNT] = {
    {level_1_2_00_map, BANK(level_1_2_00)},
    {level_1_2_01_map, BANK(level_1_2_01)},
    {level_1_2_02_map, BANK(level_1_2_02)},
    {level_1_2_01_map, BANK(level_1_2_01)},
    {level_1_2_03_map, BANK(level_1_2_03)},
    {level_1_2_04_map, BANK(level_1_2_04)},
    {level_1_2_02_map, BANK(level_1_2_02)},
    {level_1_2_02_map, BANK(level_1_2_02)},
    {level_1_2_05_map, BANK(level_1_2_05)},
    {level_1_2_06_map, BANK(level_1_2_06)},
    {level_1_2_03_map, BANK(level_1_2_03)},
    {level_1_2_04_map, BANK(level_1_2_04)},
    {level_1_2_00_map, BANK(level_1_2_00)},
    {level_gates_map, BANK(level_gates)},
};

// Level 1_3 table
const banked_map_t level_1_3_map[level_table_1_3_ENTRY_COUNT] = {
    {level_1_3_00_map, BANK(level_1_3_00)},
    {level_1_3_01_map, BANK(level_1_3_01)},
    {level_1_3_02_map, BANK(level_1_3_02)},
    {level_1_3_02_map, BANK(level_1_3_02)},
    {level_1_3_03_map, BANK(level_1_3_03)},
    {level_1_3_01_map, BANK(level_1_3_01)},
    {level_1_3_00_map, BANK(level_1_3_00)},
    {level_1_3_00_map, BANK(level_1_3_00)},
    {level_1_3_04_map, BANK(level_1_3_04)},
    {level_1_3_05_map, BANK(level_1_3_05)},
    {level_1_3_06_map, BANK(level_1_3_06)},
    {level_1_3_07_map, BANK(level_1_3_07)},
    {level_1_3_08_map, BANK(level_1_3_08)},
    {level_1_3_09_map, BANK(level_1_3_09)},
    {level_1_3_09_map, BANK(level_1_3_09)},
    {level_1_3_10_map, BANK(level_1_3_10)},
    {stage_end_map, BANK(stage_end)},
};

// Level 2_1 table
const banked_map_t level_2_1_map[level_table_2_1_ENTRY_COUNT] = {
    {level_2_1_00_map, BANK(level_2_1_00)},
    {level_2_1_01_map, BANK(level_2_1_01)},
    {level_2_1_02_map, BANK(level_2_1_02)},
    {level_2_1_03_map, BANK(level_2_1_03)},
    {level_2_1_04_map, BANK(level_2_1_04)},
    {level_2_1_05_map, BANK(level_2_1_05)},
    {level_2_1_05_map, BANK(level_2_1_05)},
    {level_2_1_06_map, BANK(level_2_1_06)},
    {level_2_1_01_map, BANK(level_2_1_01)},
    {level_2_1_02_map, BANK(level_2_1_02)},
    {level_2_1_02_map, BANK(level_2_1_02)},
    {level_2_1_04_map, BANK(level_2_1_04)},
    {level_2_1_01_map, BANK(level_2_1_01)},
    {level_2_1_05_map, BANK(level_2_1_05)},
    {level_2_1_07_map, BANK(level_2_1_07)},
    {level_gates_map, BANK(level_gates)},
};

// Level 2_2 table
const banked_map_t level_2_2_map[level_table_2_2_ENTRY_COUNT] = {
    {level_2_2_00_map, BANK(level_2_2_00)},
    {level_2_2_01_map, BANK(level_2_2_01)},
    {level_2_2_02_map, BANK(level_2_2_02)},
    {level_2_2_03_map, BANK(level_2_2_03)},
    {level_2_2_04_map, BANK(level_2_2_04)},
    {level_2_2_05_map, BANK(level_2_2_05)},
    {level_2_2_05_map, BANK(level_2_2_05)},
    {level_2_2_06_map, BANK(level_2_2_06)},
    {level_2_2_00_map, BANK(level_2_2_00)},
    {level_2_2_07_map, BANK(level_2_2_07)},
    {level_2_2_02_map, BANK(level_2_2_02)},
    {level_gates_map, BANK(level_gates)},
};

// Level 2_3 table
const banked_map_t level_2_3_map[level_table_2_3_ENTRY_COUNT] = {
    {level_2_3_00_map, BANK(level_2_3_00)},
    {level_2_3_01_map, BANK(level_2_3_01)},
    {level_2_3_02_map, BANK(level_2_3_02)},
    {level_2_3_01_map, BANK(level_2_3_01)},
    {level_2_3_00_map, BANK(level_2_3_00)},
    {level_2_3_00_map, BANK(level_2_3_00)},
    {level_2_3_02_map, BANK(level_2_3_02)},
    {level_2_3_02_map, BANK(level_2_3_02)},
    {level_2_3_01_map, BANK(level_2_3_01)},
    {level_2_3_03_map, BANK(level_2_3_03)},
    {level_2_3_03_map, BANK(level_2_3_03)},
    {level_2_3_02_map, BANK(level_2_3_02)},
    {level_2_3_02_map, BANK(level_2_3_02)},
    {level_2_3_00_map, BANK(level_2_3_00)},
    {level_2_3_04_map, BANK(level_2_3_04)},
    {level_2_3_03_map, BANK(level_2_3_03)},
    {level_2_3_03_map, BANK(level_2_3_03)},
    {level_2_3_05_map, BANK(level_2_3_05)},
    {stage_end_map, BANK(stage_end)},
};

// Level 3_1 table
const banked_map_t level_3_1_map[level_table_3_1_ENTRY_COUNT] = {
    {level_3_1_00_map, BANK(level_3_1_00)},
    {level_3_1_01_map, BANK(level_3_1_01)},
    {level_3_1_02_map, BANK(level_3_1_02)},
    {level_3_1_01_map, BANK(level_3_1_01)},
    {level_3_1_03_map, BANK(level_3_1_03)},
    {level_3_1_04_map, BANK(level_3_1_04)},
    {level_3_1_05_map, BANK(level_3_1_05)},
    {level_3_1_01_map, BANK(level_3_1_01)},
    {level_3_1_00_map, BANK(level_3_1_00)},
    {level_3_1_03_map, BANK(level_3_1_03)},
    {level_3_1_03_map, BANK(level_3_1_03)},
    {level_3_1_00_map, BANK(level_3_1_00)},
    {level_3_1_01_map, BANK(level_3_1_01)},
    {level_3_1_06_map, BANK(level_3_1_06)},
    {level_3_1_06_map, BANK(level_3_1_06)},
    {level_3_1_07_map, BANK(level_3_1_07)},
    {level_3_1_08_map, BANK(level_3_1_08)},
    {level_3_1_09_map, BANK(level_3_1_09)},
    {level_3_1_09_map, BANK(level_3_1_09)},
    {level_3_1_10_map, BANK(level_3_1_10)},
    {level_3_1_11_map, BANK(level_3_1_11)},
    {level_3_1_10_map, BANK(level_3_1_10)},
    {level_gates_map, BANK(level_gates)},
};

// Level 3_2 table
const banked_map_t level_3_2_map[level_table_3_2_ENTRY_COUNT] = {
    {level_3_2_00_map, BANK(level_3_2_00)},
    {level_3_2_01_map, BANK(level_3_2_01)},
    {level_3_2_00_map, BANK(level_3_2_00)},
    {level_3_2_02_map, BANK(level_3_2_02)},
    {level_3_2_03_map, BANK(level_3_2_03)},
    {level_3_2_02_map, BANK(level_3_2_02)},
    {level_3_2_04_map, BANK(level_3_2_04)},
    {level_3_2_03_map, BANK(level_3_2_03)},
    {level_3_2_01_map, BANK(level_3_2_01)},
    {level_3_2_04_map, BANK(level_3_2_04)},
    {level_3_2_05_map, BANK(level_3_2_05)},
    {level_3_2_05_map, BANK(level_3_2_05)},
    {level_3_2_00_map, BANK(level_3_2_00)},
    {level_3_2_06_map, BANK(level_3_2_06)},
    {level_3_2_07_map, BANK(level_3_2_07)},
    {level_gates_map, BANK(level_gates)},
};

// Level 3_3 table
const banked_map_t level_3_3_map[level_table_3_3_ENTRY_COUNT] = {
    {level_3_3_00_map, BANK(level_3_3_00)},
    {level_3_3_01_map, BANK(level_3_3_01)},
    {level_3_3_01_map, BANK(level_3_3_01)},
    {level_3_3_00_map, BANK(level_3_3_00)},
    {level_3_3_02_map, BANK(level_3_3_02)},
    {level_3_3_03_map, BANK(level_3_3_03)},
    {level_3_3_01_map, BANK(level_3_3_01)},
    {level_3_3_01_map, BANK(level_3_3_01)},
    {level_3_3_04_map, BANK(level_3_3_04)},
    {level_3_3_05_map, BANK(level_3_3_05)},
    {level_3_3_06_map, BANK(level_3_3_06)},
    {level_3_3_06_map, BANK(level_3_3_06)},
    {level_3_3_07_map, BANK(level_3_3_07)},
    {level_3_3_07_map, BANK(level_3_3_07)},
    {level_3_3_08_map, BANK(level_3_3_08)},
    {stage_end_map, BANK(stage_end)},
};

// Level 4_1 table
const banked_map_t level_4_1_map[level_table_4_1_ENTRY_COUNT] = {
    {level_4_1_00_map, BANK(level_4_1_00)},
    {level_4_1_01_map, BANK(level_4_1_01)},
    {level_4_1_02_map, BANK(level_4_1_02)},
    {level_4_1_03_map, BANK(level_4_1_03)},
    {level_4_1_02_map, BANK(level_4_1_02)},
    {level_4_1_04_map, BANK(level_4_1_04)},
    {level_4_1_04_map, BANK(level_4_1_04)},
    {level_4_1_02_map, BANK(level_4_1_02)},
    {level_4_1_05_map, BANK(level_4_1_05)},
    {level_4_1_00_map, BANK(level_4_1_00)},
    {level_4_1_03_map, BANK(level_4_1_03)},
    {level_4_1_06_map, BANK(level_4_1_06)},
    {level_4_1_06_map, BANK(level_4_1_06)},
    {level_4_1_06_map, BANK(level_4_1_06)},
    {level_4_1_03_map, BANK(level_4_1_03)},
    {level_4_1_03_map, BANK(level_4_1_03)},
    {level_4_1_05_map, BANK(level_4_1_05)},
    {level_4_1_04_map, BANK(level_4_1_04)},
    {level_4_1_07_map, BANK(level_4_1_07)},
    {level_4_1_05_map, BANK(level_4_1_05)},
    {level_4_1_04_map, BANK(level_4_1_04)},
    {level_4_1_05_map, BANK(level_4_1_05)},
    {level_gates_map, BANK(level_gates)},
};

// Level 4_2 table
const banked_map_t level_4_2_map[level_table_4_2_ENTRY_COUNT] = {
    {level_4_2_00_map, BANK(level_4_2_00)},
    {level_4_2_01_map, BANK(level_4_2_01)},
    {level_4_2_01_map, BANK(level_4_2_01)},
    {level_4_2_00_map, BANK(level_4_2_00)},
    {level_4_2_00_map, BANK(level_4_2_00)},
    {level_4_2_02_map, BANK(level_4_2_02)},
    {level_4_2_02_map, BANK(level_4_2_02)},
    {level_4_2_01_map, BANK(level_4_2_01)},
    {level_4_2_03_map, BANK(level_4_2_03)},
    {level_4_2_03_map, BANK(level_4_2_03)},
    {level_4_2_04_map, BANK(level_4_2_04)},
    {level_4_2_05_map, BANK(level_4_2_05)},
    {level_4_2_04_map, BANK(level_4_2_04)},
    {level_4_2_05_map, BANK(level_4_2_05)},
    {level_4_2_06_map, BANK(level_4_2_06)},
    {level_4_2_03_map, BANK(level_4_2_03)},
    {level_4_2_06_map, BANK(level_4_2_06)},
    {level_4_2_07_map, BANK(level_4_2_07)},
    {level_4_2_08_map, BANK(level_4_2_08)},
    {level_gates_map, BANK(level_gates)},
};

// Level 4_3 table
const banked_map_t level_4_3_map[level_table_4_3_ENTRY_COUNT] = {
    {level_4_3_00_map, BANK(level_4_3_00)},
    {level_4_3_00_map, BANK(level_4_3_00)},
    {level_4_3_00_map, BANK(level_4_3_00)},
    {level_4_3_00_map, BANK(level_4_3_00)},
    {level_4_3_01_map, BANK(level_4_3_01)},
    {level_4_3_01_map, BANK(level_4_3_01)},
    {level_4_3_01_map, BANK(level_4_3_01)},
    {level_4_3_00_map, BANK(level_4_3_00)},
    {level_4_3_00_map, BANK(level_4_3_00)},
    {level_4_3_00_map, BANK(level_4_3_00)},
    {level_4_3_01_map, BANK(level_4_3_01)},
    {level_4_3_01_map, BANK(level_4_3_01)},
    {level_4_3_00_map, BANK(level_4_3_00)},
    {level_4_3_02_map, BANK(level_4_3_02)},
    {level_4_3_02_map, BANK(level_4_3_02)},
    {level_4_3_03_map, BANK(level_4_3_03)},
    {level_4_3_04_map, BANK(level_4_3_04)},
    {level_4_3_05_map, BANK(level_4_3_05)},
    {level_4_3_05_map, BANK(level_4_3_05)},
    {level_4_3_04_map, BANK(level_4_3_04)},
    {level_4_3_06_map, BANK(level_4_3_06)},
    {level_4_3_07_map, BANK(level_4_3_07)},
    {level_4_3_08_map, BANK(level_4_3_08)},
    {level_4_3_09_map, BANK(level_4_3_09)}
};