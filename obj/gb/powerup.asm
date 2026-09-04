;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler
; Version 4.5.1 #15267 (Linux)
;--------------------------------------------------------
	.module powerup
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _powerup_active
	.globl _powerup
	.globl _powerup_new
	.globl _powerup_update
	.globl _powerup_draw
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area _HRAM
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_powerup::
	.ds 10
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
_powerup_active::
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
;src/powerup.c:9: void powerup_new(uint16_t x, uint16_t y, uint8_t type) {
;	---------------------------------
; Function powerup_new
; ---------------------------------
_powerup_new::
	push	de
;src/powerup.c:10: powerup.x = x;
	ld	de, #_powerup
	ldhl	sp,	#0
	ld	a, (hl+)
	ld	(de), a
	inc	de
	ld	a, (hl)
	ld	(de), a
;src/powerup.c:11: powerup.y = y;
	ld	hl, #(_powerup + 2)
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
;src/powerup.c:13: powerup.type = type;
	ld	de, #(_powerup + 8)
	ldhl	sp,	#4
	ld	a, (hl)
	ld	(de), a
;src/powerup.c:15: switch (powerup.type) {
	ld	c, (hl)
;src/powerup.c:17: powerup.current_frame = 0;
	ld	hl, #_powerup + 9
;src/powerup.c:15: switch (powerup.type) {
	ld	a, c
	or	a, a
	jr	Z, 00101$
	dec	c
	jr	Z, 00102$
	jr	00103$
;src/powerup.c:16: case POWERUP_MUSHROOM:
00101$:
;src/powerup.c:17: powerup.current_frame = 0;
	ld	(hl), #0x00
;src/powerup.c:19: break;
	jr	00103$
;src/powerup.c:20: case POWERUP_STAR:
00102$:
;src/powerup.c:21: powerup.current_frame = 5;
	ld	(hl), #0x05
;src/powerup.c:24: }
00103$:
;src/powerup.c:26: powerup_active = TRUE;
	ld	hl, #_powerup_active
	ld	(hl), #0x01
;src/powerup.c:27: }
	inc	sp
	inc	sp
	pop	hl
	inc	sp
	jp	(hl)
;src/powerup.c:29: void powerup_update(void) {
;	---------------------------------
; Function powerup_update
; ---------------------------------
_powerup_update::
;src/powerup.c:30: powerup.draw_x =
;src/powerup.c:31: ((powerup.x - camera_x_upscaled) >> 4) + DEVICE_SPRITE_PX_OFFSET_X + 4;
	ld	hl, #_powerup
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	ld	a, c
	ld	hl, #_camera_x_upscaled
	sub	a, (hl)
	inc	hl
	ld	c, a
	ld	a, b
	sbc	a, (hl)
	ld	b, a
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	ld	a, c
	add	a, #0x0c
	ld	(#(_powerup + 4)),a
;src/powerup.c:32: powerup.draw_y = (powerup.y >> 4) + DEVICE_SPRITE_PX_OFFSET_Y + TILE_SIZE + 4;
	ld	hl, #(_powerup + 2)
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	ld	a, c
	add	a, #0x1c
	ld	(#(_powerup + 5)),a
;src/powerup.c:34: if (powerup.draw_x >= DEVICE_SCREEN_PX_WIDTH + 8 * TILE_SIZE &&
	ld	a, (#(_powerup + 4) + 0)
	sub	a, #0xe0
	ret	C
;src/powerup.c:36: powerup_active = FALSE;
	xor	a, a
	ld	(#_powerup_active),a
;src/powerup.c:38: }
	ret
;src/powerup.c:40: uint8_t powerup_draw(uint8_t base_sprite) {
;	---------------------------------
; Function powerup_draw
; ---------------------------------
_powerup_draw::
	dec	sp
	dec	sp
	ldhl	sp,	#0
;src/powerup.c:41: uint8_t _saved_bank = _current_bank;
	ld	(hl+), a
	ldh	a, (__current_bank + 0)
	ld	(hl), a
;src/powerup.c:42: SWITCH_ROM(BANK(commonSprites));
	ld	a, #<(___bank_commonSprites)
	ldh	(__current_bank + 0), a
	ld	(#_rROMB0),a
;src/powerup.c:46: metasprite_t *commonSprites_metasprite =
	ld	bc, #_commonSprites_metasprites+0
	ld	hl, #_powerup + 9
	ld	l, (hl)
	ld	h, #0x00
	add	hl, hl
	add	hl, bc
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
;src/powerup.c:54: base_sprite, powerup.draw_x, powerup.draw_y);
	ld	hl, #_powerup + 5
	ld	e, (hl)
	ld	hl, #_powerup + 4
	ld	l, (hl)
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:160: __current_metasprite = metasprite;
	ld	a, c
	ld	(___current_metasprite), a
	ld	a, b
	ld	(___current_metasprite + 1), a
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:161: __current_base_tile = base_tile;
	ld	a, #0x3c
	ld	(___current_base_tile), a
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:162: __current_base_prop = base_prop;
	xor	a, a
	ld	(___current_base_prop), a
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:163: return __move_metasprite(base_sprite, (y << 8) | (uint8_t)x);
	ld	d, e
	ld	e, l
	ldhl	sp,	#0
	ld	a, (hl)
	call	___move_metasprite
;src/powerup.c:54: base_sprite, powerup.draw_x, powerup.draw_y);
	ldhl	sp,	#0
	add	a, (hl)
;src/powerup.c:56: SWITCH_ROM(_saved_bank);
	inc	hl
	ld	c, a
	ld	a, (hl)
	ldh	(__current_bank + 0), a
	ld	a, (hl)
	ld	(#_rROMB0),a
;src/powerup.c:58: return base_sprite;
	ld	a, c
;src/powerup.c:59: }
	inc	sp
	inc	sp
	ret
	.area _CODE
	.area _INITIALIZER
__xinit__powerup_active:
	.db #0x00	;  0
	.area _CABS (ABS)
