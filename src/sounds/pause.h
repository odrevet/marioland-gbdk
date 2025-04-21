#ifndef __pause_INCLUDE__
#define __pause_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_pause 0b00000010

BANKREF_EXTERN(pause)
extern const uint8_t pause[];
extern void __mute_mask_pause;

#endif
