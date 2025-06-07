#include <stdint.h>

#include <gb/gb.h>
#include <gbdk/emu_debug.h>

#include "../src/graphics/common.h"

#include "../src/game.h"
#include "../src/global.h"
#include "../src/level.h"

#define SCROLL_SPEED_NORMAL 16
#define SCROLL_SPEED_FAST 32

uint8_t scroll_speed;

void main(void) {
  move_bkg(0, -MARGIN_TOP_PX);
  scroll_speed = SCROLL_SPEED_NORMAL;

  uint8_t _saved_bank = _current_bank;

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
    joypad_current = joypad();

    // scroll on right pad press
    if (joypad_current & J_RIGHT && !level_end_reached) {
      camera_x_upscaled += scroll_speed;
      camera_x = camera_x_upscaled >> 4;
      SCX_REG = camera_x;
    }

    // scroll faster when B button is pressed
    if (joypad_current & J_B) {
      scroll_speed = SCROLL_SPEED_FAST;
    } else {
      scroll_speed = SCROLL_SPEED_NORMAL;
    }

    // load next level on select pressed
    if (joypad_current & J_SELECT && !(joypad_previous & J_SELECT)) {
      init();
      current_level = (++current_level) % NB_LEVELS;
      HIDE_BKG;
      level_set_current();
      load_current_level();
      SHOW_BKG;
    }

    // check if the end of the level is reached
    if (next_col_chunk_load ==
        current_map_width_in_tiles - DEVICE_SCREEN_WIDTH + 1) {
      level_end_reached = true;
      camera_x = current_map_width - DEVICE_SCREEN_PX_WIDTH;
      SCX_REG = camera_x;
    }

    // read background data
    if (camera_x >> 3 >= next_col_chunk_load && !level_end_reached) {
      level_load_column(next_col_chunk_load + DEVICE_SCREEN_WIDTH + 6, 1);
      next_col_chunk_load++;

      EMU_printf("next col load %d camera %d camera_subpixel %d\n",
                 next_col_chunk_load, camera_x, camera_x_upscaled);
    }

    vsync();
  }
}
