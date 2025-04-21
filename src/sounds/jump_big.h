#ifndef __jump_big_INCLUDE__
#define __jump_big_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_jump_big 0b00000010

BANKREF_EXTERN(jump_big)
extern const uint8_t jump_big[];
extern void __mute_mask_jump_big;

#endif
