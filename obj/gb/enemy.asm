;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler
; Version 4.5.1 #15267 (Linux)
;--------------------------------------------------------
	.module enemy
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl b_enemy_apply_vertical_movement
	.globl _enemy_apply_vertical_movement
	.globl b_enemy_apply_horizontal_movement
	.globl _enemy_apply_horizontal_movement
	.globl b_enemy_has_ground_ahead
	.globl _enemy_has_ground_ahead
	.globl b_enemy_has_ground
	.globl _enemy_has_ground
	.globl b___func_enemy
	.globl ___func_enemy
	.globl _is_tile_solid
	.globl _get_tile
	.globl _hide_sprites_range
	.globl _enemy_count
	.globl _enemies
	.globl _enemy_new
	.globl b_enemy_move_goomba
	.globl _enemy_move_goomba
	.globl b_enemy_move_koopa
	.globl _enemy_move_koopa
	.globl b_enemy_move_fly
	.globl _enemy_move_fly
	.globl b_enemy_stomp
	.globl _enemy_stomp
	.globl _enemy_remove
	.globl b_enemy_reset_all
	.globl _enemy_reset_all
	.globl b_enemy_update
	.globl _enemy_update
	.globl _enemy_draw
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area _HRAM
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_enemies::
	.ds 64
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
_enemy_count::
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
;src/enemy.c:146: void enemy_new(uint16_t x, uint16_t y, uint8_t type) NONBANKED {
;	---------------------------------
; Function enemy_new
; ---------------------------------
_enemy_new::
	add	sp, #-11
	ldhl	sp,	#9
	ld	a, e
	ld	(hl+), a
	ld	(hl), d
	ldhl	sp,	#7
	ld	a, c
	ld	(hl+), a
;src/enemy.c:150: for (uint8_t i = 0; i < ENEMY_MAX; i++) {
	ld	a, b
	ld	(hl-), a
	dec	hl
	xor	a, a
	ld	(hl-), a
	ld	(hl), a
00109$:
	ldhl	sp,	#5
	ld	a, (hl)
	sub	a, #0x04
	jp	NC, 00111$
;src/enemy.c:151: if (!enemies[i].active) {
	ld	c, (hl)
	xor	a, a
	ld	l, c
	ld	h, a
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	de, #_enemies
	add	hl, de
	ld	bc, #0x000f
	add	hl, bc
	ld	c, (hl)
	bit	0, c
	jp	NZ, 00110$
;src/enemy.c:155: switch (type) {
	ldhl	sp,	#13
	ld	a, (hl)
	or	a, a
	ld	a, #0x01
	jr	Z, 00156$
	xor	a, a
00156$:
	ld	c, a
	ldhl	sp,	#0
	ld	(hl), #0x00
;src/enemy.c:159: y -= 8;
	ldhl	sp,	#7
	ld	a, (hl+)
	ld	b, (hl)
	add	a, #0xf8
	ld	e, a
	ld	a, b
	adc	a, #0xff
	ld	b, a
;src/enemy.c:155: switch (type) {
	ld	a, c
	or	a, a
	jr	NZ, 00101$
	ldhl	sp,	#13
	ld	a, (hl)
	dec	a
	jr	Z, 00102$
	ldhl	sp,	#13
	ld	a, (hl)
	sub	a, #0x02
	jr	Z, 00103$
	jr	00104$
;src/enemy.c:156: case ENEMY_GOOMBO:
00101$:
;src/enemy.c:157: current_frame = 0;
	ldhl	sp,	#0
	ld	(hl), #0x00
;src/enemy.c:159: y -= 8;
	ldhl	sp,	#7
	ld	a, e
	ld	(hl+), a
	ld	(hl), b
;src/enemy.c:160: break;
	jr	00104$
;src/enemy.c:161: case ENEMY_KOOPA:
00102$:
;src/enemy.c:162: current_frame = 1;
	ldhl	sp,	#0
	ld	(hl), #0x01
;src/enemy.c:164: y -= 8;
	ldhl	sp,	#7
	ld	a, e
	ld	(hl+), a
	ld	(hl), b
;src/enemy.c:165: break;
	jr	00104$
;src/enemy.c:166: case ENEMY_FLY:
00103$:
;src/enemy.c:167: current_frame = 0;
	ldhl	sp,	#0
	ld	(hl), #0x00
;src/enemy.c:169: y -= 8;
	ldhl	sp,	#7
	ld	a, e
	ld	(hl+), a
	ld	(hl), b
;src/enemy.c:171: }
00104$:
;src/enemy.c:173: enemies[i].x = x << 4;
	ldhl	sp,	#6
	ld	a, (hl-)
	ld	(hl+), a
	ld	(hl), #0x00
	ld	a, #0x04
00159$:
	ldhl	sp,	#5
	sla	(hl)
	inc	hl
	rl	(hl)
	dec	a
	jr	NZ, 00159$
	dec	hl
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #_enemies
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#3
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#2
	ld	(hl), a
	ldhl	sp,	#9
	ld	a, (hl)
	ldhl	sp,	#5
	ld	(hl), a
	ldhl	sp,	#10
	ld	a, (hl)
	ldhl	sp,	#6
	ld	(hl), a
	ld	a, #0x04
00160$:
	ldhl	sp,	#5
	sla	(hl)
	inc	hl
	rl	(hl)
	dec	a
	jr	NZ, 00160$
	ldhl	sp,	#1
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ldhl	sp,	#5
	ld	a, (hl+)
	ld	(de), a
	inc	de
	ld	a, (hl)
	ld	(de), a
;src/enemy.c:174: enemies[i].y = y << 4;
	ldhl	sp,#1
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0002
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#5
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#4
	ld	(hl), a
	ldhl	sp,	#7
	ld	a, (hl-)
	dec	hl
	ld	(hl), a
	ldhl	sp,	#8
	ld	a, (hl-)
	dec	hl
	ld	(hl), a
	ld	a, #0x04
00161$:
	ldhl	sp,	#5
	sla	(hl)
	inc	hl
	rl	(hl)
	dec	a
	jr	NZ, 00161$
	ldhl	sp,	#3
	ld	a, (hl+)
	ld	e, a
	ld	a, (hl+)
	ld	d, a
	ld	a, (hl+)
	ld	(de), a
	inc	de
	ld	a, (hl)
	ld	(de), a
;src/enemy.c:175: enemies[i].vel_x = vel_x;
	ldhl	sp,#1
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0006
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#7
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#6
	ld	(hl-), a
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x00
;src/enemy.c:176: enemies[i].vel_y = 0;
	ldhl	sp,#1
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0007
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#7
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#6
	ld	(hl-), a
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x00
;src/enemy.c:177: enemies[i].type = type;
	ldhl	sp,#1
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0008
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#7
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#6
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ldhl	sp,	#13
	ld	a, (hl)
	ld	(de), a
;src/enemy.c:178: enemies[i].frame_counter = 0;
	ldhl	sp,#1
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0009
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#7
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#6
	ld	(hl-), a
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x00
;src/enemy.c:179: enemies[i].current_frame = current_frame;
	ldhl	sp,#1
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x000a
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#7
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#6
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ldhl	sp,	#0
;src/enemy.c:180: enemies[i].flip = FALSE;
	ld	a, (hl+)
	ld	(de), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x000c
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#7
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#6
	ld	(hl-), a
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x00
;src/enemy.c:181: enemies[i].stomped = FALSE;
	ldhl	sp,#1
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x000d
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#7
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#6
	ld	(hl-), a
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x00
;src/enemy.c:182: enemies[i].stomped_timer = 0;
	ldhl	sp,#1
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x000e
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#7
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#6
	ld	(hl-), a
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x00
;src/enemy.c:183: enemies[i].active = TRUE;
	ldhl	sp,#1
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x000f
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#7
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#6
	ld	(hl-), a
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x01
;src/enemy.c:185: enemy_count++;
	ld	hl, #_enemy_count
	inc	(hl)
;src/enemy.c:186: return;
	jr	00111$
00110$:
;src/enemy.c:150: for (uint8_t i = 0; i < ENEMY_MAX; i++) {
	ldhl	sp,	#5
	inc	(hl)
	ld	a, (hl+)
	ld	(hl), a
	jp	00109$
00111$:
;src/enemy.c:189: }
	add	sp, #11
	pop	hl
	inc	sp
	jp	(hl)
;src/enemy.c:295: void enemy_remove(uint8_t index_enemy) NONBANKED {
;	---------------------------------
; Function enemy_remove
; ---------------------------------
_enemy_remove::
;src/enemy.c:298: if (index_enemy < ENEMY_MAX && enemies[index_enemy].active) {
	ld	c, a
	sub	a, #0x04
	ret	NC
	ld	de, #_enemies+0
	xor	a, a
	ld	l, c
	ld	h, a
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, de
	ld	bc, #0x000f
	add	hl, bc
	bit	0, (hl)
	ret	Z
;src/enemy.c:299: enemies[index_enemy].active = FALSE;
	ld	(hl), #0x00
;src/enemy.c:300: enemy_count--;
	ld	hl, #_enemy_count
	dec	(hl)
;src/enemy.c:301: hide_sprites_range(1, MAX_HARDWARE_SPRITES);
	ld	e, #0x28
	ld	a, #0x01
;src/enemy.c:303: }
	jp	_hide_sprites_range
;src/enemy.c:390: uint8_t enemy_draw(uint8_t base_sprite) NONBANKED {
;	---------------------------------
; Function enemy_draw
; ---------------------------------
_enemy_draw::
	add	sp, #-8
	ldhl	sp,	#6
;src/enemy.c:393: for (uint8_t index_enemy = 0; index_enemy < ENEMY_MAX; index_enemy++) {
	ld	(hl+), a
	ld	(hl), #0x00
00114$:
	ldhl	sp,	#7
	ld	a, (hl)
	sub	a, #0x04
	jp	NC, 00110$
;src/enemy.c:395: if (!enemies[index_enemy].active) {
	ld	a, (hl)
	ldhl	sp,	#4
	ld	(hl+), a
	xor	a, a
	ld	(hl-), a
	ld	a, (hl)
	ldhl	sp,	#1
	ld	(hl+), a
	ld	(hl), #0x00
	ld	a, #0x04
00153$:
	ldhl	sp,	#1
	sla	(hl)
	inc	hl
	rl	(hl)
	dec	a
	jr	NZ, 00153$
	dec	hl
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #_enemies
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#5
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#4
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x000f
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	bit	0,a
	jp	Z, 00109$
;src/enemy.c:399: uint8_t draw_index = enemies[index_enemy].current_frame;
	ldhl	sp,#3
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x000a
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	ldhl	sp,	#5
	ld	(hl), a
;src/enemy.c:405: uint8_t _saved_bank = _current_bank;
	ldh	a, (__current_bank + 0)
	ldhl	sp,	#0
	ld	(hl), a
;src/enemy.c:409: if (enemies[index_enemy].type == ENEMY_FLY) {
	ldhl	sp,#3
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0008
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	sub	a, #0x02
	jr	NZ, 00104$
;src/enemy.c:410: SWITCH_ROM(BANK(enemiesBirabutoSprites));
	ld	a, #<(___bank_enemiesBirabutoSprites)
	ldh	(__current_bank + 0), a
	ld	(#_rROMB0),a
;src/enemy.c:411: metasprites = enemiesBirabutoSprites_metasprites;
	ld	bc, #_enemiesBirabutoSprites_metasprites
;src/enemy.c:412: tile_origin = enemiesBirabutoSprites_TILE_ORIGIN;
	ldhl	sp,	#1
	ld	(hl), #0x49
	jr	00105$
00104$:
;src/enemy.c:414: SWITCH_ROM(BANK(enemiesBirabutoSprites));
	ld	a, #<(___bank_enemiesBirabutoSprites)
	ldh	(__current_bank + 0), a
	ld	(#_rROMB0),a
;src/enemy.c:415: metasprites = enemiesSprites_metasprites;
	ld	bc, #_enemiesSprites_metasprites
;src/enemy.c:416: tile_origin = enemiesSprites_TILE_ORIGIN;
	ldhl	sp,	#1
	ld	(hl), #0x35
00105$:
;src/enemy.c:419: const metasprite_t *enemy_metasprite = metasprites[draw_index];
	ldhl	sp,	#5
	ld	e, (hl)
	ld	d, #0x00
	ld	l, e
	ld	h, d
	add	hl, hl
	add	hl, bc
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
;src/enemy.c:420: uint8_t draw_x = enemies[index_enemy].draw_x + DEVICE_SPRITE_PX_OFFSET_X + 4;
	ldhl	sp,	#7
	ld	e, (hl)
	xor	a, a
	ld	l, e
	ld	h, a
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	a, l
	add	a, #<(_enemies)
	ld	e, a
	ld	a, h
	adc	a, #>(_enemies)
	ld	d, a
	ld	hl, #0x0004
	add	hl, de
	ld	a, (hl)
	add	a, #0x0c
	ldhl	sp,	#2
	ld	(hl), a
;src/enemy.c:421: uint8_t draw_y = enemies[index_enemy].draw_y + DEVICE_SPRITE_PX_OFFSET_Y + enemiesSprites_HEIGHT + 8;
	ld	hl, #0x0005
	add	hl, de
	ld	a, (hl)
	add	a, #0x28
	ldhl	sp,	#3
	ld	(hl), a
;src/enemy.c:423: if (enemies[index_enemy].flip) {
	ld	hl, #0x000c
	add	hl, de
	ld	d, (hl)
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:200: __current_metasprite = metasprite;
	ldhl	sp,	#4
	ld	a, c
	ld	(hl+), a
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:203: return __move_metasprite_flipx(base_sprite, (y << 8) | (uint8_t)(x - 8u));
	ld	a, b
	ld	(hl-), a
	dec	hl
	ld	c, (hl)
;src/enemy.c:423: if (enemies[index_enemy].flip) {
	bit	0, d
	jr	Z, 00107$
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:200: __current_metasprite = metasprite;
	inc	hl
	ld	a, (hl)
	ld	(#___current_metasprite),a
	ldhl	sp,	#5
	ld	a, (hl)
	ld	(#___current_metasprite + 1),a
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:201: __current_base_tile = base_tile;
	ldhl	sp,	#1
	ld	a, (hl)
	ld	(#___current_base_tile),a
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:202: __current_base_prop = base_prop;
	xor	a, a
	ld	(#___current_base_prop),a
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:203: return __move_metasprite_flipx(base_sprite, (y << 8) | (uint8_t)(x - 8u));
	ldhl	sp,	#2
	ld	a, (hl)
	add	a, #0xf8
	ld	d, c
	ld	e, a
	ldhl	sp,	#6
	ld	a, (hl)
	call	___move_metasprite_flipx
;src/enemy.c:424: base_sprite += move_metasprite_flipx(enemy_metasprite, tile_origin, 0, base_sprite, draw_x, draw_y);
	ldhl	sp,	#6
	add	a, (hl)
	ld	(hl), a
	jr	00108$
00107$:
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:160: __current_metasprite = metasprite;
	ldhl	sp,	#4
	ld	a, (hl)
	ld	(#___current_metasprite),a
	ldhl	sp,	#5
	ld	a, (hl)
	ld	(#___current_metasprite + 1),a
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:161: __current_base_tile = base_tile;
	ldhl	sp,	#1
	ld	a, (hl)
	ld	(#___current_base_tile),a
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:162: __current_base_prop = base_prop;
	xor	a, a
	ld	(#___current_base_prop),a
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:163: return __move_metasprite(base_sprite, (y << 8) | (uint8_t)x);
	ldhl	sp,	#2
	ld	e, (hl)
	ld	d, c
	ldhl	sp,	#6
	ld	a, (hl)
	call	___move_metasprite
;src/enemy.c:426: base_sprite += move_metasprite_ex(enemy_metasprite, tile_origin, 0, base_sprite, draw_x, draw_y);
	ldhl	sp,	#6
	add	a, (hl)
	ld	(hl), a
00108$:
;src/enemy.c:429: SWITCH_ROM(_saved_bank);
	ldhl	sp,	#0
	ld	a, (hl)
	ldh	(__current_bank + 0), a
	ld	a, (hl)
	ld	(#_rROMB0),a
00109$:
;src/enemy.c:393: for (uint8_t index_enemy = 0; index_enemy < ENEMY_MAX; index_enemy++) {
	ldhl	sp,	#7
	inc	(hl)
	jp	00114$
00110$:
;src/enemy.c:433: return base_sprite;
	ldhl	sp,	#6
	ld	a, (hl)
;src/enemy.c:434: }
	add	sp, #8
	ret
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE_255
;src/enemy.c:11: BANKREF(enemy)
;	---------------------------------
; Function __func_enemy
; ---------------------------------
	b___func_enemy	= 255
___func_enemy::
	.local b___func_enemy 
	___bank_enemy = b___func_enemy 
	.globl ___bank_enemy 
;src/enemy.c:25: uint8_t enemy_has_ground(enemy_t *enemy) BANKED {
;	---------------------------------
; Function enemy_has_ground
; ---------------------------------
	b_enemy_has_ground	= 255
_enemy_has_ground::
;src/enemy.c:26: uint16_t ground_check_x = enemy->x >> 4;
	ldhl	sp,#6
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	c, a
	inc	de
	ld	a, (de)
	ld	b, a
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
;src/enemy.c:27: uint16_t ground_check_y = (enemy->y >> 4) + ENEMY_HEIGHT;
	ld	a, (hl-)
	ld	l, (hl)
	ld	h, a
	inc	hl
	inc	hl
	ld	a,	(hl+)
	ld	h, (hl)
	ld	l, a
	srl	h
	rr	l
	srl	h
	rr	l
	srl	h
	rr	l
	srl	h
	rr	l
	ld	a, l
	add	a, #0x10
	ld	e, a
;src/enemy.c:29: uint8_t tile_ground_left = get_tile(ground_check_x - camera_x, ground_check_y);
	ld	d, c
	ld	a, (_camera_x)
	ld	c, a
	ld	a, d
	sub	a, c
	push	de
	call	_get_tile
	ld	c, a
	pop	de
;src/enemy.c:30: uint8_t tile_ground_right = get_tile(ground_check_x + ENEMY_WIDTH - 1 - camera_x, ground_check_y);
	ld	a, d
	add	a, #0x07
	ld	hl, #_camera_x
	ld	b, (hl)
	sub	a, b
	push	bc
	call	_get_tile
	ld	e, a
	pop	bc
;src/enemy.c:32: return is_tile_solid(tile_ground_left) || is_tile_solid(tile_ground_right);
	push	de
	ld	a, c
	call	_is_tile_solid
	ld	c, a
	pop	de
	bit	0, c
	jr	NZ, 00104$
	ld	a, e
	call	_is_tile_solid
	bit	0,a
	jr	NZ, 00104$
	xor	a, a
	ret
00104$:
	ld	a, #0x01
;src/enemy.c:33: }
	ret
;src/enemy.c:36: uint8_t enemy_has_ground_ahead(enemy_t *enemy, int8_t vel_x) BANKED {
;	---------------------------------
; Function enemy_has_ground_ahead
; ---------------------------------
	b_enemy_has_ground_ahead	= 255
_enemy_has_ground_ahead::
	dec	sp
;src/enemy.c:37: uint16_t current_x = enemy->x >> 4;
	ldhl	sp,#7
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	c, a
	inc	de
	ld	a, (de)
	ld	b, a
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
;src/enemy.c:38: uint16_t current_y = enemy->y >> 4;
	ld	a, (hl-)
	ld	l, (hl)
	ld	h, a
	inc	hl
	inc	hl
	ld	a,	(hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
;src/enemy.c:42: uint8_t tile = get_tile(current_x + ENEMY_WIDTH - camera_x, current_y + ENEMY_HEIGHT);
	ld	a, h
	ld	hl, #_camera_x
	ld	b, (hl)
	add	a, #0x10
	ldhl	sp,	#0
	ld	(hl), a
;src/enemy.c:40: if (vel_x > 0) {
	ldhl	sp,	#9
	ld	e, (hl)
	xor	a, a
	ld	d, a
	sub	a, (hl)
	bit	7, e
	jr	Z, 00122$
	bit	7, d
	jr	NZ, 00123$
	cp	a, a
	jr	00123$
00122$:
	bit	7, d
	jr	Z, 00123$
	scf
00123$:
	jr	NC, 00104$
;src/enemy.c:42: uint8_t tile = get_tile(current_x + ENEMY_WIDTH - camera_x, current_y + ENEMY_HEIGHT);
	ld	a, c
	add	a, #0x08
	sub	a, b
	ldhl	sp,	#0
	ld	e, (hl)
	call	_get_tile
;src/enemy.c:43: return is_tile_solid(tile);
	call	_is_tile_solid
	jr	00106$
00104$:
;src/enemy.c:44: } else if (vel_x < 0) {
	ldhl	sp,	#9
	bit	7, (hl)
	jr	Z, 00105$
;src/enemy.c:46: uint8_t tile = get_tile(current_x - 1 - camera_x, current_y + ENEMY_HEIGHT);
	ld	a, c
	dec	a
	sub	a, b
	ldhl	sp,	#0
	ld	e, (hl)
	call	_get_tile
;src/enemy.c:47: return is_tile_solid(tile);
	call	_is_tile_solid
	jr	00106$
00105$:
;src/enemy.c:49: return FALSE;
	xor	a, a
00106$:
;src/enemy.c:50: }
	inc	sp
	ret
;src/enemy.c:53: void enemy_apply_horizontal_movement(enemy_t *enemy, uint8_t check_cliffs) BANKED {
;	---------------------------------
; Function enemy_apply_horizontal_movement
; ---------------------------------
	b_enemy_apply_horizontal_movement	= 255
_enemy_apply_horizontal_movement::
	add	sp, #-13
;src/enemy.c:54: if (enemy->vel_x == 0) return;
	ldhl	sp,	#19
	ld	a, (hl)
	ldhl	sp,	#0
	ld	(hl), a
	ldhl	sp,	#20
	ld	a, (hl)
	ldhl	sp,	#1
	ld	(hl), a
	pop	de
	push	de
	ld	hl, #0x0006
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
	ld	e, a
	ld	a, (hl+)
	ld	d, a
	ld	a, (de)
	ld	(hl), a
	or	a, a
	jp	Z, 00118$
;src/enemy.c:56: uint16_t next_x_upscaled = enemy->x + enemy->vel_x;
	pop	de
	push	de
	ld	a, (de)
	ld	c, a
	inc	de
	ld	a, (de)
	ld	b, a
	ldhl	sp,	#4
	ld	a, (hl)
	ld	e, a
	rlca
	sbc	a, a
	ld	l, e
	ld	h, a
	add	hl, bc
	ld	c, l
	ld	a, h
	ldhl	sp,	#5
	ld	(hl), c
	inc	hl
;src/enemy.c:57: uint16_t next_x = next_x_upscaled >> 4;
	ld	(hl-), a
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
;src/enemy.c:59: uint16_t current_y = enemy->y >> 4;
	pop	hl
	push	hl
	inc	hl
	inc	hl
	ld	a,	(hl+)
	ld	h, (hl)
	ld	e, a
	ld	d, h
	srl	d
	rr	e
	srl	d
	rr	e
	srl	d
	rr	e
	srl	d
	rr	e
;src/enemy.c:61: uint8_t hit_wall = FALSE;
	ldhl	sp,	#7
;src/enemy.c:62: uint8_t hit_cliff = FALSE;
;src/enemy.c:66: uint8_t tile_right_top = get_tile(next_x + ENEMY_WIDTH - 1 - camera_x, current_y + ENEMY_TOP_MARGIN);
	xor	a, a
	ld	(hl+), a
	ld	(hl+), a
	ld	a, e
	ld	(hl+), a
	ld	(hl), c
	ld	a, (#_camera_x)
	ldhl	sp,	#11
;src/enemy.c:67: uint8_t tile_right_bottom = get_tile(next_x + ENEMY_WIDTH - 1 - camera_x, current_y + ENEMY_HEIGHT - 1);
	ld	(hl-), a
	dec	hl
	ld	a, (hl)
	add	a, #0x0f
	ldhl	sp,	#12
	ld	(hl), a
;src/enemy.c:64: if (enemy->vel_x > 0) {
	ldhl	sp,	#4
	ld	e, (hl)
	xor	a, a
	ld	d, a
	sub	a, (hl)
	bit	7, e
	jr	Z, 00210$
	bit	7, d
	jr	NZ, 00211$
	cp	a, a
	jr	00211$
00210$:
	bit	7, d
	jr	Z, 00211$
	scf
00211$:
	jr	NC, 00112$
;src/enemy.c:66: uint8_t tile_right_top = get_tile(next_x + ENEMY_WIDTH - 1 - camera_x, current_y + ENEMY_TOP_MARGIN);
	ldhl	sp,	#10
	ld	a, (hl+)
	add	a, #0x07
	ld	d,a
	sub	a, (hl)
	dec	hl
	dec	hl
	push	de
	ld	e, (hl)
	call	_get_tile
	ld	c, a
	pop	de
;src/enemy.c:67: uint8_t tile_right_bottom = get_tile(next_x + ENEMY_WIDTH - 1 - camera_x, current_y + ENEMY_HEIGHT - 1);
	ld	a, (_camera_x)
	ld	e, a
	ld	a, d
	sub	a, e
	push	bc
	ldhl	sp,	#14
	ld	e, (hl)
	call	_get_tile
	ldhl	sp,	#13
	ld	(hl), a
	pop	bc
;src/enemy.c:69: hit_wall = is_tile_solid(tile_right_top) || is_tile_solid(tile_right_bottom);
	ld	a, c
	call	_is_tile_solid
	ldhl	sp,#12
	ld	(hl), a
	bit	0, (hl)
	jr	NZ, 00121$
	dec	hl
	ld	a, (hl)
	call	_is_tile_solid
	ldhl	sp,#12
	ld	(hl), a
	bit	0, (hl)
	jr	NZ, 00121$
	ld	(hl), #0x00
	jr	00122$
00121$:
	ldhl	sp,	#12
	ld	(hl), #0x01
00122$:
	ldhl	sp,	#12
	ld	a, (hl)
	ldhl	sp,	#7
	ld	(hl), a
;src/enemy.c:71: if (check_cliffs && !hit_wall) {
	ldhl	sp,	#21
	ld	a, (hl)
	or	a, a
	jp	Z, 00113$
	ldhl	sp,	#7
	ld	a, (hl)
	or	a, a
	jp	NZ, 00113$
;src/enemy.c:72: hit_cliff = !enemy_has_ground_ahead(enemy, enemy->vel_x);
	ldhl	sp,#2
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	push	af
	inc	sp
	ldhl	sp,	#1
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	push	de
	ld	e, #b_enemy_has_ground_ahead
	ld	hl, #_enemy_has_ground_ahead
	call	___sdcc_bcall_ehl
	add	sp, #3
	sub	a, #0x01
	ld	a, #0x00
	rla
	ldhl	sp,	#8
	ld	(hl), a
	jr	00113$
00112$:
;src/enemy.c:74: } else if (enemy->vel_x < 0) {
	ldhl	sp,	#4
	bit	7, (hl)
	jr	Z, 00113$
;src/enemy.c:76: uint8_t tile_left_top = get_tile(next_x - camera_x, current_y + ENEMY_TOP_MARGIN);
	ldhl	sp,	#10
	ld	a, (hl+)
	sub	a, (hl)
	dec	hl
	dec	hl
	ld	e, (hl)
	call	_get_tile
	ld	c, a
;src/enemy.c:77: uint8_t tile_left_bottom = get_tile(next_x - camera_x, current_y + ENEMY_HEIGHT - 1);
	ld	a, (_camera_x)
	ld	b, a
	ldhl	sp,	#10
	ld	a, (hl+)
	inc	hl
	sub	a, b
	push	bc
	ld	e, (hl)
	call	_get_tile
	ld	e, a
	pop	bc
;src/enemy.c:79: hit_wall = is_tile_solid(tile_left_top) || is_tile_solid(tile_left_bottom);
	push	de
	ld	a, c
	call	_is_tile_solid
	ld	c, a
	pop	de
	bit	0, c
	jr	NZ, 00124$
	ld	a, e
	call	_is_tile_solid
	bit	0,a
	ld	c, #0x00
	jr	Z, 00125$
00124$:
	ld	c, #0x01
00125$:
	ldhl	sp,	#7
	ld	(hl), c
;src/enemy.c:81: if (check_cliffs && !hit_wall) {
	ldhl	sp,	#21
	ld	a, (hl)
	or	a, a
	jr	Z, 00113$
	ldhl	sp,	#7
	ld	a, (hl)
	or	a, a
	jr	NZ, 00113$
;src/enemy.c:82: hit_cliff = !enemy_has_ground_ahead(enemy, enemy->vel_x);
	ldhl	sp,#2
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	push	af
	inc	sp
	ldhl	sp,	#1
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	push	de
	ld	e, #b_enemy_has_ground_ahead
	ld	hl, #_enemy_has_ground_ahead
	call	___sdcc_bcall_ehl
	add	sp, #3
	sub	a, #0x01
	ld	a, #0x00
	rla
	ldhl	sp,	#8
	ld	(hl), a
00113$:
;src/enemy.c:86: if (hit_wall || hit_cliff) {
	ldhl	sp,	#7
	ld	a, (hl)
	or	a, a
	jr	NZ, 00114$
	inc	hl
	ld	a, (hl)
	or	a, a
	jr	Z, 00115$
00114$:
;src/enemy.c:88: enemy->vel_x = -enemy->vel_x;
	ldhl	sp,#2
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	c, a
	xor	a, a
	sub	a, c
	ld	c, a
	ld	a, (hl-)
	ld	l, (hl)
	ld	h, a
	ld	(hl), c
;src/enemy.c:89: enemy->flip = !enemy->flip;
	pop	de
	push	de
	ld	hl, #0x000c
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	xor	a, #0x01
	ld	(bc), a
	jr	00118$
00115$:
;src/enemy.c:92: enemy->x = next_x_upscaled;
	ldhl	sp,	#19
	ld	a, (hl)
	ldhl	sp,	#11
	ld	(hl), a
	ldhl	sp,	#20
	ld	a, (hl)
	ldhl	sp,	#12
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ldhl	sp,	#5
	ld	a, (hl+)
	ld	(de), a
	inc	de
	ld	a, (hl)
	ld	(de), a
00118$:
;src/enemy.c:94: }
	add	sp, #13
	ret
;src/enemy.c:97: void enemy_apply_vertical_movement(enemy_t *enemy, int8_t gravity_divisor) BANKED {
;	---------------------------------
; Function enemy_apply_vertical_movement
; ---------------------------------
	b_enemy_apply_vertical_movement	= 255
_enemy_apply_vertical_movement::
	add	sp, #-10
;src/enemy.c:98: uint16_t ground_check_x = enemy->x >> 4;
	ldhl	sp,#16
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	c, a
	inc	de
	ld	a, (de)
	ld	b, a
	ldhl	sp,	#8
	ld	(hl), c
	inc	hl
	ld	(hl), b
	srl	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	srl	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	srl	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	srl	(hl)
	dec	hl
	rr	(hl)
;src/enemy.c:101: uint8_t on_ground = enemy_has_ground(enemy);
	ldhl	sp,	#16
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	push	de
	ld	e, #b_enemy_has_ground
	ld	hl, #_enemy_has_ground
	call	___sdcc_bcall_ehl
	pop	hl
	ld	c, a
;src/enemy.c:106: enemy->vel_y = ENEMY_GRAVITY;
	ldhl	sp,#16
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0007
	add	hl, de
	inc	sp
	inc	sp
	push	hl
;src/enemy.c:104: if (!on_ground) {
	ld	a, c
	or	a, a
	jr	NZ, 00105$
;src/enemy.c:105: if (gravity_divisor == 1) {
	ldhl	sp,	#18
	ld	a, (hl)
	dec	a
	jr	NZ, 00102$
;src/enemy.c:106: enemy->vel_y = ENEMY_GRAVITY;
	pop	hl
	ld	(hl), #0x20
	push	hl
	jr	00105$
00102$:
;src/enemy.c:108: enemy->vel_y += ENEMY_GRAVITY / gravity_divisor;
	pop	de
	push	de
	ld	a, (de)
	ld	c, a
	ldhl	sp,	#18
	ld	a, (hl)
	ld	e, a
	rlca
	sbc	a, a
	push	bc
	ld	c, e
	ld	b, a
	ld	de, #0x0020
	call	__divsint
	ld	e, c
	pop	bc
	ld	a, e
	add	a, c
	pop	hl
	push	hl
	ld	(hl), a
00105$:
;src/enemy.c:113: if (enemy->vel_y != 0) {
	pop	de
	push	de
	ld	a, (de)
	ldhl	sp,	#2
	ld	(hl), a
	or	a, a
	jp	Z, 00121$
;src/enemy.c:114: uint16_t next_y_upscaled = enemy->y + enemy->vel_y;
	ldhl	sp,#16
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0002
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#5
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#4
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	a, (hl+)
	inc	hl
	ld	d, a
	ld	a, (de)
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ldhl	sp,	#2
	ld	a, (hl)
	ld	e, a
	rlca
	sbc	a, a
	ld	d, a
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	ld	l, e
	ld	h, d
	add	hl, bc
	ld	c, l
	ld	b, h
	ldhl	sp,	#5
	ld	a, c
	ld	(hl+), a
;src/enemy.c:115: uint16_t next_y = next_y_upscaled >> 4;
	ld	a, b
	ld	(hl-), a
	ld	a, (hl+)
	ld	c, a
;src/enemy.c:119: uint8_t tile_bottom_left = get_tile(ground_check_x - camera_x, next_y + ENEMY_HEIGHT);
	ld	a, (hl+)
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
	ld	(hl+), a
	ld	e, (hl)
	ld	a, (_camera_x)
	ld	d, a
	ld	a, e
	sub	a, d
;src/enemy.c:120: uint8_t tile_bottom_right = get_tile(ground_check_x + ENEMY_WIDTH - 1 - camera_x, next_y + ENEMY_HEIGHT);
	ld	(hl+), a
	ld	a, e
	add	a, #0x07
	ld	(hl), a
;src/enemy.c:117: if (enemy->vel_y > 0) {
	ldhl	sp,	#2
	ld	e, (hl)
	xor	a, a
	ld	d, a
	sub	a, (hl)
	bit	7, e
	jr	Z, 00174$
	bit	7, d
	jr	NZ, 00175$
	cp	a, a
	jr	00175$
00174$:
	bit	7, d
	jr	Z, 00175$
	scf
00175$:
	jr	NC, 00117$
;src/enemy.c:119: uint8_t tile_bottom_left = get_tile(ground_check_x - camera_x, next_y + ENEMY_HEIGHT);
	ldhl	sp,	#7
	ld	a, (hl+)
	add	a, #0x10
	ld	e, a
	push	bc
	push	de
	ld	a, (hl)
	call	_get_tile
	ldhl	sp,	#12
	ld	(hl), a
	pop	de
	pop	bc
;src/enemy.c:120: uint8_t tile_bottom_right = get_tile(ground_check_x + ENEMY_WIDTH - 1 - camera_x, next_y + ENEMY_HEIGHT);
	ld	a, (_camera_x)
	ld	d, a
	ldhl	sp,	#9
	ld	a, (hl)
	sub	a, d
	push	bc
	call	_get_tile
	ld	e, a
;src/enemy.c:122: if (is_tile_solid(tile_bottom_left) || is_tile_solid(tile_bottom_right)) {
	push	de
	ldhl	sp,	#12
	ld	a, (hl)
	call	_is_tile_solid
	ld	l, a
	pop	de
	pop	bc
	bit	0, l
	jr	NZ, 00106$
	push	bc
	ld	a, e
	call	_is_tile_solid
	ld	e, a
	pop	bc
	bit	0, e
	jr	Z, 00107$
00106$:
;src/enemy.c:124: enemy->vel_y = 0;
	pop	hl
	ld	(hl), #0x00
	push	hl
;src/enemy.c:125: enemy->y = (TILE_ALIGN(next_y + ENEMY_HEIGHT) - ENEMY_HEIGHT) << 4;
	ld	hl, #0x0017
	add	hl, bc
	ld	a, l
	and	a, #0xf8
	add	a, #0xf0
	ld	l, a
	ld	a, h
	adc	a, #0xff
	ld	h, a
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	c, l
	ld	b, h
	ldhl	sp,	#3
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
	jr	00121$
00107$:
;src/enemy.c:128: enemy->y = next_y_upscaled;
	ldhl	sp,	#3
	ld	a, (hl+)
	ld	e, a
	ld	a, (hl+)
	ld	d, a
	ld	a, (hl+)
	ld	(de), a
	inc	de
	ld	a, (hl)
	ld	(de), a
	jr	00121$
00117$:
;src/enemy.c:130: } else if (enemy->vel_y < 0) {
	ldhl	sp,	#2
	ld	a, (hl)
	bit	7, a
	jr	Z, 00121$
;src/enemy.c:132: uint8_t tile_top_left = get_tile(ground_check_x - camera_x, next_y + ENEMY_TOP_MARGIN);
	ldhl	sp,	#7
	ld	a, (hl+)
	ld	e, a
	ld	a, (hl)
	call	_get_tile
	ld	d, a
;src/enemy.c:133: uint8_t tile_top_right = get_tile(ground_check_x + ENEMY_WIDTH - 1 - camera_x, next_y + ENEMY_TOP_MARGIN);
	ld	a, (_camera_x)
	ld	c, a
	ldhl	sp,	#9
	ld	a, (hl-)
	dec	hl
	sub	a, c
	push	de
	ld	e, (hl)
	call	_get_tile
	ld	c, a
	pop	de
;src/enemy.c:135: if (is_tile_solid(tile_top_left) || is_tile_solid(tile_top_right)) {
	push	bc
	ld	a, d
	call	_is_tile_solid
	ld	e, a
	pop	bc
	bit	0, e
	jr	NZ, 00110$
	ld	a, c
	call	_is_tile_solid
	ld	c, a
	bit	0, c
	jr	Z, 00111$
00110$:
;src/enemy.c:137: enemy->vel_y = 0;
	pop	hl
	ld	(hl), #0x00
	push	hl
	jr	00121$
00111$:
;src/enemy.c:140: enemy->y = next_y_upscaled;
	ldhl	sp,	#3
	ld	a, (hl+)
	ld	e, a
	ld	a, (hl+)
	ld	d, a
	ld	a, (hl+)
	ld	(de), a
	inc	de
	ld	a, (hl)
	ld	(de), a
00121$:
;src/enemy.c:144: }
	add	sp, #10
	ret
;src/enemy.c:191: void enemy_move_goomba(uint8_t index) BANKED {
;	---------------------------------
; Function enemy_move_goomba
; ---------------------------------
	b_enemy_move_goomba	= 255
_enemy_move_goomba::
;src/enemy.c:192: enemy_t *goomba = &enemies[index];
	ld	bc, #_enemies+0
	ldhl	sp,	#6
	ld	e, (hl)
	xor	a, a
	ld	l, e
	ld	h, a
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, bc
	ld	e, l
	ld	d, h
;src/enemy.c:195: if (goomba->stomped || !goomba->active) {
	ld	hl, #0x000d
	add	hl, de
	bit	0, (hl)
	ret	NZ
	ld	hl, #0x000f
	add	hl, de
	ld	c, (hl)
	bit	0, c
;src/enemy.c:196: return;
	ret	Z
;src/enemy.c:200: if (goomba->vel_x == 0) {
	ld	hl, #0x0006
	add	hl, de
	ld	a, (hl)
	or	a, a
	jr	NZ, 00105$
;src/enemy.c:201: goomba->vel_x = -ENEMY_GOOMBA_SPEED; // Start moving left
	ld	(hl), #0xfc
00105$:
;src/enemy.c:205: enemy_apply_horizontal_movement(goomba, FALSE); // Goombas don't avoid cliffs
	push	de
	xor	a, a
	push	af
	inc	sp
	push	de
	ld	e, #b_enemy_apply_horizontal_movement
	ld	hl, #_enemy_apply_horizontal_movement
	call	___sdcc_bcall_ehl
	add	sp, #3
	pop	de
;src/enemy.c:206: enemy_apply_vertical_movement(goomba, 1); // Full gravity
	ld	a, #0x01
	push	af
	inc	sp
	push	de
	ld	e, #b_enemy_apply_vertical_movement
	ld	hl, #_enemy_apply_vertical_movement
	call	___sdcc_bcall_ehl
	add	sp, #3
;src/enemy.c:207: }
	ret
;src/enemy.c:209: void enemy_move_koopa(uint8_t index) BANKED {
;	---------------------------------
; Function enemy_move_koopa
; ---------------------------------
	b_enemy_move_koopa	= 255
_enemy_move_koopa::
;src/enemy.c:210: enemy_t *koopa = &enemies[index];
	ld	bc, #_enemies+0
	ldhl	sp,	#6
	ld	e, (hl)
	xor	a, a
	ld	l, e
	ld	h, a
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, bc
	ld	e, l
	ld	d, h
;src/enemy.c:213: if (koopa->stomped || !koopa->active) {
	ld	hl, #0x000d
	add	hl, de
	bit	0, (hl)
	ret	NZ
	ld	hl, #0x000f
	add	hl, de
	ld	c, (hl)
	bit	0, c
;src/enemy.c:214: return;
	ret	Z
;src/enemy.c:218: if (koopa->vel_x == 0) {
	ld	hl, #0x0006
	add	hl, de
	ld	a, (hl)
	or	a, a
	jr	NZ, 00105$
;src/enemy.c:219: koopa->vel_x = -ENEMY_KOOPA_SPEED; // Start moving left
	ld	(hl), #0xfc
00105$:
;src/enemy.c:223: enemy_apply_horizontal_movement(koopa, TRUE); // Koopas turn at cliffs
	push	de
	ld	a, #0x01
	push	af
	inc	sp
	push	de
	ld	e, #b_enemy_apply_horizontal_movement
	ld	hl, #_enemy_apply_horizontal_movement
	call	___sdcc_bcall_ehl
	add	sp, #3
	pop	de
;src/enemy.c:224: enemy_apply_vertical_movement(koopa, 1); // Full gravity
	ld	a, #0x01
	push	af
	inc	sp
	push	de
	ld	e, #b_enemy_apply_vertical_movement
	ld	hl, #_enemy_apply_vertical_movement
	call	___sdcc_bcall_ehl
	add	sp, #3
;src/enemy.c:225: }
	ret
;src/enemy.c:227: void enemy_move_fly(uint8_t index) BANKED {
;	---------------------------------
; Function enemy_move_fly
; ---------------------------------
	b_enemy_move_fly	= 255
_enemy_move_fly::
	add	sp, #-9
;src/enemy.c:228: enemy_t *fly = &enemies[index];
	ld	bc, #_enemies+0
	ldhl	sp,	#15
	ld	e, (hl)
	xor	a, a
	ld	l, e
	ld	h, a
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, bc
	ld	c, l
	ld	a, h
	ldhl	sp,	#0
	ld	(hl), c
	inc	hl
	ld	(hl), a
;src/enemy.c:231: if (fly->stomped || !fly->active) {
	pop	de
	push	de
	ld	hl, #0x000d
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	bit	0,a
	jp	NZ, 00113$
	pop	de
	push	de
	ld	hl, #0x000f
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	bit	0,a
;src/enemy.c:232: return;
	jp	Z, 00113$
;src/enemy.c:235: uint8_t on_ground = enemy_has_ground(fly);
	pop	de
	push	de
	push	de
	ld	e, #b_enemy_has_ground
	ld	hl, #_enemy_has_ground
	call	___sdcc_bcall_ehl
	pop	hl
	ld	e, a
	ldhl	sp,	#2
;src/enemy.c:239: fly->vel_y = ENEMY_FLY_JUMP_VELOCITY;
	ld	a, e
	ld	(hl-), a
	dec	hl
	push	de
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0007
	add	hl, de
	pop	de
	ld	c, l
	ld	b, h
;src/enemy.c:244: fly->vel_x = -ENEMY_FLY_JUMP_SPEED;
	push	de
	ldhl	sp,#2
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0006
	add	hl, de
	pop	de
	push	hl
	ld	a, l
	ldhl	sp,	#5
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#4
	ld	(hl), a
;src/enemy.c:238: if (on_ground && fly->frame_counter >= ENEMY_FLY_WAIT_FRAMES) {
	ld	a, e
	or	a, a
	jr	Z, 00108$
	pop	de
	push	de
	ld	hl, #0x0009
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#7
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#6
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	sub	a, #0x3c
	jr	C, 00108$
;src/enemy.c:239: fly->vel_y = ENEMY_FLY_JUMP_VELOCITY;
	ld	a, #0xd0
	ld	(bc), a
;src/enemy.c:242: if (player_draw_x < fly->draw_x) {
	pop	de
	push	de
	ld	hl, #0x0004
	add	hl, de
	ld	e, l
	ld	d, h
	ld	a, (de)
	ld	e, a
;src/enemy.c:245: fly->flip = TRUE;
	push	de
	ldhl	sp,#2
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x000c
	add	hl, de
	pop	de
	push	hl
	ld	a, l
	ldhl	sp,	#9
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#8
	ld	(hl), a
;src/enemy.c:242: if (player_draw_x < fly->draw_x) {
	ld	a, (#_player_draw_x)
	sub	a, e
	jr	NC, 00105$
;src/enemy.c:244: fly->vel_x = -ENEMY_FLY_JUMP_SPEED;
	ldhl	sp,	#3
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0xf8
;src/enemy.c:245: fly->flip = TRUE;
	ldhl	sp,	#7
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x01
	jr	00106$
00105$:
;src/enemy.c:248: fly->vel_x = ENEMY_FLY_JUMP_SPEED;
	ldhl	sp,	#3
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x08
;src/enemy.c:249: fly->flip = FALSE;
	ldhl	sp,	#7
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x00
00106$:
;src/enemy.c:252: fly->frame_counter = 0; // Reset counter
	ldhl	sp,	#5
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x00
00108$:
;src/enemy.c:256: if (on_ground && fly->vel_y == 0) {
	ldhl	sp,	#2
	ld	a, (hl)
	or	a, a
	jr	Z, 00111$
	ld	a, (bc)
	or	a, a
	jr	NZ, 00111$
;src/enemy.c:257: fly->vel_x = 0;
	inc	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x00
00111$:
;src/enemy.c:261: enemy_apply_horizontal_movement(fly, FALSE); // No cliff checking for flies
	xor	a, a
	push	af
	inc	sp
	ldhl	sp,	#1
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	push	de
	ld	e, #b_enemy_apply_horizontal_movement
	ld	hl, #_enemy_apply_horizontal_movement
	call	___sdcc_bcall_ehl
	add	sp, #3
;src/enemy.c:262: enemy_apply_vertical_movement(fly, 8); // Lighter gravity (1/8th)
	ld	a, #0x08
	push	af
	inc	sp
	ldhl	sp,	#1
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	push	de
	ld	e, #b_enemy_apply_vertical_movement
	ld	hl, #_enemy_apply_vertical_movement
	call	___sdcc_bcall_ehl
	add	sp, #3
00113$:
;src/enemy.c:263: }
	add	sp, #9
	ret
;src/enemy.c:265: void enemy_stomp(uint8_t index_enemy) BANKED {
;	---------------------------------
; Function enemy_stomp
; ---------------------------------
	b_enemy_stomp	= 255
_enemy_stomp::
;src/enemy.c:266: enemy_t *enemy = &enemies[index_enemy];
	ld	bc, #_enemies+0
	ldhl	sp,	#6
	ld	e, (hl)
	xor	a, a
	ld	l, e
	ld	h, a
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, bc
	ld	c, l
	ld	b, h
;src/enemy.c:268: if (!enemy->active) {
	ld	hl, #0x000f
	add	hl, bc
	ld	e, (hl)
	bit	0, e
;src/enemy.c:269: return;
	ret	Z
;src/enemy.c:273: enemy->stomped = TRUE;
	ld	hl, #0x000d
	add	hl, bc
	ld	(hl), #0x01
;src/enemy.c:274: enemy->stomped_timer = ENEMY_STOMPED_DISPLAY_FRAMES;
	ld	hl, #0x000e
	add	hl, bc
	ld	(hl), #0x1e
;src/enemy.c:277: enemy->vel_x = 0;
	ld	hl, #0x0006
	add	hl, bc
	ld	(hl), #0x00
;src/enemy.c:278: enemy->vel_y = 0;
	ld	hl, #0x0007
	add	hl, bc
	ld	(hl), #0x00
;src/enemy.c:281: switch (enemy->type) {
	ld	hl, #0x0008
	add	hl, bc
	ld	e, (hl)
;src/enemy.c:283: enemy->current_frame = 1;
	ld	hl, #0x000a
	add	hl, bc
;src/enemy.c:281: switch (enemy->type) {
	ld	a, e
	or	a, a
	jr	Z, 00103$
	dec	e
	jr	Z, 00104$
	jr	00105$
;src/enemy.c:282: case ENEMY_GOOMBO:
00103$:
;src/enemy.c:283: enemy->current_frame = 1;
	ld	(hl), #0x01
;src/enemy.c:284: enemy->flip = FALSE;
	ld	hl, #0x000c
	add	hl, bc
	ld	(hl), #0x00
;src/enemy.c:285: break;
	ret
;src/enemy.c:286: case ENEMY_KOOPA:
00104$:
;src/enemy.c:287: enemy->current_frame = 4;
	ld	(hl), #0x04
;src/enemy.c:288: break;
	ret
;src/enemy.c:289: default:
00105$:
;src/enemy.c:290: enemy->current_frame++;
	inc	(hl)
;src/enemy.c:292: }
;src/enemy.c:293: }
	ret
;src/enemy.c:305: void enemy_reset_all(void) BANKED {
;	---------------------------------
; Function enemy_reset_all
; ---------------------------------
	b_enemy_reset_all	= 255
_enemy_reset_all::
;src/enemy.c:309: for (uint8_t i = 0; i < ENEMY_MAX; i++) {
	ld	c, #0x00
00103$:
	ld	a, c
	sub	a, #0x04
	jr	NC, 00101$
;src/enemy.c:310: enemies[i].active = FALSE;
	ld	l, c
	xor	a, a
	ld	h, a
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	a, l
	add	a, #<(_enemies)
	ld	e, a
	ld	a, h
	adc	a, #>(_enemies)
	ld	d, a
	ld	hl, #0x000f
	add	hl, de
	ld	(hl), #0x00
;src/enemy.c:311: enemies[i].stomped = FALSE;
	ld	hl, #0x000d
	add	hl, de
	ld	(hl), #0x00
;src/enemy.c:312: enemies[i].x = 0;
	ld	l, e
	ld	h, d
	xor	a, a
	ld	(hl+), a
	ld	(hl), a
;src/enemy.c:313: enemies[i].y = 0;
	ld	l, e
	ld	h, d
	inc	hl
	inc	hl
	xor	a, a
	ld	(hl+), a
	ld	(hl), a
;src/enemy.c:314: enemies[i].vel_x = 0;
	ld	hl, #0x0006
	add	hl, de
	ld	(hl), #0x00
;src/enemy.c:315: enemies[i].vel_y = 0;
	ld	hl, #0x0007
	add	hl, de
	ld	(hl), #0x00
;src/enemy.c:316: enemies[i].draw_x = 0;
	ld	hl, #0x0004
	add	hl, de
	ld	(hl), #0x00
;src/enemy.c:317: enemies[i].draw_y = 0;
	ld	hl, #0x0005
	add	hl, de
	ld	(hl), #0x00
;src/enemy.c:309: for (uint8_t i = 0; i < ENEMY_MAX; i++) {
	inc	c
	jr	00103$
00101$:
;src/enemy.c:321: enemy_count = 0;
	xor	a, a
	ld	(#_enemy_count),a
;src/enemy.c:324: hide_sprites_range(1, MAX_HARDWARE_SPRITES);
	ld	e, #0x28
	ld	a, #0x01
;src/enemy.c:325: }
	jp	_hide_sprites_range
;src/enemy.c:327: void enemy_update(void) BANKED {
;	---------------------------------
; Function enemy_update
; ---------------------------------
	b_enemy_update	= 255
_enemy_update::
	add	sp, #-16
;src/enemy.c:328: for (uint8_t index_enemy = 0; index_enemy < ENEMY_MAX; index_enemy++) {
	ldhl	sp,	#15
	ld	(hl), #0x00
00121$:
	ldhl	sp,	#15
	ld	a, (hl)
	sub	a, #0x04
	jp	NC, 00122$
;src/enemy.c:330: if (!enemies[index_enemy].active) {
	ld	a, (hl-)
	dec	hl
	ld	(hl+), a
	ld	(hl), #0x00
	ld	a, #0x04
00209$:
	ldhl	sp,	#13
	sla	(hl)
	inc	hl
	rl	(hl)
	dec	a
	jr	NZ, 00209$
	dec	hl
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #_enemies
	add	hl, de
	inc	sp
	inc	sp
	ld	e, l
	ld	d, h
	push	de
	ld	hl, #0x000f
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	ldhl	sp,	#14
	ld	(hl), a
	bit	0, (hl)
	jp	Z, 00118$
;src/enemy.c:335: if (enemies[index_enemy].stomped) {
	pop	de
	push	de
	ld	hl, #0x000d
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	ld	c, a
;src/enemy.c:343: enemies[index_enemy].draw_x =
	pop	de
	push	de
	ld	hl, #0x0004
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#4
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#3
	ld	(hl), a
;src/enemy.c:344: (enemies[index_enemy].x - camera_x_upscaled) >> 4;
	ldhl	sp,	#0
	ld	a, (hl)
	ldhl	sp,	#4
	ld	(hl), a
	ldhl	sp,	#1
	ld	a, (hl)
	ldhl	sp,	#5
	ld	(hl), a
;src/enemy.c:345: enemies[index_enemy].draw_y = enemies[index_enemy].y >> 4;
	pop	de
	push	de
	ld	hl, #0x0005
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#8
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#7
	ld	(hl), a
	pop	de
	push	de
	ld	hl, #0x0002
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#10
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#9
	ld	(hl), a
;src/enemy.c:335: if (enemies[index_enemy].stomped) {
	bit	0, c
	jp	Z, 00106$
;src/enemy.c:336: enemies[index_enemy].stomped_timer--;
	pop	de
	push	de
	ld	hl, #0x000e
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	dec	a
	ld	(bc), a
;src/enemy.c:337: if (enemies[index_enemy].stomped_timer == 0) {
	or	a, a
	jr	NZ, 00104$
;src/enemy.c:339: enemy_remove(index_enemy);
	ldhl	sp,	#15
	ld	a, (hl)
	call	_enemy_remove
;src/enemy.c:340: continue;
	jp	00118$
00104$:
;src/enemy.c:344: (enemies[index_enemy].x - camera_x_upscaled) >> 4;
	ldhl	sp,#4
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ldhl	sp,	#13
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #_camera_x_upscaled
	ld	a,	(hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, e
	sub	a, l
	ld	e, a
	ld	a, d
	sbc	a, h
	ldhl	sp,	#12
	ld	(hl-), a
	ld	a, e
	ld	(hl+), a
	dec	hl
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
	ldhl	sp,	#2
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
;src/enemy.c:345: enemies[index_enemy].draw_y = enemies[index_enemy].y >> 4;
	ldhl	sp,#8
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ldhl	sp,	#13
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	srl	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	srl	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	srl	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	srl	(hl)
	dec	hl
	rr	(hl)
	ld	a, (hl)
	ldhl	sp,	#6
	ld	e, (hl)
	inc	hl
	ld	h, (hl)
	ld	l, e
	ld	(hl), a
;src/enemy.c:346: continue;
	jp	00118$
00106$:
;src/enemy.c:349: switch (enemies[index_enemy].type) {
	pop	de
	push	de
	ld	hl, #0x0008
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	ldhl	sp,	#14
	ld	(hl), a
;src/enemy.c:353: if (enemies[index_enemy].frame_counter == ENEMY_LOOP_PER_ANIMATION_FRAME) {
	pop	de
	push	de
	ld	hl, #0x0009
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#12
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#11
	ld	(hl), a
;src/enemy.c:349: switch (enemies[index_enemy].type) {
	ldhl	sp,	#14
	ld	a, (hl)
	or	a, a
	jr	Z, 00107$
	ldhl	sp,	#14
	ld	a, (hl)
	dec	a
	jr	Z, 00110$
	ldhl	sp,	#14
	ld	a, (hl)
	sub	a, #0x02
	jp	Z, 00113$
	jp	00114$
;src/enemy.c:350: case ENEMY_GOOMBO:
00107$:
;src/enemy.c:351: enemy_move_goomba(index_enemy);
	ldhl	sp,	#15
	ld	a, (hl)
	push	af
	inc	sp
	ld	e, #b_enemy_move_goomba
	ld	hl, #_enemy_move_goomba
	call	___sdcc_bcall_ehl
	inc	sp
;src/enemy.c:353: if (enemies[index_enemy].frame_counter == ENEMY_LOOP_PER_ANIMATION_FRAME) {
	ldhl	sp,#10
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	sub	a, #0x0f
	jr	NZ, 00114$
;src/enemy.c:354: enemies[index_enemy].frame_counter = 0;
	ld	a, (hl-)
	ld	l, (hl)
	ld	h, a
	ld	(hl), #0x00
;src/enemy.c:355: enemies[index_enemy].flip = !enemies[index_enemy].flip;
	pop	de
	push	de
	ld	hl, #0x000c
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	xor	a, #0x01
	ld	(bc), a
;src/enemy.c:357: break;
	jr	00114$
;src/enemy.c:358: case ENEMY_KOOPA:
00110$:
;src/enemy.c:359: enemy_move_koopa(index_enemy);
	ldhl	sp,	#15
	ld	a, (hl)
	push	af
	inc	sp
	ld	e, #b_enemy_move_koopa
	ld	hl, #_enemy_move_koopa
	call	___sdcc_bcall_ehl
	inc	sp
;src/enemy.c:360: if (enemies[index_enemy].frame_counter == ENEMY_LOOP_PER_ANIMATION_FRAME) {
	ldhl	sp,#10
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	sub	a, #0x0f
	jr	NZ, 00114$
;src/enemy.c:361: enemies[index_enemy].frame_counter = 0;
	ld	a, (hl-)
	ld	l, (hl)
	ld	h, a
	ld	(hl), #0x00
;src/enemy.c:362: enemies[index_enemy].current_frame =
	pop	de
	push	de
	ld	hl, #0x000a
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#14
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#13
;src/enemy.c:363: (enemies[index_enemy].current_frame + 1) % 2 + 2;
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	d, #0x00
	ld	e, a
	inc	de
	ld	bc, #0x0002
	call	__modsint
	pop	hl
	push	bc
	ldhl	sp,	#0
	ld	a, (hl)
	ldhl	sp,	#14
	ld	(hl), a
	inc	(hl)
	inc	(hl)
	dec	hl
	dec	hl
	ld	a, (hl+)
	ld	e, a
	ld	a, (hl+)
	ld	d, a
	ld	a, (hl)
	ld	(de), a
;src/enemy.c:365: break;
	jr	00114$
;src/enemy.c:366: case ENEMY_FLY:
00113$:
;src/enemy.c:367: enemy_move_fly(index_enemy);
	ldhl	sp,	#15
	ld	a, (hl)
	push	af
	inc	sp
	ld	e, #b_enemy_move_fly
	ld	hl, #_enemy_move_fly
	call	___sdcc_bcall_ehl
	inc	sp
;src/enemy.c:370: }
00114$:
;src/enemy.c:374: (enemies[index_enemy].x - camera_x_upscaled) >> 4;
	ldhl	sp,#4
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ldhl	sp,	#0
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	pop	de
	push	de
	ld	hl, #_camera_x_upscaled
	ld	a,	(hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, e
	sub	a, l
	ld	e, a
	ld	a, d
	sbc	a, h
	ldhl	sp,	#14
	ld	(hl-), a
	ld	a, e
	ld	(hl+), a
	srl	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	srl	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	srl	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	srl	(hl)
	dec	hl
	rr	(hl)
	ld	a, (hl+)
	ld	(hl), a
	ldhl	sp,	#2
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ldhl	sp,	#14
	ld	a, (hl)
	ld	(de), a
;src/enemy.c:375: enemies[index_enemy].draw_y = enemies[index_enemy].y >> 4;
	ldhl	sp,#8
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ldhl	sp,	#13
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	srl	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	srl	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	srl	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	srl	(hl)
	dec	hl
	rr	(hl)
	ld	a, (hl+)
	ld	(hl), a
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ldhl	sp,	#14
	ld	a, (hl)
	ld	(de), a
;src/enemy.c:378: if (camera_x_upscaled > DEVICE_SCREEN_PX_WIDTH &&
	ld	hl, #_camera_x_upscaled
	ld	a, #0xa0
	sub	a, (hl)
	inc	hl
	ld	a, #0x00
	sbc	a, (hl)
	jr	NC, 00116$
;src/enemy.c:379: enemies[index_enemy].x <= camera_x_upscaled - DEVICE_SCREEN_PX_WIDTH) {
	ldhl	sp,#4
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ldhl	sp,	#13
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ld	a, (#_camera_x_upscaled)
	ldhl	sp,	#6
	ld	(hl), a
	ld	a, (#_camera_x_upscaled + 1)
	ldhl	sp,	#7
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x00a0
	ld	a, e
	sub	a, l
	ld	e, a
	ld	a, d
	sbc	a, h
	ldhl	sp,	#9
	ld	(hl-), a
	ld	(hl), e
	ldhl	sp,	#8
	ld	e, l
	ld	d, h
	ldhl	sp,	#13
	ld	a, (de)
	inc	de
	sub	a, (hl)
	inc	hl
	ld	a, (de)
	sbc	a, (hl)
	jr	C, 00116$
;src/enemy.c:380: enemy_remove(index_enemy);
	ldhl	sp,	#15
	ld	a, (hl)
	call	_enemy_remove
;src/enemy.c:381: continue;
	jr	00118$
00116$:
;src/enemy.c:384: enemies[index_enemy].frame_counter++;
	ldhl	sp,#10
	ld	a, (hl+)
	ld	e, a
	ld	a, (hl-)
	ld	d, a
	ld	a, (de)
	inc	a
	ld	e, (hl)
	inc	hl
	ld	h, (hl)
	ld	l, e
	ld	(hl), a
00118$:
;src/enemy.c:328: for (uint8_t index_enemy = 0; index_enemy < ENEMY_MAX; index_enemy++) {
	ldhl	sp,	#15
	inc	(hl)
	jp	00121$
00122$:
;src/enemy.c:386: }
	add	sp, #16
	ret
	.area _CODE_255
	.area _INITIALIZER
__xinit__enemy_count:
	.db #0x00	; 0
	.area _CABS (ABS)
