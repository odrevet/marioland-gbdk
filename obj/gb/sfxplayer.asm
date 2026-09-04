;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler
; Version 4.5.1 #15267 (Linux)
;--------------------------------------------------------
	.module sfxplayer
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _sfx_play_sample
	.globl _sfx_play_bank
	.globl _sfx_frame_skip
	.globl _sfx_play_isr
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area _HRAM
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_sfx_frame_skip::
	.ds 1
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
_sfx_play_bank::
	.ds 1
_sfx_play_sample::
	.ds 2
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
;sm83/sfxplayer.c:10: uint8_t sfx_play_isr(void) NONBANKED NAKED {
;	---------------------------------
; Function sfx_play_isr
; ---------------------------------
_sfx_play_isr::
;sm83/sfxplayer.c:136: __endasm;
	.macro	copy_reg ?lbl
	sla	b
	jr	nc, lbl
	ld	a, (hl+)
	ldh	(c), a
lbl:
	inc	c
	.endm
	ld	hl, #_sfx_play_sample
	ld	a, (hl+)
	ld	e, a
	or	(hl)
	ret	z ; return 0
	ld	d, (hl)
	ld	hl, #_sfx_frame_skip
	xor	a
	or	(hl)
	jr	z, 7$
	dec	(hl)
	ret	; A != 0 that returns 1
7$:
	ld	h, d
	ld	l, e ; HL = current position inside the sample
	ldh	a, (__current_bank) ; save bank and switch
	ld	e, a
	ld	a, (_sfx_play_bank)
	inc	a ; 0xffu ?
	ret	z ; return 0
	dec	a
	ldh	(__current_bank), a
	ld	(_rROMB0), a
	ld	d, #0x0f
	ld	a, (hl)
	swap	a
	and	d
	ld	(_sfx_frame_skip), a
	ld	a, (hl+)
	and	d
	ld	d, a ; d = frame channel count
	jp	z, 6$
2$:
	ld	a, (hl+)
	ld	b, a ; a = b = channel no + register mask
	and	#0b00000111
	cp	#5
	jr	c, 3$
	cp	#7
	jr	z, 5$ ; terminator
	ldh	a, (_NR51_REG)
	ld	c, a
	and	#0b10111011
	ldh	(_NR51_REG), a
	xor	a
	ld	(_NR30_REG), a
	.irp	ofs,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
	ld	a, (hl+)
	ldh	(__AUD3WAVERAM+ofs), a
	.endm
	ld	a, b
	cp	#6
	jr	nz, 9$ ; just load waveform, not play
	ld	a, #0x80
	ldh	(_NR30_REG),a
	ld	a, #0xFE ; length of wave
	ldh	(_NR31_REG),a
	ld	a, #0x20 ; volume
	ldh	(_NR32_REG),a
	xor	a ; low freq bits are zero
	ldh	(_NR33_REG),a
	ld	a, #0xC7 ; start; no loop; high freq bits are 111
	ldh	(_NR34_REG),a
9$:
	ld	a, c
	ldh	(_NR51_REG), a
	jr	4$
5$:
; terminator
	ld	hl, #0
	ld	d, l
	jr	0$
3$:
	ld	c, a
	add	a
	add	a
	add	c
	add	#_NR10_REG
	ld	c, a ; c = NR10_REG + (a & 7) * 5
	.rept	5
	copy_reg
	.endm
4$:
	dec	d
	jp	nz, 2$
6$:
	inc	d ; return 1 if still playing
0$:
	ld	a, l ; save current position
	ld	(_sfx_play_sample), a
	ld	a, h
	ld	(_sfx_play_sample + 1), a
	ld	a, e ; restore bank
	ldh	(__current_bank), a
	ld	(_rROMB0), a
	ld	a, d ; result in a
	ret
;sm83/sfxplayer.c:145: }
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
	.area _CODE
	.area _INITIALIZER
__xinit__sfx_play_bank:
	.db #0xff	; 255
__xinit__sfx_play_sample:
	.dw #0x0000
	.area _CABS (ABS)
