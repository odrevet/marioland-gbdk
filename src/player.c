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

#include <gbdk/emu_debug.h>

/**
 * Check if player is standing on a pipe and can enter it
 * Returns true if player should enter the pipe
 */
bool player_check_pipe_entry(void) NONBANKED {
  // Only check if player is on ground and pressing down
  if (!touch_ground || !(joypad_current & J_DOWN)) {
    return FALSE;
  }
  
  // Only trigger on button press, not hold
  if (joypad_previous & J_DOWN) {
    return FALSE;
  }
  
  // Get player's tile position in world coordinates
  uint8_t player_tile_x = (player_x) >> 3;
  uint8_t player_tile_y = (player_y >> 3);
  
  // Check pipe lookup table
  uint8_t _saved_bank = _current_bank;
  SWITCH_ROM(level_lookup_bank);
  
  bool pipe_found = FALSE;
  pipe_params found_pipe; // Create a local copy
  
  EMU_printf("---------- CHECK PIPE\n");
  for (uint16_t i = 0; i < level_lookup_size && !pipe_found; i++) {
    level_object *obj = &level_lookup[i];
    
    EMU_printf("index %d -> type %d x %d y %d. Mario at %d %d\n", i, obj->type, obj->x, obj->y, player_tile_x, player_tile_y);
    if (obj->type == OBJECT_TYPE_PIPE_VERTICAL) {
      // Check if player is within the pipe's horizontal bounds
      // Pipes are typically 2 tiles wide, so check x and x+1
      if ((player_tile_x == obj->x || player_tile_x == obj->x + 1) &&
          player_tile_y + 2 == obj->y) {
        pipe_found = TRUE;
        // Copy the pipe data while we're in the correct bank
        found_pipe = obj->data.pipe;
      }
    }
  }
  
  SWITCH_ROM(_saved_bank);
  
  if (pipe_found) {
    // Trigger pipe transition with copied pipe data
    player_enter_pipe(&found_pipe);
    return TRUE;
  }
  
  return FALSE;
}

/**
 * Handle entering a pipe and loading destination
 */
void player_enter_pipe(pipe_params* pipe) NONBANKED {
  #ifdef GAMEBOY
   music_play_sfx(BANK(sound_pipe), sound_pipe, SFX_MUTE_MASK(sound_pipe),
                  MUSIC_SFX_PRIORITY_NORMAL);
  #endif
  
  
  // Hide sprites during transition
  hide_sprites_range(0, MAX_HARDWARE_SPRITES);
  
  // TODO pipe animation
  delay(500);

  set_column_at = 0;
  camera_x = 0;
  move_bkg(0, -16);
  camera_x_upscaled = 0;
  level_end_reached = false;
  current_page = pipe->destination_page;
  map_column_in_page = 0;

  player_x_upscaled = (pipe->destination_x * TILE_SIZE) << 4;
  player_y_upscaled = (pipe->destination_y * TILE_SIZE) << 4;
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

  next_col_chunk_load = COLUMN_CHUNK_SIZE;
  
  #ifdef GAMEBOY
  music_load(pipe->destination_level->music_bank, pipe->destination_level->music);
  #endif

  #ifdef USE_COMPRESSED_LEVELS
  cached_page_index = 0xFF;
  #endif 
  
  level_load_column(0, 20, pipe->destination_level);

  uint8_t _saved_bank = _current_bank;
  // Set up lookup table for level objects
  SWITCH_ROM(pipe->destination_level->lookup_bank);
  level_lookup_bank = pipe->destination_level->lookup_bank;
  level_lookup = pipe->destination_level->lookup;
  level_lookup_size = pipe->destination_level->lookup_size;

  SWITCH_ROM(_saved_bank);
}

void player_move(void) BANKED {
  int8_t target_vel_x = 0;
  int8_t max_speed;
  int8_t accel;
  int8_t decel;
  bool on_ground = touch_ground || player_is_on_platform();

  // Check for pipe entry first (before any movement)
  if (player_check_pipe_entry()) {
    // Pipe entry handled, skip rest of movement for this frame
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

  // Choose acceleration/deceleration based on ground state
  if (on_ground) {
    accel = ACCELERATION;
    decel = DECELERATION;

    // Check for skidding (changing direction at speed)
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

  // Apply acceleration/deceleration
  if (target_vel_x == 0) {
    // Decelerate to stop
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
    // Accelerate right
    vel_x += accel;
    if (vel_x > target_vel_x)
      vel_x = target_vel_x;
  } else if (target_vel_x < vel_x) {
    // Accelerate left
    vel_x -= accel;
    if (vel_x < target_vel_x)
      vel_x = target_vel_x;
  }

  if (is_jumping) {
    current_jump++;

    // Apply gravity based on state
    if (vel_y < 0) {
      // Moving upward
      if ((joypad_current & J_A) && current_jump < JUMP_MAX_FRAMES) {
        // Still holding jump and can boost
        vel_y += GRAVITY_RISING;
        vel_y += JUMP_HOLD_BOOST; // Extra boost while holding
      } else {
        // Released button or reached max - faster fall
        vel_y += GRAVITY_FAST_FALL;
      }
    } else {
      // Started falling
      vel_y += GRAVITY;
    }

    // End jump state when falling for a bit
    if (vel_y >= 0 && current_jump > JUMP_MIN_FRAMES) {
      is_jumping = FALSE;
    }

    // Force end at max frames
    if (current_jump >= JUMP_MAX_FRAMES + 10) {
      is_jumping = FALSE;
    }
  } else if (!touch_ground && !player_is_on_platform()) {
    // Not jumping but not grounded - apply falling gravity
    vel_y += GRAVITY;
  }

  // Cap fall speed
  if (vel_y > MAX_FALL_SPEED) {
    vel_y = MAX_FALL_SPEED;
  }

  // Jump initiation
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

  // Horizontal collision detection
  player_x_next_upscaled = player_x_upscaled + vel_x;
  player_y_next_upscaled = player_y_upscaled;

  player_x_next = player_x_next_upscaled >> 4;
  player_y_next = player_y_next_upscaled >> 4;

  if (vel_x > 0) {
    // move right
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

      if(tile_next_1 == SWITCH){
        init();
        current_level = (++current_level) % NB_LEVELS;
        level_set_current();
      }

      player_x_upscaled = player_x_next_upscaled;
      player_x = player_x_upscaled >> 4;

      // check if end of level reached
      if (next_col_chunk_load ==
          current_map_width_in_tiles - DEVICE_SCREEN_WIDTH + 1) {
        level_end_reached = true;
        camera_x = current_map_width - DEVICE_SCREEN_PX_WIDTH;
        move_bkg(camera_x, -16);
      }

      // check scroll limit
      if (!level_end_reached && player_x > scroll_limit) {
        int16_t player_movement = player_x - scroll_limit;
        camera_x_upscaled += (player_movement << 4);
        camera_x = camera_x_upscaled >> 4;
        move_bkg(camera_x, -16);
        scroll_limit = player_x;
        level_load_objects((camera_x >> 3) + DEVICE_SCREEN_WIDTH);
      }

      // load level background
      if (camera_x >> 3 >= next_col_chunk_load && !level_end_reached) {
#if defined(GAMEBOY)
        level_load_column(next_col_chunk_load + DEVICE_SCREEN_WIDTH + 6, 1, levels + current_level);
#elif defined(NINTENDO_NES)
        level_load_column(next_col_chunk_load + DEVICE_SCREEN_WIDTH, 1, levels + current_level);
#endif

        
        next_col_chunk_load++;
      }
    }
  } else if (vel_x < 0 && player_draw_x > 12) {
    // move left
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

  // Vertical collision detection
  player_x_next_upscaled = player_x_upscaled;
  player_y_next_upscaled = player_y_upscaled + vel_y;

  player_x_next = player_x_next_upscaled >> 4;
  player_y_next = player_y_next_upscaled >> 4;

  if (vel_y > 0) {
    // move down
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
    // move up
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

      // Bonk head - stop upward movement
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

bool player_is_on_platform(void) NONBANKED {
  for (uint8_t index_platform = 0; index_platform < platform_moving_count;
       index_platform++) {
    if (player_y_upscaled + 128 > platforms_moving[index_platform].y &&
        player_y_upscaled + 128 <=
            platforms_moving[index_platform].y + (8 * 16) &&
        player_x_upscaled <=
            platforms_moving[index_platform].x + (3 * 8 * 16) &&
        player_x_upscaled > platforms_moving[index_platform].x) {
      vel_x += platforms_moving[index_platform].vel_x;
      vel_y = platforms_moving[index_platform].vel_y;
      player_on_touch_ground();
      return TRUE;
    }
  }

  return FALSE;
}