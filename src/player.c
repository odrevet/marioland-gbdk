#pragma bank 255 

#include "player.h"

uint8_t x_right_draw;
uint8_t x_left_draw;
uint8_t y_top_draw;
uint8_t y_bottom_draw;


uint8_t coins;
uint16_t score;
uint8_t joy;
uint16_t time;
uint8_t lives;
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

#include <gbdk/emu_debug.h>

void update_frame_counter() {
  frame_counter++;
  if (frame_counter == LOOP_PER_ANIMATION_FRAME) {
    frame_counter = 0;
    player_frame = (player_frame % 3) + 1;
  }
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

void player_move() BANKED
{
    x_right_draw = player_draw_x + MARIO_HALF_WIDTH - 1;
    x_left_draw = player_draw_x - MARIO_HALF_WIDTH;
    y_top_draw = player_draw_y - MARIO_HALF_WIDTH;
    y_bottom_draw = player_draw_y - 1;

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
    
    // apply velocity to player coords
    if (vel_x != 0) {
      player_x_subpixel_next = player_x_subpixel + vel_x;
      player_draw_x_next = player_x_subpixel_next >> 4;

      // move right
      if (vel_x > 0) {
        next_pos = player_draw_x_next + MARIO_HALF_WIDTH;
        tile_next_1 = get_tile(next_pos, y_top_draw);    // tile_right_top
        tile_next_2 = get_tile(next_pos, y_bottom_draw); // tile_right_bottom

        if (is_tile_solid(tile_next_1) || is_tile_solid(tile_next_2)) {
          vel_x = 0;
          uint8_t diff = camera_x % TILE_SIZE;

          // (((player_draw_x_next / TILE_SIZE) + 1) * TILE_SIZE)
          player_draw_x =
              (((player_draw_x_next & ~(TILE_SIZE - 1)) + TILE_SIZE) - diff -
               MARIO_HALF_WIDTH) +
              (diff > 4 ? 8 : 0);
          player_x_subpixel = player_draw_x << 4;

        } else {
          if (is_coin(tile_next_1)) {
            on_get_coin(next_pos, y_top_draw);
          }

          if (is_coin(tile_next_2)) {
            on_get_coin(next_pos, y_bottom_draw);
          }
          player_x_subpixel = player_x_subpixel_next;
          player_draw_x = player_x_subpixel >> 4;
        }

        // scroll
        if (!level_end_reached && player_draw_x >= DEVICE_SCREEN_PX_WIDTH_HALF) {
          scroll = player_x_subpixel - (DEVICE_SCREEN_PX_WIDTH_HALF << 4);

          camera_x_subpixel += scroll;
          camera_x = camera_x_subpixel >> 4;
          SCX_REG = camera_x;

          player_x_subpixel = DEVICE_SCREEN_PX_WIDTH_HALF << 4;
          player_draw_x = DEVICE_SCREEN_PX_WIDTH_HALF;

          if (camera_x >> 3 >= next_col_chunk_load) {
            nb_col = level_load_column(next_col_chunk_load + DEVICE_SCREEN_WIDTH, nb_col);


            // WIP detect level end from level width
            if (nb_col == 0) {
              level_end_reached = true;
              nb_col = COLUMN_CHUNK_SIZE;
            } else {
              next_col_chunk_load += nb_col;
            }
          }
        }
      }
      // move left
      else if (vel_x < 0) {
        next_pos = player_draw_x_next - MARIO_HALF_WIDTH;
        tile_next_1 = get_tile(next_pos, y_top_draw);    // tile_left_top
        tile_next_2 = get_tile(next_pos, y_bottom_draw); // tile_left_bottom

        if (player_draw_x_next < MARIO_HALF_WIDTH) {
          player_draw_x = MARIO_HALF_WIDTH;
          player_x_subpixel = player_draw_x << 4;
        } else {
          if (is_tile_solid(tile_next_1) || is_tile_solid(tile_next_2)) {
            vel_x = 0;
            uint8_t diff = camera_x % TILE_SIZE;

            // (((player_draw_x_next / TILE_SIZE) + 1) * TILE_SIZE)
            player_draw_x =
                ((((player_draw_x_next & ~(TILE_SIZE - 1)) + TILE_SIZE)) -
                 diff - MARIO_HALF_WIDTH) +
                (diff < 4 ? 0 : 8);
            player_x_subpixel = player_draw_x << 4;
          } else {
            if (is_coin(tile_next_1)) {
              on_get_coin(next_pos, y_top_draw);
            }

            if (is_coin(tile_next_2)) {
              on_get_coin(next_pos, y_bottom_draw);
            }

            player_x_subpixel = player_x_subpixel_next;
            player_draw_x = player_x_subpixel >> 4;
          }
        }
      }
    }

    if (vel_y != 0) {
      player_y_subpixel_next = player_y_subpixel + vel_y;
      player_draw_y_next = player_y_subpixel_next >> 4;

      // move down
      if (vel_y > 0) {
        next_pos = player_draw_y_next;
        uint8_t tile_left_bottom = get_tile(x_left_draw, next_pos);
        uint8_t tile_right_bottom = get_tile(x_right_draw, next_pos);

        if (is_tile_solid(tile_left_bottom) ||
            is_tile_solid(tile_right_bottom)) {
           player_y_subpixel = ((next_pos / TILE_SIZE) * TILE_SIZE) << 4;

          touch_ground = TRUE;
          current_jump = 0;
          is_jumping = FALSE;
          display_jump_frame = FALSE;
        } else {
          if (is_coin(tile_left_bottom)) {
            on_get_coin(x_left_draw, next_pos);
          }

          if (is_coin(tile_right_bottom)) {
            on_get_coin(x_right_draw, next_pos);
          }

          touch_ground = FALSE;
          player_y_subpixel = player_y_subpixel_next;
        }
      }

      // move up
      else if (vel_y < 0) {
        next_pos = player_draw_y_next - 6;
        uint8_t tile_left_top = get_tile(x_left_draw, next_pos);
        uint8_t tile_right_top = get_tile(x_right_draw, next_pos);

        if (is_tile_solid(tile_left_top) || is_tile_solid(tile_right_top)) {
           player_y_subpixel =
               ((player_draw_y_next / TILE_SIZE) * TILE_SIZE + TILE_SIZE) <<
               4;

          current_jump = 0;
          is_jumping = FALSE;
          sound_play_bump();
        } else {
          if (is_coin(tile_left_top)) {
            on_get_coin(x_left_draw, next_pos);
          }

          if (is_coin(tile_right_top)) {
            on_get_coin(x_right_draw, next_pos);
          }
          player_y_subpixel = player_y_subpixel_next;
        }
      }
      player_draw_y = player_y_subpixel >> 4;
    }
}