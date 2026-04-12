#pragma bank 255

#include "asm/types.h"
#include "global.h"
#include "graphics/mario.h"
#include "level.h"
#include <stdint.h>

#include "player.h"

#ifdef USE_COMPRESSED_LEVELS
#include <gbdk/gbdecompress.h>
#endif

BANKREF(player)

uint8_t coins;
uint16_t score;
uint8_t joy;
uint16_t time;
uint8_t lives;
uint8_t joypad_previous, joypad_current;

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
bool player_is_big = FALSE;

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

  uint8_t frame_index = player_is_big ? player_frame + 7 : player_frame;
  const metasprite_t *const mario_metasprite = mario_metasprites[frame_index];
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

#include <gbdk/emu_debug.h>

bool player_check_pipe_entry(void) NONBANKED {
    if (!touch_ground || !(joypad_current & J_DOWN) || (joypad_previous & J_DOWN)) {
        return FALSE;
    }
    if (!pipe_active || active_pipe_direction != PIPE_DIRECTION_VERTICAL) {
        return FALSE;
    }

    uint8_t player_tile_x = player_x >> 3;
    uint8_t player_tile_y = player_y >> 3;

    if ((player_tile_x == active_pipe_tile_x ||
         player_tile_x == active_pipe_tile_x + 1) &&
        player_tile_y + 2 == active_pipe_tile_y) {
        player_enter_pipe(&active_pipe);
        return TRUE;
    }
    return FALSE;
}

void player_enter_pipe(pipe_params* pipe) NONBANKED {
  uint8_t _saved_bank = _current_bank;
  SWITCH_ROM(pipe->destination_level->lookup_bank);
  level_lookup_bank = pipe->destination_level->lookup_bank;
  level_lookup = pipe->destination_level->lookup;
  level_lookup_size = pipe->destination_level->lookup_size;
  SWITCH_ROM(_saved_bank);

  player_warp_to(pipe->destination_level, pipe->destination_page, pipe->destination_x, pipe->destination_y);

#ifdef GAMEBOY
  music_play_sfx(BANK(sound_pipe), sound_pipe, SFX_MUTE_MASK(sound_pipe),
                 MUSIC_SFX_PRIORITY_NORMAL);
  music_load(pipe->destination_level->music_bank, pipe->destination_level->music);
#endif
}

bool player_check_horizontal_pipe_entry(void) NONBANKED {
    if (!touch_ground || vel_x == 0) {
        return FALSE;
    }
    if (!pipe_active || active_pipe_direction != PIPE_DIRECTION_HORIZONTAL) {
        return FALSE;
    }

    uint8_t player_tile_x = player_x >> 3;
    uint8_t player_tile_y = player_y >> 3;

    bool row_match = (player_tile_y == active_pipe_tile_y ||
                      player_tile_y == active_pipe_tile_y - 1);
    if (!row_match) {
        return FALSE;
    }

    if (vel_x > 0) {
        uint8_t player_right_tile = (player_x + MARIO_WIDTH) >> 3;
        if (player_right_tile == active_pipe_tile_x) {
            player_enter_pipe(&active_pipe);
            return TRUE;
        }
    } else {
        if (player_tile_x == active_pipe_tile_x + 1) {
            player_enter_pipe(&active_pipe);
            return TRUE;
        }
    }
    return FALSE;
}

void player_warp_to(level *destination_level, uint8_t destination_page, uint8_t destination_x, uint8_t destination_y) NONBANKED {
  pipe_clear();

  level_page_x_offset = destination_page * PAGE_SIZE;

  if (destination_level->page_count == destination_page - 1) {
    level_end_reached = true;
  } else {
    scroll_limit = DEVICE_SCREEN_PX_WIDTH_HALF;
  }

  enemy_reset_all();
  hide_sprites_range(0, MAX_HARDWARE_SPRITES);
  delay(500);

  camera_x = 0;
  move_bkg(0, -16);
  camera_x_upscaled = 0;
  level_end_reached = false;

  current_page = destination_page;
  current_column_in_page = 0;
  map_column = 0;

  player_x_upscaled = (destination_x * TILE_SIZE) << 4;
  player_y_upscaled = (destination_y * TILE_SIZE) << 4;
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

  load_col_at = COLUMN_SIZE;

#ifdef USE_COMPRESSED_LEVELS
  cached_page_index = 0xFF;
#endif

  level_load_column(MAP_BUFFER_WIDTH, destination_level);

  col_from = 0;
  for (uint8_t c = 0; c <= DEVICE_SCREEN_WIDTH + 1; c++) {
    level_load_objects(c);
  }
}

void player_move(void) BANKED {
  int8_t target_vel_x = 0;
  int8_t max_speed;
  int8_t accel;
  int8_t decel;
  bool on_ground = touch_ground || player_is_on_platform();

  if (player_check_pipe_entry()) {
    return;
  }

  if (player_check_horizontal_pipe_entry()) {
    return;
  }

  if (joypad_current & J_RIGHT) {
    display_walk_animation = TRUE;
    max_speed = (joypad_current & J_B) ? MAX_RUN_SPEED : MAX_WALK_SPEED;
    target_vel_x = max_speed;

    if (display_jump_frame == FALSE) {
      mario_flip = FALSE;
    }
  } else if (joypad_current & J_LEFT) {
    display_walk_animation = TRUE;
    max_speed = (joypad_current & J_B) ? MAX_RUN_SPEED : MAX_WALK_SPEED;
    target_vel_x = -max_speed;
    mario_flip = TRUE;
  } else {
    display_walk_animation = FALSE;
  }

  if (on_ground) {
    accel = ACCELERATION;
    decel = DECELERATION;

    if ((vel_x > 8 && target_vel_x < 0) || (vel_x < -8 && target_vel_x > 0)) {
      decel = SKID_DECELERATION;
      display_slide_frame = TRUE;
    } else {
      display_slide_frame = FALSE;
    }
  } else {
    accel = AIR_ACCELERATION;
    decel = AIR_DECELERATION;
    display_slide_frame = FALSE;
  }

  if (target_vel_x == 0) {
    if (vel_x > 0) {
      vel_x -= decel;
      if (vel_x < 0)
        vel_x = 0;
    } else if (vel_x < 0) {
      vel_x += decel;
      if (vel_x > 0)
        vel_x = 0;
    }
  } else if (target_vel_x > vel_x) {
    vel_x += accel;
    if (vel_x > target_vel_x)
      vel_x = target_vel_x;
  } else if (target_vel_x < vel_x) {
    vel_x -= accel;
    if (vel_x < target_vel_x)
      vel_x = target_vel_x;
  }

  if (is_jumping) {
    current_jump++;

    if (vel_y < 0) {
      if ((joypad_current & J_A) && current_jump < JUMP_MAX_FRAMES) {
        vel_y += GRAVITY_RISING;
        vel_y += JUMP_HOLD_BOOST;
      } else {
        vel_y += GRAVITY_FAST_FALL;
      }
    } else {
      vel_y += GRAVITY;
    }

    if (vel_y >= 0 && current_jump > JUMP_MIN_FRAMES) {
      is_jumping = FALSE;
    }

    if (current_jump >= JUMP_MAX_FRAMES + 10) {
      is_jumping = FALSE;
    }
  } else if (!touch_ground || !player_is_on_platform()) {
    vel_y += GRAVITY;
  }

  if (vel_y > MAX_FALL_SPEED) {
    vel_y = MAX_FALL_SPEED;
  }

  if (joypad_current & J_A && !(joypad_previous & J_A) && !is_jumping &&
      touch_ground) {
    current_jump = 0;
    is_jumping = TRUE;
    display_jump_frame = TRUE;
    vel_y = JUMP_INITIAL_VELOCITY;
    touch_ground = FALSE;
#ifdef GAMEBOY
    music_play_sfx(BANK(sound_jump_small), sound_jump_small,
                   SFX_MUTE_MASK(sound_jump_small), MUSIC_SFX_PRIORITY_NORMAL);
#endif
  }

  player_x_next_upscaled = player_x_upscaled + vel_x;
  player_y_next_upscaled = player_y_upscaled;

  player_x_next = player_x_next_upscaled >> 4;
  player_y_next = player_y_next_upscaled >> 4;

  if (vel_x > 0) {
    tile_next_1 = get_tile(player_x_next + MARIO_WIDTH -
                               PLAYER_HORIZONTAL_MARGIN - camera_x,
                           player_y_next + PLAYER_TOP_MARGIN);
    tile_next_2 = get_tile(player_x_next + MARIO_WIDTH -
                               PLAYER_HORIZONTAL_MARGIN - camera_x,
                           player_y_next + mario_HEIGHT - 1);
    if (is_tile_solid(tile_next_1) || is_tile_solid(tile_next_2)) {
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
                               player_y_next + mario_HEIGHT - 1);
      }

      if (tile_next_1 == SWITCH) {
        init();
        map_column = 0;
        current_level = (++current_level) % NB_LEVELS;
        level_set_current();
      }

      player_x_upscaled = player_x_next_upscaled;
      player_x = player_x_upscaled >> 4;

      if (load_col_at ==
          current_map_width_in_tiles - DEVICE_SCREEN_WIDTH + 1) {
        level_end_reached = true;
        camera_x = current_map_width - DEVICE_SCREEN_PX_WIDTH;
        move_bkg(camera_x, -16);
      }

      if (!level_end_reached && player_x > scroll_limit) {
        int16_t player_movement = player_x - scroll_limit;
        camera_x_upscaled += (player_movement << 4);
        camera_x = camera_x_upscaled >> 4;
        move_bkg(camera_x, -16);
        scroll_limit = player_x;
        level_load_objects(current_page * PAGE_SIZE + current_column_in_page - 7);
      }

      if (camera_x >> 3 >= load_col_at && !level_end_reached) {
#if defined(GAMEBOY)
        level_load_column(1, levels + current_level);
#elif defined(NINTENDO_NES)
        level_load_column(1, levels + current_level);
#endif
        load_col_at++;
      }
    }
  } else if (vel_x < 0 && player_draw_x > 12) {
    tile_next_1 =
        get_tile(player_x_next - camera_x, player_y_next + PLAYER_TOP_MARGIN);
    tile_next_2 =
        get_tile(player_x_next - camera_x, player_y_next + mario_HEIGHT - 1);
    if (is_tile_solid(tile_next_1) || is_tile_solid(tile_next_2)) {
      player_x = ((player_x_next + 7) & ~7);
      player_x_upscaled = player_x << 4;
    } else {
      if (is_coin(tile_next_1)) {
        on_get_coin_background(player_x_next - camera_x,
                               player_y_next + PLAYER_TOP_MARGIN);
      } else if (is_coin(tile_next_2)) {
        on_get_coin_background(player_x_next - camera_x,
                               player_y_next + mario_HEIGHT - 1);
      }

      player_x_upscaled = player_x_next_upscaled;
      player_x = player_x_upscaled >> 4;
    }
  }

  player_x_next_upscaled = player_x_upscaled;
  player_y_next_upscaled = player_y_upscaled + vel_y;

  player_x_next = player_x_next_upscaled >> 4;
  player_y_next = player_y_next_upscaled >> 4;

  if (vel_y > 0) {
    tile_next_1 = get_tile(player_x_next + MARIO_WIDTH -
                               PLAYER_HORIZONTAL_MARGIN - camera_x,
                           player_y_next + mario_HEIGHT - 1);
    tile_next_2 = get_tile(player_x_next + PLAYER_HORIZONTAL_MARGIN - camera_x,
                           player_y_next + mario_HEIGHT - 1);

    if (is_tile_solid(tile_next_1) || is_tile_solid(tile_next_2) ||
        is_tile_passthought(tile_next_1, tile_next_2)) {
      player_on_touch_ground();
      player_y = ((player_y_next + 7) & ~7) - 8;
      player_y_upscaled = player_y << 4;
    } else {
      touch_ground = FALSE;

      if (is_coin(tile_next_1)) {
        on_get_coin_background(player_x_next + MARIO_WIDTH -
                                   PLAYER_HORIZONTAL_MARGIN - camera_x,
                               player_y_next + mario_HEIGHT - 1);
      } else if (is_coin(tile_next_2)) {
        on_get_coin_background(player_x_next + PLAYER_HORIZONTAL_MARGIN -
                                   camera_x,
                               player_y_next + mario_HEIGHT - 1);
      }

      player_y_upscaled = player_y_next_upscaled;
      player_y = player_y_upscaled >> 4;
    }
  } else if (vel_y < 0) {
    tile_next_1 = get_tile(player_x_next + PLAYER_HORIZONTAL_MARGIN - camera_x,
                           player_y_next + PLAYER_TOP_MARGIN);
    tile_next_2 = get_tile(player_x_next + MARIO_WIDTH -
                               PLAYER_HORIZONTAL_MARGIN - camera_x,
                           player_y_next + PLAYER_TOP_MARGIN);
    if (is_tile_solid(tile_next_1) || is_tile_solid(tile_next_2)) {
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
        on_get_coin_background(player_x_next + PLAYER_HORIZONTAL_MARGIN -
                                   camera_x,
                               player_y_next + PLAYER_TOP_MARGIN);
      } else if (is_coin(tile_next_2)) {
        on_get_coin_background(player_x_next + MARIO_WIDTH -
                                   PLAYER_HORIZONTAL_MARGIN - camera_x,
                               player_y_next + PLAYER_TOP_MARGIN);
      }

      player_y_upscaled = ((player_y_next_upscaled >> 3) << 3) + 32;
      player_y = player_y_upscaled >> 4;

      vel_y = 0;
      is_jumping = FALSE;
      current_jump = 0;
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

bool player_is_on_platform(void) BANKED {
  for (uint8_t index_platform = 0; index_platform < platform_moving_count;
       index_platform++) {
    if (player_y_upscaled + 128 > platforms_moving[index_platform].y &&
        player_y_upscaled + 128 <=
            platforms_moving[index_platform].y + (8 * 16) &&
        player_x_upscaled <=
            platforms_moving[index_platform].x + (3 * 8 * 16) &&
        player_x_upscaled > platforms_moving[index_platform].x) {

      player_x_upscaled += platforms_moving[index_platform].vel_x;
      player_x = player_x_upscaled >> 4;
      vel_y = platforms_moving[index_platform].vel_y;
      player_on_touch_ground();
      return TRUE;
    }
  }
  return FALSE;
}