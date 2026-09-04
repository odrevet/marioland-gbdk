;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler
; Version 4.5.1 #15267 (Linux)
;--------------------------------------------------------
	.module hud
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _text_print_string
	.globl _strlen
	.globl _itoa
	.globl _hud_set_level
	.globl _hud_update_coins
	.globl _hud_update_score
	.globl _hud_update_time
	.globl _hud_update_lives
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area _HRAM
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
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
;src/hud.c:3: void hud_set_level(char major, char minor) {
;	---------------------------------
; Function hud_set_level
; ---------------------------------
_hud_set_level::
	add	sp, #-4
	ld	b, a
	ld	c, e
;src/hud.c:4: char major_str[2] = {major, '\0'};
	ldhl	sp,	#0
	ld	a, b
	ld	(hl+), a
;src/hud.c:5: char minor_str[2] = {minor, '\0'};
	xor	a, a
	ld	(hl+), a
	ld	a, c
	ld	(hl+), a
	ld	(hl), #0x00
;src/hud.c:7: text_print_string(12, 1, major_str);
	ld	hl, #0
	add	hl, sp
	push	hl
	ld	e, #0x01
	ld	a, #0x0c
	call	_text_print_string
;src/hud.c:8: text_print_string(14, 1, minor_str);
	ld	hl, #2
	add	hl, sp
	push	hl
	ld	e, #0x01
	ld	a, #0x0e
	call	_text_print_string
;src/hud.c:9: }
	add	sp, #4
	ret
;src/hud.c:11: void hud_update_coins(void) {
;	---------------------------------
; Function hud_update_coins
; ---------------------------------
_hud_update_coins::
	add	sp, #-3
;src/hud.c:14: if (coins < 10) {
	ld	a, (#_coins)
	sub	a, #0x0a
	jr	NC, 00102$
;src/hud.c:15: coins_str[0] = '0'; // Add leading zero
	ldhl	sp,	#0
	ld	(hl), #0x30
;src/hud.c:16: itoa(coins, coins_str + 1, 10);
	ld	hl, #1
	add	hl, sp
	ld	a, (_coins)
	ld	c, a
	ld	b, #0x00
	ld	a, #0x0a
	push	af
	inc	sp
	push	hl
	push	bc
	call	_itoa
	add	sp, #5
	jr	00103$
00102$:
;src/hud.c:18: itoa(coins, coins_str, 10);
	ldhl	sp,	#0
	ld	e, l
	ld	d, h
	ld	a, (_coins)
	ld	b, #0x00
	ld	h, #0x0a
	push	hl
	inc	sp
	push	de
	ld	c, a
	push	bc
	call	_itoa
	add	sp, #5
00103$:
;src/hud.c:21: text_print_string(9, 1, coins_str);
	ldhl	sp,	#0
	push	hl
	ld	e, #0x01
	ld	a, #0x09
	call	_text_print_string
;src/hud.c:22: }
	add	sp, #3
	ret
;src/hud.c:24: void hud_update_score(void) {
;	---------------------------------
; Function hud_update_score
; ---------------------------------
_hud_update_score::
	add	sp, #-6
;src/hud.c:26: itoa(score, score_str, 10);
	ldhl	sp,	#0
	ld	c, l
	ld	b, h
	ld	e, c
	ld	d, b
	ld	a, (_score)
	ld	l, a
	ld	a, (_score + 1)
	ld	h, a
	push	bc
	push	de
	ld	a, #0x0a
	push	af
	inc	sp
	push	de
	push	hl
	call	_itoa
	add	sp, #5
	pop	de
	pop	bc
;src/hud.c:27: text_print_string(5 - strlen(score_str), 1, score_str);
	push	de
	call	_strlen
	pop	hl
	ld	a, #0x05
	sub	a, e
	push	bc
	ld	e, #0x01
	call	_text_print_string
;src/hud.c:28: }
	add	sp, #6
	ret
;src/hud.c:30: void hud_update_time(void) {
;	---------------------------------
; Function hud_update_time
; ---------------------------------
_hud_update_time::
	add	sp, #-4
;src/hud.c:32: itoa(time >> TIME_SHIFT, time_str, 10);
	ld	hl, #0
	add	hl, sp
	ld	c, l
	ld	b, h
	ld	hl, #_time
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	srl	d
	rr	e
	srl	d
	rr	e
	srl	d
	rr	e
	srl	d
	rr	e
	srl	d
	rr	e
	push	bc
	ld	a, #0x0a
	push	af
	inc	sp
	push	bc
	push	de
	call	_itoa
	add	sp, #5
;src/hud.c:33: text_print_string(DEVICE_SCREEN_WIDTH - 3, 1, "000");
	ld	de, #___str_0
	push	de
	ld	e, #0x01
	ld	a, #0x11
	call	_text_print_string
;src/hud.c:34: text_print_string(DEVICE_SCREEN_WIDTH - strlen(time_str), 1, time_str);
	call	_strlen
	pop	hl
	ld	a, #0x14
	sub	a, e
	ld	hl, #0
	add	hl, sp
	push	hl
	ld	e, #0x01
	call	_text_print_string
;src/hud.c:35: }
	add	sp, #4
	ret
___str_0:
	.ascii "000"
	.db 0x00
;src/hud.c:37: void hud_update_lives(void) {
;	---------------------------------
; Function hud_update_lives
; ---------------------------------
_hud_update_lives::
	add	sp, #-4
;src/hud.c:39: itoa(lives, lives_str, 10);
	ld	hl, #0
	add	hl, sp
	ld	a, (_lives)
	ld	c, a
	ld	b, #0x00
	ld	a, #0x0a
	push	af
	inc	sp
	push	hl
	push	bc
	call	_itoa
	add	sp, #5
;src/hud.c:40: text_print_string(7, 0, lives_str);
	ld	hl, #0
	add	hl, sp
	push	hl
	ld	e, #0x00
	ld	a, #0x07
	call	_text_print_string
;src/hud.c:41: }
	add	sp, #4
	ret
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
