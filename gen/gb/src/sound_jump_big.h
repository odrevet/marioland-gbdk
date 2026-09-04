#ifndef __sound_jump_big_INCLUDE__
#define __sound_jump_big_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_sound_jump_big 0b00000010

BANKREF_EXTERN(sound_jump_big)
extern const uint8_t sound_jump_big[];
extern void __mute_mask_sound_jump_big;

#endif
