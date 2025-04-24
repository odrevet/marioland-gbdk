#ifndef __sound_pipe_INCLUDE__
#define __sound_pipe_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_sound_pipe 0b00000010

BANKREF_EXTERN(sound_pipe)
extern const uint8_t sound_pipe[];
extern void __mute_mask_sound_pipe;

#endif
