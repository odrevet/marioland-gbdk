#include <stdint.h>

#include <gb/gb.h>
#include <gbdk/emu_debug.h>

#include "../src/graphics/common.h"
#include "../src/graphics/mario.h"

#include "../src/game.h"
#include "../src/global.h"
#include "../src/level.h"
#include "../src/player.h"

#define PLAYER_SPEED 12
#define PLAYER_DRAW_OFFSET_X 4
#define PLAYER_DRAW_OFFSET_Y 4

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

  player_x_upscaled = (4 << 3) << 4;
  player_y_upscaled = 100 << 4;

  DISPLAY_ON;
  SHOW_BKG;
  SHOW_SPRITES;
  SPRITES_8x8;

  while (1) {
    joypad_current = joypad();

    if (joypad_current & J_RIGHT) {
      player_x_upscaled += PLAYER_SPEED;
    }

    if (joypad_current & J_DOWN) {
      player_y_upscaled += PLAYER_SPEED;
    }

    if (joypad_current & J_LEFT) {
      player_x_upscaled -= PLAYER_SPEED;
    }

    if (joypad_current & J_UP) {
      player_y_upscaled -= PLAYER_SPEED;
    }

    player_x = player_x_upscaled >> 4;
    player_y = player_y_upscaled >> 4;

    // check scroll limit
    if (player_x > scroll_limit) {
      // update camera and scroll register
      camera_x_upscaled += 16;
      camera_x = camera_x_upscaled >> 4;
      SCX_REG = camera_x;

      // increase the scroll limit
      scroll_limit = player_x;
    }

    player_draw_x = player_x + DEVICE_SPRITE_PX_OFFSET_X +
                    PLAYER_DRAW_OFFSET_X - camera_x;
    player_draw_y = player_y + DEVICE_SPRITE_PX_OFFSET_Y +
                    MARGIN_TOP_PX + PLAYER_DRAW_OFFSET_Y;

    EMU_printf("Camera x : %d. player X draw %d, subpixel %d\n", camera_x,
               player_draw_x, player_x);

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
