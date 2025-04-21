#ifndef __bump_INCLUDE__
#define __bump_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_bump 0b00000010

BANKREF_EXTERN(bump)
extern const uint8_t bump[];
extern void __mute_mask_bump;

#endif
