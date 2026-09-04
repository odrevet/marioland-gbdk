;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler
; Version 4.5.1 #15267 (Linux)
;--------------------------------------------------------
	.module pipe
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _pipe_active
	.globl _active_pipe_direction
	.globl _active_pipe_tile_y
	.globl _active_pipe_tile_x
	.globl _active_pipe
	.globl _pipe_new
	.globl _pipe_clear
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area _HRAM
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_active_pipe::
	.ds 7
_active_pipe_tile_x::
	.ds 1
_active_pipe_tile_y::
	.ds 1
_active_pipe_direction::
	.ds 1
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
_pipe_active::
	.ds 1
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;src/pipe.c:9: void pipe_new(uint8_t tile_x, uint8_t tile_y, uint8_t direction, pipe_params *params) {
;	---------------------------------
; Function pipe_new
; ---------------------------------
_pipe_new::
	ld	(#_active_pipe_tile_x),a
	ld	hl, #_active_pipe_tile_y
	ld	(hl), e
;src/pipe.c:12: active_pipe_direction = direction;
	ldhl	sp,	#2
	ld	a, (hl)
	ld	(#_active_pipe_direction),a
;src/pipe.c:13: active_pipe = *params;
	ldhl	sp,	#3
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	ld	de, #0x0007
	push	de
	ld	de, #_active_pipe
	call	___memcpy
;src/pipe.c:14: pipe_active = TRUE;
	ld	hl, #_pipe_active
	ld	(hl), #0x01
;src/pipe.c:15: }
	pop	hl
	add	sp, #3
	jp	(hl)
;src/pipe.c:17: void pipe_clear(void) {
;	---------------------------------
; Function pipe_clear
; ---------------------------------
_pipe_clear::
;src/pipe.c:18: pipe_active = FALSE;
	xor	a, a
	ld	(#_pipe_active),a
;src/pipe.c:19: }
	ret
	.area _CODE
	.area _INITIALIZER
__xinit__pipe_active:
	.db #0x00	;  0
	.area _CABS (ABS)
