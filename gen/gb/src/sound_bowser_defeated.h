#ifndef __sound_bowser_defeated_INCLUDE__
#define __sound_bowser_defeated_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_sound_bowser_defeated 0b00000010

BANKREF_EXTERN(sound_bowser_defeated)
extern const uint8_t sound_bowser_defeated[];
extern void __mute_mask_sound_bowser_defeated;

#endif
