#ifndef GLOBAL_H
#define GLOBAL_H

#define TILE_SIZE 8
#define WINDOW_HEIGHT_TILE 2
#define WINDOW_WIDTH_TILE DEVICE_SCREEN_WIDTH
#define WINDOW_SIZE WINDOW_WIDTH_TILE * WINDOW_HEIGHT_TILE
#define WINDOW_X MINWNDPOSX
#define WINDOW_Y MINWNDPOSY

#define INITIAL_LIVES 3
#define TIME_SHIFT 5
#define TIME_INITIAL_VALUE 400 << TIME_SHIFT
#define GRAVITY 2
#define JUMP_SPEED 32
#define JUMP_INITIAL_VELOCITY -40  
#define JUMP_HOLD_BOOST -1
#define JUMP_MIN_FRAMES 4
#define JUMP_MAX_FRAMES 13
#define GRAVITY_RISING 2
#define GRAVITY_FAST_FALL 3
#define MAX_FALL_SPEED 48
#define PLAYER_SPEED_WALK 16
#define PLAYER_SPEED_RUN 20
#define PLAYER_DRAW_OFFSET_X 4
#define PLAYER_DRAW_OFFSET_Y mario_HEIGHT / 2

#define ACCELERATION 2      // How quickly player speeds up
#define DECELERATION 3      // How quickly player slows down (friction)
#define AIR_ACCELERATION 1  // Slower acceleration in air
#define AIR_DECELERATION 1  // Less friction in air
#define SKID_DECELERATION 4 // Extra deceleration when turning around
#define MAX_WALK_SPEED 16 // Maximum walking speed
#define MAX_RUN_SPEED 28  // Maximum running speed
#define JUMP_BUFFER 6     // Frames to remember jump input before landing

#define LOOP_PER_ANIMATION_FRAME 5
#define MARIO_HALF_WIDTH 4
#define MARIO_SPRITE_COUNT 4

#define DEVICE_SCREEN_PX_WIDTH_HALF DEVICE_SCREEN_PX_WIDTH / 2
#define MARGIN_TOP 2
#define MARGIN_TOP_PX 2 * TILE_SIZE
#define DEVICE_SPRITE_OFFSET_Y 2

#endif
