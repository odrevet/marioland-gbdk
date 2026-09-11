#pragma bank 255

#include "enemy.h"
#include "global.h"
#include "level.h"
#include <stdint.h>

uint8_t enemy_count = 0;
enemy_t enemies[ENEMY_MAX];

#include "enemiesSprites.h"
#include "enemiesBirabutoSprites.h"
#include "enemiesMudaSprites.h"
#include "enemiesEastonSprites.h"
#include "enemiesChaiSprites.h"

BANKREF(enemy)

#define ENEMY_WIDTH 8
#define ENEMY_HEIGHT 16
#define ENEMY_TOP_MARGIN 0
#define ENEMY_GRAVITY 32
#define ENEMY_GOOMBA_SPEED 4
#define ENEMY_KOOPA_SPEED 4
#define ENEMY_FLY_WAIT_FRAMES 60
#define ENEMY_FLY_JUMP_VELOCITY -48
#define ENEMY_FLY_JUMP_SPEED 8

uint8_t enemy_has_ground(enemy_t *enemy) BANKED {
  uint16_t ground_check_x = enemy->x >> 4;
  uint16_t ground_check_y = (enemy->y >> 4) + ENEMY_HEIGHT;

  uint8_t tile_ground_left = get_tile(ground_check_x - camera_x, ground_check_y);
  uint8_t tile_ground_right = get_tile(ground_check_x + ENEMY_WIDTH - 1 - camera_x, ground_check_y);

  return is_tile_solid(tile_ground_left) || is_tile_solid(tile_ground_right) ||
         is_tile_passthought(tile_ground_left, tile_ground_right);
}

uint8_t enemy_has_ground_ahead(enemy_t *enemy, int8_t vel_x) BANKED {
  uint16_t current_x = enemy->x >> 4;
  uint16_t current_y = enemy->y >> 4;

  if (vel_x > 0) {
    uint8_t tile = get_tile(current_x + ENEMY_WIDTH - camera_x, current_y + ENEMY_HEIGHT);
    return is_tile_solid(tile) || is_tile_passthought(tile, tile);
  } else if (vel_x < 0) {
    uint8_t tile = get_tile(current_x - 1 - camera_x, current_y + ENEMY_HEIGHT);
    return is_tile_solid(tile) || is_tile_passthought(tile, tile);
  }
  return FALSE;
}


void enemy_apply_horizontal_movement(enemy_t *enemy, uint8_t check_cliffs) BANKED {
  if (enemy->vel_x == 0) return;

  uint16_t next_x_upscaled = enemy->x + enemy->vel_x;
  uint16_t next_x = next_x_upscaled >> 4;
  uint16_t current_x = enemy->x >> 4;
  uint16_t current_y = enemy->y >> 4;

  uint8_t hit_wall = FALSE;
  uint8_t hit_cliff = FALSE;

  if (enemy->vel_x > 0) {
    uint8_t tile_right_top = get_tile(next_x + ENEMY_WIDTH - 1 - camera_x, current_y + ENEMY_TOP_MARGIN);
    uint8_t tile_right_bottom = get_tile(next_x + ENEMY_WIDTH - 1 - camera_x, current_y + ENEMY_HEIGHT - 1);

    hit_wall = is_tile_solid(tile_right_top) || is_tile_solid(tile_right_bottom);

    if (check_cliffs && !hit_wall) {
      hit_cliff = !enemy_has_ground_ahead(enemy, enemy->vel_x);
    }
  } else if (enemy->vel_x < 0) {
    uint8_t tile_left_top = get_tile(next_x - camera_x, current_y + ENEMY_TOP_MARGIN);
    uint8_t tile_left_bottom = get_tile(next_x - camera_x, current_y + ENEMY_HEIGHT - 1);

    hit_wall = is_tile_solid(tile_left_top) || is_tile_solid(tile_left_bottom);

    if (check_cliffs && !hit_wall) {
      hit_cliff = !enemy_has_ground_ahead(enemy, enemy->vel_x);
    }
  }

  if (hit_wall || hit_cliff) {
    enemy->vel_x = -enemy->vel_x;
    enemy->flip = !enemy->flip;
  } else {
    enemy->x = next_x_upscaled;
  }
}

void enemy_apply_vertical_movement(enemy_t *enemy, int8_t gravity_divisor) BANKED {
  uint16_t ground_check_x = enemy->x >> 4;
  uint16_t ground_check_y = (enemy->y >> 4) + ENEMY_HEIGHT;

  uint8_t on_ground = enemy_has_ground(enemy);

  if (!on_ground) {
    if (gravity_divisor == 1) {
      enemy->vel_y = ENEMY_GRAVITY;
    } else {
      enemy->vel_y += ENEMY_GRAVITY / gravity_divisor;
    }
  }

  if (enemy->vel_y != 0) {
    uint16_t next_y_upscaled = enemy->y + enemy->vel_y;
    uint16_t next_y = next_y_upscaled >> 4;

    if (enemy->vel_y > 0) {
      uint8_t tile_bottom_left = get_tile(ground_check_x - camera_x, next_y + ENEMY_HEIGHT);
      uint8_t tile_bottom_right = get_tile(ground_check_x + ENEMY_WIDTH - 1 - camera_x, next_y + ENEMY_HEIGHT);

      if (is_tile_solid(tile_bottom_left) || is_tile_solid(tile_bottom_right) ||
          is_tile_passthought(tile_bottom_left, tile_bottom_right)) {
        enemy->vel_y = 0;
        enemy->y = (TILE_ALIGN(next_y + ENEMY_HEIGHT) - ENEMY_HEIGHT) << 4;
      } else {
        enemy->y = next_y_upscaled;
      }
    } else if (enemy->vel_y < 0) {
      uint8_t tile_top_left = get_tile(ground_check_x - camera_x, next_y + ENEMY_TOP_MARGIN);
      uint8_t tile_top_right = get_tile(ground_check_x + ENEMY_WIDTH - 1 - camera_x, next_y + ENEMY_TOP_MARGIN);

      if (is_tile_solid(tile_top_left) || is_tile_solid(tile_top_right)) {
        enemy->vel_y = 0;
      } else {
        enemy->y = next_y_upscaled;
      }
    }
  }
}

void enemy_new(uint16_t x, uint16_t y, uint8_t type) NONBANKED {
  for (uint8_t i = 0; i < ENEMY_MAX; i++) {
    if (!enemies[i].active) {
      uint8_t current_frame;
      int8_t vel_x = 0;

      switch (type) {
      case ENEMY_GOOMBO:
        current_frame = 0;
        vel_x = 0;
        y -= 8;
        break;
      case ENEMY_KOOPA:
        current_frame = 2;
        vel_x = 0;
        y -= 8;
        break;
      case ENEMY_FLY:
        current_frame = 0;
        vel_x = 0;
        y -= 8;
        break;
      default:
        current_frame = 0;
        vel_x = 0;
        y -= 8;
        break;
      }

      enemies[i].x = x << 4;
      enemies[i].y = y << 4;
      enemies[i].vel_x = vel_x;
      enemies[i].vel_y = 0;
      enemies[i].type = type;
      enemies[i].frame_counter = 0;
      enemies[i].current_frame = current_frame;
      enemies[i].flip = FALSE;
      enemies[i].stomped = FALSE;
      enemies[i].stomped_timer = 0;
      enemies[i].active = TRUE;

      enemy_count++;
      return;
    }
  }
}

void enemy_move_goomba(uint8_t index) BANKED {
  enemy_t *goomba = &enemies[index];

  if (goomba->stomped || !goomba->active) {
    return;
  }

  if (goomba->vel_x == 0) {
    goomba->vel_x = -ENEMY_GOOMBA_SPEED;
  }

  enemy_apply_horizontal_movement(goomba, FALSE);
  enemy_apply_vertical_movement(goomba, 1);
}

void enemy_move_koopa(uint8_t index) BANKED {
  enemy_t *koopa = &enemies[index];

  if (koopa->stomped || !koopa->active) {
    return;
  }

  if (koopa->vel_x == 0) {
    koopa->vel_x = -ENEMY_KOOPA_SPEED;
  }

  enemy_apply_horizontal_movement(koopa, TRUE);
  enemy_apply_vertical_movement(koopa, 1);
}

void enemy_move_fly(uint8_t index) BANKED {
  enemy_t *fly = &enemies[index];

  if (fly->stomped || !fly->active) {
    return;
  }

  uint8_t on_ground = enemy_has_ground(fly);

  if (on_ground && fly->frame_counter >= ENEMY_FLY_WAIT_FRAMES) {
    fly->vel_y = ENEMY_FLY_JUMP_VELOCITY;

    if (player_draw_x < fly->draw_x) {
      fly->vel_x = -ENEMY_FLY_JUMP_SPEED;
      fly->flip = TRUE;
    } else {
      fly->vel_x = ENEMY_FLY_JUMP_SPEED;
      fly->flip = FALSE;
    }

    fly->frame_counter = 0;
  }

  if (on_ground && fly->vel_y == 0) {
    fly->vel_x = 0;
  }

  enemy_apply_horizontal_movement(fly, FALSE);
  enemy_apply_vertical_movement(fly, 8);
}

#define ENEMY_BUNBUN_SPEED 3
#define ENEMY_BUNBUN_MOVE_FRAMES 60
#define ENEMY_BUNBUN_STOP_FRAMES 40

void enemy_move_bunbun(uint8_t index) BANKED {
  enemy_t *bunbun = &enemies[index];

  if (bunbun->stomped || !bunbun->active) {
    return;
  }

  if (bunbun->vel_x == 0) {
    if (bunbun->frame_counter >= ENEMY_BUNBUN_STOP_FRAMES) {
      bunbun->vel_x = -ENEMY_BUNBUN_SPEED;
      bunbun->frame_counter = 0;
    }
  } else {
    if (bunbun->frame_counter >= ENEMY_BUNBUN_MOVE_FRAMES) {
      bunbun->vel_x = 0;
      bunbun->frame_counter = 0;
    }
  }

  bunbun->x += bunbun->vel_x;
}

void enemy_move_stub(uint8_t index) BANKED {
  enemy_t *enemy = &enemies[index];

  if (enemy->stomped || !enemy->active) {
    return;
  }

  enemy_apply_vertical_movement(enemy, 1);
}

void enemy_stomp(uint8_t index_enemy) BANKED {
  enemy_t *enemy = &enemies[index_enemy];

  if (!enemy->active) {
    return;
  }

  enemy->stomped = TRUE;
  enemy->stomped_timer = ENEMY_STOMPED_DISPLAY_FRAMES;

  enemy->vel_x = 0;
  enemy->vel_y = 0;

  switch (enemy->type) {
  case ENEMY_GOOMBO:
    enemy->current_frame = 1;
    enemy->flip = FALSE;
    break;
  case ENEMY_KOOPA:
    enemy->current_frame = 4;
    break;
  default:
    enemy->current_frame++;
    break;
  }

  hide_sprites_range(0, MAX_HARDWARE_SPRITES);
}

void enemy_remove(uint8_t index_enemy) NONBANKED {
  if (index_enemy < ENEMY_MAX && enemies[index_enemy].active) {
    enemies[index_enemy].active = FALSE;
    enemy_count--;
    hide_sprites_range(1, MAX_HARDWARE_SPRITES);
  }
}

void enemy_reset_all(void) BANKED {
  for (uint8_t i = 0; i < ENEMY_MAX; i++) {
    enemies[i].active = FALSE;
    enemies[i].stomped = FALSE;
    enemies[i].x = 0;
    enemies[i].y = 0;
    enemies[i].vel_x = 0;
    enemies[i].vel_y = 0;
    enemies[i].draw_x = 0;
    enemies[i].draw_y = 0;
  }

  enemy_count = 0;

  hide_sprites_range(1, MAX_HARDWARE_SPRITES);
}

void enemy_update(void) BANKED {
  for (uint8_t index_enemy = 0; index_enemy < ENEMY_MAX; index_enemy++) {
    if (!enemies[index_enemy].active) {
      continue;
    }

    if (enemies[index_enemy].stomped) {
      enemies[index_enemy].stomped_timer--;
      if (enemies[index_enemy].stomped_timer == 0) {
        enemy_remove(index_enemy);
        continue;
      }
      enemies[index_enemy].draw_x =
          (enemies[index_enemy].x - camera_x_upscaled) >> 4;
      enemies[index_enemy].draw_y = enemies[index_enemy].y >> 4;
      continue;
    }

    switch (enemies[index_enemy].type) {
    case ENEMY_GOOMBO:
      enemy_move_goomba(index_enemy);
      if (enemies[index_enemy].frame_counter == ENEMY_LOOP_PER_ANIMATION_FRAME) {
        enemies[index_enemy].frame_counter = 0;
        enemies[index_enemy].flip = !enemies[index_enemy].flip;
      }
      break;
    case ENEMY_KOOPA:
      enemy_move_koopa(index_enemy);
      if (enemies[index_enemy].frame_counter == ENEMY_LOOP_PER_ANIMATION_FRAME) {
        enemies[index_enemy].frame_counter = 0;
        enemies[index_enemy].current_frame =
            (enemies[index_enemy].current_frame + 1) % 2 + 2;
      }
      break;
    case ENEMY_FLY:
      enemy_move_fly(index_enemy);
      break;
    case ENEMY_BUNBUN:
      enemy_move_bunbun(index_enemy);
      break;
    case ENEMY_GAO:
    case ENEMY_HONEN:
    case ENEMY_MEKABON:
    case ENEMY_YURARIN:
    case ENEMY_BATADON:
    case ENEMY_BULLET:
    case ENEMY_TOKOTOKO:
    case ENEMY_SUU:
    case ENEMY_KUMO:
    case ENEMY_HIYOIHOI:
    case ENEMY_PIONPI:
    case ENEMY_PONPON:
    case ENEMY_NYOLOLIN:
    case ENEMY_PLANT:
      enemy_move_stub(index_enemy);
      break;
    }

    enemies[index_enemy].draw_x =
        (enemies[index_enemy].x - camera_x_upscaled) >> 4;
    enemies[index_enemy].draw_y = enemies[index_enemy].y >> 4;

    if (camera_x_upscaled > DEVICE_SCREEN_PX_WIDTH &&
        enemies[index_enemy].x <= camera_x_upscaled - DEVICE_SCREEN_PX_WIDTH) {
      enemy_remove(index_enemy);
      continue;
    }

    if (enemies[index_enemy].draw_y > DEVICE_SCREEN_PX_HEIGHT) {
      enemy_remove(index_enemy);
      continue;
    }

    enemies[index_enemy].frame_counter++;
  }
}

uint8_t enemy_draw(uint8_t base_sprite) NONBANKED {

  for (uint8_t index_enemy = 0; index_enemy < ENEMY_MAX; index_enemy++) {
    if (!enemies[index_enemy].active) {
      continue;
    }

    uint8_t draw_index = enemies[index_enemy].current_frame;

    uint8_t _saved_bank = _current_bank;
    uint8_t tile_origin;
    const metasprite_t * const *metasprites;

    switch (enemies[index_enemy].type) {
    case ENEMY_BUNBUN:
    case ENEMY_GAO:
    case ENEMY_FLY:
      SWITCH_ROM(BANK(enemiesBirabutoSprites));
      metasprites = enemiesBirabutoSprites_metasprites;
      tile_origin = enemiesBirabutoSprites_TILE_ORIGIN;
      break;
    case ENEMY_HONEN:
    case ENEMY_MEKABON:
    case ENEMY_YURARIN:
      SWITCH_ROM(BANK(enemiesMudaSprites));
      metasprites = enemiesMudaSprites_metasprites;
      tile_origin = enemiesMudaSprites_TILE_ORIGIN;
      break;
    case ENEMY_TOKOTOKO:
    case ENEMY_SUU:
    case ENEMY_KUMO:
      SWITCH_ROM(BANK(enemiesEastonSprites));
      metasprites = enemiesEastonSprites_metasprites;
      tile_origin = enemiesEastonSprites_TILE_ORIGIN;
      break;
    case ENEMY_HIYOIHOI:
    case ENEMY_PIONPI:
    case ENEMY_PONPON:
    case ENEMY_NYOLOLIN:
      SWITCH_ROM(BANK(enemiesChaiSprites));
      metasprites = enemiesChaiSprites_metasprites;
      tile_origin = enemiesChaiSprites_TILE_ORIGIN;
      break;
    case ENEMY_GOOMBO:
    case ENEMY_KOOPA:
    case ENEMY_PLANT:
    case ENEMY_BATADON:
    case ENEMY_BULLET:
    default:
      SWITCH_ROM(BANK(enemiesSprites));
      metasprites = enemiesSprites_metasprites;
      tile_origin = enemiesSprites_TILE_ORIGIN;
      break;
    }

    const metasprite_t *enemy_metasprite = metasprites[draw_index];
    uint8_t draw_x = enemies[index_enemy].draw_x + DEVICE_SPRITE_PX_OFFSET_X + 4;
    uint8_t draw_y = enemies[index_enemy].draw_y + DEVICE_SPRITE_PX_OFFSET_Y + enemiesSprites_HEIGHT + 8;

#ifdef SEGA
    base_sprite += move_metasprite_ex(enemy_metasprite, tile_origin, 0, base_sprite, draw_x, draw_y);
#else
    if (enemies[index_enemy].flip) {
      base_sprite += move_metasprite_flipx(enemy_metasprite, tile_origin, 0, base_sprite, draw_x, draw_y);
    } else {
      base_sprite += move_metasprite_ex(enemy_metasprite, tile_origin, 0, base_sprite, draw_x, draw_y);
    }
#endif

    SWITCH_ROM(_saved_bank);
  }
  return base_sprite;
}