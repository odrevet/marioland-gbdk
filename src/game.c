#include "game.h"


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

