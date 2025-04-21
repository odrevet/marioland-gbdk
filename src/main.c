
#include <gb/gb.h>
#include <gbdk/metasprites.h>
#include <gbdk/platform.h>

#include "graphics/common.h"
#include "graphics/enemies.h"
#include "graphics/mario.h"
#include "graphics/text.h"

#include "enemy.h"
#include "game.h"
#include "global.h"
#include "graphics/text.h"
#include "hUGEDriver.h"
#include "level.h"
#include "player.h"
#include "sound.h"
#include "text.h"

#include "songs/overworld.h"

const uint8_t window_location = WINDOW_Y + WINDOW_HEIGHT_TILE * TILE_SIZE;


void interruptLCD(void) {
  while (STAT_REG & 3)
    ;
  HIDE_WIN;
}

void interruptVBL(void) { SHOW_WIN; }

void play_sound_vbl(void) NONBANKED {
  uint8_t _previous_bank = _current_bank;
  SWITCH_ROM(BANK(overworld_bank));
  hUGE_dosound();
  SWITCH_ROM(_previous_bank);
}

void main(void) {
  STAT_REG = 0x40;
  LYC_REG = 0x0F;

  move_bkg(0, -MARGIN_TOP_PX);

  disable_interrupts();
  add_LCD(interruptLCD);
  add_VBL(interruptVBL);
  set_interrupts(VBL_IFLAG | LCD_IFLAG);
  enable_interrupts();

  sound_init();
  __critical {
    uint8_t _previous_bank = _current_bank;
    SWITCH_ROM(BANK(overworld_bank));
    hUGE_init(&overworld);
    add_VBL(play_sound_vbl);
    SWITCH_ROM(_previous_bank);
  };

  // joypad
  joypad_previous, joypad_current = 0;

  // player
  player_x_subpixel = 43 << 4;
  player_y_subpixel = (16 * TILE_SIZE) << 4;
  player_draw_x = player_x_subpixel >> 4;
  player_draw_y = player_y_subpixel >> 4;

  set_sprite_data(SPRITE_START_MARIO, mario_TILE_COUNT, mario_tiles);
  // set_sprite_data(SPRITE_START_ENEMIES, enemies_TILE_COUNT, enemies_tiles);

  init();
  set_level_1_1();
  load_current_level();

  score = 0;
  lives = INITIAL_LIVES;
  coins = 0;

  // HUD
  // text
  unsigned char windata[WINDOW_SIZE];
  memset(windata, 15, WINDOW_SIZE);
  set_win_tiles(0, 0, WINDOW_WIDTH_TILE, WINDOW_HEIGHT_TILE, windata);
  move_win(WINDOW_X, WINDOW_Y);
  text_print_string_win(0, 0, "MARIOx00  WORLD TIME");
  text_print_string_win(0, 1, "     0  x00 1-1  000");

  // display a coin in the HUD
  set_win_tile_xy(7, 1, TILE_COIN);
  hud_update_time();
  hud_update_lives();

  // Set music channels channel
  hUGE_mute_channel(0, HT_CH_PLAY);
  hUGE_mute_channel(1, HT_CH_PLAY);
  hUGE_mute_channel(2, HT_CH_PLAY);
  hUGE_mute_channel(3, HT_CH_PLAY);

  // spawn enemies
  // enemy_new(50, 136, ENEMY_TYPE_GOOMBA);
  // enemy_new(70, 136, ENEMY_TYPE_KOOPA);

  // text and common bkg data
  uint8_t previous_bank = _current_bank;

  SWITCH_ROM(BANK(text));
  set_bkg_data(text_TILE_ORIGIN, text_TILE_COUNT, text_tiles);

  SWITCH_ROM(BANK(common));
  set_bkg_data(common_TILE_ORIGIN, common_TILE_COUNT, common_tiles);

  SWITCH_ROM(previous_bank);

  DISPLAY_ON;
  SHOW_BKG;
  SHOW_WIN;
  SHOW_SPRITES;
  SPRITES_8x16;

  while (1) {
    vsync();

    // inputs
    joypad_previous = joypad_current;
    joypad_current = joypad();

    player_move();

    // set player frame
    if (display_jump_frame) {
      player_frame = 4;
    } else if (vel_x != 0) {
      if (display_slide_frame) {
        player_frame = 5;
      } else {
        update_frame_counter();
      }
    } else {
      player_frame = 0;
    }

    // enemy_update();
    // enemy_draw(SPRITE_START_ENEMIES);

    if (joypad_current & J_SELECT && !(joypad_previous & J_SELECT)) {
      init();
      current_level = (++current_level) % NB_LEVELS;
      level_set_current();
      load_current_level();
    }

    time--;
    hud_update_time();
    if (time == 0) {
      time = TIME_INITIAL_VALUE;
      lives--;
      hud_update_lives();
    }

    // if fall under screen
    if (player_draw_y > DEVICE_SCREEN_PX_HEIGHT) {
      player_y_subpixel = 0;
      // die();
    }

    // if reach end of level
    if (level_end_reached &&
        player_draw_x >= (DEVICE_SCREEN_WIDTH - 2) * TILE_SIZE) {
      init();
      current_level = (++current_level) % NB_LEVELS;
      level_set_current();
      load_current_level();
    }

    player_draw();
  }
}