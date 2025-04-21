#include "sound.h"

void sound_init(void) {
  NR52_REG = 0x80;
  NR50_REG = 0x77;
  NR51_REG = 0xFF;
}

void sound_play_jump(void) {
  NR10_REG = 0x78;
  NR11_REG = 0x40;
  NR12_REG = 0x73;
  NR13_REG = 0x00;
  NR14_REG = 0xC3;
}

void sound_play_bump(void) {
  NR10_REG = 0X00;
  NR11_REG = 0X81;
  NR12_REG = 0X43;
  NR13_REG = 0X73;
  NR14_REG = 0X86;
}

void sound_play_coin(void) {
  NR10_REG = 0X1E;
  NR11_REG = 0X84;
  NR12_REG = 0X43;
  NR13_REG = 0X70;
  NR14_REG = 0X86;
}