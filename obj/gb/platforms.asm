;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler
; Version 4.5.1 #15267 (Linux)
;--------------------------------------------------------
	.module platforms
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _hide_sprites_range
	.globl _platform_moving_count
	.globl _platforms_moving
	.globl _platform_moving_new
	.globl _platform_moving_update
	.globl _platform_moving_draw
	.globl _platform_falling_new
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area _HRAM
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_platforms_moving::
	.ds 42
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
_platform_moving_count::
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
;src/platforms.c:8: void platform_moving_new(uint16_t x, uint16_t y,
;	---------------------------------
; Function platform_moving_new
; ---------------------------------
_platform_moving_new::
	add	sp, #-20
	ldhl	sp,	#18
	ld	a, e
	ld	(hl+), a
	ld	(hl), d
	ldhl	sp,	#16
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
;src/platforms.c:12: if (platform_moving_count < PLATFORM_MOVING_MAX) {
	ld	a, (#_platform_moving_count)
	sub	a, #0x03
	jp	NC, 00103$
;src/platforms.c:13: platform_moving_t platform_moving = {
	ldhl	sp,	#0
	ld	c, l
	ld	b, h
	ldhl	sp,	#18
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	sla	e
	rl	d
	sla	e
	rl	d
	sla	e
	rl	d
	sla	e
	rl	d
	ld	l, c
	ld	h, b
	ld	a, e
	ld	(hl+), a
	ld	(hl), d
	ldhl	sp,	#16
	ld	a, (hl-)
	dec	hl
	ld	(hl), a
	ldhl	sp,	#17
	ld	a, (hl-)
	dec	hl
	ld	(hl), a
	ld	a, #0x04
00140$:
	ldhl	sp,	#14
	sla	(hl)
	inc	hl
	rl	(hl)
	dec	a
	jr	NZ, 00140$
	dec	hl
	ld	a, (hl)
	ldhl	sp,	#2
	ld	(hl), a
	ldhl	sp,	#15
	ld	a, (hl)
	ldhl	sp,	#3
	ld	(hl), a
	ldhl	sp,	#22
	ld	a, (hl)
	ldhl	sp,	#8
	ld	(hl), a
	ldhl	sp,	#23
	ld	e, (hl)
	xor	a, a
	ld	l, e
	ld	h, a
	add	hl, hl
	add	hl, hl
	add	hl, hl
	push	hl
	ld	a, l
	ldhl	sp,	#11
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#10
	ld	(hl), a
	ldhl	sp,	#24
	ld	a, (hl)
	or	a, a
	jr	NZ, 00105$
	ld	a, #0x03
	jr	00106$
00105$:
	ldhl	sp,	#24
	ld	a, (hl)
00106$:
	add	a, a
	add	a, a
	add	a, a
	ldhl	sp,	#13
	ld	(hl), a
	ldhl	sp,	#22
	ld	a, (hl)
	dec	a
	ld	a, #0x08
	jr	Z, 00108$
	xor	a, a
00108$:
	ldhl	sp,	#6
	ld	(hl), a
	ldhl	sp,	#22
	ld	a, (hl)
	or	a, a
	ld	a, #0x08
	jr	Z, 00110$
	xor	a, a
00110$:
	ldhl	sp,	#7
	ld	(hl), a
	ldhl	sp,	#4
	xor	a, a
	ld	(hl+), a
	ld	(hl), a
	xor	a, a
	ldhl	sp,	#11
	ld	(hl+), a
	ld	(hl), a
;src/platforms.c:22: platforms_moving[platform_moving_count] = platform_moving;
	ld	hl, #_platform_moving_count
	ld	c, (hl)
	ld	b, #0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	add	hl, hl
	ld	bc, #_platforms_moving
	add	hl, bc
	ld	e, l
	ld	d, h
	ld	bc, #0x000e
	push	bc
	ld	hl, #2
	add	hl, sp
	ld	c, l
	ld	b, h
	call	___memcpy
;src/platforms.c:23: platform_moving_count++;
	ld	hl, #_platform_moving_count
	inc	(hl)
00103$:
;src/platforms.c:25: }
	add	sp, #20
	pop	hl
	add	sp, #3
	jp	(hl)
;src/platforms.c:27: void platform_moving_update() {
;	---------------------------------
; Function platform_moving_update
; ---------------------------------
_platform_moving_update::
	add	sp, #-19
;src/platforms.c:29: while (index_platform_moving < platform_moving_count) {
	ldhl	sp,	#18
	ld	(hl), #0x00
00106$:
	ldhl	sp,	#18
	ld	a, (hl)
	ld	hl, #_platform_moving_count
	sub	a, (hl)
	jp	NC, 00112$
;src/platforms.c:30: platforms_moving[index_platform_moving].x +=
	ldhl	sp,	#18
	ld	c, (hl)
	ld	b, #0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	add	hl, hl
	inc	sp
	inc	sp
	ld	e, l
	ld	d, h
	push	de
	ld	hl, #_platforms_moving
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#4
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#3
	ld	(hl-), a
	ld	a, (hl+)
	inc	hl
	ld	(hl-), a
	ld	a, (hl+)
	inc	hl
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ldhl	sp,	#14
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
;src/platforms.c:31: platforms_moving[index_platform_moving].vel_x;
	ldhl	sp,#2
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0006
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#8
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#7
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ldhl	sp,	#16
	ld	(hl+), a
	rlca
	sbc	a, a
	ld	(hl), a
	ldhl	sp,	#14
	ld	a, (hl-)
	dec	hl
	ld	(hl), a
	ldhl	sp,	#15
	ld	a, (hl-)
	dec	hl
	ld	(hl), a
	ldhl	sp,	#16
	ld	a, (hl-)
	dec	hl
	ld	(hl), a
	ldhl	sp,	#17
	ld	a, (hl-)
	dec	hl
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ldhl	sp,	#12
	ld	a,	(hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#18
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#17
	ld	(hl-), a
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
;src/platforms.c:32: platforms_moving[index_platform_moving].y +=
	ldhl	sp,#2
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0002
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#10
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#9
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	c, a
	inc	de
	ld	a, (de)
	ld	b, a
;src/platforms.c:33: platforms_moving[index_platform_moving].vel_y;
	ldhl	sp,#2
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0007
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#12
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#11
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ldhl	sp,	#16
	ld	(hl+), a
	rlca
	sbc	a, a
	ld	(hl), a
	ldhl	sp,	#12
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
	ldhl	sp,	#16
	ld	a, (hl-)
	dec	hl
	ld	(hl), a
	ldhl	sp,	#17
	ld	a, (hl-)
	dec	hl
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ldhl	sp,	#12
	ld	a,	(hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#18
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#17
	ld	(hl-), a
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	ldhl	sp,	#8
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
;src/platforms.c:35: platforms_moving[index_platform_moving].draw_x =
	ldhl	sp,#2
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0004
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#18
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#17
	ld	(hl), a
;src/platforms.c:36: (platforms_moving[index_platform_moving].x - camera_x_upscaled) >> 4;
	ldhl	sp,#4
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	c, a
	inc	de
	ld	a, (de)
	ld	b, a
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
	ldhl	sp,	#16
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
;src/platforms.c:37: platforms_moving[index_platform_moving].draw_y =
	ldhl	sp,#2
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0005
	add	hl, de
	ld	c, l
	ld	b, h
;src/platforms.c:38: platforms_moving[index_platform_moving].y >> 4;
	ldhl	sp,#8
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	l, a
	inc	de
	ld	a, (de)
	ld	h, a
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	a, h
	ld	(bc), a
;src/platforms.c:40: platforms_moving[index_platform_moving].range_current++;
	ldhl	sp,#2
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x000b
	add	hl, de
	ld	c,l
	ld	b,h
	ld	a,	(hl+)
	ld	h, (hl)
	ld	e, a
	ld	d, h
	inc	de
	ld	l, c
	ld	h, b
	ld	a, e
	ld	(hl+), a
	ld	(hl), d
;src/platforms.c:41: if (platforms_moving[index_platform_moving].range_current >=
	ld	a, e
	sub	a, #0x70
	ld	a, d
	sbc	a, #0x00
	jr	C, 00102$
;src/platforms.c:44: -platforms_moving[index_platform_moving].vel_x;
	ldhl	sp,#6
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	l, a
	xor	a, a
	sub	a, l
	ldhl	sp,	#17
	ld	(hl), a
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ldhl	sp,	#17
	ld	a, (hl)
	ld	(de), a
;src/platforms.c:46: -platforms_moving[index_platform_moving].vel_y;
	ldhl	sp,#10
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	l, a
	xor	a, a
	sub	a, l
	ldhl	sp,	#17
	ld	(hl), a
	ldhl	sp,	#10
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ldhl	sp,	#17
	ld	a, (hl)
	ld	(de), a
;src/platforms.c:48: platforms_moving[index_platform_moving].range_current = 0;
	xor	a, a
	ld	(bc), a
	inc	bc
	ld	(bc), a
00102$:
;src/platforms.c:51: if (platforms_moving[index_platform_moving].x <=
	pop	de
	push	de
	ld	hl, #_platforms_moving
	add	hl, de
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
;src/platforms.c:52: camera_x_upscaled - DEVICE_SCREEN_PX_WIDTH) {
	ld	a, (_camera_x_upscaled)
	ld	hl, #_camera_x_upscaled + 1
	ld	e, (hl)
	add	a, #0x60
	ld	l, a
	ld	a, e
	adc	a, #0xff
	ld	h, a
	ld	a, l
	sub	a, c
	ld	a, h
	sbc	a, b
	jr	C, 00105$
;src/platforms.c:54: for (uint8_t j = index_platform_moving; j < platform_moving_count - 1;
	ldhl	sp,	#18
	ld	a, (hl-)
	ld	(hl), a
00110$:
	ld	a, (_platform_moving_count)
	ld	b, #0x00
	ld	c, a
	dec	bc
	ldhl	sp,	#17
	ld	a, (hl-)
	dec	hl
	ld	(hl+), a
	xor	a, a
	ld	(hl-), a
	ld	a, (hl+)
	sub	a, c
	ld	a, (hl)
	sbc	a, b
	ld	d, (hl)
	ld	a, b
	bit	7,a
	jr	Z, 00158$
	bit	7, d
	jr	NZ, 00159$
	cp	a, a
	jr	00159$
00158$:
	bit	7, d
	jr	Z, 00159$
	scf
00159$:
	jr	NC, 00103$
;src/platforms.c:56: platforms_moving[j] = platforms_moving[j + 1];
	ldhl	sp,	#17
	ld	a, (hl-)
	ld	(hl), a
	inc	(hl)
	ld	c, (hl)
	ld	a, c
	rlca
	sbc	a, a
	ld	b, a
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	add	hl, hl
	push	hl
	ld	a, l
	ldhl	sp,	#17
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#16
	ld	(hl), a
	ld	de, #_platforms_moving
	ld	a, (hl-)
	ld	l, (hl)
	ld	h, a
	add	hl, de
	ld	c, l
	ld	b, h
	ldhl	sp,	#17
	ld	e, (hl)
	ld	d, #0x00
	ld	l, e
	ld	h, d
	add	hl, hl
	add	hl, de
	add	hl, hl
	add	hl, de
	add	hl, hl
	ld	de, #_platforms_moving
	add	hl, de
	ld	e, l
	ld	d, h
	ld	hl, #0x000e
	push	hl
	call	___memcpy
;src/platforms.c:55: j++) {
	ldhl	sp,	#17
	inc	(hl)
	jr	00110$
00103$:
;src/platforms.c:58: platform_moving_count--;
	ld	hl, #_platform_moving_count
	dec	(hl)
;src/platforms.c:59: hide_sprites_range(1, MAX_HARDWARE_SPRITES);
	ld	e, #0x28
	ld	a, #0x01
	call	_hide_sprites_range
;src/platforms.c:60: continue;
	jp	00106$
00105$:
;src/platforms.c:63: index_platform_moving++;
	ldhl	sp,	#18
	inc	(hl)
	jp	00106$
00112$:
;src/platforms.c:65: }
	add	sp, #19
	ret
;src/platforms.c:67: uint8_t platform_moving_draw(uint8_t base_sprite) {
;	---------------------------------
; Function platform_moving_draw
; ---------------------------------
_platform_moving_draw::
;src/platforms.c:89: return 0;
	xor	a, a
;src/platforms.c:90: }
	ret
;src/platforms.c:92: void platform_falling_new(uint16_t x, uint16_t y) {}
;	---------------------------------
; Function platform_falling_new
; ---------------------------------
_platform_falling_new::
	ret
	.area _CODE
	.area _INITIALIZER
__xinit__platform_moving_count:
	.db #0x00	; 0
	.area _CABS (ABS)
