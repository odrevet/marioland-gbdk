#pragma bank 255

#include "game.h"
#include "global.h"
#include "level.h"

#ifdef NINTENDO
#include "musicmanager.h"
#include "musics.h"
#endif

void init(void) BANKED {
  time = TIME_INITIAL_VALUE;

  camera_x = 0;
  camera_x_upscaled = 0;

  player_x_upscaled = (5 * TILE_SIZE) << 4;

if(current_level >= LEVEL_WORLD2_START && current_level <= LEVEL_WORLD2_END){
    player_y_upscaled = (12 * TILE_SIZE) << 4;
  }
else{
    player_y_upscaled = (14 * TILE_SIZE) << 4;
  }



  player_x = player_x_upscaled >> 4;
  player_y = player_y_upscaled >> 4;
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
  marioSpritesflip = FALSE;
  touch_ground = FALSE;
  player_ducking = FALSE;
  player_super_ball_timer = 0;

  current_column_in_page = 0;
  map_column = 0;
}

void state_title(void) BANKED {
while (1) {
vsync();
    joypad_previous = joypad_current;
    joypad_current = joypad();
if (joypad_current & J_START && !(joypad_previous & J_START)) {
break;
    }
  }
}

// Debug placement: speed in pixels per frame and movement limits.
#define PLACE_SPEED 2
#define PLACE_MAX_Y (LEVEL_HEIGHT * TILE_SIZE - 16)

#define PAUSE_TEXT_PAUSE 0
#define PAUSE_TEXT_PLACE 1
#define PAUSE_TEXT_BLANK 2

// Prints the pause label. The strings are local arrays (RAM) on purpose:
// a string literal would live in this ROM bank and text_print_string cannot
// read it once it switches banks, which shows up as "?" characters.
static void pause_text(uint8_t which) {
  char pause_str[6] = {'P', 'A', 'U', 'S', 'E', '\0'};
  char place_str[6] = {'P', 'L', 'A', 'C', 'E', '\0'};
  char blank_str[6] = {' ', ' ', ' ', ' ', ' ', '\0'};

  if (which == PAUSE_TEXT_PAUSE) {
    text_print_string(DEVICE_SCREEN_WIDTH - 5, 1, pause_str);
  } else if (which == PAUSE_TEXT_PLACE) {
    text_print_string(DEVICE_SCREEN_WIDTH - 5, 1, place_str);
  } else {
    text_print_string(DEVICE_SCREEN_WIDTH - 5, 1, blank_str);
  }
}

// Recompute the draw position from the logical position and redraw Mario.
static void place_refresh(void) {
  player_x_upscaled = player_x << 4;
  player_y_upscaled = player_y << 4;
  player_x_next_upscaled = player_x_upscaled;
  player_y_next_upscaled = player_y_upscaled;
  player_draw_x =
      player_x + DEVICE_SPRITE_PX_OFFSET_X + PLAYER_DRAW_OFFSET_X - camera_x;
  player_draw_y = player_y + DEVICE_SPRITE_PX_OFFSET_Y + MARGIN_TOP_PX +
                  PLAYER_DRAW_OFFSET_Y;
  hide_sprites_range(0, MAX_HARDWARE_SPRITES);
  player_draw(0);
}

void state_pause(void) BANKED {
bool placing = FALSE;

pause_text(PAUSE_TEXT_PAUSE);

while (1) {
vsync();

    joypad_previous = joypad_current;
    joypad_current = joypad();

if (placing) {
      // Placement mode: the d-pad moves Mario, B returns to the skip
      // controls, Start leaves the pause.
      bool moved = FALSE;

if (joypad_current & J_LEFT) {
        if (player_x >= camera_x + PLACE_SPEED) {
          player_x -= PLACE_SPEED;
          moved = TRUE;
        }
      } else if (joypad_current & J_RIGHT) {
        if (player_x + PLACE_SPEED + 8 <= camera_x + DEVICE_SCREEN_PX_WIDTH) {
          player_x += PLACE_SPEED;
          moved = TRUE;
        }
      }

if (joypad_current & J_UP) {
        if (player_y >= PLACE_SPEED) {
          player_y -= PLACE_SPEED;
          moved = TRUE;
        }
      } else if (joypad_current & J_DOWN) {
        if (player_y + PLACE_SPEED <= PLACE_MAX_Y) {
          player_y += PLACE_SPEED;
          moved = TRUE;
        }
      }

if (moved) {
        place_refresh();
      }

if (joypad_current & J_B && !(joypad_previous & J_B)) {
        placing = FALSE;
        pause_text(PAUSE_TEXT_PAUSE);
      }

if (joypad_current & J_START && !(joypad_previous & J_START)) {
        break;
      }
    } else {
      // Debug: Up goes to the next level, Down to the previous one.
if (joypad_current & J_UP && !(joypad_previous & J_UP)) {
        map_column = 0;
        current_level = (current_level + 1) % NB_LEVELS;
init();
level_set_current();
      }

if (joypad_current & J_DOWN && !(joypad_previous & J_DOWN)) {
        map_column = 0;
        if (current_level == 0) {
          current_level = NB_LEVELS - 1;
        } else {
          current_level--;
        }
init();
level_set_current();
      }

      // Debug: Right advances one page of the current level, Left goes back
      // one page. Both wrap around at the ends. The page is derived from
      // Mario's position (current_page runs ahead of the camera because of
      // column preloading).
if (joypad_current & J_RIGHT && !(joypad_previous & J_RIGHT)) {
        uint8_t page_count = levels[current_level].page_count;
        uint8_t next_page = player_x / (PAGE_SIZE * TILE_SIZE);
        if (next_page >= page_count) {
          next_page = page_count - 1;
        }
        next_page = (next_page + 1) % page_count;
        player_warp_to(levels + current_level, next_page, 5, 12);
      }

if (joypad_current & J_LEFT && !(joypad_previous & J_LEFT)) {
        uint8_t page_count = levels[current_level].page_count;
        uint8_t page = player_x / (PAGE_SIZE * TILE_SIZE);
        if (page >= page_count) {
          page = page_count - 1;
        }
        page = (page == 0) ? page_count - 1 : page - 1;
        player_warp_to(levels + current_level, page, 5, 12);
      }

      // Start enters placement mode, a second Start unpauses.
if (joypad_current & J_START && !(joypad_previous & J_START)) {
        placing = TRUE;
        pause_text(PAUSE_TEXT_PLACE);
        place_refresh();
      }
    }
  }

#ifdef GAMEBOY
hUGE_mute_channel(0, HT_CH_PLAY);
hUGE_mute_channel(1, HT_CH_PLAY);
hUGE_mute_channel(2, HT_CH_PLAY);
hUGE_mute_channel(3, HT_CH_PLAY);
#endif 

pause_text(PAUSE_TEXT_BLANK);
hud_update_time();
}

#define DEATH_BOUNCE_VELOCITY -40  // Initial upward velocity for bounce
#define DEATH_GRAVITY 2            // Gravity during death animation
#define DEATH_ANIMATION_FRAME 6

void die(void) BANKED {
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
// Wait after Mario falls off screen (~2 seconds) while idling the CPU.
WAIT_FRAMES(120);

//init();

  lives--;
if (lives == 0) {
    lives = INITIAL_LIVES;
    current_map = 0;
    current_page = 0;
    current_level = 0;
set_level(current_level);
  }

player_warp_to(levels + current_level, 0, 5, 12);

#ifdef GAMEBOY
music_load(levels[current_level].music_bank, levels[current_level].music);
#endif

hud_update_lives();

}