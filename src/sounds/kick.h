#ifndef __kick_INCLUDE__
#define __kick_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_kick 0b00000010

BANKREF_EXTERN(kick)
extern const uint8_t kick[];
extern void __mute_mask_kick;

#endif
