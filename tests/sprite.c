#include <stdint.h>

#include <gb/gb.h>
#include <gbdk/emu_debug.h>

#include "../src/graphics/common.h"
#include "../src/graphics/mario.h"

#include "../src/game.h"
#include "../src/global.h"
#include "../src/level.h"
#include "../src/player.h"

void main(void) {
  move_bkg(0, -MARGIN_TOP_PX);

  unsigned char windata[WINDOW_SIZE];
  memset(windata, 15, WINDOW_SIZE);
  set_win_tiles(0, 0, WINDOW_WIDTH_TILE, WINDOW_HEIGHT_TILE, windata);
  move_win(WINDOW_X, WINDOW_Y);

  uint8_t _saved_bank = _current_bank;

  // background
  SWITCH_ROM(BANK(common));
  set_bkg_data(common_TILE_ORIGIN, common_TILE_COUNT, common_tiles);

  // sprite
  SWITCH_ROM(BANK(mario));
  set_sprite_data(mario_TILE_ORIGIN, mario_TILE_COUNT, mario_tiles);

  SWITCH_ROM(_saved_bank);

  init();
  current_level = 0;
  level_set_current();
  load_current_level();

  player_draw_x = 4 * TILE_SIZE;
  player_draw_y = 1 * TILE_SIZE;

  DISPLAY_ON;
  SHOW_BKG;
  SHOW_SPRITES;

  while (1) {
    joypad_current = joypad();

    if (joypad_current & J_RIGHT) {
      player_draw_x++;
    }

    if (joypad_current & J_DOWN) {
      player_draw_y++;
    }

    if (joypad_current & J_LEFT) {
      player_draw_x--;
    }

    if (joypad_current & J_UP) {
      player_draw_y--;
    }

    EMU_printf("player draw x %d, player draw y %d\n", player_draw_x,
               player_draw_y);

    if (next_col_chunk_load ==
        current_map_width_in_tiles - DEVICE_SCREEN_WIDTH + 1) {
      level_end_reached = true;
      camera_x = current_map_width - DEVICE_SCREEN_PX_WIDTH;
      SCX_REG = camera_x;
    }

    if (camera_x >> 3 >= next_col_chunk_load && !level_end_reached) {
      level_load_column(next_col_chunk_load + DEVICE_SCREEN_WIDTH + 6, 1);
      next_col_chunk_load++;
    }

    player_draw(0);
    vsync();
  }
}
