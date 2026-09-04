#ifndef __sound_jump_small_INCLUDE__
#define __sound_jump_small_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_sound_jump_small 0b00000010

BANKREF_EXTERN(sound_jump_small)
extern const uint8_t sound_jump_small[];
extern void __mute_mask_sound_jump_small;

#endif
