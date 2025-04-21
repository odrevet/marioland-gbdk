#ifndef __oneup_INCLUDE__
#define __oneup_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_oneup 0b00000010

BANKREF_EXTERN(oneup)
extern const uint8_t oneup[];
extern void __mute_mask_oneup;

#endif
