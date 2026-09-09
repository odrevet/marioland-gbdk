#ifndef __sound_bullet_bill_INCLUDE__
#define __sound_bullet_bill_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_sound_bullet_bill 0b00000010

BANKREF_EXTERN(sound_bullet_bill)
extern const uint8_t sound_bullet_bill[];
extern void __mute_mask_sound_bullet_bill;

#endif
