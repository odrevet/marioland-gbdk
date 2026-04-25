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

bool powerups_collide() {
  if (!powerup_active) {
    return false;
  }

  uint16_t powerup_left = (powerup.x >> 4);
  uint16_t powerup_right = (powerup.x >> 4) + TILE_SIZE;
  uint16_t powerup_top = (powerup.y >> 4);
  uint16_t powerup_bottom = (powerup.y >> 4) + TILE_SIZE;

  uint16_t player_right = player_x + TILE_SIZE;
  uint16_t player_top = player_y + 8;
  uint16_t player_bottom = player_y + mario_HEIGHT;

  if (player_x < powerup_right && player_right > powerup_left &&
      player_top < powerup_bottom && player_bottom > powerup_top) {

    if (powerup.type == POWERUP_MUSHROOM) {
      player_is_big = TRUE;
    } else {
      on_get_coin();
    }

#ifdef GAMEBOY
    music_play_sfx(BANK(sound_coin), sound_coin, SFX_MUTE_MASK(sound_coin),
                   MUSIC_SFX_PRIORITY_NORMAL);
#endif

    return true;
  }

  return false;
}

#define ENEMY_TOP_MARGIN 8

bool enemy_collide() {
  for (uint8_t enemy_index = 0; enemy_index < ENEMY_MAX; enemy_index++) {
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
        uint8_t _saved_bank = _current_bank;
        SWITCH_ROM(BANK(enemy));
        enemy_stomp(enemy_index);
        SWITCH_ROM(_saved_bank);

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
        if(player_is_big){
          player_is_big = FALSE;
#ifdef GAMEBOY
        music_play_sfx(BANK(sound_pipe), sound_pipe,
                       SFX_MUTE_MASK(sound_pipe), MUSIC_SFX_PRIORITY_NORMAL);
#endif     

        // collid with enemy when big remove the enemy
        // TODO: invincibility frames !  
        uint8_t _saved_bank = _current_bank;
        SWITCH_ROM(BANK(enemy));
        enemy_stomp(enemy_index);
        SWITCH_ROM(_saved_bank);

        }
        else{
          die();
          uint8_t _saved_bank = _current_bank;
          SWITCH_ROM(BANK(enemy));
          enemy_reset_all();
          SWITCH_ROM(_saved_bank);
        }
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
    music_setup_timer();
    add_low_priority_TIM(music_play_isr);
  }
  set_interrupts(IE_REG | TIM_IFLAG);
#endif

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

  uint8_t _saved_bank = _current_bank;

  SWITCH_ROM(BANK(mario));
  set_sprite_data(mario_TILE_ORIGIN, mario_TILE_COUNT, mario_tiles);

  SWITCH_ROM(BANK(enemies));
  set_sprite_data(enemies_TILE_ORIGIN, enemies_TILE_COUNT, enemies_tiles);

  SWITCH_ROM(BANK(enemies_large_birabuto));
  set_sprite_data(enemies_large_birabuto_TILE_ORIGIN, enemies_large_birabuto_TILE_COUNT, enemies_large_birabuto_tiles);

  SWITCH_ROM(BANK(sprite_common));
  set_sprite_data(sprite_common_TILE_ORIGIN, sprite_common_TILE_COUNT,
                  sprite_common_tiles);

  SWITCH_ROM(BANK(text));
  set_bkg_data(text_TILE_ORIGIN, text_TILE_COUNT, text_tiles);

  SWITCH_ROM(BANK(common));
  set_bkg_data(common_TILE_ORIGIN, common_TILE_COUNT, common_tiles);

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

  uint8_t base_sprite = 0;
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
  map_column = 0;
  level_set_current();

  score = 0;
  lives = INITIAL_LIVES;
  coins = 0;

  unsigned char windata[WINDOW_SIZE];
  memset(windata, 15, WINDOW_SIZE);
#ifdef GAMEBOY
  set_win_tiles(0, 0, WINDOW_WIDTH_TILE, WINDOW_HEIGHT_TILE, windata);
  move_win(WINDOW_X, WINDOW_Y);
  text_print_string(0, 0, "MARIOx00  WORLD TIME");
  text_print_string(0, 1, "     0  x00 1-1  000");

  set_win_tile_xy(7, 1, TILE_COIN);
  hud_update_time();
  hud_update_lives();
#endif

  while (1) {
    joypad_previous = joypad_current;
    joypad_current = joypad();

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

    SWITCH_ROM(BANK(player));
    // TODO create a bool to check movement type
    if(current_level == 5 || current_level == 11){
      player_move_vehicle();
    }
    else{
      player_move();
    }
    SWITCH_ROM(_saved_bank);


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

    SWITCH_ROM(BANK(enemy));
    enemy_update();
    SWITCH_ROM(_saved_bank);

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

    if (powerup_active && powerups_collide()) {
      powerup_active = FALSE;
      hide_metasprite(sprite_common_metasprites[0], base_sprite - 1);
      powerup.x = 0;
      powerup.draw_x = 0;
      powerup.y = 0;
      powerup.draw_y = 0;
    }

    time--;
    hud_update_time();
    if (time == 0) {
      time = TIME_INITIAL_VALUE;
      lives--;
      hud_update_lives();
    }

    if (player_draw_y > DEVICE_SCREEN_PX_HEIGHT) {
      player_y = 0;
    }

    if (level_end_reached && player_draw_x >= DEVICE_SCREEN_WIDTH << 3) {
#ifdef GAMEBOY
      music_load(BANK(music_stage_clear), &music_stage_clear);
#endif

      delay(4500);

      while (time >> TIME_SHIFT > 0) {
        time -= 32;
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

    if (current_level == 2) {
      uint8_t _saved_bank = _current_bank;
      anim_frame_counter++;
      if (anim_frame_counter >= 12) {
        anim_frame_counter = 0;
        background_animation_counter ^= 1;

        if (background_animation_counter) {
          SWITCH_ROM(BANK(birabuto_torch));
          set_bkg_data(TILE_TORCH, 1, birabuto_torch_tiles);
        } else {
          SWITCH_ROM(BANK(birabuto));
          set_bkg_data(TILE_TORCH, 1,
                       birabuto_tiles + 288);
        }
      }

      SWITCH_ROM(_saved_bank);
    }

    vsync();
  }
}