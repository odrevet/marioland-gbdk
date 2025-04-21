#ifndef __pipe_INCLUDE__
#define __pipe_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_pipe 0b00000010

BANKREF_EXTERN(pipe)
extern const uint8_t pipe[];
extern void __mute_mask_pipe;

#endif
