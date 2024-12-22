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

#pragma bank 255 
#include "../res/level_1_1.h"
INCBIN(map_1_1, "res/level_1_1_map.bin.rle")

//#include "../res/level_1_2.h"
//INCBIN(map_1_2, "res/level_1_2_map.bin.rle")

//#include "../res/level_1_3.h"
//INCBIN(map_1_3, "res/level_1_3_map.bin.rle")


#include "../res/common.h"
INCBIN(common_tiles_bin, "res/common_tiles.bin")

#include "../res/birabuto.h"
INCBIN(birabuto_tiles_bin, "res/birabuto_tiles.bin")


const uint8_t window_location = WINDOW_Y + WINDOW_HEIGHT_TILE * TILE_SIZE;

uint8_t coins;
uint16_t score;
uint8_t joy;
uint16_t time;
uint8_t lives;
uint8_t level_index;
uint8_t joypad_previous, joypad_current;
uint8_t nb_col = COLUMN_CHUNK_SIZE;

// player coords and movements
uint16_t player_x_subpixel;
uint16_t player_y_subpixel;
uint16_t player_x_subpixel_next;
uint16_t player_y_subpixel_next;
uint8_t player_draw_x;
uint8_t player_draw_y;
uint8_t player_draw_x_next;
uint8_t player_draw_y_next;
int8_t vel_x;
int8_t vel_y;
bool is_jumping = FALSE;
bool display_jump_frame;
bool display_slide_frame;
bool touch_ground = FALSE;
uint8_t current_jump = 0;
int8_t player_max_speed = PLAYER_MAX_SPEED_WALK;
uint8_t player_frame = 0;
uint8_t frame_counter = 0;
bool mario_flip;
uint8_t current_gravity = GRAVITY;


uint8_t next_pos;
uint8_t tile_next_1;
uint8_t tile_next_2;

uint8_t scroll;

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

inline bool is_coin(uint8_t tile) { return tile == TILE_COIN; }

inline void on_get_coin(uint8_t x, uint8_t y) {
  uint16_t index = ((y / TILE_SIZE - DEVICE_SPRITE_OFFSET_Y) * MAP_BUFFER_WIDTH) + 
                   (((x + camera_x) / TILE_SIZE) % MAP_BUFFER_WIDTH);
  map_buffer[index] = TILE_EMPTY;

  set_bkg_tile_xy(((x + camera_x) / TILE_SIZE) % DEVICE_SCREEN_BUFFER_WIDTH,
                  y / TILE_SIZE - DEVICE_SPRITE_OFFSET_Y, TILE_EMPTY);

  sound_play_coin();

  coins++;
  score += 100;

  if (coins == 100) {
    lives++;
    coins = 0;
  }

  hud_update_coins();
  hud_update_score();
}

void hud_update_coins() {
  char coins_str[3];

  if (coins < 10) {
    coins_str[0] = '0'; // Add leading zero
    itoa(coins, coins_str + 1, 10);
  } else {
    itoa(coins, coins_str, 10);
  }

  text_print_string_win(9, 1, coins_str);
}

void hud_update_score() {
  char score_str[5];
  itoa(score, score_str, 10);
  text_print_string_win(3, 1, score_str);
}

void hud_update_time() {
  char time_str[4];
  itoa(time / 40, time_str, 10);
  text_print_string_win(DEVICE_SCREEN_WIDTH - 3, 1, "000");
  text_print_string_win(DEVICE_SCREEN_WIDTH - strlen(time_str), 1, time_str);
}

void hud_update_lives() {
  char lives_str[4];
  itoa(lives, lives_str, 10);
  // text_print_string_win(8, 0, "00");
  text_print_string_win(7, 0, lives_str);
}

void player_draw() {
  metasprite_t *const mario_metasprite = mario_metasprites[player_frame];
  if (mario_flip) {
    move_metasprite_flipx(mario_metasprite, 0, 0, 0, player_draw_x + TILE_SIZE,
                          player_draw_y + DEVICE_SPRITE_PX_OFFSET_Y -
                              TILE_SIZE);
  } else {
    move_metasprite_ex(mario_metasprite, 0, 0, 0, player_draw_x + TILE_SIZE,
                       player_draw_y + DEVICE_SPRITE_PX_OFFSET_Y - TILE_SIZE);
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

  level_index = 0;

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

  uint8_t x_right_draw;
  uint8_t x_left_draw;
  uint8_t y_top_draw;
  uint8_t y_bottom_draw;

  while (1) {
    vsync();
//
//    // inputs
//    joypad_previous = joypad_current;
//    joypad_current = joypad();
//
//    if (joypad_current & J_RIGHT) {
//      if (vel_x < player_max_speed) {
//        vel_x += 1;
//        if(display_jump_frame == FALSE){
//          mario_flip = FALSE;
//          }
//        if (vel_x < 0) {
//          display_slide_frame = TRUE;
//        } else {
//          display_slide_frame = FALSE;
//        }
//      } else if (vel_x > player_max_speed) {
//        vel_x -= 1;
//      }
//    } else if (vel_x > 0) {
//      vel_x -= 1;
//    }
//
//    if ((joypad_current & J_LEFT)) {
//      if (abs(vel_x) < player_max_speed) {
//        vel_x -= 1;
//        if(display_jump_frame == FALSE){
//          mario_flip = TRUE;
//        }
//        if (vel_x > 0) {
//          display_slide_frame = TRUE;
//        } else {
//          display_slide_frame = FALSE;
//        }
//      } else if (abs(vel_x) > player_max_speed) {
//        vel_x += 1;
//      }
//    } else if (vel_x < 0) {
//      vel_x += 1;
//    }
//
//    if (joypad_current & J_A && !(joypad_previous & J_A) && !is_jumping &&
//        touch_ground) {
//      is_jumping = TRUE;
//      display_jump_frame = TRUE;
//      vel_y = -JUMP_SPEED;
//      sound_play_jump();
//    }
//
//    // pause
//    if (joypad_current & J_START && !(joypad_previous & J_START)) {
//      pause();
//    }
//
//    if (joypad_current & J_B) {
//      player_max_speed = PLAYER_MAX_SPEED_RUN;
//    } else {
//      player_max_speed = PLAYER_MAX_SPEED_WALK;
//    }
//
//    if (is_jumping) {
//      vel_y += GRAVITY_JUMP;
//      if (vel_y > TERMINAL_VELOCITY) {
//        vel_y = TERMINAL_VELOCITY;
//      }
//    } else {
//      vel_y = GRAVITY;
//    }
//
//    x_right_draw = player_draw_x + MARIO_HALF_WIDTH - 1;
//    x_left_draw = player_draw_x - MARIO_HALF_WIDTH;
//    y_top_draw = player_draw_y - MARIO_HALF_WIDTH;
//    y_bottom_draw = player_draw_y - 1;
//
//    // apply velocity to player coords
//    if (vel_x != 0) {
//      player_x_subpixel_next = player_x_subpixel + vel_x;
//      player_draw_x_next = player_x_subpixel_next >> 4;
//
//      // move right
//      if (vel_x > 0) {
//        next_pos = player_draw_x_next + MARIO_HALF_WIDTH;
//        tile_next_1 = get_tile(next_pos, y_top_draw);    // tile_right_top
//        tile_next_2 = get_tile(next_pos, y_bottom_draw); // tile_right_bottom
//
//        if (is_tile_solid(tile_next_1) || is_tile_solid(tile_next_2)) {
//          vel_x = 0;
//          uint8_t diff = camera_x % TILE_SIZE;
//
//          // (((player_draw_x_next / TILE_SIZE) + 1) * TILE_SIZE)
//          player_draw_x =
//              (((player_draw_x_next & ~(TILE_SIZE - 1)) + TILE_SIZE) - diff -
//               MARIO_HALF_WIDTH) +
//              (diff > 4 ? 8 : 0);
//          player_x_subpixel = player_draw_x << 4;
//
//        } else {
//          if (is_coin(tile_next_1)) {
//            on_get_coin(next_pos, y_top_draw);
//          }
//
//          if (is_coin(tile_next_2)) {
//            on_get_coin(next_pos, y_bottom_draw);
//          }
//          player_x_subpixel = player_x_subpixel_next;
//          player_draw_x = player_x_subpixel >> 4;
//        }
//
//        // scroll
//        if (!level_end_reached && player_draw_x >= DEVICE_SCREEN_PX_WIDTH_HALF) {
//          scroll = player_x_subpixel - (DEVICE_SCREEN_PX_WIDTH_HALF << 4);
//
//          camera_x_subpixel += scroll;
//          camera_x = camera_x_subpixel >> 4;
//          SCX_REG = camera_x;
//
//          player_x_subpixel = DEVICE_SCREEN_PX_WIDTH_HALF << 4;
//          player_draw_x = DEVICE_SCREEN_PX_WIDTH_HALF;
//
//          if (camera_x >> 3 >= next_col_chunk_load) {
//            nb_col = bkg_load_column(next_col_chunk_load + DEVICE_SCREEN_WIDTH,
//                                     nb_col);
//
//            if (nb_col == 0) {
//              level_end_reached = true;
//              nb_col = COLUMN_CHUNK_SIZE;
//            } else {
//              next_col_chunk_load += nb_col;
//            }
//          }
//        }
//      }
//      // move left
//      else if (vel_x < 0) {
//        next_pos = player_draw_x_next - MARIO_HALF_WIDTH;
//        tile_next_1 = get_tile(next_pos, y_top_draw);    // tile_left_top
//        tile_next_2 = get_tile(next_pos, y_bottom_draw); // tile_left_bottom
//
//        if (player_draw_x_next < MARIO_HALF_WIDTH) {
//          player_draw_x = MARIO_HALF_WIDTH;
//          player_x_subpixel = player_draw_x << 4;
//        } else {
//          if (is_tile_solid(tile_next_1) || is_tile_solid(tile_next_2)) {
//            vel_x = 0;
//            uint8_t diff = camera_x % TILE_SIZE;
//
//            // (((player_draw_x_next / TILE_SIZE) + 1) * TILE_SIZE)
//            player_draw_x =
//                ((((player_draw_x_next & ~(TILE_SIZE - 1)) + TILE_SIZE)) -
//                 diff - MARIO_HALF_WIDTH) +
//                (diff < 4 ? 0 : 8);
//            player_x_subpixel = player_draw_x << 4;
//          } else {
//            if (is_coin(tile_next_1)) {
//              on_get_coin(next_pos, y_top_draw);
//            }
//
//            if (is_coin(tile_next_2)) {
//              on_get_coin(next_pos, y_bottom_draw);
//            }
//
//            player_x_subpixel = player_x_subpixel_next;
//            player_draw_x = player_x_subpixel >> 4;
//          }
//        }
//      }
//    }
//
//    if (vel_y != 0) {
//      player_y_subpixel_next = player_y_subpixel + vel_y;
//      player_draw_y_next = player_y_subpixel_next >> 4;
//
//      // move down
//      if (vel_y > 0) {
//        next_pos = player_draw_y_next;
//        uint8_t tile_left_bottom = get_tile(x_left_draw, next_pos);
//        uint8_t tile_right_bottom = get_tile(x_right_draw, next_pos);
//
//        if (is_tile_solid(tile_left_bottom) ||
//            is_tile_solid(tile_right_bottom)) {
//           player_y_subpixel = ((next_pos / TILE_SIZE) * TILE_SIZE) << 4;
//
//          touch_ground = TRUE;
//          current_jump = 0;
//          is_jumping = FALSE;
//          display_jump_frame = FALSE;
//        } else {
//          if (is_coin(tile_left_bottom)) {
//            on_get_coin(x_left_draw, next_pos);
//          }
//
//          if (is_coin(tile_right_bottom)) {
//            on_get_coin(x_right_draw, next_pos);
//          }
//
//          touch_ground = FALSE;
//          player_y_subpixel = player_y_subpixel_next;
//        }
//      }
//
//      // move up
//      else if (vel_y < 0) {
//        next_pos = player_draw_y_next - 6;
//        uint8_t tile_left_top = get_tile(x_left_draw, next_pos);
//        uint8_t tile_right_top = get_tile(x_right_draw, next_pos);
//
//        if (is_tile_solid(tile_left_top) || is_tile_solid(tile_right_top)) {
//           player_y_subpixel =
//               ((player_draw_y_next / TILE_SIZE) * TILE_SIZE + TILE_SIZE) <<
//               4;
//
//          current_jump = 0;
//          is_jumping = FALSE;
//          sound_play_bump();
//        } else {
//          if (is_coin(tile_left_top)) {
//            on_get_coin(x_left_draw, next_pos);
//          }
//
//          if (is_coin(tile_right_top)) {
//            on_get_coin(x_right_draw, next_pos);
//          }
//          player_y_subpixel = player_y_subpixel_next;
//        }
//      }
//      player_draw_y = player_y_subpixel >> 4;
//    }
//
//    // set player frame
//    if (display_jump_frame) {
//      player_frame = 4;
//    } else if (vel_x != 0) {
//      if (display_slide_frame) {
//        player_frame = 5;
//      } else {
//        update_frame_counter();
//      }
//    } else {
//      player_frame = 0;
//    }
//
//    // enemy_update();
//    // enemy_draw(SPRITE_START_ENEMIES);
//
//
//    if (joypad_current & J_SELECT && !(joypad_previous & J_SELECT)) {
//      init();
//      next_level();
//    }
//
//
//    // print DEBUG text
//#if defined(DEBUG)
//    char buffer[WINDOW_SIZE + 1];
//    sprintf(buffer, 
//            "%d.%d.%d.%d.%d.\n.%d.%d.%d.%d.", 
//            (uint16_t)player_x_subpixel,
//            (uint16_t)player_y_subpixel, 
//            player_draw_x, 
//            vel_x, 
//            vel_y,
//            camera_x, 
//            scroll, 
//            current_map_width, 
//            level_end_reached);
//    text_print_string_win(0, 0, buffer);
//#else
//    time--;
//    hud_update_time();
//    if (time == 0) {
//      time = TIME_INITIAL_VALUE;
//      lives--;
//      hud_update_lives();
//    }
//#endif
//
//    // if fall under screen
//    if (player_draw_y > DEVICE_SCREEN_PX_HEIGHT) {
//      die();
//    }
//
//    // if reach end of level
//    if(level_end_reached && player_draw_x >= (DEVICE_SCREEN_WIDTH - 2) * TILE_SIZE){
//      init();
//      next_level();
//    }
//
//    player_draw();
  }
}
