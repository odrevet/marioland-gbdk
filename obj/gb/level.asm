;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler
; Version 4.5.1 #15267 (Linux)
;--------------------------------------------------------
	.module level
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _powerup_new
	.globl _enemy_new
	.globl _hud_update_lives
	.globl _hud_update_score
	.globl _hud_update_coins
	.globl _hud_set_level
	.globl _pipe_clear
	.globl _pipe_new
	.globl _platform_falling_new
	.globl _platform_moving_new
	.globl _coin_animated_new
	.globl _hide_sprites_range
	.globl _set_sprite_data
	.globl _set_bkg_tile_xy
	.globl _set_bkg_tiles
	.globl _set_bkg_data
	.globl _col_from
	.globl _current_page
	.globl _level_page_x_offset
	.globl _current_column_in_page
	.globl _map_column
	.globl _map_buffer
	.globl _level_lookup_size
	.globl _level_lookup
	.globl _level_lookup_bank
	.globl _level_bank
	.globl _current_map_width_in_tiles
	.globl _current_map_width
	.globl _current_map_tile_count
	.globl _current_map_tiles
	.globl _current_map_tile_origin
	.globl _current_level
	.globl _level_end_reached
	.globl _coldata
	.globl _current_map
	.globl _load_col_at
	.globl _camera_x_upscaled
	.globl _camera_x
	.globl _undergrounds
	.globl _levels
	.globl _get_tile
	.globl _is_tile_solid
	.globl _is_tile_passthought
	.globl _is_coin
	.globl _on_get_coin_background
	.globl _on_break_tile
	.globl b_on_block_bump
	.globl _on_block_bump
	.globl b_block_bump_update
	.globl _block_bump_update
	.globl b_block_bump_draw
	.globl _block_bump_draw
	.globl _on_get_coin
	.globl _on_interogation_block_hit
	.globl _level_load_objects
	.globl _level_load_column
	.globl _level_set_current
	.globl _load_current_level
	.globl _set_level
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area _HRAM
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_camera_x::
	.ds 2
_camera_x_upscaled::
	.ds 2
_load_col_at::
	.ds 2
_current_map::
	.ds 2
_coldata::
	.ds 16
_level_end_reached::
	.ds 1
_current_level::
	.ds 1
_current_map_tile_origin::
	.ds 2
_current_map_tiles::
	.ds 2
_current_map_tile_count::
	.ds 2
_current_map_width::
	.ds 2
_current_map_width_in_tiles::
	.ds 2
_level_bank::
	.ds 1
_level_lookup_bank::
	.ds 1
_level_lookup::
	.ds 2
_level_lookup_size::
	.ds 2
_block_bump_state:
	.ds 7
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
_map_buffer::
	.ds 512
_map_column::
	.ds 1
_current_column_in_page::
	.ds 1
_level_page_x_offset::
	.ds 2
_current_page::
	.ds 1
_col_from::
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
;src/level.c:597: void level_load_objects(uint16_t col) NONBANKED {
;	---------------------------------
; Function level_load_objects
; ---------------------------------
_level_load_objects::
	add	sp, #-16
	ldhl	sp,	#12
	ld	(hl), e
	inc	hl
	ld	(hl), d
;src/level.c:598: uint8_t _saved_bank = _current_bank;
	ldh	a, (__current_bank + 0)
	ldhl	sp,	#4
	ld	(hl), a
;src/level.c:599: SWITCH_ROM(level_lookup_bank);
	ld	a, (_level_lookup_bank)
	ldh	(__current_bank + 0), a
	ld	(#_rROMB0),a
;src/level.c:601: for (uint16_t i = col_from; i < level_lookup_size; i++) {
	ld	a, (#_col_from)
	ldhl	sp,	#10
	ld	(hl), a
	ld	a, (#_col_from + 1)
	ldhl	sp,	#11
	ld	(hl-), a
	ld	a, (hl)
	ldhl	sp,	#14
	ld	(hl), a
	ldhl	sp,	#11
	ld	a, (hl)
	ldhl	sp,	#15
	ld	(hl), a
00125$:
	ldhl	sp,	#14
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	ld	hl, #_level_lookup_size
	ld	a, c
	sub	a, (hl)
	inc	hl
	ld	a, b
	sbc	a, (hl)
	jp	NC, 00123$
;src/level.c:602: level_object *obj = &level_lookup[i];
	ldhl	sp,#14
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	hl, #_level_lookup
	ld	a,	(hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	inc	sp
	inc	sp
;src/level.c:603: if (obj->x == col) {
	ld	e, l
	ld	d, h
	push	de
	ld	a, (de)
	ldhl	sp,	#7
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl-), a
	ld	a, (hl)
	ldhl	sp,	#12
	sub	a, (hl)
	jp	NZ, 00121$
	ldhl	sp,	#8
	ld	a, (hl)
	ldhl	sp,	#13
	sub	a, (hl)
	jp	NZ, 00121$
;src/level.c:604: if (obj->type == OBJECT_TYPE_ENEMY) {
	pop	bc
	push	bc
	inc	bc
	inc	bc
	inc	bc
	ld	a, (bc)
	ldhl	sp,	#9
	ld	(hl), a
;src/level.c:608: obj->data.enemy.type);
	pop	de
	push	de
	ld	hl, #0x0004
	add	hl, de
	ld	c, l
	ld	b, h
;src/level.c:607: (obj->y + MARGIN_TOP) * TILE_SIZE - enemiesSprites_HEIGHT,
	pop	de
	push	de
	ld	hl, #0x0002
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#12
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#11
;src/level.c:604: if (obj->type == OBJECT_TYPE_ENEMY) {
	ld	(hl-), a
	dec	hl
	ld	a, (hl)
	or	a, a
	jr	NZ, 00116$
;src/level.c:605: uint16_t relative_x = obj->x - level_page_x_offset;
	dec	hl
	dec	hl
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #_level_page_x_offset
	ld	a,	(hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, e
	sub	a, l
	ld	e, a
	ld	a, d
	sbc	a, h
	ldhl	sp,	#6
	ld	(hl-), a
	ld	(hl), e
;src/level.c:608: obj->data.enemy.type);
	ld	a, (bc)
	ldhl	sp,	#9
;src/level.c:607: (obj->y + MARGIN_TOP) * TILE_SIZE - enemiesSprites_HEIGHT,
	ld	(hl+), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	l, a
	xor	a, a
	ld	h, a
	inc	hl
	inc	hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	bc, #0xfff0
	add	hl,bc
	ld	c, l
	ld	b, h
;src/level.c:606: enemy_new(relative_x * TILE_SIZE,
	ldhl	sp,	#5
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	l, e
	ld	h, d
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	e, l
	ld	d, h
	ldhl	sp,	#9
	ld	a, (hl)
	push	af
	inc	sp
	call	_enemy_new
	jp	00126$
00116$:
;src/level.c:610: } else if (obj->type == OBJECT_TYPE_POWERUP) {
	ldhl	sp,	#9
	ld	a, (hl)
	dec	a
	jp	Z, 00126$
;src/level.c:614: obj->x * TILE_SIZE, (obj->y + MARGIN_TOP) * TILE_SIZE,
	ldhl	sp,	#7
	ld	a, (hl+)
	ld	e, (hl)
	add	a, a
	rl	e
	add	a, a
	rl	e
	add	a, a
	rl	e
	ldhl	sp,	#5
	ld	(hl+), a
	ld	(hl), e
;src/level.c:612: } else if (obj->type == OBJECT_TYPE_PLATFORM_MOVING) {
	ldhl	sp,	#9
	ld	a, (hl)
	sub	a, #0x02
	jr	NZ, 00110$
;src/level.c:616: obj->data.platform_moving.range, obj->data.platform_moving.width);
	pop	de
	push	de
	ld	hl, #0x0006
	add	hl, de
	ld	e, l
	ld	d, h
	ld	a, (de)
	ldhl	sp,	#7
	ld	(hl+), a
	ld	a, (bc)
	ld	(hl), a
;src/level.c:615: obj->data.platform_moving.platform_direction,
	pop	de
	push	de
	ld	hl, #0x0005
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
	ld	d, (hl)
	ld	a, (de)
	ldhl	sp,	#9
;src/level.c:614: obj->x * TILE_SIZE, (obj->y + MARGIN_TOP) * TILE_SIZE,
	ld	(hl+), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	(hl), a
	ld	a, (hl)
	ldhl	sp,	#2
	ld	(hl+), a
	xor	a, a
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0002
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#12
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#11
	ld	(hl), a
	ld	a, #0x03
00205$:
	ldhl	sp,	#10
	sla	(hl)
	inc	hl
	rl	(hl)
	dec	a
	jr	NZ, 00205$
	ldhl	sp,	#7
	ld	a, (hl+)
	ld	d, a
	ld	a, (hl+)
	ld	e, a
	push	de
	ld	a, (hl+)
	push	af
	inc	sp
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	ldhl	sp,	#8
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	call	_platform_moving_new
	jp	00126$
00110$:
;src/level.c:617: } else if (obj->type == OBJECT_TYPE_PLATFORM_FALLING) {
	ldhl	sp,	#9
	ld	a, (hl)
	sub	a, #0x03
	jr	NZ, 00107$
;src/level.c:619: (obj->y + MARGIN_TOP) * TILE_SIZE);
	ldhl	sp,#10
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ldhl	sp,	#8
	ld	(hl+), a
	xor	a, a
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0002
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#12
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#11
	ld	(hl), a
	ld	a, #0x03
00208$:
	ldhl	sp,	#10
	sla	(hl)
	inc	hl
	rl	(hl)
	dec	a
	jr	NZ, 00208$
;src/level.c:618: platform_falling_new(obj->x * TILE_SIZE,
	dec	hl
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	ldhl	sp,	#5
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	call	_platform_falling_new
	jr	00126$
00107$:
;src/level.c:622: pipe_new((uint8_t)obj->x, (uint8_t)obj->y, PIPE_DIRECTION_VERTICAL, &obj->data.pipe);
	pop	de
	push	de
	ld	hl, #0x0004
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#7
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#6
	ld	(hl+), a
	ld	a, (hl+)
;src/level.c:621: else if (obj->type == OBJECT_TYPE_PIPE_VERTICAL) {
	ld	(hl+), a
	ld	a, (hl)
	sub	a, #0x04
	jr	NZ, 00104$
;src/level.c:622: pipe_new((uint8_t)obj->x, (uint8_t)obj->y, PIPE_DIRECTION_VERTICAL, &obj->data.pipe);
	ldhl	sp,#10
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ldhl	sp,	#5
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	push	de
	ld	h, #0x00
	push	hl
	inc	sp
	ld	e, a
	ldhl	sp,	#11
	ld	a, (hl)
	call	_pipe_new
	jr	00126$
00104$:
;src/level.c:624: else if (obj->type == OBJECT_TYPE_PIPE_HORIZONTAL) {
	ldhl	sp,	#9
	ld	a, (hl)
	sub	a, #0x05
	jr	NZ, 00126$
;src/level.c:625: pipe_new((uint8_t)obj->x, (uint8_t)obj->y, PIPE_DIRECTION_HORIZONTAL, &obj->data.pipe);
	ldhl	sp,#10
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	(hl), a
	ldhl	sp,	#5
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	push	de
	ld	a, #0x01
	push	af
	inc	sp
	ldhl	sp,	#14
	ld	e, (hl)
	ldhl	sp,	#11
	ld	a, (hl)
	call	_pipe_new
	jr	00126$
00121$:
;src/level.c:627: } else if (obj->x > col) {
	ldhl	sp,	#12
	ld	e, l
	ld	d, h
	ldhl	sp,	#7
	ld	a, (de)
	inc	de
	sub	a, (hl)
	inc	hl
	ld	a, (de)
	sbc	a, (hl)
	jr	NC, 00126$
;src/level.c:628: col_from = i;
	ldhl	sp,	#10
	ld	a, (hl)
	ld	(#_col_from),a
	ldhl	sp,	#11
	ld	a, (hl)
	ld	(#_col_from + 1),a
;src/level.c:629: break;
	jr	00123$
00126$:
;src/level.c:601: for (uint16_t i = col_from; i < level_lookup_size; i++) {
	ldhl	sp,	#14
	inc	(hl)
	jr	NZ, 00213$
	inc	hl
	inc	(hl)
00213$:
	ldhl	sp,	#14
	ld	a, (hl)
	ldhl	sp,	#10
	ld	(hl), a
	ldhl	sp,	#15
	ld	a, (hl)
	ldhl	sp,	#11
	ld	(hl), a
	jp	00125$
00123$:
;src/level.c:633: SWITCH_ROM(_saved_bank);
	ldhl	sp,	#4
	ld	a, (hl)
	ldh	(__current_bank + 0), a
	ld	a, (hl)
	ld	(#_rROMB0),a
;src/level.c:634: }
	add	sp, #16
	ret
;src/level.c:636: uint8_t level_load_column(uint8_t nb, level *level_to_load) NONBANKED {
;	---------------------------------
; Function level_load_column
; ---------------------------------
_level_load_column::
	add	sp, #-10
	ldhl	sp,	#6
	ld	(hl), a
	ld	c, e
	ld	b, d
;src/level.c:637: uint8_t _saved_bank = _current_bank;
	ldh	a, (__current_bank + 0)
	ldhl	sp,	#0
	ld	(hl), a
;src/level.c:638: uint8_t col = 0;
	ldhl	sp,	#9
	ld	(hl), #0x00
;src/level.c:642: while (col < nb) {
	ld	hl, #0x0004
	add	hl, bc
	push	hl
	ld	a, l
	ldhl	sp,	#3
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#2
	ld	(hl+), a
	inc	bc
	inc	bc
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
	ldhl	sp,	#7
	ld	(hl), #0x00
00106$:
	ldhl	sp,	#7
	ld	a, (hl-)
	sub	a, (hl)
	jp	NC, 00108$
;src/level.c:644: if (current_column_in_page == PAGE_SIZE) {
	ld	a, (#_current_column_in_page)
	sub	a, #0x14
	jr	NZ, 00102$
;src/level.c:645: current_column_in_page = 0;
	xor	a, a
	ld	(#_current_column_in_page),a
;src/level.c:646: current_page++;
	ld	hl, #_current_page
	inc	(hl)
00102$:
;src/level.c:653: if (current_page >= level_to_load->page_count) {
	ldhl	sp,#1
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	c, a
	ld	a, (#_current_page)
	sub	a, c
	jr	C, 00104$
;src/level.c:655: SWITCH_ROM(_saved_bank);
	ldhl	sp,	#0
	ld	a, (hl)
	ldh	(__current_bank + 0), a
	ld	a, (hl)
	ld	(#_rROMB0),a
;src/level.c:656: return col;
	ldhl	sp,	#9
	ld	a, (hl)
	jp	00112$
00104$:
;src/level.c:659: const banked_map_t *page_entry = level_to_load->map_pages + current_page;
	ldhl	sp,#3
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ldhl	sp,	#8
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ld	hl, #_current_page
	ld	c, (hl)
	ld	b, #0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	ld	c, l
	ld	b, h
	ldhl	sp,	#8
	ld	a,	(hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
;src/level.c:660: SWITCH_ROM(page_entry->bank);
	ld	e, c
	ld	d, b
	inc	de
	inc	de
	ld	a, (de)
	ldh	(__current_bank + 0), a
	ld	a, (de)
	ld	(#_rROMB0),a
;src/level.c:673: current_page_data = page_entry->map;
	ld	l, c
	ld	h, b
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
;src/level.c:679: for (int row = 0; row < LEVEL_HEIGHT; row++) {
	xor	a, a
	ldhl	sp,	#8
	ld	(hl+), a
	ld	(hl), a
00110$:
	ldhl	sp,	#8
	ld	a, (hl+)
	sub	a, #0x10
	ld	a, (hl)
	sbc	a, #0x00
	jr	NC, 00105$
;src/level.c:680: uint8_t tile = current_page_data[(row * PAGE_SIZE) + current_column_in_page];
	dec	hl
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	l, e
	ld	h, d
	add	hl, hl
	add	hl, hl
	add	hl, de
	add	hl, hl
	add	hl, hl
	ld	a, (_current_column_in_page)
	ld	e, a
	ld	d, #0x00
	add	hl, de
	add	hl, bc
	ld	a, (hl)
	ldhl	sp,	#5
	ld	(hl), a
;src/level.c:681: map_buffer[row * DEVICE_SCREEN_BUFFER_WIDTH + map_column] = tile;
	ldhl	sp,	#8
	ld	e, (hl)
	ld	d, #0x00
	sla	e
	rl	d
	sla	e
	rl	d
	sla	e
	rl	d
	sla	e
	rl	d
	sla	e
	rl	d
	ld	a, (_map_column)
	ld	l, a
	ld	h, #0x00
	add	hl, de
	ld	a, l
	add	a, #<(_map_buffer)
	ld	e, a
	ld	a, h
	adc	a, #>(_map_buffer)
	ld	d, a
	ldhl	sp,	#5
	ld	a, (hl)
	ld	(de), a
;src/level.c:682: coldata[row] = tile;
	ld	de, #_coldata
	ldhl	sp,	#8
	ld	a,	(hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, de
	ld	e, l
	ld	d, h
	ldhl	sp,	#5
	ld	a, (hl)
	ld	(de), a
;src/level.c:679: for (int row = 0; row < LEVEL_HEIGHT; row++) {
	ldhl	sp,	#8
	inc	(hl)
	jr	00110$
00105$:
;src/level.c:692: set_bkg_tiles(map_column, TILE_Y, 1, LEVEL_HEIGHT, coldata);
	ld	de, #_coldata
	push	de
	ld	hl, #0x1001
	push	hl
	xor	a, a
	push	af
	inc	sp
	ld	a, (_map_column)
	push	af
	inc	sp
	call	_set_bkg_tiles
	add	sp, #6
;src/level.c:694: current_column_in_page++;
	ld	hl, #_current_column_in_page
	inc	(hl)
;src/level.c:695: col++;
	ldhl	sp,	#7
	inc	(hl)
	ld	a, (hl+)
	inc	hl
	ld	(hl), a
;src/level.c:696: map_column = (map_column + 1) % 32;
	ld	a, (_map_column)
	ld	d, #0x00
	ld	e, a
	inc	de
	ld	bc, #0x0020
	call	__modsint
	ld	hl, #_map_column
	ld	(hl), c
	jp	00106$
00108$:
;src/level.c:701: SWITCH_ROM(_saved_bank);
	ldhl	sp,	#0
	ld	a, (hl)
	ldh	(__current_bank + 0), a
	ld	a, (hl)
	ld	(#_rROMB0),a
;src/level.c:702: return col;
	ldhl	sp,	#9
	ld	a, (hl)
00112$:
;src/level.c:703: }
	add	sp, #10
	ret
;src/level.c:708: void level_set_current(void) NONBANKED {
;	---------------------------------
; Function level_set_current
; ---------------------------------
_level_set_current::
;src/level.c:709: set_level(current_level);
	ld	a, (_current_level)
	call	_set_level
;src/level.c:710: scroll_limit = DEVICE_SCREEN_PX_WIDTH_HALF;
	ld	hl, #_scroll_limit
	ld	a, #0x50
	ld	(hl+), a
;src/level.c:711: enemy_count = 0;
;src/level.c:712: platform_moving_count = 0;
	xor	a, a
	ld	(hl), a
	ld	(#_enemy_count), a
	ld	(#_platform_moving_count),a
;src/level.c:713: col_from = 0;
	xor	a, a
	ld	hl, #_col_from
	ld	(hl+), a
	ld	(hl), a
;src/level.c:714: hide_sprites_range(1, MAX_HARDWARE_SPRITES);
	ld	e, #0x28
	ld	a, #0x01
	call	_hide_sprites_range
;src/level.c:715: load_current_level();
;src/level.c:716: }
	jp	_load_current_level
;src/level.c:721: void load_current_level(void) NONBANKED {
;	---------------------------------
; Function load_current_level
; ---------------------------------
_load_current_level::
;src/level.c:722: camera_x = 0;
	xor	a, a
	ld	hl, #_camera_x
	ld	(hl+), a
	ld	(hl), a
;/home/odrevet/projects/gbdk/include/gb/gb.h:1461: SCX_REG=x, SCY_REG=y;
	xor	a, a
	ldh	(_SCX_REG + 0), a
	ld	a, #0xf0
	ldh	(_SCY_REG + 0), a
;src/level.c:724: camera_x_upscaled = 0;
	xor	a, a
	ld	hl, #_camera_x_upscaled
	ld	(hl+), a
	ld	(hl), a
;src/level.c:725: level_end_reached = false;
;src/level.c:726: current_page = 0;
	xor	a, a
	ld	(#_level_end_reached), a
	ld	(#_current_page),a
;src/level.c:727: level_page_x_offset = 0;
	xor	a, a
	ld	hl, #_level_page_x_offset
	ld	(hl+), a
	ld	(hl), a
;src/level.c:733: pipe_clear();
	call	_pipe_clear
;src/level.c:735: level_load_column(MAP_BUFFER_WIDTH, levels + current_level);
	ld	hl, #_current_level
	ld	c, (hl)
	ld	b, #0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc, #_levels
	add	hl, bc
	ld	e, l
	ld	d, h
	ld	a, #0x1b
	call	_level_load_column
;src/level.c:736: load_col_at = COLUMN_SIZE;
	ld	hl, #_load_col_at
	ld	a, #0x01
	ld	(hl+), a
	xor	a, a
	ld	(hl), a
;src/level.c:737: }
	ret
;src/level.c:742: void set_level(uint8_t level_index) NONBANKED {
;	---------------------------------
; Function set_level
; ---------------------------------
_set_level::
	dec	sp
	ld	c, a
;src/level.c:743: hud_set_level(levels[level_index].major, levels[level_index].minor);
	ld	b, #0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	a, #<(_levels)
	add	a, l
	ld	c, a
	ld	a, #>(_levels)
	adc	a, h
	ld	b, a
	ld	l, c
	ld	h, b
	inc	hl
	ld	e, (hl)
	ld	a, (bc)
	push	bc
	call	_hud_set_level
	pop	bc
;src/level.c:746: music_load(levels[level_index].music_bank, levels[level_index].music);
	ld	hl, #0x0015
	add	hl, bc
	ld	a,	(hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, c
	add	a, #0x14
	ld	e, a
	ld	a, b
	adc	a, #0x00
	ld	d, a
	ld	a, (de)
	ld	e, a
;sm83/musicmanager.h:88: music_current_track_bank = MUSIC_STOP_BANK, music_next_track = data; music_current_track_bank = bank;
	ld	a, #0xff
	ld	(_music_current_track_bank), a
	ld	a, l
	ld	(_music_next_track), a
	ld	a, h
	ld	(_music_next_track + 1), a
	ld	hl, #_music_current_track_bank
	ld	(hl), e
;src/level.c:749: uint8_t _saved_bank = _current_bank;
	ldh	a, (__current_bank + 0)
	ldhl	sp,	#0
	ld	(hl), a
;src/level.c:752: SWITCH_ROM(levels[level_index].map_tiles_bank);
	ld	hl, #0x0009
	add	hl, bc
	ld	a, (hl)
	ldh	(__current_bank + 0), a
	ld	(#_rROMB0),a
;src/level.c:753: current_map_tiles = levels[level_index].map_tiles;
	ld	hl, #0x000a
	add	hl, bc
	ld	e, l
	ld	d, h
	ld	a, (de)
	ld	hl, #_current_map_tiles
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
;src/level.c:754: current_map_tile_origin = levels[level_index].map_tile_origin;
	ld	hl, #0x000c
	add	hl, bc
	ld	a, (hl)
	ld	hl, #_current_map_tile_origin
	ld	(hl+), a
	ld	(hl), #0x00
;src/level.c:755: current_map_tile_count = levels[level_index].map_tiles_count;
	ld	hl, #0x000d
	add	hl, bc
	ld	e, l
	ld	d, h
	ld	a, (de)
	ld	hl, #_current_map_tile_count
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
;src/level.c:756: set_bkg_data(current_map_tile_origin, current_map_tile_count,
	ld	a, (_current_map_tile_count)
	ld	d, a
	ld	a, (_current_map_tile_origin)
	ld	e, a
	ld	a, (_current_map_tiles)
	ld	l, a
	ld	a, (_current_map_tiles + 1)
	ld	h, a
	push	hl
	push	de
	call	_set_bkg_data
	add	sp, #4
;src/level.c:760: current_map_width = levels[level_index].map_width;
	ld	hl, #0x0005
	add	hl, bc
	ld	e, l
	ld	d, h
	ld	a, (de)
	ld	hl, #_current_map_width
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
;src/level.c:761: current_map_width_in_tiles = levels[level_index].map_width_in_tiles;
	ld	hl, #0x0007
	add	hl, bc
	ld	e, l
	ld	d, h
	ld	a, (de)
	ld	hl, #_current_map_width_in_tiles
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
;src/level.c:764: SWITCH_ROM(levels[level_index].lookup_bank);
	ld	hl, #0x000f
	add	hl, bc
	ld	a, (hl)
	ldh	(__current_bank + 0), a
	ld	(#_rROMB0),a
;src/level.c:765: level_lookup_bank = levels[level_index].lookup_bank;
	ld	(#_level_lookup_bank),a
;src/level.c:766: level_lookup = levels[level_index].lookup;
	ld	hl, #0x0010
	add	hl, bc
	ld	e, l
	ld	d, h
	ld	a, (de)
	ld	hl, #_level_lookup
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
;src/level.c:767: level_lookup_size = levels[level_index].lookup_size;
	ld	hl, #0x0012
	add	hl, bc
	ld	e, l
	ld	d, h
	ld	a, (de)
	ld	hl, #_level_lookup_size
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
;src/level.c:769: SWITCH_ROM(_saved_bank);
	ldhl	sp,	#0
	ld	a, (hl)
	ldh	(__current_bank + 0), a
	ld	a, (hl)
	ld	(#_rROMB0),a
;src/level.c:770: }
	inc	sp
	ret
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;src/level.c:320: uint8_t get_tile(uint8_t x, uint8_t y) {
;	---------------------------------
; Function get_tile
; ---------------------------------
_get_tile::
	ld	c, a
;src/level.c:321: if (y >> 3 < 2 || y >> 3 > MAP_BUFFER_HEIGHT + 1) {
	srl	e
	srl	e
	srl	e
	ld	a, e
	sub	a, #0x02
	jr	C, 00101$
	ld	a, #0x11
	sub	a, e
	jr	NC, 00102$
00101$:
;src/level.c:322: return TILE_EMPTY;
	ld	a, #0x28
	ret
00102$:
;src/level.c:325: uint8_t tile_x = TILE_INDEX_X(x, camera_x);
	ld	b, #0x00
	ld	a, c
	ld	hl, #_camera_x
	add	a, (hl)
	inc	hl
	ld	c, a
	ld	a, b
	adc	a, (hl)
	ld	b, a
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	ld	a, c
	and	a, #0x1f
	ld	c, a
;src/level.c:326: uint8_t tile_y = TILE_INDEX_Y(y);
;src/level.c:327: return map_buffer[tile_y * DEVICE_SCREEN_BUFFER_WIDTH + tile_x];
	ld	l, e
	ld	h, #0x00
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	b, #0x00
	add	hl, bc
	ld	de, #_map_buffer
	add	hl, de
	ld	a, (hl)
;src/level.c:328: }
	ret
_levels:
	.db #0x31	;  49	'1'
	.db #0x31	;  49	'1'
	.dw _level_1_1_map
	.db #0x0f	; 15
	.dw #0x0960
	.dw #0x012c
	.byte ___bank_birabutoTileset
	.dw _birabutoTileset_tiles
	.db #0x60	; 96
	.dw #0x003c
	.byte ___bank_level_1_1_lookup
	.dw _level_1_1_lookup
	.dw #0x0014
	.byte ___bank_music_overworld
	.dw _music_overworld
	.db #0x31	;  49	'1'
	.db #0x32	;  50	'2'
	.dw _level_1_2_map
	.db #0x0e	; 14
	.dw #0x08c0
	.dw #0x0118
	.byte ___bank_birabutoTileset
	.dw _birabutoTileset_tiles
	.db #0x60	; 96
	.dw #0x003c
	.byte ___bank_level_1_2_lookup
	.dw _level_1_2_lookup
	.dw #0x0016
	.byte ___bank_music_overworld
	.dw _music_overworld
	.db #0x31	;  49	'1'
	.db #0x33	;  51	'3'
	.dw _level_1_3_map
	.db #0x11	; 17
	.dw #0x0aa0
	.dw #0x0154
	.byte ___bank_birabutoTileset
	.dw _birabutoTileset_tiles
	.db #0x60	; 96
	.dw #0x003c
	.byte ___bank_level_1_3_lookup
	.dw _level_1_3_lookup
	.dw #0x0006
	.byte ___bank_music_castle
	.dw _music_castle
	.db #0x32	;  50	'2'
	.db #0x31	;  49	'1'
	.dw _level_2_1_map
	.db #0x10	; 16
	.dw #0x0a00
	.dw #0x0140
	.byte ___bank_mudaTileset
	.dw _mudaTileset_tiles
	.db #0x60	; 96
	.dw #0x003c
	.byte ___bank_level_2_1_lookup
	.dw _level_2_1_lookup
	.dw #0x0023
	.byte ___bank_music_overworld
	.dw _music_overworld
	.db #0x32	;  50	'2'
	.db #0x32	;  50	'2'
	.dw _level_2_2_map
	.db #0x0c	; 12
	.dw #0x0780
	.dw #0x00f0
	.byte ___bank_mudaTileset
	.dw _mudaTileset_tiles
	.db #0x60	; 96
	.dw #0x003c
	.byte ___bank_level_2_2_lookup
	.dw _level_2_2_lookup
	.dw #0x001d
	.byte ___bank_music_overworld
	.dw _music_overworld
	.db #0x32	;  50	'2'
	.db #0x33	;  51	'3'
	.dw _level_2_3_map
	.db #0x13	; 19
	.dw #0x0be0
	.dw #0x017c
	.byte ___bank_mudaTileset
	.dw _mudaTileset_tiles
	.db #0x60	; 96
	.dw #0x003c
	.byte ___bank_level_2_3_lookup
	.dw _level_2_3_lookup
	.dw #0x0001
	.byte ___bank_music_underwater
	.dw _music_underwater
	.db #0x33	;  51	'3'
	.db #0x31	;  49	'1'
	.dw _level_3_1_map
	.db #0x17	; 23
	.dw #0x0e60
	.dw #0x01cc
	.byte ___bank_eastonTileset
	.dw _eastonTileset_tiles
	.db #0x60	; 96
	.dw #0x0046
	.byte ___bank_level_3_1_lookup
	.dw _level_3_1_lookup
	.dw #0x002b
	.byte ___bank_music_overworld
	.dw _music_overworld
	.db #0x33	;  51	'3'
	.db #0x32	;  50	'2'
	.dw _level_3_2_map
	.db #0x10	; 16
	.dw #0x0a00
	.dw #0x0140
	.byte ___bank_eastonTileset
	.dw _eastonTileset_tiles
	.db #0x60	; 96
	.dw #0x0046
	.byte ___bank_level_3_2_lookup
	.dw _level_3_2_lookup
	.dw #0x002c
	.byte ___bank_music_overworld
	.dw _music_overworld
	.db #0x33	;  51	'3'
	.db #0x33	;  51	'3'
	.dw _level_3_3_map
	.db #0x10	; 16
	.dw #0x0a00
	.dw #0x0140
	.byte ___bank_eastonTileset
	.dw _eastonTileset_tiles
	.db #0x60	; 96
	.dw #0x0046
	.byte ___bank_level_3_3_lookup
	.dw _level_3_3_lookup
	.dw #0x0013
	.byte ___bank_music_castle
	.dw _music_castle
	.db #0x34	;  52	'4'
	.db #0x31	;  49	'1'
	.dw _level_4_1_map
	.db #0x17	; 23
	.dw #0x0e60
	.dw #0x01cc
	.byte ___bank_chaiTileset
	.dw _chaiTileset_tiles
	.db #0x60	; 96
	.dw #0x005a
	.byte ___bank_level_4_1_lookup
	.dw _level_4_1_lookup
	.dw #0x0039
	.byte ___bank_music_overworld
	.dw _music_overworld
	.db #0x34	;  52	'4'
	.db #0x32	;  50	'2'
	.dw _level_4_2_map
	.db #0x14	; 20
	.dw #0x0c80
	.dw #0x0190
	.byte ___bank_chaiTileset
	.dw _chaiTileset_tiles
	.db #0x60	; 96
	.dw #0x005a
	.byte ___bank_level_4_2_lookup
	.dw _level_4_2_lookup
	.dw #0x0028
	.byte ___bank_music_overworld
	.dw _music_overworld
	.db #0x34	;  52	'4'
	.db #0x33	;  51	'3'
	.dw _level_4_3_map
	.db #0x18	; 24
	.dw #0x0f00
	.dw #0x01e0
	.byte ___bank_chaiTileset
	.dw _chaiTileset_tiles
	.db #0x60	; 96
	.dw #0x005a
	.byte ___bank_level_4_3_lookup
	.dw _level_4_3_lookup
	.dw #0x0001
	.byte ___bank_music_underwater
	.dw _music_underwater
_undergrounds:
	.db #0x31	;  49	'1'
	.db #0x31	;  49	'1'
	.dw _underground_0_map_pages
	.db #0x01	; 1
	.dw #0x00a0
	.dw #0x0014
	.db #0x00	; 0
	.dw #0x0000
	.db #0x00	; 0
	.dw #0x0000
	.byte ___bank_underground_lookup
	.dw _underground_0_lookup
	.dw #0x0001
	.byte ___bank_music_underground
	.dw _music_underground
;src/level.c:333: bool is_tile_solid(uint8_t tile) {
;	---------------------------------
; Function is_tile_solid
; ---------------------------------
_is_tile_solid::
	add	sp, #-4
;src/level.c:335: switch (tile) {
	ld	c, a
	sub	a, #0x29
	jr	Z, 00119$
	ld	a,c
	cp	a,#0x2a
	jr	Z, 00119$
	cp	a,#0x2b
	jr	Z, 00119$
	cp	a,#0x2c
	jr	Z, 00119$
	cp	a,#0x30
	jr	Z, 00119$
	cp	a,#0x31
	jr	Z, 00119$
	cp	a,#0x3c
	jr	Z, 00119$
	cp	a,#0x3e
	jr	Z, 00119$
	cp	a,#0x3f
	jr	Z, 00119$
	cp	a,#0x4a
	jr	Z, 00119$
	cp	a,#0x4b
	jr	Z, 00119$
	cp	a,#0x4c
	jr	Z, 00119$
	cp	a,#0x4d
	jr	Z, 00119$
	cp	a,#0x56
	jr	Z, 00119$
	cp	a,#0x57
	jr	Z, 00119$
	cp	a,#0x58
	jr	Z, 00119$
	cp	a,#0x59
	jr	Z, 00119$
	cp	a,#0x5a
	jr	Z, 00119$
	sub	a, #0x5b
	jr	NZ, 00120$
;src/level.c:354: case METAL_BLOCK_RIGHT:
00119$:
;src/level.c:355: return true;
	ld	a, #0x01
	jp	00130$
;src/level.c:356: }
00120$:
;src/level.c:362: (tile == TILED_FLOOR) || (tile == STONE_BIS_LEFT) ||
	ld	a, c
	sub	a, #0x91
	ld	a, #0x01
	jr	Z, 00758$
	xor	a, a
00758$:
	ld	b, a
	ld	a, c
	sub	a, #0x99
	ld	a, #0x01
	jr	Z, 00760$
	xor	a, a
00760$:
	ld	e, a
;src/level.c:363: (tile == STONE_BIS_RIGHT) || (tile == BRICK_BLOCK) || 
	ld	a, c
	sub	a, #0x9a
	ld	a, #0x01
	jr	Z, 00762$
	xor	a, a
00762$:
	ldhl	sp,	#0
	ld	(hl), a
	ld	a, c
	sub	a, #0x9b
	ld	a, #0x01
	jr	Z, 00764$
	xor	a, a
00764$:
	ld	d, a
;src/level.c:359: if (current_level <= LEVEL_WORLD1_END) {
	ld	a, #0x02
	ld	hl, #_current_level
	sub	a, (hl)
	jr	C, 00128$
;src/level.c:360: return ((tile == TILE_FLOOR) || (tile == TILE_FLOOR_BIS) ||
	ld	a,c
	cp	a,#0x75
	jr	Z, 00133$
;src/level.c:361: (tile == STONE_LEFT) || (tile == STONE_RIGHT) ||
	cp	a,#0x7f
	jr	Z, 00133$
	cp	a,#0x5c
	jr	Z, 00133$
	sub	a, #0x5d
	jr	Z, 00133$
;src/level.c:362: (tile == TILED_FLOOR) || (tile == STONE_BIS_LEFT) ||
	bit	0, b
	jr	NZ, 00133$
	bit	0, e
	jr	NZ, 00133$
;src/level.c:363: (tile == STONE_BIS_RIGHT) || (tile == BRICK_BLOCK) || 
	ldhl	sp,	#0
	bit	0, (hl)
	jr	NZ, 00133$
	bit	0, d
	jr	NZ, 00133$
;src/level.c:364: (tile == GREY_BLOCK));
	ld	a, c
	sub	a, #0x61
	jr	Z, 00133$
	xor	a, a
	jp	00130$
00133$:
	ld	a, #0x01
	jp	00130$
00128$:
;src/level.c:366: return ((tile == BIG_BLOCK_TOP_LEFT) || (tile == BIG_BLOCK_TOP_RIGHT) ||
	ld	a, c
	sub	a, #0x87
	ld	a, #0x01
	jr	Z, 00771$
	xor	a, a
00771$:
	ldhl	sp,	#1
	ld	(hl), a
;src/level.c:368: (tile == BIG_BLOCK_BOTTOM_RIGHT) || (tile == OCEAN_FLOOR_LEFT) ||
	ld	a, c
	sub	a, #0x88
	ld	a, #0x01
	jr	Z, 00773$
	xor	a, a
00773$:
	ldhl	sp,	#2
	ld	(hl), a
;src/level.c:369: (tile == OCEAN_FLOOR_RIGHT) || (tile == MUDA_BRIDGE) ||
	ld	a, c
	sub	a, #0x89
	ld	a, #0x01
	jr	Z, 00775$
	xor	a, a
00775$:
	ldhl	sp,	#3
	ld	(hl), a
;src/level.c:365: } else if (current_level <= LEVEL_WORLD2_END) {
	ld	a, #0x05
	ld	hl, #_current_level
	sub	a, (hl)
	jr	C, 00125$
;src/level.c:366: return ((tile == BIG_BLOCK_TOP_LEFT) || (tile == BIG_BLOCK_TOP_RIGHT) ||
	ld	a, c
	sub	a, #0x86
	jr	Z, 00157$
	ldhl	sp,	#1
	bit	0, (hl)
	jr	NZ, 00157$
;src/level.c:367: (tile == BIG_BLOCK_BOTTOM_LEFT) ||
	ld	a, c
	sub	a, #0x90
	jr	Z, 00157$
;src/level.c:368: (tile == BIG_BLOCK_BOTTOM_RIGHT) || (tile == OCEAN_FLOOR_LEFT) ||
	bit	0, b
	jr	NZ, 00157$
	inc	hl
	bit	0, (hl)
	jr	NZ, 00157$
;src/level.c:369: (tile == OCEAN_FLOOR_RIGHT) || (tile == MUDA_BRIDGE) ||
	inc	hl
	bit	0, (hl)
	jr	NZ, 00157$
	bit	0, e
	jr	NZ, 00157$
;src/level.c:370: (tile == HALF_BIG_BLOCK_TOP_LEFT) ||
	ldhl	sp,	#0
	bit	0, (hl)
	jr	NZ, 00157$
;src/level.c:371: (tile == HALF_BIG_BLOCK_TOP_RIGHT));
	bit	0, d
	jr	NZ, 00157$
	xor	a, a
	jp	00130$
00157$:
	ld	a, #0x01
	jp	00130$
00125$:
;src/level.c:373: return ((tile == EASTON_FLOOR_1) || (tile == EASTON_FLOOR_2) ||
	ld	a, c
	sub	a, #0x9c
	ld	a, #0x01
	jr	Z, 00779$
	xor	a, a
00779$:
	ld	e, a
;src/level.c:372: } else if (current_level <= LEVEL_WORLD3_END) {
	ld	a, #0x08
	ld	hl, #_current_level
	sub	a, (hl)
	jr	C, 00122$
;src/level.c:373: return ((tile == EASTON_FLOOR_1) || (tile == EASTON_FLOOR_2) ||
	ld	a, c
	sub	a, #0x9d
	jr	Z, 00181$
	bit	0, e
	jr	NZ, 00181$
;src/level.c:374: (tile == EASTON_STONE_PLATEFORM_1) ||
	ldhl	sp,	#1
	bit	0, (hl)
	jr	NZ, 00181$
;src/level.c:375: (tile == EASTON_STONE_PLATEFORM_2) ||
	bit	0, b
	jr	NZ, 00181$
;src/level.c:376: (tile == EASTON_STONE_PLATEFORM_3) ||
;src/level.c:377: (tile == EASTON_STONE_PLATEFORM_4) ||
	ld	a,c
	cp	a,#0x9e
	jr	Z, 00181$
	sub	a, #0x9f
	jr	Z, 00181$
;src/level.c:378: (tile == EASTON_STONE_PLATEFORM_BOTTOM) ||
	bit	0, d
	jr	NZ, 00181$
;src/level.c:379: (tile == EASTON_LARGE_BLACK_BLOCK_TOP_LEFT) ||
;src/level.c:380: (tile == EASTON_LARGE_BLACK_BLOCK_TOP_RIGHT) ||
	ld	a,c
	cp	a,#0x72
	jr	Z, 00181$
;src/level.c:381: (tile == EASTON_LARGE_BLACK_BLOCK_BOTOM_LEFT) ||
;src/level.c:382: (tile == EASTON_LARGE_BLACK_BLOCK_BOTTOM_RIGHT) ||
	cp	a,#0x73
	jr	Z, 00181$
	cp	a,#0x7c
	jr	Z, 00181$
;src/level.c:383: (tile == EASTON_BLOCK) || (tile == EASTON_STONE_PLATEFORM_LEFT) ||
	cp	a,#0x7d
	jr	Z, 00181$
	cp	a,#0xa0
	jr	Z, 00181$
;src/level.c:384: (tile == EASTON_STONE_PLATEFORM_RIGHT));
	cp	a,#0xa1
	jr	Z, 00181$
	sub	a, #0xa2
	jr	Z, 00181$
	xor	a, a
	jr	00130$
00181$:
	ld	a, #0x01
	jr	00130$
00122$:
;src/level.c:386: return ((tile == CHAI_FLOOR_LEFT) || (tile == CHAI_FLOOR_MIDDLE_1) ||
	ldhl	sp,	#2
	bit	0, (hl)
	jr	NZ, 00220$
	inc	hl
	bit	0, (hl)
	jr	NZ, 00220$
;src/level.c:387: (tile == CHAI_FLOOR_MIDDLE_2) ||
;src/level.c:388: (tile == CHAI_FLOOR_MIDDLE_RIGHT) || (tile == CHAI_GREY_BLOCK) ||
	ld	a,c
	cp	a,#0x8a
	jr	Z, 00220$
;src/level.c:389: (tile == CHAI_PIPE) || (tile == CHAI_PIPE_LEFT) ||
	cp	a,#0x8b
	jr	Z, 00220$
	cp	a,#0x93
	jr	Z, 00220$
;src/level.c:390: (tile == CHAI_PIPE_RIGHT) || (tile == CHAI_PIPE_BOTTOM_LEFT) ||
	cp	a,#0xaf
	jr	Z, 00220$
	cp	a,#0xb6
	jr	Z, 00220$
;src/level.c:391: (tile == CHAI_PIPE_BOTTOM_RIGHT) || (tile == CHAI_BLOCK) ||
	cp	a,#0xb7
	jr	Z, 00220$
	cp	a,#0xb8
	jr	Z, 00220$
;src/level.c:392: (tile == CHAI_BRICK_BLOCK) || (tile == CHAI_BLACK_BLOCK_LEFT) ||
	cp	a,#0xb9
	jr	Z, 00220$
	cp	a,#0x63
	jr	Z, 00220$
;src/level.c:393: (tile == CHAI_BLACK_BLOCK_RIGHT) || (tile == CHAI_FIRE_BLOCK));
	cp	a,#0x83
	jr	Z, 00220$
	cp	a,#0x96
	jr	Z, 00220$
	sub	a, #0x97
	jr	Z, 00220$
	bit	0, e
	jr	NZ, 00220$
	xor	a, a
	jr	00221$
00220$:
	ld	a, #0x01
00221$:
;src/level.c:396: return false;
00130$:
;src/level.c:397: }
	add	sp, #4
	ret
;src/level.c:402: bool is_tile_passthought(uint8_t tile_left_bottom, uint8_t tile_right_bottom) {
;	---------------------------------
; Function is_tile_passthought
; ---------------------------------
_is_tile_passthought::
	ld	c, a
;src/level.c:403: return (current_level == LEVEL_1_2 && ((tile_left_bottom == PALM_TREE_LEFT) ||
	ld	a, (#_current_level)
	dec	a
	jr	NZ, 00108$
;src/level.c:404: (tile_left_bottom == PALM_TREE_CENTER) ||
	ld	a,c
	cp	a,#0x79
	jr	Z, 00104$
;src/level.c:405: (tile_left_bottom == PALM_TREE_RIGHT) ||
	cp	a,#0x7a
	jr	Z, 00104$
	sub	a, #0x7b
	jr	Z, 00104$
;src/level.c:406: (tile_right_bottom == PALM_TREE_LEFT) ||
;src/level.c:407: (tile_right_bottom == PALM_TREE_CENTER) ||
	ld	a,e
	cp	a,#0x79
	jr	Z, 00104$
;src/level.c:408: (tile_right_bottom == PALM_TREE_RIGHT))) ||
	cp	a,#0x7a
	jr	Z, 00104$
	sub	a, #0x7b
	jr	Z, 00104$
00108$:
;src/level.c:409: (current_level == LEVEL_2_1 && ((tile_left_bottom == MUDA_PLATEFORM_LEFT) ||
	ld	a, (#_current_level)
	sub	a, #0x03
	jr	NZ, 00103$
;src/level.c:410: (tile_left_bottom == MUDA_PLATEFORM_CENTER) ||
	ld	a,c
	cp	a,#0x83
	jr	Z, 00104$
;src/level.c:411: (tile_left_bottom == MUDA_PLATEFORM_RIGHT) ||
	cp	a,#0x84
	jr	Z, 00104$
	sub	a, #0x85
	jr	Z, 00104$
;src/level.c:412: (tile_right_bottom == MUDA_PLATEFORM_LEFT) ||
;src/level.c:413: (tile_right_bottom == MUDA_PLATEFORM_CENTER) ||
	ld	a,e
	cp	a,#0x83
	jr	Z, 00104$
;src/level.c:414: (tile_right_bottom == MUDA_PLATEFORM_RIGHT)));
	cp	a,#0x84
	jr	Z, 00104$
	sub	a, #0x85
	jr	Z, 00104$
00103$:
	xor	a, a
	ret
00104$:
	ld	a, #0x01
;src/level.c:415: }
	ret
;src/level.c:420: bool is_coin(uint8_t tile) { 
;	---------------------------------
; Function is_coin
; ---------------------------------
_is_coin::
;src/level.c:421: return tile == TILE_COIN; 
	sub	a, #0x37
	ld	a, #0x01
	ret	Z
	xor	a, a
;src/level.c:422: }
	ret
;src/level.c:427: void on_get_coin_background(uint8_t x, uint8_t y) {
;	---------------------------------
; Function on_get_coin_background
; ---------------------------------
_on_get_coin_background::
;src/level.c:428: uint8_t index_x = TILE_INDEX_X(x, camera_x);
	ld	c, a
	ld	b, #0x00
	ld	a, c
	ld	hl, #_camera_x
	add	a, (hl)
	inc	hl
	ld	c, a
	ld	a, b
	adc	a, (hl)
	ld	b, a
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	ld	a, c
	and	a, #0x1f
	ld	d, a
;src/level.c:429: uint8_t index_y = TILE_INDEX_Y(y);
	srl	e
	srl	e
	srl	e
;src/level.c:431: map_buffer[index_y * DEVICE_SCREEN_BUFFER_WIDTH + index_x] = TILE_EMPTY;
	ld	l, e
	ld	h, #0x00
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	c, d
	ld	b, #0x00
	add	hl, bc
	ld	bc, #_map_buffer
	add	hl, bc
;src/level.c:432: set_bkg_tile_xy(index_x, index_y, TILE_EMPTY);
	ld	a,#0x28
	ld	(hl),a
	push	af
	inc	sp
	ld	a, d
	call	_set_bkg_tile_xy
;src/level.c:434: on_get_coin();
;src/level.c:435: }
	jp	_on_get_coin
;src/level.c:437: void on_break_tile(uint8_t x, uint8_t y) {
;	---------------------------------
; Function on_break_tile
; ---------------------------------
_on_break_tile::
;src/level.c:438: uint8_t index_x = TILE_INDEX_X(x, camera_x);
	ld	c, a
	ld	b, #0x00
	ld	a, c
	ld	hl, #_camera_x
	add	a, (hl)
	inc	hl
	ld	c, a
	ld	a, b
	adc	a, (hl)
	ld	b, a
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	ld	a, c
	and	a, #0x1f
	ld	d, a
;src/level.c:439: uint8_t index_y = TILE_INDEX_Y(y);
	srl	e
	srl	e
	srl	e
;src/level.c:441: map_buffer[index_y * DEVICE_SCREEN_BUFFER_WIDTH + index_x] = TILE_EMPTY;
	ld	l, e
	ld	h, #0x00
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	c, d
	ld	b, #0x00
	add	hl, bc
	ld	bc, #_map_buffer
	add	hl, bc
	ld	(hl), #0x28
;src/level.c:442: set_bkg_tile_xy(index_x, index_y, TILE_EMPTY);
	ld	a, #0x28
	push	af
	inc	sp
	ld	a, d
	call	_set_bkg_tile_xy
;src/level.c:447: music_play_sfx(BANK(sound_destroyed), sound_destroyed, SFX_MUTE_MASK(sound_destroyed),
	ld	c, #<(___mute_mask_sound_destroyed)
	ld	b, #<(___bank_sound_destroyed)
;sm83/musicmanager.h:105: if (music_sfx_priority > priority) return;
	ld	a, #0x04
	ld	hl, #_music_sfx_priority
	sub	a, (hl)
	ret	C
;sm83/musicmanager.h:106: sfx_play_bank = SFX_STOP_BANK;
	ld	hl, #_sfx_play_bank
	ld	(hl), #0xff
;sm83/musicmanager.h:107: music_sfx_priority = priority;
	ld	hl, #_music_sfx_priority
	ld	(hl), #0x04
;sm83/musicmanager.h:108: music_sound_cut_mask(music_mute_mask);
	ld	a, (_music_mute_mask)
;sm83/musicmanager.h:80: sfx_sound_cut_mask(mask);
	ld	e, a
;sm83/sfxplayer.h:47: if (mask & SFX_CH_1) NR12_REG = 0, NR14_REG = SFX_CH_RETRIGGER;
	rrca
	jr	NC, 00104$
	xor	a, a
	ldh	(_NR12_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR14_REG + 0), a
00104$:
;sm83/sfxplayer.h:48: if (mask & SFX_CH_2) NR22_REG = 0, NR24_REG = SFX_CH_RETRIGGER;
	bit	1, e
	jr	Z, 00106$
	xor	a, a
	ldh	(_NR22_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR24_REG + 0), a
00106$:
;sm83/sfxplayer.h:49: if (mask & SFX_CH_3) NR32_REG = 0;
	bit	2, e
	jr	Z, 00108$
	xor	a, a
	ldh	(_NR32_REG + 0), a
00108$:
;sm83/sfxplayer.h:50: if (mask & SFX_CH_4) NR42_REG = 0, NR44_REG = SFX_CH_RETRIGGER;
	bit	3, e
	jr	Z, 00110$
	xor	a, a
	ldh	(_NR42_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR44_REG + 0), a
00110$:
;sm83/sfxplayer.h:51: NR51_REG = 0xFF;
	ld	a, #0xff
	ldh	(_NR51_REG + 0), a
;sm83/musicmanager.h:109: music_mute_mask = mute_mask;
	ld	hl, #_music_mute_mask
	ld	(hl), c
;sm83/sfxplayer.h:64: sfx_play_bank = SFX_STOP_BANK, sfx_frame_skip = 0, sfx_play_sample = sample, sfx_play_bank = bank;
	ld	hl, #_sfx_play_bank
	ld	(hl), #0xff
	xor	a, a
	ld	(#_sfx_frame_skip),a
	ld	hl, #_sfx_play_sample
	ld	(hl), #<(_sound_destroyed)
	inc	hl
	ld	(hl), #>(_sound_destroyed)
	ld	hl, #_sfx_play_bank
	ld	(hl), b
;src/level.c:448: MUSIC_SFX_PRIORITY_NORMAL);
;src/level.c:450: }
	ret
;src/level.c:465: void on_block_bump(uint8_t x, uint8_t y) BANKED {
;	---------------------------------
; Function on_block_bump
; ---------------------------------
	b_on_block_bump	= 0
_on_block_bump::
	add	sp, #-3
;src/level.c:466: uint8_t index_x = TILE_INDEX_X(x, camera_x);
	ldhl	sp,	#9
	ld	c, (hl)
	ld	b, #0x00
	ld	a, c
	ld	hl, #_camera_x
	add	a, (hl)
	inc	hl
	ld	c, a
	ld	a, b
	adc	a, (hl)
	ld	b, a
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	ld	a, c
	and	a, #0x1f
	ldhl	sp,	#0
	ld	(hl), a
;src/level.c:467: uint8_t index_y = TILE_INDEX_Y(y);
	ldhl	sp,	#10
	ld	a, (hl)
	swap	a
	rlca
	and	a, #0x1f
	ldhl	sp,	#1
	ld	(hl), a
;src/level.c:469: map_buffer[index_y * DEVICE_SCREEN_BUFFER_WIDTH + index_x] = TILE_EMPTY;
	ld	a, (hl-)
	ld	c, a
	ld	b, #0x00
	ld	a, c
	add	a, a
	rl	b
	add	a, a
	rl	b
	add	a, a
	rl	b
	add	a, a
	rl	b
	add	a, a
	rl	b
	ld	e, (hl)
	ld	d, #0x00
	ld	l, a
	ld	h, b
	add	hl, de
	ld	de, #_map_buffer
	add	hl, de
	ld	(hl), #0x28
;src/level.c:470: set_bkg_tile_xy(index_x, index_y, TILE_EMPTY);
	ld	a, #0x28
	push	af
	inc	sp
	ldhl	sp,	#2
	ld	a, (hl-)
	ld	e, a
	ld	a, (hl)
	call	_set_bkg_tile_xy
;src/level.c:473: music_play_sfx(BANK(sound_bump), sound_bump, SFX_MUTE_MASK(sound_bump),
	ld	c, #<(___mute_mask_sound_bump)
	ldhl	sp,	#2
	ld	(hl), #<(___bank_sound_bump)
;sm83/musicmanager.h:105: if (music_sfx_priority > priority) return;
	ld	a, #0x04
	ld	hl, #_music_sfx_priority
	sub	a, (hl)
	jr	C, 00114$
;sm83/musicmanager.h:106: sfx_play_bank = SFX_STOP_BANK;
	ld	hl, #_sfx_play_bank
	ld	(hl), #0xff
;sm83/musicmanager.h:107: music_sfx_priority = priority;
	ld	hl, #_music_sfx_priority
	ld	(hl), #0x04
;sm83/musicmanager.h:108: music_sound_cut_mask(music_mute_mask);
	ld	a, (_music_mute_mask)
;sm83/musicmanager.h:80: sfx_sound_cut_mask(mask);
	ld	b, a
;sm83/sfxplayer.h:47: if (mask & SFX_CH_1) NR12_REG = 0, NR14_REG = SFX_CH_RETRIGGER;
	rrca
	jr	NC, 00104$
	xor	a, a
	ldh	(_NR12_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR14_REG + 0), a
00104$:
;sm83/sfxplayer.h:48: if (mask & SFX_CH_2) NR22_REG = 0, NR24_REG = SFX_CH_RETRIGGER;
	bit	1, b
	jr	Z, 00106$
	xor	a, a
	ldh	(_NR22_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR24_REG + 0), a
00106$:
;sm83/sfxplayer.h:49: if (mask & SFX_CH_3) NR32_REG = 0;
	bit	2, b
	jr	Z, 00108$
	xor	a, a
	ldh	(_NR32_REG + 0), a
00108$:
;sm83/sfxplayer.h:50: if (mask & SFX_CH_4) NR42_REG = 0, NR44_REG = SFX_CH_RETRIGGER;
	bit	3, b
	jr	Z, 00110$
	xor	a, a
	ldh	(_NR42_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR44_REG + 0), a
00110$:
;sm83/sfxplayer.h:51: NR51_REG = 0xFF;
	ld	a, #0xff
	ldh	(_NR51_REG + 0), a
;sm83/musicmanager.h:109: music_mute_mask = mute_mask;
	ld	hl, #_music_mute_mask
	ld	(hl), c
;sm83/sfxplayer.h:64: sfx_play_bank = SFX_STOP_BANK, sfx_frame_skip = 0, sfx_play_sample = sample, sfx_play_bank = bank;
	ld	hl, #_sfx_play_bank
	ld	(hl), #0xff
	xor	a, a
	ld	(#_sfx_frame_skip),a
	ld	hl, #_sfx_play_sample
	ld	a, #<(_sound_bump)
	ld	(hl+), a
	ld	(hl), #>(_sound_bump)
	ldhl	sp,	#2
	ld	a, (hl)
	ld	(#_sfx_play_bank),a
;src/level.c:474: MUSIC_SFX_PRIORITY_NORMAL);
00114$:
;src/level.c:476: uint8_t _saved_bank = _current_bank;
	ldh	a, (__current_bank + 0)
	ld	c, a
;src/level.c:477: SWITCH_ROM(BANK(commonTileset));
	ld	a, #<(___bank_commonTileset)
	ldh	(__current_bank + 0), a
	ld	(#_rROMB0),a
;src/level.c:478: set_sprite_data(90, 1, commonTileset_tiles + ((BREAKABLE_BLOCK - commonTileset_TILE_ORIGIN) * 16));
	ld	de, #(_commonTileset_tiles + 32)
	push	de
	ld	hl, #0x15a
	push	hl
	call	_set_sprite_data
	add	sp, #4
;src/level.c:479: SWITCH_ROM(_saved_bank);
	ld	a, c
	ldh	(__current_bank + 0), a
	ld	hl, #_rROMB0
	ld	(hl), c
;src/level.c:481: block_bump_state.active = true;
	ld	hl, #_block_bump_state
;src/level.c:482: block_bump_state.timer = 0;
	ld	a, #0x01
	ld	(hl+), a
	ld	(hl), #0x00
;src/level.c:483: block_bump_state.screen_x = (index_x << 3) + DEVICE_SPRITE_PX_OFFSET_X - (uint8_t)camera_x;
	ldhl	sp,	#0
	ld	a, (hl)
	add	a, a
	add	a, a
	add	a, a
	add	a, #0x08
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	ld	(#(_block_bump_state + 2)),a
;src/level.c:484: block_bump_state.screen_y_base = (index_y << 3) + 5 * TILE_SIZE;
	ldhl	sp,	#1
	ld	a, (hl)
	add	a, a
	add	a, a
	add	a, a
	add	a, #0x28
	ld	(#(_block_bump_state + 3)),a
;src/level.c:485: block_bump_state.index_x = index_x;
	ld	de, #(_block_bump_state + 4)
	ldhl	sp,	#0
;src/level.c:486: block_bump_state.index_y = index_y;
	ld	a, (hl+)
	ld	(de), a
	ld	de, #(_block_bump_state + 5)
	ld	a, (hl)
	ld	(de), a
;src/level.c:488: }
	add	sp, #3
	ret
;src/level.c:490: void block_bump_update(void) BANKED {
;	---------------------------------
; Function block_bump_update
; ---------------------------------
	b_block_bump_update	= 0
_block_bump_update::
;src/level.c:491: if (!block_bump_state.active) return;
	ld	bc, #_block_bump_state
	ld	a, (bc)
	ld	e, a
	bit	0, e
	ret	Z
;src/level.c:493: block_bump_state.timer++;
	ld	hl, #_block_bump_state + 1
	inc	(hl)
	ld	a, (hl)
;src/level.c:494: if (block_bump_state.timer >= BLOCK_BUMP_FRAMES) {
	sub	a, #0x0c
	ret	C
;src/level.c:495: block_bump_state.active = false;
	xor	a, a
	ld	(bc), a
;src/level.c:496: hide_sprite(block_bump_state.hw_sprite);
	ld	hl, #(_block_bump_state + 6)
	ld	c, (hl)
;/home/odrevet/projects/gbdk/include/gb/gb.h:2001: shadow_OAM[nb].y = 0;
	xor	a, a
	ld	l, c
	ld	h, a
	add	hl, hl
	add	hl, hl
	ld	de, #_shadow_OAM
	add	hl, de
	ld	(hl), #0x00
;src/level.c:497: map_buffer[block_bump_state.index_y * DEVICE_SCREEN_BUFFER_WIDTH + block_bump_state.index_x] = BREAKABLE_BLOCK;
	ld	hl, #(_block_bump_state + 5)
	ld	l, (hl)
	ld	h, #0x00
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	c, l
	ld	b, h
	ld	hl, #(_block_bump_state + 4)
	ld	l, (hl)
	ld	h, #0x00
	add	hl, bc
	ld	de, #_map_buffer
	add	hl, de
	ld	(hl), #0x2a
;src/level.c:498: set_bkg_tile_xy(block_bump_state.index_x, block_bump_state.index_y, BREAKABLE_BLOCK);
	ld	hl, #(_block_bump_state + 5)
	ld	c, (hl)
	ld	a, (#(_block_bump_state + 4) + 0)
	ld	h, #0x2a
	push	hl
	inc	sp
	ld	e, c
	call	_set_bkg_tile_xy
;src/level.c:500: }
	ret
;src/level.c:502: uint8_t block_bump_draw(uint8_t base_sprite) BANKED {
;	---------------------------------
; Function block_bump_draw
; ---------------------------------
	b_block_bump_draw	= 0
_block_bump_draw::
	dec	sp
;src/level.c:503: if (!block_bump_state.active) return base_sprite;
	ld	hl, #_block_bump_state
	bit	0, (hl)
	jr	NZ, 00102$
	ldhl	sp,	#7
	ld	a, (hl)
	jr	00108$
00102$:
;src/level.c:505: block_bump_state.hw_sprite = base_sprite;
	ld	de, #(_block_bump_state + 6)
	ldhl	sp,	#7
	ld	a, (hl)
	ld	(de), a
;src/level.c:508: if (block_bump_state.timer < BLOCK_BUMP_RISE) {
	ld	a, (#(_block_bump_state + 1) + 0)
;src/level.c:509: y_offset = -(block_bump_state.timer + 1) * 2;
	ld	c, a
;src/level.c:508: if (block_bump_state.timer < BLOCK_BUMP_RISE) {
	sub	a, #0x06
	jr	NC, 00104$
;src/level.c:509: y_offset = -(block_bump_state.timer + 1) * 2;
	inc	c
	xor	a, a
	sub	a, c
	ld	c, a
	sla	c
	jr	00105$
00104$:
;src/level.c:511: y_offset = -((BLOCK_BUMP_FRAMES - 1) - block_bump_state.timer) * 2;
	ld	a, #0x0b
	sub	a, c
	ld	c, a
	xor	a, a
	sub	a, c
	ld	c, a
	sla	c
00105$:
;src/level.c:514: move_sprite(base_sprite, block_bump_state.screen_x, block_bump_state.screen_y_base + y_offset);
	ld	a, (#(_block_bump_state + 3) + 0)
	add	a, c
	ldhl	sp,	#0
	ld	(hl), a
	ld	hl, #(_block_bump_state + 2)
	ld	b, (hl)
	ldhl	sp,	#7
	ld	c, (hl)
;/home/odrevet/projects/gbdk/include/gb/gb.h:1973: OAM_item_t * itm = &shadow_OAM[nb];
	ld	l, c
	ld	h, #0x00
	add	hl, hl
	add	hl, hl
	ld	e, l
	ld	d, h
	ld	hl, #_shadow_OAM
	add	hl, de
;/home/odrevet/projects/gbdk/include/gb/gb.h:1974: itm->y=y, itm->x=x;
	push	hl
	ldhl	sp,	#2
	ld	a, (hl)
	pop	hl
	ld	(hl+), a
	ld	(hl), b
;/home/odrevet/projects/gbdk/include/gb/gb.h:1887: shadow_OAM[nb].tile=tile;
	ld	hl,#_shadow_OAM + 1
	add	hl,de
	inc	hl
	ld	(hl), #0x5a
;src/level.c:517: return base_sprite + 1;
	ld	a, c
	inc	a
00108$:
;src/level.c:518: }
	inc	sp
	ret
;src/level.c:523: void on_get_coin() {
;	---------------------------------
; Function on_get_coin
; ---------------------------------
_on_get_coin::
;src/level.c:525: music_play_sfx(BANK(sound_coin), sound_coin, SFX_MUTE_MASK(sound_coin),
	ld	c, #<(___mute_mask_sound_coin)
	ld	b, #<(___bank_sound_coin)
;sm83/musicmanager.h:105: if (music_sfx_priority > priority) return;
	ld	a, #0x04
	ld	hl, #_music_sfx_priority
	sub	a, (hl)
	jr	C, 00116$
;sm83/musicmanager.h:106: sfx_play_bank = SFX_STOP_BANK;
	ld	hl, #_sfx_play_bank
	ld	(hl), #0xff
;sm83/musicmanager.h:107: music_sfx_priority = priority;
	ld	hl, #_music_sfx_priority
	ld	(hl), #0x04
;sm83/musicmanager.h:108: music_sound_cut_mask(music_mute_mask);
	ld	a, (_music_mute_mask)
;sm83/musicmanager.h:80: sfx_sound_cut_mask(mask);
	ld	e, a
;sm83/sfxplayer.h:47: if (mask & SFX_CH_1) NR12_REG = 0, NR14_REG = SFX_CH_RETRIGGER;
	rrca
	jr	NC, 00106$
	xor	a, a
	ldh	(_NR12_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR14_REG + 0), a
00106$:
;sm83/sfxplayer.h:48: if (mask & SFX_CH_2) NR22_REG = 0, NR24_REG = SFX_CH_RETRIGGER;
	bit	1, e
	jr	Z, 00108$
	xor	a, a
	ldh	(_NR22_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR24_REG + 0), a
00108$:
;sm83/sfxplayer.h:49: if (mask & SFX_CH_3) NR32_REG = 0;
	bit	2, e
	jr	Z, 00110$
	xor	a, a
	ldh	(_NR32_REG + 0), a
00110$:
;sm83/sfxplayer.h:50: if (mask & SFX_CH_4) NR42_REG = 0, NR44_REG = SFX_CH_RETRIGGER;
	bit	3, e
	jr	Z, 00112$
	xor	a, a
	ldh	(_NR42_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR44_REG + 0), a
00112$:
;sm83/sfxplayer.h:51: NR51_REG = 0xFF;
	ld	a, #0xff
	ldh	(_NR51_REG + 0), a
;sm83/musicmanager.h:109: music_mute_mask = mute_mask;
	ld	hl, #_music_mute_mask
	ld	(hl), c
;sm83/sfxplayer.h:64: sfx_play_bank = SFX_STOP_BANK, sfx_frame_skip = 0, sfx_play_sample = sample, sfx_play_bank = bank;
	ld	hl, #_sfx_play_bank
	ld	(hl), #0xff
	xor	a, a
	ld	(#_sfx_frame_skip),a
	ld	hl, #_sfx_play_sample
	ld	a, #<(_sound_coin)
	ld	(hl+), a
	ld	(hl), #>(_sound_coin)
	ld	hl, #_sfx_play_bank
	ld	(hl), b
;src/level.c:526: MUSIC_SFX_PRIORITY_NORMAL);
00116$:
;src/level.c:529: coins++;
	ld	hl, #_coins
	inc	(hl)
;src/level.c:530: score += 10;
	ld	a, (_score)
	ld	hl, #_score + 1
	ld	b, (hl)
	dec	hl
	add	a, #0x0a
	ld	c, a
	ld	a, b
	adc	a, #0x00
	ld	(hl), c
	inc	hl
	ld	(hl), a
;src/level.c:532: if (coins == 100) {
	ld	a, (#_coins)
	sub	a, #0x64
	jr	NZ, 00102$
;src/level.c:533: lives++;
	ld	hl, #_lives
	inc	(hl)
;src/level.c:534: hud_update_lives();
	call	_hud_update_lives
;src/level.c:535: coins = 0;
	xor	a, a
	ld	(#_coins),a
;src/level.c:537: music_play_sfx(BANK(sound_oneup), sound_oneup, SFX_MUTE_MASK(sound_oneup),
	ld	c, #<(___mute_mask_sound_oneup)
	ld	b, #<(___bank_sound_oneup)
;sm83/musicmanager.h:105: if (music_sfx_priority > priority) return;
	ld	a, #0x04
	ld	hl, #_music_sfx_priority
	sub	a, (hl)
	jr	C, 00102$
;sm83/musicmanager.h:106: sfx_play_bank = SFX_STOP_BANK;
	ld	hl, #_sfx_play_bank
	ld	(hl), #0xff
;sm83/musicmanager.h:107: music_sfx_priority = priority;
	ld	hl, #_music_sfx_priority
	ld	(hl), #0x04
;sm83/musicmanager.h:108: music_sound_cut_mask(music_mute_mask);
	ld	a, (_music_mute_mask)
;sm83/musicmanager.h:80: sfx_sound_cut_mask(mask);
	ld	e, a
;sm83/sfxplayer.h:47: if (mask & SFX_CH_1) NR12_REG = 0, NR14_REG = SFX_CH_RETRIGGER;
	rrca
	jr	NC, 00120$
	xor	a, a
	ldh	(_NR12_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR14_REG + 0), a
00120$:
;sm83/sfxplayer.h:48: if (mask & SFX_CH_2) NR22_REG = 0, NR24_REG = SFX_CH_RETRIGGER;
	bit	1, e
	jr	Z, 00122$
	xor	a, a
	ldh	(_NR22_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR24_REG + 0), a
00122$:
;sm83/sfxplayer.h:49: if (mask & SFX_CH_3) NR32_REG = 0;
	bit	2, e
	jr	Z, 00124$
	xor	a, a
	ldh	(_NR32_REG + 0), a
00124$:
;sm83/sfxplayer.h:50: if (mask & SFX_CH_4) NR42_REG = 0, NR44_REG = SFX_CH_RETRIGGER;
	bit	3, e
	jr	Z, 00126$
	xor	a, a
	ldh	(_NR42_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR44_REG + 0), a
00126$:
;sm83/sfxplayer.h:51: NR51_REG = 0xFF;
	ld	a, #0xff
	ldh	(_NR51_REG + 0), a
;sm83/musicmanager.h:109: music_mute_mask = mute_mask;
	ld	hl, #_music_mute_mask
	ld	(hl), c
;sm83/sfxplayer.h:64: sfx_play_bank = SFX_STOP_BANK, sfx_frame_skip = 0, sfx_play_sample = sample, sfx_play_bank = bank;
	ld	hl, #_sfx_play_bank
	ld	(hl), #0xff
	xor	a, a
	ld	(#_sfx_frame_skip),a
	ld	hl, #_sfx_play_sample
	ld	a, #<(_sound_oneup)
	ld	(hl+), a
	ld	(hl), #>(_sound_oneup)
	ld	hl, #_sfx_play_bank
	ld	(hl), b
;src/level.c:538: MUSIC_SFX_PRIORITY_NORMAL);
00102$:
;src/level.c:542: hud_update_coins();
	call	_hud_update_coins
;src/level.c:543: hud_update_score();
;src/level.c:544: }
	jp	_hud_update_score
;src/level.c:549: void on_interogation_block_hit(uint8_t x, uint8_t y) {
;	---------------------------------
; Function on_interogation_block_hit
; ---------------------------------
_on_interogation_block_hit::
	add	sp, #-11
;src/level.c:551: uint8_t index_x = TILE_INDEX_X(x, camera_x);
	ld	c, a
	ld	b, #0x00
	ld	a, c
	ld	hl, #_camera_x
	add	a, (hl)
	inc	hl
	ld	c, a
	ld	a, b
	adc	a, (hl)
	ld	b, a
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	ld	a, c
	and	a, #0x1f
	ldhl	sp,	#0
;src/level.c:552: uint8_t index_y = TILE_INDEX_Y(y);
	ld	(hl+), a
	ld	a, e
	swap	a
	rlca
	and	a, #0x1f
;src/level.c:555: uint8_t world_tile_x = (x + camera_x) >> 3;
	ld	(hl+), a
;src/level.c:558: map_buffer[index_y * DEVICE_SCREEN_BUFFER_WIDTH + index_x] = TILE_EMPTIED;
	ld	a, c
	ld	(hl-), a
	ld	c, (hl)
	ld	b, #0x00
	ldhl	sp,	#9
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
	ld	a, #0x05
00156$:
	ldhl	sp,	#9
	sla	(hl)
	inc	hl
	rl	(hl)
	dec	a
	jr	NZ, 00156$
	ldhl	sp,	#0
	ld	e, (hl)
	ld	d, #0x00
	ldhl	sp,	#9
	ld	a,	(hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, de
	ld	e, l
	ld	d, h
	ld	hl, #_map_buffer
	add	hl, de
	ld	(hl), #0x29
;src/level.c:561: set_bkg_tile_xy(index_x, index_y, TILE_EMPTIED);
	push	bc
	ld	a, #0x29
	push	af
	inc	sp
	ldhl	sp,	#4
	ld	a, (hl-)
	ld	e, a
	ld	a, (hl)
	call	_set_bkg_tile_xy
	pop	bc
;src/level.c:567: uint8_t _saved_bank = _current_bank;
	ldh	a, (__current_bank + 0)
	ldhl	sp,	#3
	ld	(hl), a
;src/level.c:568: SWITCH_ROM(level_lookup_bank);
	ld	a, (_level_lookup_bank)
	ldh	(__current_bank + 0), a
	ld	(#_rROMB0),a
;src/level.c:571: bool lookup_found = FALSE;
	ldhl	sp,	#4
	ld	(hl), #0x00
;src/level.c:572: for (uint16_t i = 0; i < level_lookup_size && !lookup_found; i++) {
	sla	c
	rl	b
	sla	c
	rl	b
	sla	c
	rl	b
	ldhl	sp,	#9
	ld	a, c
	ld	(hl+), a
	ld	a, b
	ld	(hl-), a
	ld	a, (hl)
	ldhl	sp,	#5
	ld	(hl+), a
	ld	(hl), #0x00
	ld	a, #0x04
00158$:
	ldhl	sp,	#5
	sla	(hl)
	inc	hl
	rl	(hl)
	dec	a
	jr	NZ, 00158$
	ldhl	sp,	#9
	ld	(hl+), a
	ld	(hl), a
00109$:
	ldhl	sp,	#9
	ld	a, (hl-)
	dec	hl
	ld	(hl), a
	ldhl	sp,	#10
	ld	a, (hl-)
	dec	hl
	ld	(hl), a
	ldhl	sp,	#7
	ld	e, l
	ld	d, h
	ld	hl, #_level_lookup_size
	ld	a, (de)
	inc	de
	sub	a, (hl)
	inc	hl
	ld	a, (de)
	sbc	a, (hl)
	jr	NC, 00104$
	ldhl	sp,	#4
	bit	0, (hl)
	jr	NZ, 00104$
;src/level.c:573: level_object *obj = &level_lookup[i];
	ldhl	sp,#9
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	push	hl
	ld	a, l
	ldhl	sp,	#9
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#8
	ld	(hl), a
	ld	hl, #_level_lookup
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ldhl	sp,	#7
	ld	a,	(hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, de
	ld	c, l
	ld	b, h
;src/level.c:575: if (obj->x == world_tile_x && obj->y == index_y) {
	ld	e, c
	ld	d, b
	ld	a, (de)
	ldhl	sp,	#7
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ldhl	sp,	#2
	ld	e, (hl)
	ld	d, #0x00
	ldhl	sp,	#7
	ld	a, (hl)
	sub	a, e
	jr	NZ, 00110$
	inc	hl
	ld	a, (hl)
	sub	a, d
	jr	NZ, 00110$
	ld	l, c
	ld	h, b
	inc	hl
	inc	hl
	ld	e, (hl)
	ldhl	sp,	#1
	ld	a, (hl)
	sub	a, e
	jr	NZ, 00110$
;src/level.c:576: lookup_found = TRUE;
	ldhl	sp,	#4
	ld	(hl), #0x01
;src/level.c:577: powerup_new((index_x << 3) << 4, (index_y << 3) << 4, obj->data.enemy.type);
	ld	hl, #0x0004
	add	hl, bc
	ld	d, (hl)
	ldhl	sp,	#5
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	ldhl	sp,	#0
	ld	e, (hl)
	xor	a, a
	ld	l, e
	ld	h, a
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	push	de
	inc	sp
	ld	e, l
	ld	d, h
	call	_powerup_new
00110$:
;src/level.c:572: for (uint16_t i = 0; i < level_lookup_size && !lookup_found; i++) {
	ldhl	sp,	#9
	inc	(hl)
	jp	NZ, 00109$
	inc	hl
	inc	(hl)
	jp	00109$
00104$:
;src/level.c:581: SWITCH_ROM(_saved_bank);
	ldhl	sp,	#3
	ld	a, (hl)
	ldh	(__current_bank + 0), a
	ld	a, (hl)
	ld	(#_rROMB0),a
;src/level.c:584: if (lookup_found == FALSE) {
	ldhl	sp,	#4
	bit	0, (hl)
	jr	NZ, 00111$
;src/level.c:585: on_get_coin();
	call	_on_get_coin
;src/level.c:586: coin_animated_new(index_x, index_y);
	ldhl	sp,	#1
	ld	a, (hl-)
	ld	e, a
	ld	a, (hl)
	call	_coin_animated_new
00111$:
;src/level.c:588: }
	add	sp, #11
	ret
	.area _CODE
	.area _INITIALIZER
__xinit__map_buffer:
	.db #0x28	; 40
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
__xinit__map_column:
	.db #0x00	; 0
__xinit__current_column_in_page:
	.db #0x00	; 0
__xinit__level_page_x_offset:
	.dw #0x0000
__xinit__current_page:
	.db #0x00	; 0
__xinit__col_from:
	.dw #0x0000
	.area _CABS (ABS)
