#pragma bank 7

#include "enemy.h"

#define BOSS_BIRABUTO_ANIMATION_FRAMES 30
#define BOSS_BIRABUTO_JUMP_WAIT_FRAMES 60
#define BOSS_BIRABUTO_JUMP_STEP_FRAMES 12
#define BOSS_BIRABUTO_JUMP_STEP 32

#define BOSS_BIRABUTO_SHOOT_WAIT_FRAMES 30
#define BOSS_BIRABUTO_FIREBALL_SPEED 24
#define BOSS_BIRABUTO_FIREBALL_Y_OFFSET 6

#define BOSS_BIRABUTO_STATE_WAIT 0
#define BOSS_BIRABUTO_STATE_RISE 1
#define BOSS_BIRABUTO_STATE_FALL 2

static void boss_birabuto_shoot(enemy_t *boss) {
#ifdef GAMEBOY
  // The boss faces left and its mouth is at the pivot of the 32x24 sprite.
  // Spawn the 16x16 fireball centered on the mouth.
  enemy_new_fireball(boss->x >> 4, (boss->y >> 4) - BOSS_BIRABUTO_FIREBALL_Y_OFFSET,
                     -BOSS_BIRABUTO_FIREBALL_SPEED);
#else
  (void)boss;
#endif
}

void boss_birabuto_update(uint8_t index_enemy) BANKED {
  enemy_t *boss = &enemies[index_enemy];

  if (boss->stomped || !boss->active) {
    return;
  }

  if (boss->frame_counter >= BOSS_BIRABUTO_ANIMATION_FRAMES) {
    boss->frame_counter = 0;
    boss->current_frame = (boss->current_frame + 1) & 1;
  }

  switch (boss->move_state) {
  case BOSS_BIRABUTO_STATE_WAIT:
    boss->anim_counter++;
    if (boss->anim_counter == BOSS_BIRABUTO_SHOOT_WAIT_FRAMES) {
      boss_birabuto_shoot(boss);
    }
    if (boss->anim_counter >= BOSS_BIRABUTO_JUMP_WAIT_FRAMES) {
      boss->anim_counter = 0;
      boss->y_origin = boss->y;
      boss->move_state = BOSS_BIRABUTO_STATE_RISE;
    }
    break;
  case BOSS_BIRABUTO_STATE_RISE:
    boss->y -= BOSS_BIRABUTO_JUMP_STEP;
    boss->anim_counter++;
    if (boss->anim_counter >= BOSS_BIRABUTO_JUMP_STEP_FRAMES) {
      boss_birabuto_shoot(boss);
      boss->anim_counter = 0;
      boss->move_state = BOSS_BIRABUTO_STATE_FALL;
    }
    break;
  case BOSS_BIRABUTO_STATE_FALL:
    boss->y += BOSS_BIRABUTO_JUMP_STEP;
    boss->anim_counter++;
    if (boss->anim_counter >= BOSS_BIRABUTO_JUMP_STEP_FRAMES) {
      boss->y = boss->y_origin;
      boss->anim_counter = 0;
      boss->move_state = BOSS_BIRABUTO_STATE_WAIT;
    }
    break;
  }
}
