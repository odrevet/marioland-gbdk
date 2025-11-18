#include <stdint.h>

#include <gb/gb.h>
#include <gbdk/emu_debug.h>

#include "../src/graphics/common.h"

#include "../src/game.h"
#include "../src/global.h"
#include "../src/level.h"
#include "../src/enemy.h"


void main(void) {
    move_bkg(0, -MARGIN_TOP_PX);
    
    uint8_t _saved_bank = _current_bank;
    SWITCH_ROM(BANK(common));
    set_bkg_data(common_TILE_ORIGIN, common_TILE_COUNT, common_tiles);
    SWITCH_ROM(BANK(enemies));
    set_sprite_data(enemies_TILE_ORIGIN, enemies_TILE_COUNT, enemies_tiles);
    SWITCH_ROM(_saved_bank);
    
    init();
    current_level = 0;
    level_set_current();
    load_current_level();
    
    DISPLAY_ON;
    SHOW_BKG;
    SHOW_SPRITES;
    SPRITES_8x8;
    
    enemy_new(7 * TILE_SIZE, 12 * TILE_SIZE, ENEMY_GOOMBO);
    
    while (1) {
        EMU_printf("enemy at %d %d\n", enemies[0].x, enemies[0].y);
        enemy_update();
        enemy_draw(0);

        joypad_current = joypad();

        if (joypad_current & J_START) {
            enemy_remove(0);
        }

        vsync();
    }
}
