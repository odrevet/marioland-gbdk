#ifndef __vine_INCLUDE__
#define __vine_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_vine 0b00000010

BANKREF_EXTERN(vine)
extern const uint8_t vine[];
extern void __mute_mask_vine;

#endif
