#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include <stdint.h>

#include "coin_animated.h"
#include "gb/hardware.h"
#include "gb/metasprites.h"
#include "graphics/birabuto_torch.h"
#include "graphics/common.h"
#include "graphics/enemies.h"
#include "graphics/enemies_large_birabuto.h"
#include "graphics/mario.h"
#include "graphics/sprite_common.h"
#include "graphics/text.h"
#include "graphics/title.h"

#include "hud.h"
#include "musics/musics.h"
#include "sounds/sound_coin.h"
#include "sounds/sound_pause.h"
#include "sounds/sound_skid.h"
#include "sounds/sound_squish.h"

#include "game.h"
#include "global.h"

#include "enemy.h"
#include "level.h"
#include "platforms.h"
#include "player.h"
#include "powerup.h"
#include "text.h"

#ifdef GAMEBOY
const uint8_t window_location = WINDOW_Y + WINDOW_HEIGHT_TILE * TILE_SIZE;
#endif

#ifdef GAMEBOY
void interruptLCD(void) {
  while (STAT_REG & 3)
    ;
  HIDE_WIN;
}

void interruptVBL(void) { SHOW_WIN; }
#endif 

//#include <gbdk/emu_debug.h>

bool powerups_collide() {
  // Check if powerup is active
  if (!powerup_active) {
    return false;
  }

  // Get powerup boundaries (convert from upscaled coordinates)
  uint16_t powerup_left = (powerup.x >> 4);
  uint16_t powerup_right = (powerup.x >> 4) + TILE_SIZE;
  uint16_t powerup_top = (powerup.y >> 4);
  uint16_t powerup_bottom = (powerup.y >> 4) + TILE_SIZE;

  // Get player boundaries
  uint16_t player_right = player_x + TILE_SIZE;
  uint16_t player_top = player_y + 8;
  uint16_t player_bottom = player_y + mario_HEIGHT;

//  EMU_printf("POWERUP: left=%d right=%d top=%d bottom=%d\n", 
//             powerup_left, powerup_right, powerup_top, powerup_bottom);
//  EMU_printf("PLAYER: x=%d right=%d y=%d bottom=%d\n", 
//             player_x, player_right, player_y, player_bottom);


  // AABB collision detection
  if (player_x < powerup_right && player_right > powerup_left &&
      player_top < powerup_bottom && player_bottom > powerup_top) {
    
    // TODO Collision detected - collect the powerup 
    on_get_coin();
    
    #ifdef GAMEBOY
    // Play powerup collection sound
    music_play_sfx(BANK(sound_coin), sound_coin, SFX_MUTE_MASK(sound_coin),
                   MUSIC_SFX_PRIORITY_NORMAL);
    #endif
    
    return true;
  }

  return false;
}

#define ENEMY_TOP_MARGIN 8

// Updated enemy_collide() function for main.c
// Replace the existing enemy_collide() function with this:

bool enemy_collide() {
  for (uint8_t enemy_index = 0; enemy_index < ENEMY_MAX; enemy_index++) {
    // Skip inactive or stomped enemies
    if (!enemies[enemy_index].active || enemies[enemy_index].stomped) {
      continue;
    }
    
    uint16_t enemy_left = (enemies[enemy_index].x >> 4);
    uint16_t enemy_right = (enemies[enemy_index].x >> 4) + TILE_SIZE;
    uint16_t enemy_top = (enemies[enemy_index].y >> 4);
    uint16_t enemy_bottom = (enemies[enemy_index].y >> 4) + enemies_HEIGHT;

    if (player_x < enemy_right && player_x + TILE_SIZE > enemy_left &&
        player_y < enemy_bottom &&
        player_y + mario_HEIGHT > enemy_top + ENEMY_TOP_MARGIN) {
      
      if (player_y + mario_HEIGHT < enemy_top + ENEMY_TOP_MARGIN + 4) {
        // Stomp the enemy
        uint8_t _saved_bank = _current_bank;
        SWITCH_ROM(_saved_bank);
        enemy_stomp(enemy_index);
        SWITCH_ROM(BANK(enemy));

        current_jump = 0;
        is_jumping = TRUE;
        display_jump_frame = TRUE;
        vel_y = -16;
        touch_ground = FALSE;
        #ifdef GAMEBOY
        music_play_sfx(BANK(sound_squish), sound_squish,
                       SFX_MUTE_MASK(sound_squish), MUSIC_SFX_PRIORITY_NORMAL);
        #endif
        continue;
      } else {
        die();
        enemy_reset_all();
      }
      return true;
    }
  }
  return false;
}

void main(void) {
  #ifdef GAMEBOY
  STAT_REG = 0x40;
  LYC_REG = 0x0F;

  disable_interrupts();
  set_interrupts(VBL_IFLAG | LCD_IFLAG);
  add_LCD(interruptLCD);
  enable_interrupts();


  music_init();

  CRITICAL {
    // set up the game boy timer
    music_setup_timer();
    // add music and SFX driver ISR to the low priority timer chain
    add_low_priority_TIM(music_play_isr);
  }
  // enable the timer interrupt
  set_interrupts(IE_REG | TIM_IFLAG);
  #endif

  // joypad
  joypad_previous, joypad_current = 0;

  init();

#ifdef NINTENDO_NES
uint8_t y;
uint8_t initial_tiles[32];

memset(initial_tiles, TILE_EMPTY, 32);

for (y = 0; y != 30; y++) {
    set_bkg_tiles(0, y, 32, 1, initial_tiles);
}
#endif

  // set sprite and background data
  uint8_t _saved_bank = _current_bank;

  // sprite
  SWITCH_ROM(BANK(mario));
  set_sprite_data(mario_TILE_ORIGIN, mario_TILE_COUNT, mario_tiles);

  SWITCH_ROM(BANK(enemies));
  set_sprite_data(enemies_TILE_ORIGIN, enemies_TILE_COUNT, enemies_tiles);

  SWITCH_ROM(BANK(enemies_large_birabuto));
  set_sprite_data(enemies_large_birabuto_TILE_ORIGIN, enemies_large_birabuto_TILE_COUNT, enemies_large_birabuto_tiles);

  SWITCH_ROM(BANK(sprite_common));
  set_sprite_data(sprite_common_TILE_ORIGIN, sprite_common_TILE_COUNT,
                  sprite_common_tiles);

  // background
  SWITCH_ROM(BANK(text));
  set_bkg_data(text_TILE_ORIGIN, text_TILE_COUNT, text_tiles);

  SWITCH_ROM(BANK(common));
  set_bkg_data(common_TILE_ORIGIN, common_TILE_COUNT, common_tiles);

  // load title tiles and map
  SWITCH_ROM(BANK(title));
  set_bkg_data(title_TILE_ORIGIN, title_TILE_COUNT, title_tiles);
  set_bkg_tiles(0, 0, 20, 18, title_map);

  SWITCH_ROM(_saved_bank);

  DISPLAY_ON;
  SHOW_BKG;
  #ifdef GAMEBOY
  SHOW_WIN;
  #endif 

  SHOW_SPRITES;
  SPRITES_8x8;

  uint8_t base_sprite = 0; // base hardware sprite
  uint8_t background_animation_counter = 0;
  uint8_t anim_frame_counter = 0;

  state_title();
  #ifdef GAMEBOY
  disable_interrupts();
  add_VBL(interruptVBL);
  move_bkg(0, -MARGIN_TOP_PX);
  enable_interrupts();
  #endif

  current_level = 0;
  init();
  level_set_current();

  score = 0;
  lives = INITIAL_LIVES;
  coins = 0;

  // HUD
  // text
  unsigned char windata[WINDOW_SIZE];
  memset(windata, 15, WINDOW_SIZE);
  #ifdef GAMEBOY
  set_win_tiles(0, 0, WINDOW_WIDTH_TILE, WINDOW_HEIGHT_TILE, windata);
  move_win(WINDOW_X, WINDOW_Y);
  text_print_string(0, 0, "MARIOx00  WORLD TIME");
  text_print_string(0, 1, "     0  x00 1-1  000");

  // display a coin in the HUD
  set_win_tile_xy(7, 1, TILE_COIN);
  hud_update_time();
  hud_update_lives();
  #endif

  while (1) {
    joypad_previous = joypad_current;
    joypad_current = joypad();

    // pause
    if (joypad_current & J_START && !(joypad_previous & J_START)) {
      #ifdef GAMEBOY
      music_pause(TRUE);
      music_play_sfx(BANK(sound_pause), sound_pause, SFX_MUTE_MASK(sound_pause),
                     MUSIC_SFX_PRIORITY_NORMAL);
      state_pause();
      music_pause(FALSE);
      #endif
    }

    enemy_collide();
    player_move();

    // set player frame
    if (display_jump_frame) {
      player_frame = 4;
    } else if (display_slide_frame) {
      #ifdef GAMEBOY
      music_play_sfx(BANK(sound_skid), sound_skid, SFX_MUTE_MASK(sound_skid),
                     MUSIC_SFX_PRIORITY_NORMAL);
      #endif
      player_frame = 5;
    } else if (display_walk_animation) {
      update_frame_counter();
    } else {
      player_frame = 0;
    }

    enemy_update();
    platform_moving_update();
    player_draw(0);
    base_sprite = enemy_draw(MARIO_SPRITE_COUNT);
    base_sprite = platform_moving_draw(base_sprite);
    if (powerup_active) {
      powerup_update();
      base_sprite = powerup_draw(base_sprite);
    }

    coin_animated_update();
    base_sprite = coin_animated_draw(base_sprite);

    // check if mario collids with a power up
    if (powerup_active && powerups_collide()) {
      // EMU_printf("Power up collids\n");
      powerup_active = FALSE;
      hide_metasprite(sprite_common_metasprites[0], base_sprite - 1);
      powerup.x = 0;
      powerup.draw_x = 0;
      powerup.y = 0;
      powerup.draw_y = 0;
      //powerup_draw(base_sprite - 1);
    }

    time--;
    hud_update_time();
    if (time == 0) {
      time = TIME_INITIAL_VALUE;
      lives--;
      hud_update_lives();
    }

    // if fall under screen
    if (player_draw_y > DEVICE_SCREEN_PX_HEIGHT) {
      player_y = 0;
      //die();
    }

    // if reach end of level
    if (level_end_reached && player_draw_x >= DEVICE_SCREEN_WIDTH << 3) {

      #ifdef GAMEBOY
      music_load(BANK(music_stage_clear), &music_stage_clear);
      #endif 
      
      delay(4500);

      while (time >> TIME_SHIFT > 0) {
        time -= 32; // 2 power of 5
        score += 1;
        hud_update_time();
        hud_update_score();
        #ifdef GAMEBOY
        music_play_sfx(BANK(sound_coin), sound_coin, SFX_MUTE_MASK(sound_coin),
                       MUSIC_SFX_PRIORITY_NORMAL);
        #endif
        delay(10);
      }

      HIDE_SPRITES;
      HIDE_BKG;

      init();
      current_level = (++current_level) % NB_LEVELS;
      level_set_current();

      SHOW_SPRITES;
      SHOW_BKG;
    }

    // animation
    if (current_level == 2) {
      uint8_t _saved_bank = _current_bank;
      anim_frame_counter++;
      if (anim_frame_counter >= 12) {
        anim_frame_counter = 0;
        background_animation_counter ^= 1; // toggle between 0 and 1

        if (background_animation_counter) {
          SWITCH_ROM(BANK(birabuto_torch));
          set_bkg_data(TILE_TORCH, 1, birabuto_torch_tiles);
        } else {
          SWITCH_ROM(BANK(birabuto));
          set_bkg_data(TILE_TORCH, 1,
                       birabuto_tiles + 288); // 18th tile * 16 bytes
        }
      }

      SWITCH_ROM(_saved_bank);
    }

    vsync();
  }
}
