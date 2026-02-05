#include "game.h"
#include "global.h"
#include "level.h"

void init(void) {
  time = TIME_INITIAL_VALUE;

  camera_x = 0;
  camera_x_upscaled = 0;

  player_x_upscaled = (5 * TILE_SIZE) << 4;
  player_y_upscaled = (14 * TILE_SIZE) << 4;
  player_draw_x = player_x_upscaled >> 4;
  player_draw_y = player_y_upscaled >> 4;
  player_x_next_upscaled = player_x_upscaled;
  player_y_next_upscaled = player_y_upscaled;

  vel_x = 0;
  vel_y = 0;

  display_jump_frame = FALSE;
  display_slide_frame = FALSE;
  display_walk_animation = FALSE;

  frame_counter = 0;
  mario_flip = FALSE;
  touch_ground = FALSE;
}

void state_title(void) {
  while (1) {
    vsync();
    
    joypad_previous = joypad_current;
    joypad_current = joypad();
    if (joypad_current & J_START && !(joypad_previous & J_START)) {
      break;
    }
  }
}

void state_pause(void) {
  text_print_string(DEVICE_SCREEN_WIDTH - 5, 1, "PAUSE");

  while (1) {
    vsync();

    joypad_previous = joypad_current;
    joypad_current = joypad();

    if (joypad_current & J_SELECT && !(joypad_previous & J_SELECT)) {
      init();
      current_level = (++current_level) % NB_LEVELS;
      level_set_current();
    }

    if (joypad_current & J_START && !(joypad_previous & J_START)) {
      break;
    }
  }

  #ifdef GAMEBOY
  hUGE_mute_channel(0, HT_CH_PLAY);
  hUGE_mute_channel(1, HT_CH_PLAY);
  hUGE_mute_channel(2, HT_CH_PLAY);
  hUGE_mute_channel(3, HT_CH_PLAY);
  #endif 

  text_print_string(DEVICE_SCREEN_WIDTH - 5, 1, "     ");
  hud_update_time();
}

#define DEATH_BOUNCE_VELOCITY -40  // Initial upward velocity for bounce
#define DEATH_GRAVITY 2            // Gravity during death animation
#define DEATH_ANIMATION_FRAME 6

void die(void) {
  #ifdef GAMEBOY
  hUGE_mute_channel(0, HT_CH_PLAY);
  hUGE_mute_channel(1, HT_CH_PLAY);
  hUGE_mute_channel(2, HT_CH_PLAY);
  hUGE_mute_channel(3, HT_CH_PLAY);

  music_load(BANK(music_defeat), &music_defeat);
  #endif

  player_frame = DEATH_ANIMATION_FRAME;  // Death pose
    
  // Initialize death animation variables
  int16_t death_vel_y = DEATH_BOUNCE_VELOCITY;
  uint16_t death_y = player_y_upscaled;
  
#if defined(GAMEBOY)
  // Freeze game and perform death animation
  while (player_draw_y < DEVICE_SCREEN_PX_HEIGHT ) {
      // Apply gravity
      death_vel_y += DEATH_GRAVITY;
      death_y += death_vel_y;
      
      // Update Mario's position
      player_y = death_y >> 4;
      player_draw_y = player_y + DEVICE_SPRITE_PX_OFFSET_Y + 
                      MARGIN_TOP_PX + PLAYER_DRAW_OFFSET_Y;
      
      // Draw Mario in death pose
      player_draw(0);
      
      // Wait for next frame
      vsync();
  }
    
  // Wait after Mario falls off screen
  delay(2000);
#endif

  init();

  lives--;
  if (lives == 0) {
    lives = INITIAL_LIVES;
    current_map = 0;
    set_level(0);
  }

  hud_update_lives();
  load_current_level();
  level_set_current();
}
