
#include <gb/gb.h>
#include <gbdk/metasprites.h>
#include <gbdk/platform.h>
#include <stdint.h>

#include "coin_animated.h"
#include "gb/hardware.h"
#include "gb/metasprites.h"
#include "graphics/birabuto_torch.h"
#include "graphics/common.h"
#include "graphics/enemies.h"
#include "graphics/mario.h"
#include "graphics/sprite_common.h"
#include "graphics/text.h"

#include "hud.h"
#include "musics/musics.h"
#include "sounds/sound_coin.h"
#include "sounds/sound_skid.h"

#include "game.h"
#include "global.h"

#include "enemy.h"
#include "level.h"
#include "platforms.h"
#include "player.h"
#include "powerup.h"
#include "text.h"

const uint8_t window_location = WINDOW_Y + WINDOW_HEIGHT_TILE * TILE_SIZE;

void interruptLCD(void) {
  while (STAT_REG & 3)
    ;
  HIDE_WIN;
}

void interruptVBL(void) { SHOW_WIN; }

bool powerups_collide() {
  uint8_t powerup_left = powerup.draw_x - 4;
  uint8_t powerup_right = powerup.draw_x + 4;
  uint8_t powerup_top = powerup.draw_y - 4;
  uint8_t powerup_bottom = powerup.draw_y;

  if (powerup_right <= x_left_draw || powerup_left >= x_right_draw ||
      powerup_bottom <= y_top_draw || powerup_top >= y_bottom_draw) {
    return false;
  }

  return true;
}

bool enemy_collide() {
    for (uint8_t enemy_index = 0; enemy_index < enemy_count; enemy_index++) {
        uint8_t enemy_left = enemies[enemy_index].draw_x - 4;
        uint8_t enemy_right = enemies[enemy_index].draw_x + 4;
        uint8_t enemy_top = enemies[enemy_index].draw_y - 4;
        uint8_t enemy_bottom = enemies[enemy_index].draw_y + 4;
        
        EMU_printf("%d:%d:%d:%d %d:%d:%d:%d\n", enemy_left, enemy_right, enemy_top, enemy_bottom, x_left_draw, x_right_draw, y_top_draw, y_bottom_draw);

        if (enemy_right > x_left_draw && enemy_left < x_right_draw &&
            enemy_bottom > y_top_draw && enemy_top < y_bottom_draw) {
            return true;
        }
    }
    return false;
}

const uint8_t empty_tiles[DEVICE_SCREEN_BUFFER_HEIGHT *
                          DEVICE_SCREEN_BUFFER_WIDTH] = {TILE_EMPTY};

void main(void) {
  STAT_REG = 0x40;
  LYC_REG = 0x0F;

  move_bkg(0, -MARGIN_TOP_PX);

  // Clear video buffer with empty tiles
  set_bkg_tiles(0, 0, DEVICE_SCREEN_BUFFER_WIDTH, DEVICE_SCREEN_BUFFER_HEIGHT,
                empty_tiles);

  disable_interrupts();
  add_LCD(interruptLCD);
  add_VBL(interruptVBL);
  set_interrupts(VBL_IFLAG | LCD_IFLAG);
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

  // joypad
  joypad_previous, joypad_current = 0;

  init();
  current_level = 0;
  level_set_current();

  score = 0;
  lives = INITIAL_LIVES;
  coins = 0;

  // HUD
  // text
  unsigned char windata[WINDOW_SIZE];
  memset(windata, 15, WINDOW_SIZE);
  set_win_tiles(0, 0, WINDOW_WIDTH_TILE, WINDOW_HEIGHT_TILE, windata);
  move_win(WINDOW_X, WINDOW_Y);
  text_print_string_win(0, 0, "MARIOx00  WORLD TIME");
  text_print_string_win(0, 1, "     0  x00 1-1  000");

  // display a coin in the HUD
  set_win_tile_xy(7, 1, TILE_COIN);
  hud_update_time();
  hud_update_lives();

  // set sprite and background data
  uint8_t _saved_bank = _current_bank;

  // sprite
  SWITCH_ROM(BANK(mario));
  set_sprite_data(mario_TILE_ORIGIN, mario_TILE_COUNT, mario_tiles);

  SWITCH_ROM(BANK(enemies));
  set_sprite_data(enemies_TILE_ORIGIN, enemies_TILE_COUNT, enemies_tiles);

  SWITCH_ROM(BANK(sprite_common));
  set_sprite_data(sprite_common_TILE_ORIGIN, sprite_common_TILE_COUNT,
                  sprite_common_tiles);

  // background
  SWITCH_ROM(BANK(text));
  set_bkg_data(text_TILE_ORIGIN, text_TILE_COUNT, text_tiles);

  SWITCH_ROM(BANK(common));
  set_bkg_data(common_TILE_ORIGIN, common_TILE_COUNT, common_tiles);

  SWITCH_ROM(_saved_bank);

  DISPLAY_ON;
  SHOW_BKG;
  SHOW_WIN;
  SHOW_SPRITES;
  SPRITES_8x8;

  uint8_t base_sprite = 0; // base hardware sprite
  uint8_t background_animation_counter = 0;
  uint8_t anim_frame_counter = 0;

  while (1) {
    vsync();

    // inputs
    joypad_previous = joypad_current;
    joypad_current = joypad();

    player_move();

    EMU_printf("MARIO %d %d\n", player_draw_x, player_draw_y);

    // set player frame
    if (display_jump_frame) {
      player_frame = 4;
    } else if (vel_x != 0) {
      if (display_slide_frame) {
        music_play_sfx(BANK(sound_skid), sound_skid, SFX_MUTE_MASK(sound_skid),
                       MUSIC_SFX_PRIORITY_NORMAL);
        player_frame = 5;
      } else {
        update_frame_counter();
      }
    } else {
      player_frame = 0;
    }

    enemy_update();
    platform_moving_update();

    base_sprite = player_draw(base_sprite);
    base_sprite = enemy_draw(MARIO_SPRITE_COUNT);
    base_sprite = platform_moving_draw(base_sprite);
    if (powerup_active) {
      powerup_update();
      base_sprite = powerup_draw(base_sprite);
    }

    coin_animated_update();
    base_sprite = coin_animated_draw(base_sprite);

    if (joypad_current & J_SELECT && !(joypad_previous & J_SELECT)) {
      init();
      current_level = (++current_level) % NB_LEVELS;
      level_set_current();
      load_current_level();
    }

    // check if mario collids with a power up
    if (powerup_active && powerups_collide()) {
      // EMU_printf("Power up collids\n");
      powerup_active = FALSE;
      hide_metasprite(sprite_common_metasprites[0], base_sprite - 1);
      powerup.x = 0;
      powerup.draw_x = 0;
      powerup.y = 0;
      powerup.draw_y = 0;
      powerup_draw(base_sprite - 1);
    }

    if(enemy_collide()){
      die();
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
      player_y_subpixel = 0;
      // die();
    }

    // if reach end of level
    if (level_end_reached &&
        player_draw_x >= (DEVICE_SCREEN_WIDTH - 1) * TILE_SIZE) {

      music_load(BANK(music_stage_clear), &music_stage_clear);
      delay(4500);

      while (time >> TIME_SHIFT > 0) {
        time -= 32; // 2 power of 5
        score += 1;
        hud_update_time();
        hud_update_score();
        music_play_sfx(BANK(sound_coin), sound_coin, SFX_MUTE_MASK(sound_coin),
                       MUSIC_SFX_PRIORITY_NORMAL);
        delay(10);
      }

      HIDE_SPRITES;
      HIDE_BKG;

      init();
      current_level = (++current_level) % NB_LEVELS;
      level_set_current();
      load_current_level();

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
  }
}
