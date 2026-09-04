;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler
; Version 4.5.1 #15267 (Linux)
;--------------------------------------------------------
	.module coin_animated
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _coin_index
	.globl _coin_animated_array
	.globl _coin_animated_new
	.globl _coin_animated_update
	.globl _coin_animated_draw
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area _HRAM
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_coin_animated_array::
	.ds 12
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
_coin_index::
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
;src/coin_animated.c:9: void coin_animated_new(uint8_t index_x, uint8_t index_y) {
;	---------------------------------
; Function coin_animated_new
; ---------------------------------
_coin_animated_new::
	ld	d, a
;src/coin_animated.c:10: coin_animated_array[coin_index].draw_x = index_x << 3;
	ld	bc, #_coin_animated_array+0
	ld	a, (_coin_index)
	ld	l, a
	ld	h, #0x00
	add	hl, hl
	add	hl, hl
	add	hl, bc
	ld	a, d
	add	a, a
	add	a, a
	add	a, a
	ld	(hl), a
;src/coin_animated.c:11: coin_animated_array[coin_index].draw_y = index_y << 3;
	ld	a, (_coin_index)
	ld	h, #0x00
	ld	l, a
	add	hl, hl
	add	hl, hl
	add	hl, bc
	inc	hl
	ld	a, e
	add	a, a
	add	a, a
	add	a, a
	ld	(hl), a
;src/coin_animated.c:12: coin_animated_array[coin_index].ttl = COIN_ANIMATED_INITIAL_TTL;
	ld	a, (_coin_index)
	ld	h, #0x00
	ld	l, a
	add	hl, hl
	add	hl, hl
	add	hl, bc
	inc	hl
	inc	hl
	ld	(hl), #0x14
;src/coin_animated.c:13: hide_sprite(COIN_HW_SPRITE_BASE + coin_index);
	ld	a, (_coin_index)
	add	a, #0x0a
	ld	e, a
;/home/odrevet/projects/gbdk/include/gb/gb.h:2001: shadow_OAM[nb].y = 0;
	xor	a, a
	ld	l, e
	ld	h, a
	add	hl, hl
	add	hl, hl
	ld	de, #_shadow_OAM
	add	hl, de
	ld	(hl), #0x00
;src/coin_animated.c:14: coin_animated_array[coin_index].hw_sprite_index = COIN_HW_SPRITE_BASE + coin_index;
	ld	a, (_coin_index)
	ld	h, #0x00
	ld	l, a
	add	hl, hl
	add	hl, hl
	add	hl, bc
	inc	hl
	inc	hl
	inc	hl
	ld	a, (_coin_index)
	add	a, #0x0a
	ld	(hl), a
;src/coin_animated.c:15: coin_index = (coin_index + 1) % NB_COIN_ANIMATED;
	ld	a, (_coin_index)
	ld	d, #0x00
	ld	e, a
	inc	de
	ld	bc, #0x0003
	call	__modsint
	ld	hl, #_coin_index
	ld	(hl), c
;src/coin_animated.c:16: }
	ret
;src/coin_animated.c:18: void coin_animated_update(void) {
;	---------------------------------
; Function coin_animated_update
; ---------------------------------
_coin_animated_update::
	dec	sp
;src/coin_animated.c:21: for (i = 0; i < NB_COIN_ANIMATED; i++) {
	ldhl	sp,	#0
	ld	(hl), #0x00
00107$:
;src/coin_animated.c:22: if (coin_animated_array[i].ttl > 0) {
	ldhl	sp,	#0
	ld	c, (hl)
	ld	b, #0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	ld	de, #_coin_animated_array
	add	hl, de
	ld	e, l
	ld	d, h
	inc	de
	inc	de
	ld	a, (de)
	or	a, a
	jr	Z, 00108$
;src/coin_animated.c:23: coin_animated_array[i].ttl--;
	dec	a
	ld	(de), a
;src/coin_animated.c:24: coin_animated_array[i].draw_y--;
	ld	c, l
	ld	b, h
	inc	bc
	ld	a, (bc)
	dec	a
	ld	(bc), a
;src/coin_animated.c:25: if (coin_animated_array[i].ttl == 0) {
	ld	a, (de)
	or	a, a
	jr	NZ, 00108$
;src/coin_animated.c:26: hide_sprite(coin_animated_array[i].hw_sprite_index);
	inc	hl
	inc	hl
	inc	hl
;/home/odrevet/projects/gbdk/include/gb/gb.h:2001: shadow_OAM[nb].y = 0;
	ld	l, (hl)
	xor	a, a
	ld	h, a
	add	hl, hl
	add	hl, hl
	ld	de, #_shadow_OAM
	add	hl, de
	ld	(hl), #0x00
;src/coin_animated.c:26: hide_sprite(coin_animated_array[i].hw_sprite_index);
00108$:
;src/coin_animated.c:21: for (i = 0; i < NB_COIN_ANIMATED; i++) {
	ldhl	sp,	#0
	inc	(hl)
	ld	a, (hl)
	sub	a, #0x03
	jr	C, 00107$
;src/coin_animated.c:30: }
	inc	sp
	ret
;src/coin_animated.c:32: uint8_t coin_animated_draw(uint8_t base_sprite) {
;	---------------------------------
; Function coin_animated_draw
; ---------------------------------
_coin_animated_draw::
	add	sp, #-11
	ldhl	sp,	#9
	ld	(hl), a
;src/coin_animated.c:33: uint8_t _saved_bank = _current_bank;
	ldh	a, (__current_bank + 0)
	ldhl	sp,	#2
	ld	(hl), a
;src/coin_animated.c:34: SWITCH_ROM(BANK(commonSprites));
	ld	a, #<(___bank_commonSprites)
	ldh	(__current_bank + 0), a
	ld	(#_rROMB0),a
;src/coin_animated.c:38: for (i = 0; i < NB_COIN_ANIMATED; i++) {
	ldhl	sp,	#10
	ld	(hl), #0x00
00105$:
;src/coin_animated.c:39: if (coin_animated_array[i].ttl > 0) {
	ldhl	sp,	#10
	ld	c, (hl)
	ld	b, #0x00
	sla	c
	rl	b
	sla	c
	rl	b
	ld	hl, #_coin_animated_array
	add	hl, bc
	inc	sp
	inc	sp
	ld	c, l
	ld	b, h
	push	bc
	inc	bc
	inc	bc
	ld	a, (bc)
	ldhl	sp,	#8
	ld	(hl), a
	ld	a, (hl)
	or	a, a
	jp	Z, 00106$
;src/coin_animated.c:40: uint8_t draw_index = 3 + ((20 - coin_animated_array[i].ttl) % 3) * 5;
	ld	c, (hl)
	ld	b, #0x00
	ld	a, #0x14
	sub	a, c
	ld	e, a
	sbc	a, a
	sub	a, b
	ld	bc, #0x0003
	ld	d, a
	call	__modsint
	ld	a, c
	add	a, a
	add	a, a
	add	a, c
	add	a, #0x03
;src/coin_animated.c:42: metasprite_t *commonSprites_metasprite =
	ld	h, #0x00
	ld	l, a
	add	hl, hl
	ld	de, #_commonSprites_metasprites
	add	hl, de
	ld	e, l
	ld	d, h
	ld	a, (de)
	ldhl	sp,	#3
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
;src/coin_animated.c:48: coin_animated_array[i].draw_y + 32);
	pop	de
	push	de
	ld	l, e
	ld	h, d
	inc	hl
	push	hl
	ld	a, l
	ldhl	sp,	#9
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#8
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	(hl), a
	ld	a, (hl)
	add	a, #0x20
	ldhl	sp,	#5
	ld	(hl), a
;src/coin_animated.c:47: coin_animated_array[i].draw_x + 12 - camera_x,
	pop	de
	push	de
	ld	a, (de)
	add	a, #0x0c
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	ldhl	sp,	#6
	ld	(hl), a
;src/coin_animated.c:46: commonSprites_metasprite, commonSprites_TILE_ORIGIN, 0, coin_animated_array[i].hw_sprite_index,
	pop	de
	push	de
	ld	hl, #0x0003
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#9
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#8
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	(hl), a
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:160: __current_metasprite = metasprite;
	ldhl	sp,	#3
	ld	a, (hl)
	ld	(#___current_metasprite),a
	ldhl	sp,	#4
	ld	a, (hl)
	ld	(#___current_metasprite + 1),a
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:161: __current_base_tile = base_tile;
	ld	hl, #___current_base_tile
	ld	(hl), #0x3c
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:162: __current_base_prop = base_prop;
	xor	a, a
	ld	(#___current_base_prop),a
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:163: return __move_metasprite(base_sprite, (y << 8) | (uint8_t)x);
	ldhl	sp,	#5
	ld	a, (hl-)
	ld	(hl+), a
	xor	a, a
	ld	(hl-), a
	ld	a, (hl+)
	ld	(hl-), a
	xor	a, a
	ld	(hl+), a
	inc	hl
	ld	a, (hl)
	ldhl	sp,	#0
	ld	(hl+), a
	xor	a, a
	ld	(hl-), a
	ld	a, (hl)
	ldhl	sp,	#6
	ld	(hl-), a
	ld	a, (hl+)
	inc	hl
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	a, (hl+)
	ld	d, a
	ld	a, (hl)
	call	___move_metasprite
;src/coin_animated.c:48: coin_animated_array[i].draw_y + 32);
	ldhl	sp,	#9
	add	a, (hl)
	ld	(hl), a
00106$:
;src/coin_animated.c:38: for (i = 0; i < NB_COIN_ANIMATED; i++) {
	ldhl	sp,	#10
	inc	(hl)
	ld	a, (hl)
	sub	a, #0x03
	jp	C, 00105$
;src/coin_animated.c:52: SWITCH_ROM(_saved_bank);
	ldhl	sp,	#2
	ld	a, (hl)
	ldh	(__current_bank + 0), a
	ld	a, (hl)
	ld	(#_rROMB0),a
;src/coin_animated.c:54: return base_sprite;
	ldhl	sp,	#9
	ld	a, (hl)
;src/coin_animated.c:55: }
	add	sp, #11
	ret
	.area _CODE
	.area _INITIALIZER
__xinit__coin_index:
	.db #0x00	; 0
	.area _CABS (ABS)
