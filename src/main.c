#include <gb/gb.h>
#include <gb/metasprites.h>
#include <gbdk/incbin.h>
#include <gbdk/platform.h>
#include <gbdk/rledecompress.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphics/enemies.h"
#include "graphics/text.h"
#include "graphics/mario.h"

#include "enemy.h"
#include "global.h"
#include "graphics/text.h"
#include "hUGEDriver.h"
#include "sound.h"
#include "text.h"
#include "level.h"
#include "player.h"

#pragma bank 255 
#include "../res/level_1_1.h"
INCBIN(map_1_1, "res/level_1_1_map.bin.rle")

#include "../res/level_1_2.h"
INCBIN(map_1_2, "res/level_1_2_map.bin.rle")

//#include "../res/level_1_3.h"
//INCBIN(map_1_3, "res/level_1_3_map.bin.rle")


#include "../res/common.h"
INCBIN(common_tiles_bin, "res/common_tiles.bin")

#include "../res/birabuto.h"
INCBIN(birabuto_tiles_bin, "res/birabuto_tiles.bin")


const uint8_t window_location = WINDOW_Y + WINDOW_HEIGHT_TILE * TILE_SIZE;



#define INITIAL_LIVES 3

// music
extern const hUGESong_t overworld;

void update_frame_counter() {
  frame_counter++;
  if (frame_counter == LOOP_PER_ANIMATION_FRAME) {
    frame_counter = 0;
    player_frame = (player_frame % 3) + 1;
  }
}

void interruptLCD() {
  while (STAT_REG & 3)
    ;
  HIDE_WIN;
}

void interruptVBL() { SHOW_WIN; }

void pause() {
  hUGE_mute_channel(0, HT_CH_MUTE);
  hUGE_mute_channel(1, HT_CH_MUTE);
  hUGE_mute_channel(2, HT_CH_MUTE);
  hUGE_mute_channel(3, HT_CH_MUTE);

  sound_play_bump();
  text_print_string_win(DEVICE_SCREEN_WIDTH - 5, 1, "PAUSE");

#if defined(DEBUG)
  // debug a column of background
  char buffer[WINDOW_SIZE + 1];
  char fmt[] = "%d.%d.%d.%d.%d.%d.%d..";
  uint8_t col = player_draw_x / TILE_SIZE;
  
  for (uint8_t row = 0; row < 7; row++) {
    uint16_t index = (row * MAP_BUFFER_WIDTH) + col;
    sprintf(buffer, fmt, 
            map_buffer[index], 
            map_buffer[index + MAP_BUFFER_WIDTH], 
            map_buffer[index + 2 * MAP_BUFFER_WIDTH], 
            map_buffer[index + 3 * MAP_BUFFER_WIDTH], 
            map_buffer[index + 4 * MAP_BUFFER_WIDTH], 
            map_buffer[index + 5 * MAP_BUFFER_WIDTH], 
            map_buffer[index + 6 * MAP_BUFFER_WIDTH]);
    text_print_string_win(0, row, buffer);
  }
#endif


  vsync();

  while (1) {
    joypad_previous = joypad_current;
    joypad_current = joypad();
    if (joypad_current & J_START && !(joypad_previous & J_START)) {
      break;
    }
  }

  hUGE_mute_channel(0, HT_CH_PLAY);
  hUGE_mute_channel(1, HT_CH_PLAY);
  hUGE_mute_channel(2, HT_CH_PLAY);
  hUGE_mute_channel(3, HT_CH_PLAY);

  text_print_string_win(DEVICE_SCREEN_WIDTH - 5, 1, "     ");
  hud_update_time();
}



void init() {
  time = TIME_INITIAL_VALUE;

  camera_x = 0;
  camera_x_subpixel = 0;
  SCX_REG = 0;

  player_x_subpixel = 43 << 4;
  player_y_subpixel = (16 * TILE_SIZE) << 4;
  player_draw_x = player_x_subpixel >> 4;
  player_draw_y = player_y_subpixel >> 4;

  vel_x = 0;
  vel_y = 0;

  display_jump_frame = FALSE;
  display_slide_frame = FALSE;

  frame_counter = 0;
  mario_flip = FALSE;
}

void die() {
  hUGE_mute_channel(0, HT_CH_PLAY);
  hUGE_mute_channel(1, HT_CH_PLAY);
  hUGE_mute_channel(2, HT_CH_PLAY);
  hUGE_mute_channel(3, HT_CH_PLAY);

  init();

  lives--;
  if(lives == 0){
    lives = INITIAL_LIVES;
    current_map = 0;
    set_level_1_1();
  }

  hud_update_lives();
  load_current_level();
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
    hUGE_init(&overworld);
    add_VBL(hUGE_dosound);
  };

  // joypad
  joypad_previous, joypad_current = 0;

  // player
  player_x_subpixel = 43 << 4;
  player_y_subpixel = (16 * TILE_SIZE) << 4;
  player_draw_x = player_x_subpixel >> 4;
  player_draw_y = player_y_subpixel >> 4;

  set_sprite_data(SPRITE_START_MARIO, mario_TILE_COUNT, mario_tiles);
  set_sprite_data(SPRITE_START_ENEMIES, enemies_TILE_COUNT, enemies_tiles);

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
  set_bkg_data(text_TILE_ORIGIN, text_TILE_COUNT, text_tiles);
  set_bkg_data(common_TILE_ORIGIN, INCBIN_SIZE(common_tiles_bin) >> 4, common_tiles_bin);


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

    if (joypad_current & J_RIGHT) {
      if (vel_x < player_max_speed) {
        vel_x += 1;
        if(display_jump_frame == FALSE){
          mario_flip = FALSE;
          }
        if (vel_x < 0) {
          display_slide_frame = TRUE;
        } else {
          display_slide_frame = FALSE;
        }
      } else if (vel_x > player_max_speed) {
        vel_x -= 1;
      }
    } else if (vel_x > 0) {
      vel_x -= 1;
    }

    if ((joypad_current & J_LEFT)) {
      if (abs(vel_x) < player_max_speed) {
        vel_x -= 1;
        if(display_jump_frame == FALSE){
          mario_flip = TRUE;
        }
        if (vel_x > 0) {
          display_slide_frame = TRUE;
        } else {
          display_slide_frame = FALSE;
        }
      } else if (abs(vel_x) > player_max_speed) {
        vel_x += 1;
      }
    } else if (vel_x < 0) {
      vel_x += 1;
    }

    if (joypad_current & J_A && !(joypad_previous & J_A) && !is_jumping &&
        touch_ground) {
      is_jumping = TRUE;
      display_jump_frame = TRUE;
      vel_y = -JUMP_SPEED;
      sound_play_jump();
    }

    // pause
    if (joypad_current & J_START && !(joypad_previous & J_START)) {
      pause();
    }

    if (joypad_current & J_B) {
      player_max_speed = PLAYER_MAX_SPEED_RUN;
    } else {
      player_max_speed = PLAYER_MAX_SPEED_WALK;
    }

    if (is_jumping) {
      vel_y += GRAVITY_JUMP;
      if (vel_y > TERMINAL_VELOCITY) {
        vel_y = TERMINAL_VELOCITY;
      }
    } else {
      vel_y = GRAVITY;
    }


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


    // print DEBUG text
#if defined(DEBUG)
    char buffer[WINDOW_SIZE + 1];
    sprintf(buffer, 
            "%d.%d.%d.%d.%d.\n.%d.%d.%d.%d.", 
            (uint16_t)player_x_subpixel,
            (uint16_t)player_y_subpixel, 
            player_draw_x, 
            vel_x, 
            vel_y,
            camera_x, 
            scroll, 
            current_map_width, 
            level_end_reached);
    text_print_string_win(0, 0, buffer);
#else
    time--;
    hud_update_time();
    if (time == 0) {
      time = TIME_INITIAL_VALUE;
      lives--;
      hud_update_lives();
    }
#endif

    // if fall under screen
    if (player_draw_y > DEVICE_SCREEN_PX_HEIGHT) {
      die();
    }

    // if reach end of level
    if(level_end_reached && player_draw_x >= (DEVICE_SCREEN_WIDTH - 2) * TILE_SIZE){
      init();
      current_level = (++current_level) % NB_LEVELS;
      level_set_current();
      load_current_level();
    }

    player_draw();
  }
}