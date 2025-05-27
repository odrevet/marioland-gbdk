
#include <gb/gb.h>
#include <gbdk/platform.h>
#include <stdint.h>

#include "gb/hardware.h"
#include "gb/metasprites.h"

#include "../src/graphics/common.h"
#include "../src/graphics/text.h"

#include "../src/global.h"
#include "../src/game.h"
#include "../src/level.h"

void main(void) {
  move_bkg(0, -MARGIN_TOP_PX);

  unsigned char windata[WINDOW_SIZE];
  memset(windata, 15, WINDOW_SIZE);
  set_win_tiles(0, 0, WINDOW_WIDTH_TILE, WINDOW_HEIGHT_TILE, windata);
  move_win(WINDOW_X, WINDOW_Y);
  text_print_string_win(0, 0, "MARIOx00  WORLD TIME");
  text_print_string_win(0, 1, "     0  x00 1-1  000");

  uint8_t _saved_bank = _current_bank;

  // background
  SWITCH_ROM(BANK(text));
  set_bkg_data(text_TILE_ORIGIN, text_TILE_COUNT, text_tiles);

  SWITCH_ROM(BANK(common));
  set_bkg_data(common_TILE_ORIGIN, common_TILE_COUNT, common_tiles);

  SWITCH_ROM(_saved_bank);

  init();
  current_level = 0;
  level_set_current();
  load_current_level();

  DISPLAY_ON;
  SHOW_BKG;

  while (1) {
    vsync();
  }
}
