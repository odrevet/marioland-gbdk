#pragma bank 255

#include "enemy.h"
#include "global.h"
#include "level.h"
#include <stdint.h>
#include <stdlib.h>

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
#define ENEMY_FLY_JUMP_SPEED 14

#define ENEMY_BUNBUN_SPEED 3
#define ENEMY_BUNBUN_MOVE_FRAMES 60
#define ENEMY_BUNBUN_STOP_FRAMES 40

#define ENEMY_GAO_ATTACK_WAIT_FRAMES 240
#define ENEMY_GAO_ATTACK_DURATION_FRAMES 20

#define ENEMY_HONEN_REST_FRAMES 90
#define ENEMY_HONEN_SPEED 8
#define ENEMY_HONEN_RISE_TARGET_Y 24
#define ENEMY_HONEN_BASE_Y 128

#define HONEN_STATE_RESTING 0
#define HONEN_STATE_RISING 1
#define HONEN_STATE_FALLING 2

#define ENEMY_MEKABON_SPEED 3
#define ENEMY_MEKABON_DETECT_RANGE 40
#define ENEMY_MEKABON_HEAD_SPEED 6

#define MEKABON_STATE_WALK 0
#define MEKABON_STATE_HEAD_OUT 1
#define MEKABON_STATE_HEAD_BACK 2

#define ENEMY_YURARIN_SPEED 2
#define ENEMY_YURARIN_WAVE_FRAMES 30
#define ENEMY_YURARIN_VERTICAL_SPEED 1

#define ENEMY_BATADON_SPEED 3
#define ENEMY_BATADON_BOUNCE_VELOCITY -40
#define ENEMY_BATADON_GRAVITY_DIVISOR 10
#define ENEMY_BATADON_BOUNCE_FRAMES 50

#define ENEMY_BULLET_SPEED 6

#define ENEMY_TOKOTOKO_SPEED 6

#define ENEMY_SUU_DETECT_RANGE_X 32
#define ENEMY_SUU_DROP_SPEED 4
#define ENEMY_SUU_RISE_SPEED 2
#define ENEMY_SUU_MAX_DROP 64

#define SUU_STATE_WAIT 0
#define SUU_STATE_DROP 1
#define SUU_STATE_RISE 2

#define ENEMY_KUMO_SPEED 4
#define ENEMY_KUMO_JUMP_VELOCITY -40
#define ENEMY_KUMO_WAIT_FRAMES 30

#define ENEMY_HIYOIHOI_SPEED 3
#define ENEMY_HIYOIHOI_BACK_DETECT_RANGE 24

#define ENEMY_PIONPI_SPEED 2
#define ENEMY_PIONPI_JUMP_VELOCITY -24
#define ENEMY_PIONPI_JUMP_INTERVAL_FRAMES 20
#define ENEMY_PIONPI_STUN_FRAMES 60

#define ENEMY_PONPON_SPEED 2
#define ENEMY_PONPON_SHOOT_INTERVAL_FRAMES 90

#define ENEMY_PLANT_SPEED 2
#define ENEMY_PLANT_RISE_HEIGHT 24
#define ENEMY_PLANT_WAIT_FRAMES 60
#define ENEMY_PLANT_SAFE_RANGE_X 16

#define PLANT_STATE_HIDDEN 0
#define PLANT_STATE_RISING 1
#define PLANT_STATE_UP 2
#define PLANT_STATE_FALLING 3

uint8_t enemy_has_ground(enemy_t *enemy) BANKED {
#ifndef NINTENDO_NES
  uint16_t ground_check_x = enemy->x >> 4;
  uint16_t ground_check_y = (enemy->y >> 4) + ENEMY_HEIGHT;

  uint8_t tile_ground_left = get_tile(ground_check_x - camera_x, ground_check_y);
  uint8_t tile_ground_right = get_tile(ground_check_x + ENEMY_WIDTH - 1 - camera_x, ground_check_y);

  return is_tile_solid(tile_ground_left) || is_tile_solid(tile_ground_right) ||
         is_tile_passthought(tile_ground_left, tile_ground_right);
#else
  return 0;
#endif
}

uint8_t enemy_has_ground_ahead(enemy_t *enemy, int8_t vel_x) BANKED {
#ifndef NINTENDO_NES
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
#else
  return 0;
#endif
}

void enemy_apply_horizontal_movement(enemy_t *enemy, uint8_t check_cliffs) BANKED {
#ifndef NINTENDO_NES
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
#else
#endif
}

void enemy_apply_vertical_movement(enemy_t *enemy, int8_t gravity_divisor, uint8_t on_ground) BANKED {
#ifndef NINTENDO_NES
  uint16_t ground_check_x = enemy->x >> 4;
  uint16_t ground_check_y = (enemy->y >> 4) + ENEMY_HEIGHT;

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
#else
#endif
}

void enemy_new(uint16_t x, uint16_t y, uint8_t type) BANKED {
#ifndef NINTENDO_NES
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
      case ENEMY_BUNBUN:
        current_frame = 3;
        vel_x = 0;
        y -= 8;
        break;
      case ENEMY_GAO:
        current_frame = 6;
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
      enemies[i].anim_counter = 0;
      enemies[i].current_frame = current_frame;
      enemies[i].flip = FALSE;
      enemies[i].stomped = FALSE;
      enemies[i].stomped_timer = 0;
      enemies[i].active = TRUE;
      enemies[i].move_state = 0;
      enemies[i].hp = 0;

      if (type == ENEMY_SUU || type == ENEMY_PLANT) {
        enemies[i].y_origin = enemies[i].y;
      }

      enemy_count++;
      return;
    }
  }
#endif
}

void enemy_move_goomba(uint8_t index) BANKED {
#ifndef NINTENDO_NES
  enemy_t *goomba = &enemies[index];

  if (goomba->stomped || !goomba->active) {
    return;
  }

  if (goomba->vel_x == 0) {
    goomba->vel_x = -ENEMY_GOOMBA_SPEED;
  }

  enemy_apply_horizontal_movement(goomba, FALSE);
  enemy_apply_vertical_movement(goomba, 1, enemy_has_ground(goomba));
#else
#endif
}

void enemy_move_koopa(uint8_t index) BANKED {
#ifndef NINTENDO_NES
  enemy_t *koopa = &enemies[index];

  if (koopa->stomped || !koopa->active) {
    return;
  }

  if (koopa->vel_x == 0) {
    koopa->vel_x = -ENEMY_KOOPA_SPEED;
  }

  enemy_apply_horizontal_movement(koopa, TRUE);
  enemy_apply_vertical_movement(koopa, 1, enemy_has_ground(koopa));
#else
#endif
}

void enemy_move_fly(uint8_t index) BANKED {
#ifndef NINTENDO_NES
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
  enemy_apply_vertical_movement(fly, 8, on_ground);
#else
#endif
}

void enemy_move_bunbun(uint8_t index) BANKED {
#ifndef NINTENDO_NES
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
#else
#endif
}

void enemy_move_gao(uint8_t index) BANKED {
#ifndef NINTENDO_NES
  enemy_t *gao = &enemies[index];

  if (gao->stomped || !gao->active) {
    return;
  }

  if (gao->anim_counter > 0) {
    gao->anim_counter++;
    if (gao->anim_counter >= ENEMY_GAO_ATTACK_DURATION_FRAMES) {
      gao->anim_counter = 0;
      gao->current_frame = 6;
    }
  } else if (gao->frame_counter >= ENEMY_GAO_ATTACK_WAIT_FRAMES) {
    gao->frame_counter = 0;
    gao->anim_counter = 1;
    gao->current_frame = 7;
  }

  enemy_apply_vertical_movement(gao, 1, enemy_has_ground(gao));
#else
#endif
}

void enemy_move_honen(uint8_t index) BANKED {
#ifndef NINTENDO_NES
  enemy_t *honen = &enemies[index];

  if (honen->stomped || !honen->active) {
    return;
  }

  switch (honen->move_state) {
  case HONEN_STATE_RESTING:
    if (honen->frame_counter >= ENEMY_HONEN_REST_FRAMES) {
      honen->frame_counter = 0;
      honen->move_state = HONEN_STATE_RISING;
    }
    break;
  case HONEN_STATE_RISING:
    if ((honen->y >> 4) <= ENEMY_HONEN_RISE_TARGET_Y) {
      honen->move_state = HONEN_STATE_FALLING;
    } else {
      honen->y -= ENEMY_HONEN_SPEED;
    }
    break;
  case HONEN_STATE_FALLING:
    if ((honen->y >> 4) >= ENEMY_HONEN_BASE_Y) {
      honen->y = ENEMY_HONEN_BASE_Y << 4;
      honen->move_state = HONEN_STATE_RESTING;
    } else {
      honen->y += ENEMY_HONEN_SPEED;
    }
    break;
  }
#else
#endif
}

void enemy_move_mekabon(uint8_t index) BANKED {
  enemy_t *mekabon = &enemies[index];

  if (mekabon->stomped || !mekabon->active) {
    return;
  }

  switch (mekabon->move_state) {
  case MEKABON_STATE_WALK:
    if (mekabon->vel_x == 0) {
      mekabon->vel_x = -ENEMY_MEKABON_SPEED;
    }

    if (abs((int16_t)player_draw_x - (int16_t)mekabon->draw_x) < ENEMY_MEKABON_DETECT_RANGE) {
      mekabon->x_origin = mekabon->x;
      mekabon->move_state = MEKABON_STATE_HEAD_OUT;
      break;
    }

    enemy_apply_horizontal_movement(mekabon, TRUE);
    enemy_apply_vertical_movement(mekabon, 1, enemy_has_ground(mekabon));
    break;

  case MEKABON_STATE_HEAD_OUT: {
    uint16_t diff;

    if (player_draw_x < mekabon->draw_x) {
      mekabon->x -= ENEMY_MEKABON_HEAD_SPEED;
    } else {
      mekabon->x += ENEMY_MEKABON_HEAD_SPEED;
    }

    diff = mekabon->x > mekabon->x_origin ? mekabon->x - mekabon->x_origin : mekabon->x_origin - mekabon->x;
    if (diff >= (ENEMY_MEKABON_DETECT_RANGE << 4)) {
      mekabon->move_state = MEKABON_STATE_HEAD_BACK;
    }
    break;
  }

  case MEKABON_STATE_HEAD_BACK:
    if (mekabon->x < mekabon->x_origin) {
      mekabon->x += ENEMY_MEKABON_HEAD_SPEED;
      if (mekabon->x >= mekabon->x_origin) mekabon->x = mekabon->x_origin;
    } else {
      mekabon->x -= ENEMY_MEKABON_HEAD_SPEED;
      if (mekabon->x <= mekabon->x_origin) mekabon->x = mekabon->x_origin;
    }

    if (mekabon->x == mekabon->x_origin) {
      mekabon->vel_x = -mekabon->vel_x;
      mekabon->move_state = MEKABON_STATE_WALK;
    }
    break;
  }
}

void enemy_move_yurarin(uint8_t index) BANKED {
  enemy_t *yurarin = &enemies[index];

  if (yurarin->stomped || !yurarin->active) {
    return;
  }

  if (yurarin->vel_x == 0) {
    yurarin->vel_x = -ENEMY_YURARIN_SPEED;
  }

  if (yurarin->frame_counter >= ENEMY_YURARIN_WAVE_FRAMES) {
    yurarin->frame_counter = 0;
    yurarin->vel_y = -yurarin->vel_y;
    if (yurarin->vel_y == 0) {
      yurarin->vel_y = ENEMY_YURARIN_VERTICAL_SPEED;
    }
  }

  enemy_apply_horizontal_movement(yurarin, FALSE);
  yurarin->y += yurarin->vel_y;
}

void enemy_move_batadon(uint8_t index) BANKED {
  enemy_t *batadon = &enemies[index];

  if (batadon->stomped || !batadon->active) {
    return;
  }

  if (batadon->frame_counter >= ENEMY_BATADON_BOUNCE_FRAMES) {
    batadon->frame_counter = 0;
    batadon->vel_y = ENEMY_BATADON_BOUNCE_VELOCITY;
  }

  if (player_draw_x < batadon->draw_x) {
    batadon->vel_x = -ENEMY_BATADON_SPEED;
    batadon->flip = TRUE;
  } else {
    batadon->vel_x = ENEMY_BATADON_SPEED;
    batadon->flip = FALSE;
  }

  batadon->x += batadon->vel_x;
  batadon->vel_y += ENEMY_GRAVITY / ENEMY_BATADON_GRAVITY_DIVISOR;
  batadon->y += batadon->vel_y;
}

void enemy_move_bullet(uint8_t index) BANKED {
  enemy_t *bullet = &enemies[index];

  if (!bullet->active) {
    return;
  }

  bullet->x += bullet->vel_x;
}

void enemy_move_tokotoko(uint8_t index) BANKED {
  enemy_t *tokotoko = &enemies[index];

  if (tokotoko->stomped || !tokotoko->active) {
    return;
  }

  if (tokotoko->vel_x == 0) {
    tokotoko->vel_x = -ENEMY_TOKOTOKO_SPEED;
  }

  enemy_apply_horizontal_movement(tokotoko, FALSE);
  enemy_apply_vertical_movement(tokotoko, 1, enemy_has_ground(tokotoko));
}

void enemy_move_suu(uint8_t index) BANKED {
  enemy_t *suu = &enemies[index];

  if (suu->stomped || !suu->active) {
    return;
  }

  switch (suu->move_state) {
  case SUU_STATE_WAIT:
    if (abs((int16_t)player_draw_x - (int16_t)suu->draw_x) < ENEMY_SUU_DETECT_RANGE_X) {
      suu->move_state = SUU_STATE_DROP;
    }
    break;
  case SUU_STATE_DROP:
    suu->y += ENEMY_SUU_DROP_SPEED;
    if ((suu->y >> 4) - (suu->y_origin >> 4) >= ENEMY_SUU_MAX_DROP) {
      suu->move_state = SUU_STATE_RISE;
    }
    break;
  case SUU_STATE_RISE:
    suu->y -= ENEMY_SUU_RISE_SPEED;
    if (suu->y <= suu->y_origin) {
      suu->y = suu->y_origin;
      suu->move_state = SUU_STATE_WAIT;
    }
    break;
  }
}

void enemy_move_kumo(uint8_t index) BANKED {
  enemy_t *kumo = &enemies[index];

  if (kumo->stomped || !kumo->active) {
    return;
  }

  uint8_t on_ground = enemy_has_ground(kumo);

  if (on_ground && kumo->vel_y == 0 && kumo->frame_counter >= ENEMY_KUMO_WAIT_FRAMES) {
    kumo->vel_y = ENEMY_KUMO_JUMP_VELOCITY;

    if (player_draw_x < kumo->draw_x) {
      kumo->vel_x = -ENEMY_KUMO_SPEED;
      kumo->flip = TRUE;
    } else {
      kumo->vel_x = ENEMY_KUMO_SPEED;
      kumo->flip = FALSE;
    }

    kumo->frame_counter = 0;
  }

  if (on_ground && kumo->vel_y == 0) {
    kumo->vel_x = 0;
  }

  enemy_apply_horizontal_movement(kumo, FALSE);
  enemy_apply_vertical_movement(kumo, 4, on_ground);
}

void enemy_move_hiyoihoi(uint8_t index) BANKED {
  enemy_t *hiyoihoi = &enemies[index];
  int8_t facing_forward;
  int16_t rel_x;
  uint8_t player_behind;

  if (hiyoihoi->stomped || !hiyoihoi->active) {
    return;
  }

  if (hiyoihoi->vel_x == 0) {
    hiyoihoi->vel_x = -ENEMY_HIYOIHOI_SPEED;
  }

  facing_forward = hiyoihoi->flip ? -1 : 1;
  rel_x = (int16_t)player_draw_x - (int16_t)hiyoihoi->draw_x;
  player_behind = (facing_forward > 0 && rel_x < 0 && -rel_x < ENEMY_HIYOIHOI_BACK_DETECT_RANGE) ||
                  (facing_forward < 0 && rel_x > 0 && rel_x < ENEMY_HIYOIHOI_BACK_DETECT_RANGE);

  if (player_behind) {
    hiyoihoi->vel_x = -hiyoihoi->vel_x;
    hiyoihoi->flip = !hiyoihoi->flip;
  }

  enemy_apply_horizontal_movement(hiyoihoi, TRUE);
  enemy_apply_vertical_movement(hiyoihoi, 1, enemy_has_ground(hiyoihoi));
}

void enemy_move_pionpi(uint8_t index) BANKED {
  enemy_t *pionpi = &enemies[index];
  uint8_t on_ground;

  if (!pionpi->active) {
    return;
  }

  if (pionpi->hp > 0) {
    pionpi->hp--;
    return;
  }

  on_ground = enemy_has_ground(pionpi);

  if (on_ground && pionpi->frame_counter >= ENEMY_PIONPI_JUMP_INTERVAL_FRAMES) {
    pionpi->vel_y = ENEMY_PIONPI_JUMP_VELOCITY;

    if (player_draw_x < pionpi->draw_x) {
      pionpi->vel_x = -ENEMY_PIONPI_SPEED;
      pionpi->flip = TRUE;
    } else {
      pionpi->vel_x = ENEMY_PIONPI_SPEED;
      pionpi->flip = FALSE;
    }

    pionpi->frame_counter = 0;
  }

  enemy_apply_horizontal_movement(pionpi, FALSE);
  enemy_apply_vertical_movement(pionpi, 2, on_ground);
}

void enemy_move_ponpon(uint8_t index) BANKED {
  enemy_t *ponpon = &enemies[index];

  if (ponpon->stomped || !ponpon->active) {
    return;
  }

  if (ponpon->vel_x == 0) {
    ponpon->vel_x = -ENEMY_PONPON_SPEED;
  }

  if (ponpon->frame_counter >= ENEMY_PONPON_SHOOT_INTERVAL_FRAMES) {
    ponpon->frame_counter = 0;
  }

  enemy_apply_horizontal_movement(ponpon, TRUE);
  enemy_apply_vertical_movement(ponpon, 1, enemy_has_ground(ponpon));
}

void enemy_move_plant(uint8_t index) BANKED {
  enemy_t *plant = &enemies[index];
  uint8_t player_near;

  if (plant->stomped || !plant->active) {
    return;
  }

  player_near = abs((int16_t)player_draw_x - (int16_t)plant->draw_x) < ENEMY_PLANT_SAFE_RANGE_X;

  switch (plant->move_state) {
  case PLANT_STATE_HIDDEN:
    if (plant->frame_counter >= ENEMY_PLANT_WAIT_FRAMES && !player_near) {
      plant->frame_counter = 0;
      plant->move_state = PLANT_STATE_RISING;
    }
    break;
  case PLANT_STATE_RISING:
    plant->y -= ENEMY_PLANT_SPEED;
    if ((plant->y_origin >> 4) - (plant->y >> 4) >= ENEMY_PLANT_RISE_HEIGHT) {
      plant->frame_counter = 0;
      plant->move_state = PLANT_STATE_UP;
    }
    break;
  case PLANT_STATE_UP:
    if (plant->frame_counter >= ENEMY_PLANT_WAIT_FRAMES) {
      plant->frame_counter = 0;
      plant->move_state = PLANT_STATE_FALLING;
    }
    break;
  case PLANT_STATE_FALLING:
    plant->y += ENEMY_PLANT_SPEED;
    if (plant->y >= plant->y_origin) {
      plant->y = plant->y_origin;
      plant->frame_counter = 0;
      plant->move_state = PLANT_STATE_HIDDEN;
    }
    break;
  }
}

void enemy_move_stub(uint8_t index) BANKED {
  enemy_t *enemy = &enemies[index];

  if (enemy->stomped || !enemy->active) {
    return;
  }

  enemy_apply_vertical_movement(enemy, 1, enemy_has_ground(enemy));
}

void enemy_stomp(uint8_t index_enemy) BANKED {
  enemy_t *enemy = &enemies[index_enemy];

  if (!enemy->active) {
    return;
  }

  if (enemy->type == ENEMY_PIONPI) {
    enemy->hp = ENEMY_PIONPI_STUN_FRAMES;
    enemy->vel_x = 0;
    enemy->vel_y = 0;
    enemy->current_frame = 9;
    hide_sprites_range(0, MAX_HARDWARE_SPRITES);
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
  case ENEMY_FLY:
    enemy->current_frame = 2;
    enemy->flip = FALSE;
    break;
  case ENEMY_BUNBUN:
    enemy->current_frame = 5;
    enemy->flip = FALSE;
    break;
  case ENEMY_GAO:
    enemy->current_frame = 8;
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
    enemies[i].move_state = 0;
    enemies[i].hp = 0;
  }

  enemy_count = 0;

  hide_sprites_range(1, MAX_HARDWARE_SPRITES);
}

void enemy_update(void) BANKED {
#ifndef NINTENDO_NES
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
      enemies[index_enemy].anim_counter++;
      if (enemies[index_enemy].anim_counter >= ENEMY_LOOP_PER_ANIMATION_FRAME) {
        enemies[index_enemy].anim_counter = 0;
        enemies[index_enemy].current_frame =
            (enemies[index_enemy].current_frame - 3 + 1) % 2 + 3;
      }
      break;
    case ENEMY_GAO:
      enemy_move_gao(index_enemy);
      break;
    case ENEMY_HONEN:
      enemy_move_honen(index_enemy);
      enemies[index_enemy].anim_counter++;
      if (enemies[index_enemy].anim_counter >= ENEMY_LOOP_PER_ANIMATION_FRAME) {
        enemies[index_enemy].anim_counter = 0;
        enemies[index_enemy].current_frame =
            (enemies[index_enemy].current_frame + 1) % 2 + 8;
      }
      break;
    case ENEMY_MEKABON:
      enemy_move_mekabon(index_enemy);
      break;
    case ENEMY_YURARIN:
      enemy_move_yurarin(index_enemy);
      break;
    case ENEMY_BATADON:
      enemy_move_batadon(index_enemy);
      break;
    case ENEMY_BULLET:
      enemy_move_bullet(index_enemy);
      break;
    case ENEMY_TOKOTOKO:
      enemy_move_tokotoko(index_enemy);
      break;
    case ENEMY_SUU:
      enemy_move_suu(index_enemy);
      break;
    case ENEMY_KUMO:
      enemy_move_kumo(index_enemy);
      break;
    case ENEMY_HIYOIHOI:
      enemy_move_hiyoihoi(index_enemy);
      break;
    case ENEMY_PIONPI:
      enemy_move_pionpi(index_enemy);
      break;
    case ENEMY_PONPON:
      enemy_move_ponpon(index_enemy);
      break;
    case ENEMY_NYOLOLIN:
      enemy_move_stub(index_enemy);
      break;
    case ENEMY_PLANT:
      enemy_move_plant(index_enemy);
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
#else
#endif
}

uint8_t enemy_draw(uint8_t base_sprite) NONBANKED {
#ifndef NINTENDO_NES
  uint8_t _saved_bank = _current_bank;
  uint8_t current_bank = _current_bank;

  for (uint8_t index_enemy = 0; index_enemy < ENEMY_MAX; index_enemy++) {
    if (!enemies[index_enemy].active) {
      continue;
    }

    uint8_t draw_index = enemies[index_enemy].current_frame;

    uint8_t enemy_bank;
    uint8_t tile_origin;
    const metasprite_t * const *metasprites;

    switch (enemies[index_enemy].type) {
    case ENEMY_BUNBUN:
    case ENEMY_GAO:
    case ENEMY_FLY:
      enemy_bank = BANK(enemiesBirabutoSprites);
      metasprites = enemiesBirabutoSprites_metasprites;
      tile_origin = enemiesBirabutoSprites_TILE_ORIGIN;
      break;
    case ENEMY_HONEN:
    case ENEMY_MEKABON:
    case ENEMY_YURARIN:
      enemy_bank = BANK(enemiesMudaSprites);
      metasprites = enemiesMudaSprites_metasprites;
      tile_origin = enemiesMudaSprites_TILE_ORIGIN;
      break;
    case ENEMY_TOKOTOKO:
    case ENEMY_SUU:
    case ENEMY_KUMO:
      enemy_bank = BANK(enemiesEastonSprites);
      metasprites = enemiesEastonSprites_metasprites;
      tile_origin = enemiesEastonSprites_TILE_ORIGIN;
      break;
    case ENEMY_HIYOIHOI:
    case ENEMY_PIONPI:
    case ENEMY_PONPON:
    case ENEMY_NYOLOLIN:
      enemy_bank = BANK(enemiesChaiSprites);
      metasprites = enemiesChaiSprites_metasprites;
      tile_origin = enemiesChaiSprites_TILE_ORIGIN;
      break;
    case ENEMY_GOOMBO:
    case ENEMY_KOOPA:
    case ENEMY_PLANT:
    case ENEMY_BATADON:
    case ENEMY_BULLET:
    default:
      enemy_bank = BANK(enemiesSprites);
      metasprites = enemiesSprites_metasprites;
      tile_origin = enemiesSprites_TILE_ORIGIN;
      break;
    }

    if (enemy_bank != current_bank) {
      SWITCH_ROM(enemy_bank);
      current_bank = enemy_bank;
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
  }
  SWITCH_ROM(_saved_bank);
  return base_sprite;
#else
  return base_sprite;
#endif
}