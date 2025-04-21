#ifndef __jump_small_INCLUDE__
#define __jump_small_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_jump_small 0b00000010

BANKREF_EXTERN(jump_small)
extern const uint8_t jump_small[];
extern void __mute_mask_jump_small;

#endif
