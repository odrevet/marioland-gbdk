#ifndef __squish_INCLUDE__
#define __squish_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_squish 0b00000010

BANKREF_EXTERN(squish)
extern const uint8_t squish[];
extern void __mute_mask_squish;

#endif
