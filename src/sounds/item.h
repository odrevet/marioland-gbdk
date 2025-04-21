#ifndef __item_INCLUDE__
#define __item_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_item 0b00000010

BANKREF_EXTERN(item)
extern const uint8_t item[];
extern void __mute_mask_item;

#endif
