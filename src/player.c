#include "asm/types.h"
#include "global.h"
#include "level.h"
#include <stdint.h>
#pragma bank 255

#include "player.h"

BANKREF(player)

uint8_t coins;
uint16_t score;
uint8_t joy;
uint16_t time;
uint8_t lives;
uint8_t joypad_previous, joypad_current;

// player coords and movements
uint16_t player_x_upscaled;
uint16_t player_y_upscaled;
uint16_t player_x_next_upscaled;
uint16_t player_y_next_upscaled;
uint16_t player_x;
uint16_t player_y;
uint16_t player_x_next;
uint16_t player_y_next;
uint8_t player_draw_x;
uint8_t player_draw_y;
int8_t vel_x;
int8_t vel_y;
bool is_jumping = FALSE;
bool display_jump_frame;
bool display_slide_frame;
bool display_walk_animation;
bool touch_ground = FALSE;
uint16_t current_jump = 0;

uint8_t player_frame = 0;
uint8_t frame_counter = 0;
bool mario_flip;
uint16_t scroll_limit;

uint8_t tile_next_1;
uint8_t tile_next_2;

uint8_t scroll;
bool plane_mode;

void update_frame_counter(void) NONBANKED {
  frame_counter++;
  if (frame_counter == LOOP_PER_ANIMATION_FRAME) {
    frame_counter = 0;
    player_frame = (player_frame % 3) + 1;
  }
}

uint8_t player_draw(uint8_t base_sprite) NONBANKED {
  uint8_t _saved_bank = _current_bank;
  SWITCH_ROM(BANK(mario));

  const metasprite_t *const mario_metasprite = mario_metasprites[player_frame];
  if (mario_flip) {
    base_sprite += move_metasprite_flipx(mario_metasprite, 0, 0, 0,
                                         player_draw_x, player_draw_y);
  } else {
    base_sprite += move_metasprite_ex(mario_metasprite, 0, 0, 0, player_draw_x,
                                      player_draw_y);
  }

  SWITCH_ROM(_saved_bank);

  return base_sprite;
}

void player_move(void) BANKED {
  if (joypad_current & J_RIGHT) {
    display_walk_animation = TRUE;
    if (joypad_current & J_B) {
      vel_x = PLAYER_SPEED_RUN;
    } else {
      vel_x = PLAYER_SPEED_WALK;
    }

    if (display_jump_frame == FALSE) {
      mario_flip = FALSE;
    }
  } else if (joypad_current & J_LEFT) {
    display_walk_animation = TRUE;
    if (joypad_current & J_B) {
      vel_x = -PLAYER_SPEED_RUN;
    } else {
      vel_x = -PLAYER_SPEED_WALK;
    }
    mario_flip = TRUE;
  } else {
    vel_x = 0;
    display_walk_animation = FALSE;
  }

  if (is_jumping) {
    EMU_printf("jumping current before %d, add %d\n", current_jump, vel_y);
    current_jump += JUMP_SPEED;
    EMU_printf("jumping current after %d\n", current_jump);
    if (current_jump >= MAX_JUMP) {
      EMU_printf("jump max reached ! _\n");
      is_jumping = FALSE;
      current_jump = 0;
    }
  } else if (!player_is_on_platform()) {
    vel_y = GRAVITY;
  }

  EMU_printf("IS NOT JUMPING %d IS GROUNDED %d\n", !is_jumping, touch_ground);
  if (joypad_current & J_A && !(joypad_previous & J_A) && !is_jumping &&
      touch_ground) {
    EMU_printf("JUMP!!!!!!!!!!!!!!!!\n");
    current_jump = 0;
    is_jumping = TRUE;
    display_jump_frame = TRUE;
    vel_y = -JUMP_SPEED;
    touch_ground = FALSE;
    music_play_sfx(BANK(sound_jump_small), sound_jump_small,
                   SFX_MUTE_MASK(sound_jump_small), MUSIC_SFX_PRIORITY_NORMAL);
  }

  player_x_next_upscaled = player_x_upscaled + vel_x;
  player_y_next_upscaled = player_y_upscaled;

  player_x_next = player_x_next_upscaled >> 4;
  player_y_next = player_y_next_upscaled >> 4;

  if (vel_x > 0) {
    // move right
    tile_next_1 = get_tile(player_x_next + MARIO_WIDTH -
                               PLAYER_HORIZONTAL_MARGIN - camera_x,
                           player_y_next + PLAYER_TOP_MARGIN); // right top
    tile_next_2 = get_tile(
        player_x_next + MARIO_WIDTH - PLAYER_HORIZONTAL_MARGIN - camera_x,
        player_y_next + MARIO_HEIGHT_SMALL - 1); // right bottom
    if (is_tile_solid(tile_next_1) || is_tile_solid(tile_next_2)) {
      EMU_printf("right collision. pos %d:%d next %d:%d \n", player_x, player_y,
                 player_x_next, player_y_next);
      player_x = ((player_x_next + 7) & ~7) - 7;
      player_x_upscaled = player_x << 4;
    } else {
      if (is_coin(tile_next_1)) {
        on_get_coin_background(player_x_next + MARIO_WIDTH -
                                   PLAYER_HORIZONTAL_MARGIN - camera_x,
                               player_y_next + PLAYER_TOP_MARGIN);
      } else if (is_coin(tile_next_2)) {
        on_get_coin_background(player_x_next + MARIO_WIDTH -
                                   PLAYER_HORIZONTAL_MARGIN - camera_x,
                               player_y_next + MARIO_HEIGHT_SMALL - 1);
      }

      player_x_upscaled = player_x_next_upscaled;
      player_x = player_x_upscaled >> 4;

      // check if end of level reached
      if (next_col_chunk_load ==
          current_map_width_in_tiles - DEVICE_SCREEN_WIDTH + 1) {
        level_end_reached = true;
        // fix camera at end of level
        camera_x = current_map_width - DEVICE_SCREEN_PX_WIDTH;
        SCX_REG = camera_x;
      }

      // check scroll limit
      if (!level_end_reached && player_x > scroll_limit) {
        // update camera and scroll register
        camera_x_upscaled += vel_x;
        camera_x = camera_x_upscaled >> 4;
        SCX_REG = camera_x;

        // increase the scroll limit
        scroll_limit = player_x;

        level_load_objects((camera_x >> 3) + DEVICE_SCREEN_WIDTH);
      }

      // load level background
      if (camera_x >> 3 >= next_col_chunk_load && !level_end_reached) {
        level_load_column(next_col_chunk_load + DEVICE_SCREEN_WIDTH + 6, 1);
        next_col_chunk_load++;
      }
    }
  } else if (vel_x < 0 && player_draw_x > 12) {
    // move left
    tile_next_1 = get_tile(player_x_next - camera_x,
                           player_y_next + PLAYER_TOP_MARGIN); // left top
    tile_next_2 =
        get_tile(player_x_next - camera_x,
                 player_y_next + MARIO_HEIGHT_SMALL - 1); // left bottom
    if (is_tile_solid(tile_next_1) || is_tile_solid(tile_next_2)) {
      player_x = ((player_x_next + 7) & ~7);
      player_x_upscaled = player_x << 4;
      EMU_printf("left collision. pos %d:%d next %d:%d \n", player_x, player_y,
                 player_x_next, player_y_next);
    } else {
      if (is_coin(tile_next_1)) {
        on_get_coin_background(player_x_next + PLAYER_HORIZONTAL_MARGIN -
                                   camera_x,
                               player_y_next + PLAYER_TOP_MARGIN);
      } else if (is_coin(tile_next_2)) {
        on_get_coin_background(player_x_next + PLAYER_HORIZONTAL_MARGIN -
                                   camera_x,
                               player_y_next + MARIO_HEIGHT_SMALL - 1);
      }

      player_x_upscaled = player_x_next_upscaled;
      player_x = player_x_upscaled >> 4;
    }
  }

  EMU_printf("DRAW %d PLAYER X NEXT %d\n", player_draw_x, player_x_next);

  player_x_next_upscaled = player_x_upscaled;
  player_y_next_upscaled = player_y_upscaled + vel_y;

  player_x_next = player_x_next_upscaled >> 4;
  player_y_next = player_y_next_upscaled >> 4;

  if (vel_y > 0) {
    // move down
    tile_next_1 = get_tile(
        player_x_next + MARIO_WIDTH - PLAYER_HORIZONTAL_MARGIN - camera_x,
        player_y_next + MARIO_HEIGHT_SMALL - 1); // right bottom
    tile_next_2 =
        get_tile(player_x_next + PLAYER_HORIZONTAL_MARGIN - camera_x,
                 player_y_next + MARIO_HEIGHT_SMALL - 1); // left bottom

    if (is_tile_solid(tile_next_1) || is_tile_solid(tile_next_2) ||
        is_tile_passthought(tile_next_1, tile_next_2)) {
      EMU_printf("down collision. pos %d:%d next %d:%d \n", player_x, player_y,
                 player_x_next, player_y_next);
      player_on_touch_ground();
      player_y = ((player_y_next + 7) & ~7) - 4;
      player_y_upscaled = player_y << 4;
    } else {
      touch_ground = FALSE;

      if (is_coin(tile_next_1)) {
        on_get_coin_background(player_x_next + MARIO_WIDTH -
                                   PLAYER_HORIZONTAL_MARGIN - camera_x,
                               player_y_next + MARIO_HEIGHT_SMALL - 1);
      } else if (is_coin(tile_next_2)) {
        on_get_coin_background(player_x_next + PLAYER_HORIZONTAL_MARGIN -
                                   camera_x,
                               player_y_next + MARIO_HEIGHT_SMALL - 1);
      }

      player_y_upscaled = player_y_next_upscaled;
      player_y = player_y_upscaled >> 4;
    }
  } else if (vel_y < 0) {
    // move up
    tile_next_1 = get_tile(player_x_next + PLAYER_HORIZONTAL_MARGIN - camera_x,
                           player_y_next + PLAYER_TOP_MARGIN); // left top
    tile_next_2 = get_tile(player_x_next + MARIO_WIDTH -
                               PLAYER_HORIZONTAL_MARGIN - camera_x,
                           player_y_next + PLAYER_TOP_MARGIN); // right top
    if (is_tile_solid(tile_next_1) || is_tile_solid(tile_next_2)) {
      EMU_printf("up collision. pos %d:%d next %d:%d \n", player_x, player_y,
                 player_x_next, player_y_next);
      if (tile_next_1 == TILE_INTEROGATION_BLOCK) {
        on_interogation_block_hit(player_x_next + PLAYER_HORIZONTAL_MARGIN -
                                      camera_x,
                                  player_y_next + PLAYER_TOP_MARGIN);
      } else if (tile_next_2 == TILE_INTEROGATION_BLOCK) {
        on_interogation_block_hit(player_x_next + MARIO_WIDTH -
                                      PLAYER_HORIZONTAL_MARGIN - camera_x,
                                  player_y_next + PLAYER_TOP_MARGIN);
      }

      if (is_coin(tile_next_1)) {
        on_get_coin_background(player_x_next - camera_x,
                               player_y_next + PLAYER_TOP_MARGIN);
      } else if (is_coin(tile_next_2)) {
        on_get_coin_background(player_x_next + 8 - camera_x,
                               player_y_next + PLAYER_TOP_MARGIN);
      }

      player_y_upscaled = ((player_y_next_upscaled >> 3) << 3) + 32;
      player_y = player_y_upscaled >> 4;

      vel_y = 0;
      is_jumping = FALSE;
    } else {
      player_y_upscaled = player_y_next_upscaled;
      player_y = player_y_upscaled >> 4;
    }
  }

  player_x = player_x_upscaled >> 4;
  player_y = player_y_upscaled >> 4;

  player_draw_x =
      player_x + DEVICE_SPRITE_PX_OFFSET_X + PLAYER_DRAW_OFFSET_X - camera_x;
  player_draw_y = player_y + DEVICE_SPRITE_PX_OFFSET_Y + MARGIN_TOP_PX +
                  PLAYER_DRAW_OFFSET_Y;
}

void player_on_touch_ground(void) NONBANKED {
  current_jump = 0;
  touch_ground = TRUE;
  is_jumping = FALSE;
  display_jump_frame = FALSE;
}

bool player_is_on_platform(void) NONBANKED {
  EMU_printf("plateform count: %d\n", platform_moving_count);

  for (uint8_t index_platform = 0; index_platform < platform_moving_count;
       index_platform++) {
    EMU_printf("x %d between %d and %d . y %d between %d and %d.\n",
               player_x_upscaled, platforms_moving[index_platform].x,
               platforms_moving[index_platform].x + (3 * 8 * 16),
               player_y_upscaled + 128, platforms_moving[index_platform].y,
               platforms_moving[index_platform].y + (8 * 16));
    if (player_y_upscaled + 128 > platforms_moving[index_platform].y &&
        player_y_upscaled + 128 <=
            platforms_moving[index_platform].y + (8 * 16) &&
        player_x_upscaled <= platforms_moving[index_platform].x +
                                 (3 * 8 * 16) /*platforms_moving[i].width*/
        && player_x_upscaled > platforms_moving[index_platform].x) {
      vel_x += platforms_moving[index_platform].vel_x;
      vel_y = platforms_moving[index_platform].vel_y;
      EMU_printf("ON PLATEFORM\n");

      player_on_touch_ground();
      return TRUE;
    }
  }

  return FALSE;
}
