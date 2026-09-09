#ifndef __sound_item_INCLUDE__
#define __sound_item_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_sound_item 0b00000010

BANKREF_EXTERN(sound_item)
extern const uint8_t sound_item[];
extern void __mute_mask_sound_item;

#endif
