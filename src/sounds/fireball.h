#ifndef __fireball_INCLUDE__
#define __fireball_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_fireball 0b00000010

BANKREF_EXTERN(fireball)
extern const uint8_t fireball[];
extern void __mute_mask_fireball;

#endif
