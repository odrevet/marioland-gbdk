#include "game.h"

void init(void) {
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

void state_pause(void) {
  text_print_string_win(DEVICE_SCREEN_WIDTH - 5, 1, "PAUSE");

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

void die(void) {
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
