;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler
; Version 4.5.1 #15267 (Linux)
;--------------------------------------------------------
	.module player
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _EMU_printf
	.globl b___func_player
	.globl ___func_player
	.globl _level_set_current
	.globl _level_load_column
	.globl _level_load_objects
	.globl _on_interogation_block_hit
	.globl b_on_block_bump
	.globl _on_block_bump
	.globl _on_break_tile
	.globl _on_get_coin_background
	.globl _is_coin
	.globl _is_tile_solid
	.globl _is_tile_passthought
	.globl _get_tile
	.globl b_enemy_reset_all
	.globl _enemy_reset_all
	.globl _pipe_clear
	.globl _hide_sprites_range
	.globl _vsync
	.globl _delay
	.globl _player_is_big
	.globl _frame_counter
	.globl _player_frame
	.globl _current_jump
	.globl _touch_ground
	.globl _is_jumping
	.globl _plane_mode
	.globl _tile_next_2
	.globl _tile_next_1
	.globl _scroll_limit
	.globl _marioSpritesflip
	.globl _display_walk_animation
	.globl _display_slide_frame
	.globl _display_jump_frame
	.globl _vel_y
	.globl _vel_x
	.globl _player_draw_y
	.globl _player_draw_x
	.globl _player_y_next
	.globl _player_x_next
	.globl _player_y
	.globl _player_x
	.globl _player_y_next_upscaled
	.globl _player_x_next_upscaled
	.globl _player_y_upscaled
	.globl _player_x_upscaled
	.globl _joypad_current
	.globl _joypad_previous
	.globl _lives
	.globl _time
	.globl _score
	.globl _coins
	.globl _update_frame_counter
	.globl _player_draw
	.globl _player_check_pipe_entry
	.globl _player_enter_pipe
	.globl _player_check_horizontal_pipe_entry
	.globl _player_warp_to
	.globl b_player_move
	.globl _player_move
	.globl b_player_move_vehicle
	.globl _player_move_vehicle
	.globl _player_on_touch_ground
	.globl b_player_is_on_platform
	.globl _player_is_on_platform
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area _HRAM
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_coins::
	.ds 1
_score::
	.ds 2
_time::
	.ds 2
_lives::
	.ds 1
_joypad_previous::
	.ds 1
_joypad_current::
	.ds 1
_player_x_upscaled::
	.ds 2
_player_y_upscaled::
	.ds 2
_player_x_next_upscaled::
	.ds 2
_player_y_next_upscaled::
	.ds 2
_player_x::
	.ds 2
_player_y::
	.ds 2
_player_x_next::
	.ds 2
_player_y_next::
	.ds 2
_player_draw_x::
	.ds 1
_player_draw_y::
	.ds 1
_vel_x::
	.ds 1
_vel_y::
	.ds 1
_display_jump_frame::
	.ds 1
_display_slide_frame::
	.ds 1
_display_walk_animation::
	.ds 1
_marioSpritesflip::
	.ds 1
_scroll_limit::
	.ds 2
_tile_next_1::
	.ds 1
_tile_next_2::
	.ds 1
_plane_mode::
	.ds 1
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
___EMU_PROFILER_INIT:
	.ds 2
_is_jumping::
	.ds 1
_touch_ground::
	.ds 1
_current_jump::
	.ds 2
_player_frame::
	.ds 1
_frame_counter::
	.ds 1
_player_is_big::
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
;src/player.c:78: void update_frame_counter(void) NONBANKED {
;	---------------------------------
; Function update_frame_counter
; ---------------------------------
_update_frame_counter::
;src/player.c:79: frame_counter++;
	ld	hl, #_frame_counter
	inc	(hl)
;src/player.c:80: if (frame_counter == LOOP_PER_ANIMATION_FRAME) {
	ld	a, (hl)
	sub	a, #0x05
	ret	NZ
;src/player.c:81: frame_counter = 0;
	xor	a, a
	ld	(#_frame_counter),a
;src/player.c:82: player_frame = (player_frame % 3) + 1;
	ld	a, (_player_frame)
	ld	e, #0x03
	call	__moduchar
	ld	a, c
	inc	a
	ld	(#_player_frame),a
;src/player.c:84: }
	ret
;src/player.c:86: uint8_t player_draw(uint8_t base_sprite) NONBANKED {
;	---------------------------------
; Function player_draw
; ---------------------------------
_player_draw::
	add	sp, #-4
	ldhl	sp,	#0
;src/player.c:87: uint8_t _saved_bank = _current_bank;
	ld	(hl+), a
	ldh	a, (__current_bank + 0)
	ld	(hl), a
;src/player.c:88: SWITCH_ROM(BANK(marioSprites));
	ld	a, #<(___bank_marioSprites)
	ldh	(__current_bank + 0), a
	ld	(#_rROMB0),a
;src/player.c:90: uint8_t frame_index = player_is_big ? player_frame + 7 : player_frame;
	ld	hl, #_player_is_big
	bit	0, (hl)
	jr	Z, 00108$
	ld	a, (_player_frame)
	add	a, #0x07
	jr	00109$
00108$:
	ld	a, (_player_frame)
00109$:
;src/player.c:91: const metasprite_t *const marioSprites_metasprite =
	ld	l, a
	ld	bc, #_marioSprites_metasprites+0
	ld	h, #0x00
	add	hl, hl
	add	hl, bc
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
;src/player.c:95: player_draw_x, player_draw_y);
	ld	a, (_player_draw_y)
	ld	hl, #_player_draw_x
	ld	e, (hl)
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:200: __current_metasprite = metasprite;
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:203: return __move_metasprite_flipx(base_sprite, (y << 8) | (uint8_t)(x - 8u));
	ldhl	sp,	#3
	ld	(hl-), a
	ld	(hl), #0x00
;src/player.c:93: if (marioSpritesflip) {
	ld	hl, #_marioSpritesflip
	bit	0, (hl)
	jr	Z, 00102$
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:200: __current_metasprite = metasprite;
	ld	hl, #___current_metasprite
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:201: __current_base_tile = base_tile;
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:202: __current_base_prop = base_prop;
	xor	a, a
	ld	(#___current_base_tile), a
	ld	(#___current_base_prop),a
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:203: return __move_metasprite_flipx(base_sprite, (y << 8) | (uint8_t)(x - 8u));
	ld	a, e
	add	a, #0xf8
	ld	e, a
	ldhl	sp,	#3
	ld	d, (hl)
	xor	a, a
	call	___move_metasprite_flipx
;src/player.c:95: player_draw_x, player_draw_y);
	ldhl	sp,	#0
	add	a, (hl)
	ld	c, a
	jr	00103$
00102$:
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:160: __current_metasprite = metasprite;
	ld	hl, #___current_metasprite
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:161: __current_base_tile = base_tile;
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:162: __current_base_prop = base_prop;
	xor	a, a
	ld	(#___current_base_tile), a
	ld	(#___current_base_prop),a
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:163: return __move_metasprite(base_sprite, (y << 8) | (uint8_t)x);
	ldhl	sp,	#3
	ld	d, (hl)
	xor	a, a
	call	___move_metasprite
;src/player.c:98: player_draw_x, player_draw_y);
	ldhl	sp,	#0
	add	a, (hl)
	ld	c, a
00103$:
;src/player.c:101: SWITCH_ROM(_saved_bank);
	ldhl	sp,	#1
	ld	a, (hl)
	ldh	(__current_bank + 0), a
	ld	a, (hl)
	ld	(#_rROMB0),a
;src/player.c:103: return base_sprite;
	ld	a, c
;src/player.c:104: }
	add	sp, #4
	ret
;src/player.c:108: bool player_check_pipe_entry(void) NONBANKED {
;	---------------------------------
; Function player_check_pipe_entry
; ---------------------------------
_player_check_pipe_entry::
;src/player.c:109: if (!touch_ground || !(joypad_current & J_DOWN) ||
	ld	hl, #_touch_ground
	bit	0, (hl)
	jr	Z, 00101$
	ld	a, (_joypad_current)
	bit	3, a
	jr	Z, 00101$
;src/player.c:110: (joypad_previous & J_DOWN)) {
	ld	a, (_joypad_previous)
	bit	3, a
	jr	Z, 00102$
00101$:
;src/player.c:111: return FALSE;
	xor	a, a
	ret
00102$:
;src/player.c:113: if (!pipe_active || active_pipe_direction != PIPE_DIRECTION_VERTICAL) {
	ld	hl, #_pipe_active
	bit	0, (hl)
	jr	Z, 00105$
	ld	a, (#_active_pipe_direction)
	or	a, a
	jr	Z, 00106$
00105$:
;src/player.c:114: return FALSE;
	xor	a, a
	ret
00106$:
;src/player.c:117: uint8_t player_tile_x = player_x >> 3;
	ld	a, (_player_x)
	ld	e, a
	ld	hl, #_player_x + 1
	ld	c, (hl)
	srl	c
	rr	e
	srl	c
	rr	e
	srl	c
	rr	e
;src/player.c:118: uint8_t player_tile_y = player_y >> 3;
	ld	hl, #_player_y
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
;src/player.c:120: if ((player_tile_x == active_pipe_tile_x ||
	ld	a, (#_active_pipe_tile_x)
	sub	a, e
	jr	Z, 00111$
;src/player.c:121: player_tile_x == active_pipe_tile_x + 1) &&
	ld	a, (_active_pipe_tile_x)
	ld	l, a
	ld	h, #0x00
	inc	hl
	ld	b, #0x00
	ld	a, l
	sub	a, e
	jr	NZ, 00109$
	ld	a, h
	sub	a, b
	jr	NZ, 00109$
00111$:
;src/player.c:122: player_tile_y + 2 == active_pipe_tile_y) {
	xor	a, a
	ld	b, a
	inc	bc
	inc	bc
	ld	a, (_active_pipe_tile_y)
	ld	e, a
	ld	d, #0x00
	ld	a, e
	sub	a, c
	jr	NZ, 00109$
	ld	a, d
	sub	a, b
	jr	NZ, 00109$
;src/player.c:123: player_enter_pipe(&active_pipe);
	ld	de, #_active_pipe
	call	_player_enter_pipe
;src/player.c:124: return TRUE;
	ld	a, #0x01
	ret
00109$:
;src/player.c:126: return FALSE;
	xor	a, a
;src/player.c:127: }
	ret
;src/player.c:129: void player_enter_pipe(pipe_params *pipe) NONBANKED {
;	---------------------------------
; Function player_enter_pipe
; ---------------------------------
_player_enter_pipe::
	add	sp, #-12
	ld	c, e
	ld	b, d
;src/player.c:130: uint8_t _saved_bank = _current_bank;
	ldh	a, (__current_bank + 0)
	ldhl	sp,	#0
	ld	(hl), a
;src/player.c:131: SWITCH_ROM(pipe->destination_level->lookup_bank);
	ld	hl, #0x0003
	add	hl, bc
	push	hl
	ld	a, l
	ldhl	sp,	#3
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#2
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	l, a
	inc	de
	ld	a, (de)
	ld	h, a
	ld	de, #0x000f
	add	hl, de
	ld	a, (hl)
	ldh	(__current_bank + 0), a
	ldhl	sp,#1
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	l, a
	inc	de
	ld	a, (de)
	ld	h, a
	ld	de, #0x000f
	add	hl, de
	ld	a, (hl)
	ld	(#_rROMB0),a
;src/player.c:132: level_lookup_bank = pipe->destination_level->lookup_bank;
	ldhl	sp,#1
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	l, a
	inc	de
	ld	a, (de)
	ld	h, a
	ld	de, #0x000f
	add	hl, de
	ld	a, (hl)
	ld	(#_level_lookup_bank),a
;src/player.c:133: level_lookup = pipe->destination_level->lookup;
	ldhl	sp,#1
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	l, a
	inc	de
	ld	a, (de)
	ld	h, a
	ld	de, #0x0010
	add	hl, de
	ld	e, l
	ld	d, h
	ld	a, (de)
	ld	hl, #_level_lookup
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
;src/player.c:134: level_lookup_size = pipe->destination_level->lookup_size;
	ldhl	sp,#1
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	l, a
	inc	de
	ld	a, (de)
	ld	h, a
	ld	de, #0x0012
	add	hl, de
	ld	e, l
	ld	d, h
	ld	a, (de)
	ld	hl, #_level_lookup_size
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
;src/player.c:135: SWITCH_ROM(_saved_bank);
	ldhl	sp,	#0
	ld	a, (hl)
	ldh	(__current_bank + 0), a
	ld	a, (hl)
	ld	(#_rROMB0),a
;src/player.c:138: uint8_t frame_index = player_is_big ? player_frame + 7 : player_frame;
	ld	hl, #_player_is_big
	bit	0, (hl)
	jr	Z, 00137$
	ld	a, (_player_frame)
	add	a, #0x07
	jr	00138$
00137$:
	ld	a, (_player_frame)
00138$:
	ld	e, a
;src/player.c:139: SWITCH_ROM(BANK(marioSprites));
	ld	a, #<(___bank_marioSprites)
	ldh	(__current_bank + 0), a
	ld	(#_rROMB0),a
;src/player.c:147: move_metasprite_ex(marioSprites_metasprites[frame_index], 0, S_PRIORITY,
	xor	a, a
	sla	e
	adc	a, a
	ldhl	sp,	#3
	ld	(hl), e
	inc	hl
	ld	(hl), a
;src/player.c:141: if (active_pipe_direction == PIPE_DIRECTION_VERTICAL) {
	ld	a, (#_active_pipe_direction)
	or	a, a
	jp	NZ, 00109$
;src/player.c:142: for (uint8_t i = 0; i < 24; i++) {
	ldhl	sp,	#11
	ld	(hl), #0x00
00130$:
	ldhl	sp,	#11
	ld	a, (hl)
	sub	a, #0x18
	jp	NC, 00110$
;src/player.c:143: player_y_upscaled += 16;
	ld	a, (_player_y_upscaled)
	ld	hl, #_player_y_upscaled + 1
	ld	d, (hl)
	dec	hl
	add	a, #0x10
	ld	e, a
	ld	a, d
	adc	a, #0x00
	ld	(hl), e
	inc	hl
;src/player.c:144: player_y = player_y_upscaled >> 4;
	ld	(hl-), a
	ld	a, (hl)
	ld	(#_player_y),a
	ld	a, (#_player_y_upscaled + 1)
	ld	hl, #_player_y + 1
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
;src/player.c:145: player_draw_y = player_y + DEVICE_SPRITE_PX_OFFSET_Y + MARGIN_TOP_PX +
	ld	a, (hl)
	add	a, #0x28
	ld	hl, #_player_draw_y
	ld	(hl), a
;src/player.c:148: 0, player_draw_x, player_draw_y);
	ld	a, (hl)
	ldhl	sp,	#7
	ld	(hl), a
	ld	a, (#_player_draw_x)
	ldhl	sp,	#8
	ld	(hl), a
;src/player.c:147: move_metasprite_ex(marioSprites_metasprites[frame_index], 0, S_PRIORITY,
	ld	de, #_marioSprites_metasprites
	ldhl	sp,	#3
	ld	a,	(hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#11
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#10
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	l, a
	inc	de
	ld	a, (de)
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:160: __current_metasprite = metasprite;
	ld	e, l
	ld	d, a
	ld	hl, #___current_metasprite
	ld	a, e
	ld	(hl+), a
	ld	(hl), d
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:161: __current_base_tile = base_tile;
	xor	a, a
	ld	(#___current_base_tile),a
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:162: __current_base_prop = base_prop;
	ld	hl, #___current_base_prop
	ld	(hl), #0x80
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:163: return __move_metasprite(base_sprite, (y << 8) | (uint8_t)x);
	ldhl	sp,	#7
	ld	e, (hl)
	ldhl	sp,	#10
	ld	a, e
	ld	(hl-), a
	xor	a, a
	ld	(hl-), a
	ld	a, (hl+)
	inc	hl
	ld	e, a
	ld	d, (hl)
	push	bc
	xor	a, a
	call	___move_metasprite
	pop	bc
;src/player.c:149: vsync();
	call	_vsync
;src/player.c:142: for (uint8_t i = 0; i < 24; i++) {
	ldhl	sp,	#11
	inc	(hl)
	jp	00130$
00109$:
;src/player.c:151: } else if (active_pipe_direction == PIPE_DIRECTION_HORIZONTAL) {
	ld	a, (#_active_pipe_direction)
	dec	a
	jp	NZ, 00110$
;src/player.c:152: int8_t dir = (vel_x > 0) ? 1 : -1;
	ld	hl, #_vel_x
	ld	e, (hl)
	xor	a, a
	ld	d, a
	sub	a, (hl)
	bit	7, e
	jr	Z, 00244$
	bit	7, d
	jr	NZ, 00245$
	cp	a, a
	jr	00245$
00244$:
	bit	7, d
	jr	Z, 00245$
	scf
00245$:
	jr	NC, 00139$
	ld	a, #0x01
	jr	00140$
00139$:
	ld	a, #0xff
00140$:
	ldhl	sp,	#5
	ld	(hl), a
;src/player.c:153: for (uint8_t i = 0; i < 24; i++) {
	ldhl	sp,	#11
	ld	(hl), #0x00
00133$:
	ldhl	sp,	#11
	ld	a, (hl)
	sub	a, #0x18
	jp	NC, 00110$
;src/player.c:154: player_x_upscaled += dir * 16;
	ldhl	sp,	#5
	ld	a, (hl)
	ld	e, a
	rlca
	sbc	a, a
	ld	l, e
	ld	h, a
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	a, (_player_x_upscaled)
	push	hl
	ld	hl, #_player_x_upscaled + 1
	ld	d, (hl)
	pop	hl
	add	a, l
	ld	e, a
	ld	a, d
	adc	a, h
	ld	hl, #_player_x_upscaled
	ld	(hl), e
	inc	hl
;src/player.c:155: player_x = player_x_upscaled >> 4;
	ld	(hl-), a
	ld	a, (hl)
	ld	(#_player_x),a
	ld	a, (#_player_x_upscaled + 1)
	ld	hl, #_player_x + 1
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
;src/player.c:156: player_draw_x = player_x + DEVICE_SPRITE_PX_OFFSET_X +
	ld	a, (hl)
	add	a, #0x0c
;src/player.c:157: PLAYER_DRAW_OFFSET_X - camera_x;
	ld	hl, #_camera_x
	ld	e, (hl)
	sub	a, e
	ld	hl, #_player_draw_x
	ld	(hl), a
;src/player.c:148: 0, player_draw_x, player_draw_y);
	ld	a, (_player_draw_y)
	ld	e, a
	ld	a, (hl)
	ldhl	sp,	#6
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:203: return __move_metasprite_flipx(base_sprite, (y << 8) | (uint8_t)(x - 8u));
	ld	(hl+), a
	inc	hl
	ld	a, e
	ld	(hl-), a
	ld	(hl), #0x00
;src/player.c:158: if (marioSpritesflip) {
	ld	hl, #_marioSpritesflip
	bit	0, (hl)
	jr	Z, 00103$
;src/player.c:159: move_metasprite_flipx(marioSprites_metasprites[frame_index], 0,
	ld	de, #_marioSprites_metasprites
	ldhl	sp,	#3
	ld	a,	(hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#11
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#10
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	l, a
	inc	de
	ld	a, (de)
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:200: __current_metasprite = metasprite;
	ld	e, l
	ld	d, a
	ld	hl, #___current_metasprite
	ld	a, e
	ld	(hl+), a
	ld	(hl), d
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:201: __current_base_tile = base_tile;
	xor	a, a
	ld	(#___current_base_tile),a
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:202: __current_base_prop = base_prop;
	ld	hl, #___current_base_prop
	ld	(hl), #0x80
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:203: return __move_metasprite_flipx(base_sprite, (y << 8) | (uint8_t)(x - 8u));
	ldhl	sp,	#6
	ld	a, (hl+)
	inc	hl
	add	a, #0xf8
	ld	e, a
	ld	d, (hl)
	push	bc
	xor	a, a
	call	___move_metasprite_flipx
	pop	bc
;src/player.c:160: S_PRIORITY, 0, player_draw_x, player_draw_y);
	jr	00104$
00103$:
;src/player.c:162: move_metasprite_ex(marioSprites_metasprites[frame_index], 0, S_PRIORITY,
	ld	de, #_marioSprites_metasprites
	ldhl	sp,	#3
	ld	a,	(hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#11
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#10
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	l, a
	inc	de
	ld	a, (de)
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:160: __current_metasprite = metasprite;
	ld	e, l
	ld	d, a
	ld	hl, #___current_metasprite
	ld	a, e
	ld	(hl+), a
	ld	(hl), d
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:161: __current_base_tile = base_tile;
	xor	a, a
	ld	(#___current_base_tile),a
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:162: __current_base_prop = base_prop;
	ld	hl, #___current_base_prop
	ld	(hl), #0x80
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:163: return __move_metasprite(base_sprite, (y << 8) | (uint8_t)x);
	ldhl	sp,	#6
	ld	a, (hl+)
	inc	hl
	ld	e, a
	ld	d, (hl)
	push	bc
	xor	a, a
	call	___move_metasprite
	pop	bc
00104$:
;src/player.c:165: vsync();
	call	_vsync
;src/player.c:153: for (uint8_t i = 0; i < 24; i++) {
	ldhl	sp,	#11
	inc	(hl)
	jp	00133$
00110$:
;src/player.c:169: SWITCH_ROM(_saved_bank);
	ldhl	sp,	#0
	ld	a, (hl)
	ldh	(__current_bank + 0), a
	ld	a, (hl)
	ld	(#_rROMB0),a
;src/player.c:171: music_play_sfx(BANK(sound_pipe), sound_pipe, SFX_MUTE_MASK(sound_pipe),
	ld	e, #<(___mute_mask_sound_pipe)
	ld	d, #<(___bank_sound_pipe)
;sm83/musicmanager.h:105: if (music_sfx_priority > priority) return;
	ld	a, #0x04
	ld	hl, #_music_sfx_priority
	sub	a, (hl)
	jr	C, 00127$
;sm83/musicmanager.h:106: sfx_play_bank = SFX_STOP_BANK;
	ld	hl, #_sfx_play_bank
	ld	(hl), #0xff
;sm83/musicmanager.h:107: music_sfx_priority = priority;
	ld	hl, #_music_sfx_priority
	ld	(hl), #0x04
;sm83/musicmanager.h:108: music_sound_cut_mask(music_mute_mask);
	ld	a, (_music_mute_mask)
;sm83/musicmanager.h:80: sfx_sound_cut_mask(mask);
	ld	l, a
;sm83/sfxplayer.h:47: if (mask & SFX_CH_1) NR12_REG = 0, NR14_REG = SFX_CH_RETRIGGER;
	rrca
	jr	NC, 00117$
	xor	a, a
	ldh	(_NR12_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR14_REG + 0), a
00117$:
;sm83/sfxplayer.h:48: if (mask & SFX_CH_2) NR22_REG = 0, NR24_REG = SFX_CH_RETRIGGER;
	bit	1, l
	jr	Z, 00119$
	xor	a, a
	ldh	(_NR22_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR24_REG + 0), a
00119$:
;sm83/sfxplayer.h:49: if (mask & SFX_CH_3) NR32_REG = 0;
	bit	2, l
	jr	Z, 00121$
	xor	a, a
	ldh	(_NR32_REG + 0), a
00121$:
;sm83/sfxplayer.h:50: if (mask & SFX_CH_4) NR42_REG = 0, NR44_REG = SFX_CH_RETRIGGER;
	bit	3, l
	jr	Z, 00123$
	xor	a, a
	ldh	(_NR42_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR44_REG + 0), a
00123$:
;sm83/sfxplayer.h:51: NR51_REG = 0xFF;
	ld	a, #0xff
	ldh	(_NR51_REG + 0), a
;sm83/musicmanager.h:109: music_mute_mask = mute_mask;
	ld	hl, #_music_mute_mask
	ld	(hl), e
;sm83/sfxplayer.h:64: sfx_play_bank = SFX_STOP_BANK, sfx_frame_skip = 0, sfx_play_sample = sample, sfx_play_bank = bank;
	ld	hl, #_sfx_play_bank
	ld	(hl), #0xff
	xor	a, a
	ld	(#_sfx_frame_skip),a
	ld	hl, #_sfx_play_sample
	ld	a, #<(_sound_pipe)
	ld	(hl+), a
	ld	(hl), #>(_sound_pipe)
	ld	hl, #_sfx_play_bank
	ld	(hl), d
;src/player.c:172: MUSIC_SFX_PRIORITY_NORMAL);
00127$:
;src/player.c:176: pipe->destination_x, pipe->destination_y);
	ld	e, c
	ld	d, b
	inc	de
	inc	de
	ld	a, (de)
	ldhl	sp,	#9
	ld	(hl+), a
	ld	a, (bc)
	ld	(hl), a
;src/player.c:175: player_warp_to(pipe->destination_level, pipe->destination_page,
	ld	hl, #0x0005
	add	hl, bc
	ld	a, (hl)
	ldhl	sp,	#11
	ld	(hl), a
	ldhl	sp,#1
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	c, a
	inc	de
	ld	a, (de)
	ld	b, a
	ldhl	sp,	#9
	ld	a, (hl+)
	ld	d, a
	ld	a, (hl+)
	ld	e, a
	push	de
	ld	a, (hl)
	ld	e, c
	ld	d, b
	call	_player_warp_to
;src/player.c:180: pipe->destination_level->music);
	ldhl	sp,#1
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	c, a
	inc	de
	ld	a, (de)
	ld	b, a
	ld	hl, #0x0015
	add	hl, bc
	ld	a,	(hl+)
	ld	h, (hl)
	ld	l, a
;src/player.c:179: music_load(pipe->destination_level->music_bank,
	ld	a, c
	add	a, #0x14
	ld	c, a
	jr	NC, 00250$
	inc	b
00250$:
	ld	a, (bc)
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
;src/player.c:180: pipe->destination_level->music);
;src/player.c:182: }
	add	sp, #12
	ret
;src/player.c:184: bool player_check_horizontal_pipe_entry(void) NONBANKED {
;	---------------------------------
; Function player_check_horizontal_pipe_entry
; ---------------------------------
_player_check_horizontal_pipe_entry::
;src/player.c:185: if (!touch_ground || vel_x == 0) {
	ld	hl, #_touch_ground
	bit	0, (hl)
	jr	Z, 00101$
	ld	a, (#_vel_x)
	or	a, a
	jr	NZ, 00102$
00101$:
;src/player.c:186: return FALSE;
	xor	a, a
	ret
00102$:
;src/player.c:188: if (!pipe_active || active_pipe_direction != PIPE_DIRECTION_HORIZONTAL) {
	ld	hl, #_pipe_active
	bit	0, (hl)
	jr	Z, 00104$
	ld	a, (#_active_pipe_direction)
	dec	a
	jr	Z, 00105$
00104$:
;src/player.c:189: return FALSE;
	xor	a, a
	ret
00105$:
;src/player.c:192: uint8_t player_tile_x = player_x >> 3;
	ld	hl, #_player_x
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
;src/player.c:193: uint8_t player_tile_y = player_y >> 3;
	ld	a, (_player_y)
	ld	b, a
	ld	hl, #_player_y + 1
	ld	e, (hl)
	srl	e
	rr	b
	srl	e
	rr	b
	srl	e
	rr	b
	ld	l, b
;src/player.c:195: bool row_match = (player_tile_y == active_pipe_tile_y ||
	ld	a,(_active_pipe_tile_y)
	cp	a,l
	jr	Z, 00108$
	ld	d, #0x00
	ld	e, a
	dec	de
	ld	b, #0x00
	ld	a, l
	sub	a, e
	jr	NZ, 00173$
	ld	a, b
	sub	a, d
	jr	Z, 00108$
00173$:
;src/player.c:198: return FALSE;
	xor	a, a
	ret
00108$:
;src/player.c:201: if (vel_x > 0) {
	ld	hl, #_vel_x
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
	jr	NC, 00114$
;src/player.c:202: uint8_t player_right_tile = (player_x + MARIO_WIDTH) >> 3;
	ld	a, (_player_x)
	ld	hl, #_player_x + 1
	ld	h, (hl)
	ld	l, a
	ld	de, #0x0008
	add	hl, de
	srl	h
	rr	l
	srl	h
	rr	l
	srl	h
	rr	l
;src/player.c:203: if (player_right_tile == active_pipe_tile_x) {
	ld	a, (_active_pipe_tile_x)
	sub	a, l
	jr	NZ, 00115$
;src/player.c:204: player_enter_pipe(&active_pipe);
	ld	de, #_active_pipe
	call	_player_enter_pipe
;src/player.c:205: return TRUE;
	ld	a, #0x01
	ret
00114$:
;src/player.c:208: if (player_tile_x == active_pipe_tile_x + 1) {
	ld	a, (_active_pipe_tile_x)
	ld	d, #0x00
	ld	e, a
	inc	de
	ld	b, #0x00
	ld	a, c
	sub	a, e
	jr	NZ, 00115$
	ld	a, b
	sub	a, d
	jr	NZ, 00115$
;src/player.c:209: player_enter_pipe(&active_pipe);
	ld	de, #_active_pipe
	call	_player_enter_pipe
;src/player.c:210: return TRUE;
	ld	a, #0x01
	ret
00115$:
;src/player.c:213: return FALSE;
	xor	a, a
;src/player.c:214: }
	ret
;src/player.c:216: void player_warp_to(level *destination_level, uint8_t destination_page,
;	---------------------------------
; Function player_warp_to
; ---------------------------------
_player_warp_to::
	add	sp, #-3
	ldhl	sp,	#1
	ld	(hl), e
	inc	hl
	ld	(hl), d
	dec	hl
	dec	hl
	ld	(hl), a
;src/player.c:218: pipe_clear();
	call	_pipe_clear
;src/player.c:220: level_page_x_offset = destination_page * PAGE_SIZE;
	ldhl	sp,	#0
	ld	c, (hl)
	ld	b, #0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	ld	e, l
	ld	d, h
	ld	hl, #_level_page_x_offset
	ld	a, e
	ld	(hl+), a
	ld	(hl), d
;src/player.c:222: if (destination_page == destination_level->page_count - 1) {
	ldhl	sp,#1
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0004
	add	hl, de
	ld	e, l
	ld	d, h
	ld	a, (de)
	ld	d, #0x00
	ld	e, a
	dec	de
	ld	a, e
	sub	a, c
	jr	NZ, 00102$
	ld	a, d
	sub	a, b
	jr	NZ, 00102$
;src/player.c:223: level_end_reached = true;
	ld	hl, #_level_end_reached
	ld	(hl), #0x01
	jr	00103$
00102$:
;src/player.c:225: scroll_limit = DEVICE_SCREEN_PX_WIDTH_HALF;
	ld	hl, #_scroll_limit
	ld	a, #0x50
	ld	(hl+), a
;src/player.c:226: level_end_reached = false;
	xor	a, a
	ld	(hl), a
	ld	(#_level_end_reached),a
00103$:
;src/player.c:229: enemy_reset_all();
	ld	e, #b_enemy_reset_all
	ld	hl, #_enemy_reset_all
	call	___sdcc_bcall_ehl
;src/player.c:230: hide_sprites_range(0, MAX_HARDWARE_SPRITES);
	ld	e, #0x28
	xor	a, a
	call	_hide_sprites_range
;src/player.c:231: delay(500);
	ld	de, #0x01f4
	call	_delay
;src/player.c:233: camera_x = 0;
	xor	a, a
	ld	hl, #_camera_x
	ld	(hl+), a
	ld	(hl), a
;/home/odrevet/projects/gbdk/include/gb/gb.h:1461: SCX_REG=x, SCY_REG=y;
	xor	a, a
	ldh	(_SCX_REG + 0), a
	ld	a, #0xf0
	ldh	(_SCY_REG + 0), a
;src/player.c:235: camera_x_upscaled = 0;
	xor	a, a
	ld	hl, #_camera_x_upscaled
	ld	(hl+), a
	ld	(hl), a
;src/player.c:237: current_page = destination_page;
	ldhl	sp,	#0
	ld	a, (hl)
	ld	(#_current_page),a
;src/player.c:238: current_column_in_page = 0;
;src/player.c:239: map_column = 0;
	xor	a, a
	ld	(#_current_column_in_page), a
	ld	(#_map_column),a
;src/player.c:241: player_x_upscaled = (destination_x * TILE_SIZE) << 4;
	ldhl	sp,	#5
	ld	c, (hl)
	xor	a, a
	ld	l, c
	ld	h, a
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	a, l
	ld	c, h
	ld	hl, #_player_x_upscaled
	ld	(hl+), a
	ld	(hl), c
;src/player.c:242: player_y_upscaled = (destination_y * TILE_SIZE) << 4;
	ldhl	sp,	#6
	ld	c, (hl)
	xor	a, a
	ld	l, c
	ld	h, a
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	a, l
	ld	c, h
	ld	hl, #_player_y_upscaled
	ld	(hl+), a
	ld	(hl), c
;src/player.c:243: player_draw_x = player_x_upscaled >> 4;
	ld	hl, #_player_x_upscaled
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
	ld	hl, #_player_draw_x
	ld	(hl), c
;src/player.c:244: player_draw_y = player_y_upscaled >> 4;
	ld	hl, #_player_y_upscaled
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
	ld	hl, #_player_draw_y
	ld	(hl), c
;src/player.c:245: player_x_next_upscaled = player_x_upscaled;
	ld	a, (#_player_x_upscaled)
	ld	(#_player_x_next_upscaled),a
	ld	a, (#_player_x_upscaled + 1)
	ld	(#_player_x_next_upscaled + 1),a
;src/player.c:246: player_y_next_upscaled = player_y_upscaled;
	ld	a, (#_player_y_upscaled)
	ld	(#_player_y_next_upscaled),a
	ld	a, (#_player_y_upscaled + 1)
	ld	(#_player_y_next_upscaled + 1),a
;src/player.c:248: vel_x = 0;
;src/player.c:249: vel_y = 0;
	xor	a, a
	ld	(#_vel_x), a
	ld	(#_vel_y),a
;src/player.c:250: display_jump_frame = FALSE;
;src/player.c:251: display_slide_frame = FALSE;
	xor	a, a
	ld	(#_display_jump_frame), a
	ld	(#_display_slide_frame),a
;src/player.c:252: display_walk_animation = FALSE;
;src/player.c:253: frame_counter = 0;
	xor	a, a
	ld	(#_display_walk_animation), a
	ld	(#_frame_counter),a
;src/player.c:254: marioSpritesflip = FALSE;
;src/player.c:255: touch_ground = FALSE;
	xor	a, a
	ld	(#_marioSpritesflip), a
	ld	(#_touch_ground),a
;src/player.c:257: load_col_at = COLUMN_SIZE;
	ld	hl, #_load_col_at
	ld	a, #0x01
	ld	(hl+), a
	xor	a, a
	ld	(hl), a
;src/player.c:263: level_load_column(MAP_BUFFER_WIDTH, destination_level);
	ldhl	sp,	#1
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, #0x1b
	call	_level_load_column
;src/player.c:265: col_from = 0;
	xor	a, a
	ld	hl, #_col_from
	ld	(hl+), a
	ld	(hl), a
;src/player.c:266: for (uint8_t c = 0; c <= DEVICE_SCREEN_WIDTH + 1; c++) {
	ld	c, #0x00
00107$:
	ld	a, #0x15
	sub	a, c
	jr	C, 00109$
;src/player.c:267: level_load_objects(c);
	ld	e, c
	xor	a, a
	push	bc
	ld	d, a
	call	_level_load_objects
	pop	bc
;src/player.c:266: for (uint8_t c = 0; c <= DEVICE_SCREEN_WIDTH + 1; c++) {
	inc	c
	jr	00107$
00109$:
;src/player.c:269: }
	add	sp, #3
	pop	hl
	pop	af
	jp	(hl)
;src/player.c:745: void player_on_touch_ground(void) NONBANKED {
;	---------------------------------
; Function player_on_touch_ground
; ---------------------------------
_player_on_touch_ground::
;src/player.c:746: current_jump = 0;
	xor	a, a
	ld	hl, #_current_jump
	ld	(hl+), a
	ld	(hl), a
;src/player.c:747: touch_ground = TRUE;
	ld	hl, #_touch_ground
	ld	(hl), #0x01
;src/player.c:748: is_jumping = FALSE;
;src/player.c:749: display_jump_frame = FALSE;
	xor	a, a
	ld	(#_is_jumping), a
	ld	(#_display_jump_frame),a
;src/player.c:750: }
	ret
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE_255
;src/player.c:15: BANKREF(player)
;	---------------------------------
; Function __func_player
; ---------------------------------
	b___func_player	= 255
___func_player::
	.local b___func_player 
	___bank_player = b___func_player 
	.globl ___bank_player 
;src/player.c:54: static int8_t apply_velocity(int8_t vel, int8_t target, int8_t accel,
;	---------------------------------
; Function apply_velocity
; ---------------------------------
_apply_velocity:
	ld	c, a
	ld	b, e
;src/player.c:56: if (target == 0) {
	ld	a, b
	or	a, a
	jr	NZ, 00120$
;src/player.c:57: if (vel > 0) {
	ld	e, c
	xor	a, a
	ld	d, a
	sub	a, c
	bit	7, e
	jr	Z, 00187$
	bit	7, d
	jr	NZ, 00188$
	cp	a, a
	jr	00188$
00187$:
	bit	7, d
	jr	Z, 00188$
	scf
00188$:
	jr	NC, 00108$
;src/player.c:58: vel -= decel;
	ld	a, c
	ldhl	sp,	#3
	sub	a, (hl)
	ld	c, a
;src/player.c:59: if (vel < 0)
	bit	7, c
	jp	Z, 00121$
;src/player.c:60: vel = 0;
	ld	c, #0x00
	jp	00121$
00108$:
;src/player.c:61: } else if (vel < 0) {
	bit	7, c
	jp	Z, 00121$
;src/player.c:62: vel += decel;
	ld	a, c
	ldhl	sp,	#3
	add	a, (hl)
	ld	c, a
;src/player.c:63: if (vel > 0)
	ld	e, c
	xor	a, a
	ld	d, a
	sub	a, c
	bit	7, e
	jr	Z, 00189$
	bit	7, d
	jr	NZ, 00190$
	cp	a, a
	jr	00190$
00189$:
	bit	7, d
	jr	Z, 00190$
	scf
00190$:
	jr	NC, 00121$
;src/player.c:64: vel = 0;
	ld	c, #0x00
	jr	00121$
00120$:
;src/player.c:66: } else if (target > vel) {
	ld	e, b
	ld	a,c
	ld	d,a
	sub	a, b
	bit	7, e
	jr	Z, 00191$
	bit	7, d
	jr	NZ, 00192$
	cp	a, a
	jr	00192$
00191$:
	bit	7, d
	jr	Z, 00192$
	scf
00192$:
	jr	NC, 00117$
;src/player.c:67: vel += accel;
	ld	a, c
	ldhl	sp,	#2
	add	a, (hl)
	ld	c, a
;src/player.c:68: if (vel > target)
	ld	e, c
	ld	a,b
	ld	d,a
	sub	a, c
	bit	7, e
	jr	Z, 00193$
	bit	7, d
	jr	NZ, 00194$
	cp	a, a
	jr	00194$
00193$:
	bit	7, d
	jr	Z, 00194$
	scf
00194$:
	jr	NC, 00121$
;src/player.c:69: vel = target;
	ld	c, b
	jr	00121$
00117$:
;src/player.c:70: } else if (target < vel) {
	ld	e, c
	ld	a,b
	ld	d,a
	sub	a, c
	bit	7, e
	jr	Z, 00195$
	bit	7, d
	jr	NZ, 00196$
	cp	a, a
	jr	00196$
00195$:
	bit	7, d
	jr	Z, 00196$
	scf
00196$:
	jr	NC, 00121$
;src/player.c:71: vel -= accel;
	ld	a, c
	ldhl	sp,	#2
	sub	a, (hl)
;src/player.c:72: if (vel < target)
	ld	c, a
	ld	e, b
	ld	d,a
	sub	a, b
	bit	7, e
	jr	Z, 00197$
	bit	7, d
	jr	NZ, 00198$
	cp	a, a
	jr	00198$
00197$:
	bit	7, d
	jr	Z, 00198$
	scf
00198$:
	jr	NC, 00121$
;src/player.c:73: vel = target;
	ld	c, b
00121$:
;src/player.c:75: return vel;
	ld	a, c
;src/player.c:76: }
	pop	hl
	pop	bc
	jp	(hl)
;src/player.c:271: void player_move(void) BANKED {
;	---------------------------------
; Function player_move
; ---------------------------------
	b_player_move	= 255
_player_move::
	add	sp, #-6
;src/player.c:272: int8_t target_vel_x = 0;
	ldhl	sp,	#4
	ld	(hl), #0x00
;src/player.c:276: bool on_ground = touch_ground || player_is_on_platform();
	ld	hl, #_touch_ground
	bit	0, (hl)
	jr	NZ, 00240$
	ld	e, #b_player_is_on_platform
	ld	hl, #_player_is_on_platform
	call	___sdcc_bcall_ehl
	bit	0,a
	jr	NZ, 00240$
	xor	a, a
	jr	00241$
00240$:
	ld	a, #0x01
00241$:
	ldhl	sp,	#5
	ld	(hl), a
;src/player.c:278: if (player_check_pipe_entry()) {
	call	_player_check_pipe_entry
	bit	0,a
;src/player.c:279: return;
	jp	NZ, 00237$
;src/player.c:282: if (player_check_horizontal_pipe_entry()) {
	call	_player_check_horizontal_pipe_entry
	bit	0,a
;src/player.c:283: return;
	jp	NZ, 00237$
;src/player.c:286: if (joypad_current & J_RIGHT) {
	ld	a, (_joypad_current)
;src/player.c:288: max_speed = (joypad_current & J_B) ? MAX_RUN_SPEED : MAX_WALK_SPEED;
	ld	c, a
	and	a, #0x20
;src/player.c:286: if (joypad_current & J_RIGHT) {
	bit	0, c
	jr	Z, 00111$
;src/player.c:287: display_walk_animation = TRUE;
	ld	hl, #_display_walk_animation
	ld	(hl), #0x01
;src/player.c:288: max_speed = (joypad_current & J_B) ? MAX_RUN_SPEED : MAX_WALK_SPEED;
	or	a, a
	ld	a, #0x1c
	jr	NZ, 00243$
	ld	a, #0x10
00243$:
	ldhl	sp,	#4
	ld	(hl), a
;src/player.c:291: if (display_jump_frame == FALSE) {
	ld	hl, #_display_jump_frame
	bit	0, (hl)
	jr	NZ, 00112$
;src/player.c:292: marioSpritesflip = FALSE;
	xor	a, a
	ld	(#_marioSpritesflip),a
	jr	00112$
00111$:
;src/player.c:294: } else if (joypad_current & J_LEFT) {
	bit	1, c
	jr	Z, 00108$
;src/player.c:295: display_walk_animation = TRUE;
	ld	hl, #_display_walk_animation
	ld	(hl), #0x01
;src/player.c:296: max_speed = (joypad_current & J_B) ? MAX_RUN_SPEED : MAX_WALK_SPEED;
	or	a, a
	ld	c, #0x1c
	jr	NZ, 00245$
	ld	c, #0x10
00245$:
;src/player.c:297: target_vel_x = -max_speed;
	xor	a, a
	sub	a, c
	ldhl	sp,	#4
	ld	(hl), a
;src/player.c:298: marioSpritesflip = TRUE;
	ld	hl, #_marioSpritesflip
	ld	(hl), #0x01
	jr	00112$
00108$:
;src/player.c:300: display_walk_animation = FALSE;
	xor	a, a
	ld	(#_display_walk_animation),a
00112$:
;src/player.c:303: if (on_ground) {
	ldhl	sp,	#5
	bit	0, (hl)
	jr	Z, 00120$
;src/player.c:304: accel = ACCELERATION;
;src/player.c:305: decel = DECELERATION;
	ld	bc, #0x302
;src/player.c:307: if ((vel_x > 8 && target_vel_x < 0) || (vel_x < -8 && target_vel_x > 0)) {
	ld	hl, #_vel_x
	ld	e, (hl)
	ld	a,#0x08
	ld	d,a
	sub	a, (hl)
	bit	7, e
	jr	Z, 00685$
	bit	7, d
	jr	NZ, 00686$
	cp	a, a
	jr	00686$
00685$:
	bit	7, d
	jr	Z, 00686$
	scf
00686$:
	jr	NC, 00118$
	ldhl	sp,	#4
	bit	7, (hl)
	jr	NZ, 00113$
00118$:
	ld	a, (#_vel_x)
	xor	a, #0x80
	sub	a, #0x78
	jr	NC, 00114$
	ldhl	sp,	#4
	ld	e, (hl)
	xor	a, a
	ld	d, a
	sub	a, (hl)
	bit	7, e
	jr	Z, 00687$
	bit	7, d
	jr	NZ, 00688$
	cp	a, a
	jr	00688$
00687$:
	bit	7, d
	jr	Z, 00688$
	scf
00688$:
	jr	NC, 00114$
00113$:
;src/player.c:308: decel = SKID_DECELERATION;
	ld	b, #0x04
;src/player.c:309: display_slide_frame = TRUE;
	ld	hl, #_display_slide_frame
	ld	(hl), #0x01
	jr	00121$
00114$:
;src/player.c:311: display_slide_frame = FALSE;
	xor	a, a
	ld	(#_display_slide_frame),a
	jr	00121$
00120$:
;src/player.c:314: accel = AIR_ACCELERATION;
;src/player.c:315: decel = AIR_DECELERATION;
	ld	bc, #0x101
;src/player.c:316: display_slide_frame = FALSE;
	xor	a, a
	ld	(#_display_slide_frame),a
00121$:
;src/player.c:319: vel_x = apply_velocity(vel_x, target_vel_x, accel, decel);
	push	bc
	ldhl	sp,	#6
	ld	e, (hl)
	ld	a, (_vel_x)
	call	_apply_velocity
	ld	(#_vel_x),a
;src/player.c:321: if (is_jumping) {
	ld	hl, #_is_jumping
	bit	0, (hl)
	jr	Z, 00138$
;src/player.c:322: current_jump++;
	ld	hl, #_current_jump
	inc	(hl)
	jr	NZ, 00689$
	inc	hl
	inc	(hl)
00689$:
;src/player.c:325: if ((joypad_current & J_A) && current_jump < JUMP_MAX_FRAMES) {
	ld	a, (#_current_jump)
	ldhl	sp,	#4
	ld	(hl), a
	ld	a, (#_current_jump + 1)
	ldhl	sp,	#5
	ld	(hl), a
;src/player.c:326: vel_y += GRAVITY_RISING;
	ld	hl, #_vel_y
	ld	c, (hl)
	inc	c
	inc	c
;src/player.c:324: if (vel_y < 0) {
	bit	7, (hl)
	jr	Z, 00127$
;src/player.c:325: if ((joypad_current & J_A) && current_jump < JUMP_MAX_FRAMES) {
	ld	a, (_joypad_current)
	bit	4, a
	jr	Z, 00123$
	ldhl	sp,	#4
	ld	a, (hl+)
	sub	a, #0x0d
	ld	a, (hl)
	sbc	a, #0x00
	jr	NC, 00123$
;src/player.c:326: vel_y += GRAVITY_RISING;
	ld	hl, #_vel_y
	ld	(hl), c
;src/player.c:327: vel_y += JUMP_HOLD_BOOST;
	dec	(hl)
	ld	a, (hl)
	jr	00128$
00123$:
;src/player.c:329: vel_y += GRAVITY_FAST_FALL;
	ld	hl, #_vel_y
	inc	(hl)
	inc	(hl)
	inc	(hl)
	jr	00128$
00127$:
;src/player.c:332: vel_y += GRAVITY;
	ld	hl, #_vel_y
	ld	(hl), c
00128$:
;src/player.c:335: if (vel_y >= 0 && current_jump > JUMP_MIN_FRAMES) {
	ld	a, (#_vel_y)
	bit	7, a
	jr	NZ, 00130$
	ldhl	sp,	#4
	ld	a, #0x04
	sub	a, (hl)
	inc	hl
	ld	a, #0x00
	sbc	a, (hl)
	jr	NC, 00130$
;src/player.c:336: is_jumping = FALSE;
	xor	a, a
	ld	(#_is_jumping),a
00130$:
;src/player.c:339: if (current_jump >= JUMP_MAX_FRAMES + 10) {
	ld	hl, #_current_jump
	ld	a, (hl+)
	sub	a, #0x17
	ld	a, (hl)
	sbc	a, #0x00
	jr	C, 00139$
;src/player.c:340: is_jumping = FALSE;
	xor	a, a
	ld	(#_is_jumping),a
	jr	00139$
00138$:
;src/player.c:342: } else if (!touch_ground || !player_is_on_platform()) {
	ld	hl, #_touch_ground
	bit	0, (hl)
	jr	Z, 00134$
	ld	e, #b_player_is_on_platform
	ld	hl, #_player_is_on_platform
	call	___sdcc_bcall_ehl
	bit	0,a
	jr	NZ, 00139$
00134$:
;src/player.c:343: vel_y += GRAVITY;
	ld	hl, #_vel_y
	inc	(hl)
	inc	(hl)
00139$:
;src/player.c:346: if (vel_y > MAX_FALL_SPEED) {
	ld	hl, #_vel_y
	ld	e, (hl)
	ld	a,#0x30
	ld	d,a
	sub	a, (hl)
	bit	7, e
	jr	Z, 00691$
	bit	7, d
	jr	NZ, 00692$
	cp	a, a
	jr	00692$
00691$:
	bit	7, d
	jr	Z, 00692$
	scf
00692$:
	jr	NC, 00141$
;src/player.c:347: vel_y = MAX_FALL_SPEED;
	ld	hl, #_vel_y
	ld	(hl), #0x30
00141$:
;src/player.c:350: if (joypad_current & J_A && !(joypad_previous & J_A) && !is_jumping &&
	ld	a, (_joypad_current)
	bit	4, a
	jp	Z, 00143$
	ld	a, (_joypad_previous)
	bit	4, a
	jp	NZ, 00143$
	ld	hl, #_is_jumping
	bit	0, (hl)
	jp	NZ, 00143$
;src/player.c:351: touch_ground) {
	ld	hl, #_touch_ground
	bit	0, (hl)
	jr	Z, 00143$
;src/player.c:352: current_jump = 0;
	xor	a, a
	ld	hl, #_current_jump
	ld	(hl+), a
	ld	(hl), a
;src/player.c:353: is_jumping = TRUE;
	ld	hl, #_is_jumping
	ld	(hl), #0x01
;src/player.c:354: display_jump_frame = TRUE;
	ld	hl, #_display_jump_frame
	ld	(hl), #0x01
;src/player.c:355: vel_y = JUMP_INITIAL_VELOCITY;
	ld	hl, #_vel_y
	ld	(hl), #0xd8
;src/player.c:356: touch_ground = FALSE;
	xor	a, a
	ld	(#_touch_ground),a
;src/player.c:359: SFX_MUTE_MASK(sound_jump_small), MUSIC_SFX_PRIORITY_NORMAL);
	ld	c, #<(___mute_mask_sound_jump_small)
;src/player.c:358: music_play_sfx(BANK(sound_jump_small), sound_jump_small,
	ld	b, #<(___bank_sound_jump_small)
;sm83/musicmanager.h:105: if (music_sfx_priority > priority) return;
	ld	a, #0x04
	ld	hl, #_music_sfx_priority
	sub	a, (hl)
	jr	C, 00143$
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
	jr	NC, 00224$
	xor	a, a
	ldh	(_NR12_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR14_REG + 0), a
00224$:
;sm83/sfxplayer.h:48: if (mask & SFX_CH_2) NR22_REG = 0, NR24_REG = SFX_CH_RETRIGGER;
	bit	1, e
	jr	Z, 00226$
	xor	a, a
	ldh	(_NR22_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR24_REG + 0), a
00226$:
;sm83/sfxplayer.h:49: if (mask & SFX_CH_3) NR32_REG = 0;
	bit	2, e
	jr	Z, 00228$
	xor	a, a
	ldh	(_NR32_REG + 0), a
00228$:
;sm83/sfxplayer.h:50: if (mask & SFX_CH_4) NR42_REG = 0, NR44_REG = SFX_CH_RETRIGGER;
	bit	3, e
	jr	Z, 00230$
	xor	a, a
	ldh	(_NR42_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR44_REG + 0), a
00230$:
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
	ld	(hl), #<(_sound_jump_small)
	inc	hl
	ld	(hl), #>(_sound_jump_small)
	ld	hl, #_sfx_play_bank
	ld	(hl), b
;src/player.c:359: SFX_MUTE_MASK(sound_jump_small), MUSIC_SFX_PRIORITY_NORMAL);
00143$:
;src/player.c:363: player_x_next_upscaled = player_x_upscaled + vel_x;
	ld	a, (_vel_x)
	ld	c, a
	rlca
	sbc	a, a
	ld	b, a
	ld	a, (_player_x_upscaled)
	ld	hl, #_player_x_upscaled + 1
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	e, l
	ld	d, h
	ld	hl, #_player_x_next_upscaled
	ld	a, e
	ld	(hl+), a
	ld	(hl), d
;src/player.c:364: player_y_next_upscaled = player_y_upscaled;
	ld	a, (#_player_y_upscaled)
	ld	(#_player_y_next_upscaled),a
	ld	a, (#_player_y_upscaled + 1)
	ld	(#_player_y_next_upscaled + 1),a
;src/player.c:366: player_x_next = player_x_next_upscaled >> 4;
	ld	a, (#_player_x_next_upscaled)
	ld	(#_player_x_next),a
	ld	a, (#_player_x_next_upscaled + 1)
	ld	hl, #_player_x_next + 1
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
;src/player.c:367: player_y_next = player_y_next_upscaled >> 4;
	ld	a, (#_player_y_next_upscaled)
	ld	(#_player_y_next),a
	ld	a, (#_player_y_next_upscaled + 1)
	ld	hl, #_player_y_next + 1
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
;src/player.c:372: player_y_next + PLAYER_TOP_MARGIN);
	ld	c, (hl)
;src/player.c:370: tile_next_1 = get_tile(player_x_next + MARIO_WIDTH -
	ld	a, (#_player_x_next)
	ldhl	sp,	#3
	ld	(hl), a
;src/player.c:371: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	a, (#_camera_x)
	ldhl	sp,	#4
;src/player.c:372: player_y_next + PLAYER_TOP_MARGIN);
	ld	(hl+), a
	ld	a, c
	add	a, #0x08
	ld	(hl), a
;src/player.c:369: if (vel_x > 0) {
	ld	hl, #_vel_x
	ld	e, (hl)
	xor	a, a
	ld	d, a
	sub	a, (hl)
	bit	7, e
	jr	Z, 00700$
	bit	7, d
	jr	NZ, 00701$
	cp	a, a
	jr	00701$
00700$:
	bit	7, d
	jr	Z, 00701$
	scf
00701$:
	jp	NC, 00179$
;src/player.c:370: tile_next_1 = get_tile(player_x_next + MARIO_WIDTH -
	ldhl	sp,	#3
;src/player.c:371: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	a, (hl+)
	add	a, #0x06
	ld	c, (hl)
	inc	hl
	sub	a, c
	ld	e, (hl)
	call	_get_tile
	ld	(#_tile_next_1),a
;src/player.c:375: player_y_next + marioSprites_HEIGHT - 1);
	ld	a, (_player_y_next)
	add	a, #0x0f
	ld	e, a
;src/player.c:373: tile_next_2 = get_tile(player_x_next + MARIO_WIDTH -
	ld	a, (_player_x_next)
	add	a, #0x06
;src/player.c:374: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_get_tile
	ld	(#_tile_next_2),a
;src/player.c:377: uint8_t tx1 = TILE_INDEX_X(player_x_next + MARIO_WIDTH - PLAYER_HORIZONTAL_MARGIN - camera_x, camera_x);
	ld	a, (_player_x_next)
	ld	hl, #_player_x_next + 1
	ld	b, (hl)
	add	a, #0x06
	ld	c, a
	jr	NC, 00702$
	inc	b
00702$:
	ld	a, c
	ld	hl, #_camera_x
	sub	a, (hl)
	inc	hl
	ld	c, a
	ld	a, b
	sbc	a, (hl)
	dec	hl
	ld	b, a
	ld	a, c
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
	ldhl	sp,	#5
	ld	(hl), a
;src/player.c:378: uint8_t ty1 = TILE_INDEX_Y(player_y_next + PLAYER_TOP_MARGIN);
	ld	a, (_player_y_next)
	ld	hl, #_player_y_next + 1
	ld	h, (hl)
	ld	l, a
	ld	de, #0x0008
	add	hl, de
	ld	c, l
	srl	h
	rr	c
	srl	h
	rr	c
	srl	h
	rr	c
;src/player.c:381: is_tile_solid(tile_next_1) || is_tile_solid(tile_next_2));
	push	bc
	ld	a, (_tile_next_1)
	call	_is_tile_solid
	ld	e, a
	pop	bc
	bit	0, e
	jr	NZ, 00247$
	push	bc
	ld	a, (_tile_next_2)
	call	_is_tile_solid
	ld	e, a
	pop	bc
	bit	0, e
	ld	e, #0x00
	jr	Z, 00248$
00247$:
	ld	e, #0x01
00248$:
	ld	d, #0x00
;src/player.c:380: player_x_next, player_y_next, tx1, ty1, tile_next_1, tile_next_2,
	ld	a, (#_tile_next_2)
	ldhl	sp,	#0
	ld	(hl+), a
	ld	(hl), #0x00
	ld	a, (#_tile_next_1)
	ldhl	sp,	#2
	ld	(hl+), a
	xor	a, a
	ld	(hl+), a
	inc	hl
	ld	b, #0x00
	ld	a, (hl-)
	ld	(hl+), a
	ld	(hl), #0x00
;src/player.c:379: EMU_printf("H px=%d py=%d tx=%d ty=%d t1=%02x t2=%02x solid=%d\n",
	push	de
	ldhl	sp,	#2
	ld	a, (hl+)
	inc	hl
	ld	e, a
	ld	d, #0x00
	push	de
	ld	a, (hl+)
	inc	hl
	ld	e, a
	ld	d, #0x00
	push	de
	push	bc
	ld	e, (hl)
	ld	d, #0x00
	push	de
	ld	a, (_player_y_next)
	ld	e, a
	ld	hl, #_player_y_next + 1
	ld	d, (hl)
	push	de
	ld	a, (_player_x_next)
	ld	e, a
	ld	hl, #_player_x_next + 1
	ld	d, (hl)
	push	de
	ld	de, #___str_0
	push	de
	call	_EMU_printf
	add	sp, #16
;src/player.c:383: if (is_tile_solid(tile_next_1) || is_tile_solid(tile_next_2)) {
	ld	a, (_tile_next_1)
	call	_is_tile_solid
	bit	0,a
	jr	NZ, 00162$
	ld	a, (_tile_next_2)
	call	_is_tile_solid
	bit	0,a
	jr	Z, 00163$
00162$:
;src/player.c:384: player_x = TILE_ALIGN(player_x_next) - 7;
	ld	a, (_player_x_next)
	ld	hl, #_player_x_next + 1
	ld	h, (hl)
	ld	l, a
	ld	de, #0x0007
	add	hl, de
	ld	a, l
	and	a, #0xf8
	add	a, #0xf9
	ld	c, a
	ld	a, h
	adc	a, #0xff
	ld	hl, #_player_x
	ld	(hl), c
	inc	hl
;src/player.c:385: player_x_upscaled = player_x << 4;
	ld	(hl-), a
	ld	a, (hl)
	ld	(#_player_x_upscaled),a
	ld	a, (#_player_x + 1)
	ld	(#_player_x_upscaled + 1),a
	ld	a, #0x04
00703$:
	ld	hl, #_player_x_upscaled
	sla	(hl)
	inc	hl
	rl	(hl)
	dec	a
	jr	NZ, 00703$
	jp	00180$
00163$:
;src/player.c:387: if (is_coin(tile_next_1)) {
	ld	a, (_tile_next_1)
	call	_is_coin
	bit	0,a
	jr	Z, 00150$
;src/player.c:390: player_y_next + PLAYER_TOP_MARGIN);
	ld	a, (_player_y_next)
	add	a, #0x08
	ld	e, a
;src/player.c:388: on_get_coin_background(player_x_next + MARIO_WIDTH -
	ld	a, (_player_x_next)
	add	a, #0x06
;src/player.c:389: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_on_get_coin_background
	jr	00151$
00150$:
;src/player.c:391: } else if (is_coin(tile_next_2)) {
	ld	a, (_tile_next_2)
	call	_is_coin
	bit	0,a
	jr	Z, 00151$
;src/player.c:394: player_y_next + marioSprites_HEIGHT - 1);
	ld	a, (_player_y_next)
	add	a, #0x0f
	ld	e, a
;src/player.c:392: on_get_coin_background(player_x_next + MARIO_WIDTH -
	ld	a, (_player_x_next)
	add	a, #0x06
;src/player.c:393: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_on_get_coin_background
00151$:
;src/player.c:397: if (tile_next_1 == SWITCH) {
	ld	a, (#_tile_next_1)
	sub	a, #0x3d
	jr	NZ, 00153$
;src/player.c:398: init();
	call	_init
;src/player.c:399: map_column = 0;
	xor	a, a
	ld	(#_map_column),a
;src/player.c:400: current_level = (++current_level) % NB_LEVELS;
	ld	hl, #_current_level
	inc	(hl)
	ld	a, (hl)
	ld	e, #0x0c
	call	__moduchar
	ld	hl, #_current_level
	ld	(hl), c
;src/player.c:401: level_set_current();
	call	_level_set_current
00153$:
;src/player.c:404: player_x_upscaled = player_x_next_upscaled;
	ld	a, (#_player_x_next_upscaled)
	ld	(#_player_x_upscaled),a
	ld	a, (#_player_x_next_upscaled + 1)
	ld	hl, #_player_x_upscaled + 1
;src/player.c:405: player_x = player_x_upscaled >> 4;
	ld	(hl-), a
	ld	a, (hl)
	ld	(#_player_x),a
	ld	a, (#_player_x_upscaled + 1)
	ld	hl, #_player_x + 1
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
;src/player.c:407: if (load_col_at == current_map_width_in_tiles - DEVICE_SCREEN_WIDTH + 1) {
	ld	hl, #_current_map_width_in_tiles
	ld	a, (hl+)
	add	a, #0xed
	ld	c, a
	ld	a, (hl)
	adc	a, #0xff
	ld	b, a
	ld	a, (_load_col_at)
	ld	e, a
	ld	hl, #_load_col_at + 1
	ld	d, (hl)
	ld	a, e
	sub	a, c
	jr	NZ, 00155$
	ld	a, d
	sub	a, b
	jr	NZ, 00155$
;src/player.c:408: level_end_reached = true;
	ld	hl, #_level_end_reached
	ld	(hl), #0x01
;src/player.c:409: camera_x = current_map_width - DEVICE_SCREEN_PX_WIDTH;
	ld	hl, #_current_map_width
	ld	a, (hl+)
	add	a, #0x60
	ld	c, a
	ld	a, (hl)
	adc	a, #0xff
	ld	b, a
	ld	hl, #_camera_x
	ld	a, c
	ld	(hl+), a
;src/player.c:410: move_bkg(camera_x, SCROLL_TOP_OFFSET);
	ld	a, b
	ld	(hl-), a
	ld	a, (hl)
	ldh	(_SCX_REG + 0), a
;/home/odrevet/projects/gbdk/include/gb/gb.h:1461: SCX_REG=x, SCY_REG=y;
	ld	a, #0xf0
	ldh	(_SCY_REG + 0), a
;src/player.c:410: move_bkg(camera_x, SCROLL_TOP_OFFSET);
00155$:
;src/player.c:413: if (!level_end_reached && player_x > scroll_limit) {
	ld	hl, #_level_end_reached
	bit	0, (hl)
	jp	NZ, 00157$
	ld	de, #_scroll_limit
	ld	hl, #_player_x
	ld	a, (de)
	inc	de
	sub	a, (hl)
	inc	hl
	ld	a, (de)
	sbc	a, (hl)
	jr	NC, 00157$
;src/player.c:414: int16_t player_movement = player_x - scroll_limit;
	ld	a, (#_player_x)
	ld	hl, #_scroll_limit
	sub	a, (hl)
	ld	c, a
	ld	a, (#_player_x + 1)
	ld	hl, #_scroll_limit + 1
	sbc	a, (hl)
	ld	b, a
;src/player.c:415: camera_x_upscaled += (player_movement << 4);
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	c, l
	ld	b, h
	ld	hl, #_camera_x_upscaled
	ld	a, (hl)
	add	a, c
	ld	(hl+), a
	ld	a, (hl)
	adc	a, b
;src/player.c:416: camera_x = camera_x_upscaled >> 4;
	ld	(hl-), a
	ld	a, (hl)
	ld	(#_camera_x),a
	ld	a, (#_camera_x_upscaled + 1)
	ld	hl, #_camera_x + 1
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
;src/player.c:417: move_bkg(camera_x, SCROLL_TOP_OFFSET);
	ld	a, (hl)
	ldh	(_SCX_REG + 0), a
;/home/odrevet/projects/gbdk/include/gb/gb.h:1461: SCX_REG=x, SCY_REG=y;
	ld	a, #0xf0
	ldh	(_SCY_REG + 0), a
;src/player.c:418: scroll_limit = player_x;
	ld	a, (#_player_x)
	ld	(#_scroll_limit),a
	ld	a, (#_player_x + 1)
	ld	(#_scroll_limit + 1),a
;src/player.c:419: level_load_objects(current_page * PAGE_SIZE + current_column_in_page -
	ld	a, (_current_page)
	ld	c, a
	ld	b, #0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	ld	a, (_current_column_in_page)
	ld	d, #0x00
	ld	e, a
	add	hl, de
	ld	de, #0xfff9
	add	hl, de
	ld	e, l
	ld	d, h
	call	_level_load_objects
00157$:
;src/player.c:423: if (camera_x >> 3 >= load_col_at && !level_end_reached) {
	ld	hl, #_camera_x
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	ld	hl, #_load_col_at
	ld	a, c
	sub	a, (hl)
	inc	hl
	ld	a, b
	sbc	a, (hl)
	jp	C, 00180$
	ld	hl, #_level_end_reached
	bit	0, (hl)
	jp	NZ, 00180$
;src/player.c:425: level_load_column(1, levels + current_level);
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
	ld	a, #0x01
	call	_level_load_column
;src/player.c:429: load_col_at++;
	ld	hl, #_load_col_at
	inc	(hl)
	jp	NZ, 00180$
	inc	hl
	inc	(hl)
	jp	00180$
00179$:
;src/player.c:432: } else if (vel_x < 0 && player_draw_x > PLAYER_SCREEN_LEFT_MARGIN) {
	ld	a, (#_vel_x)
	bit	7, a
	jp	Z, 00180$
	ld	a, #0x0c
	ld	hl, #_player_draw_x
	sub	a, (hl)
	jp	NC, 00180$
;src/player.c:434: get_tile(player_x_next - camera_x, player_y_next + PLAYER_TOP_MARGIN);
	ldhl	sp,	#3
	ld	a, (hl+)
	sub	a, (hl)
	inc	hl
	ld	e, (hl)
	call	_get_tile
	ld	(#_tile_next_1),a
;src/player.c:436: player_y_next + marioSprites_HEIGHT - 1);
	ld	a, (_player_y_next)
	add	a, #0x0f
	ld	e, a
;src/player.c:435: tile_next_2 = get_tile(player_x_next - camera_x,
	ld	a, (_player_x_next)
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_get_tile
	ld	(#_tile_next_2),a
;src/player.c:437: if (is_tile_solid(tile_next_1) || is_tile_solid(tile_next_2)) {
	ld	a, (_tile_next_1)
	call	_is_tile_solid
	bit	0,a
	jr	NZ, 00171$
	ld	a, (_tile_next_2)
	call	_is_tile_solid
	bit	0,a
	jr	Z, 00172$
00171$:
;src/player.c:438: player_x = TILE_ALIGN(player_x_next);
	ld	a, (_player_x_next)
	ld	c, a
	ld	hl, #_player_x_next + 1
	ld	b, (hl)
	ld	hl, #0x0007
	add	hl, bc
	ld	c, h
	ld	a, l
	and	a, #0xf8
	ld	hl, #_player_x
	ld	(hl+), a
;src/player.c:439: player_x_upscaled = player_x << 4;
	ld	a, c
	ld	(hl-), a
	ld	a, (hl)
	ld	(#_player_x_upscaled),a
	ld	a, (#_player_x + 1)
	ld	(#_player_x_upscaled + 1),a
	ld	a, #0x04
00709$:
	ld	hl, #_player_x_upscaled
	sla	(hl)
	inc	hl
	rl	(hl)
	dec	a
	jr	NZ, 00709$
	jr	00180$
00172$:
;src/player.c:441: if (is_coin(tile_next_1)) {
	ld	a, (_tile_next_1)
	call	_is_coin
	bit	0,a
	jr	Z, 00169$
;src/player.c:443: player_y_next + PLAYER_TOP_MARGIN);
	ld	a, (_player_y_next)
	add	a, #0x08
	ld	e, a
;src/player.c:442: on_get_coin_background(player_x_next - camera_x,
	ld	a, (_player_x_next)
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_on_get_coin_background
	jr	00170$
00169$:
;src/player.c:444: } else if (is_coin(tile_next_2)) {
	ld	a, (_tile_next_2)
	call	_is_coin
	bit	0,a
	jr	Z, 00170$
;src/player.c:446: player_y_next + marioSprites_HEIGHT - 1);
	ld	a, (_player_y_next)
	add	a, #0x0f
	ld	e, a
;src/player.c:445: on_get_coin_background(player_x_next - camera_x,
	ld	a, (_player_x_next)
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_on_get_coin_background
00170$:
;src/player.c:449: player_x_upscaled = player_x_next_upscaled;
	ld	a, (#_player_x_next_upscaled)
	ld	(#_player_x_upscaled),a
	ld	a, (#_player_x_next_upscaled + 1)
	ld	hl, #_player_x_upscaled + 1
;src/player.c:450: player_x = player_x_upscaled >> 4;
	ld	(hl-), a
	ld	a, (hl)
	ld	(#_player_x),a
	ld	a, (#_player_x_upscaled + 1)
	ld	hl, #_player_x + 1
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
00180$:
;src/player.c:454: player_x_next_upscaled = player_x_upscaled;
	ld	a, (#_player_x_upscaled)
	ld	(#_player_x_next_upscaled),a
	ld	a, (#_player_x_upscaled + 1)
	ld	(#_player_x_next_upscaled + 1),a
;src/player.c:455: player_y_next_upscaled = player_y_upscaled + vel_y;
	ld	a, (_vel_y)
	ld	c, a
	rlca
	sbc	a, a
	ld	b, a
	ld	a, (_player_y_upscaled)
	ld	l, a
	ld	a, (_player_y_upscaled + 1)
	ld	h, a
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	hl, #_player_y_next_upscaled
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
;src/player.c:457: player_x_next = player_x_next_upscaled >> 4;
	ld	a, (#_player_x_next_upscaled)
	ld	(#_player_x_next),a
	ld	a, (#_player_x_next_upscaled + 1)
	ld	hl, #_player_x_next + 1
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
;src/player.c:458: player_y_next = player_y_next_upscaled >> 4;
	ld	a, (#_player_y_next_upscaled)
	ld	(#_player_y_next),a
	ld	a, (#_player_y_next_upscaled + 1)
	ld	hl, #_player_y_next + 1
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
;src/player.c:372: player_y_next + PLAYER_TOP_MARGIN);
	ld	a, (hl)
;src/player.c:370: tile_next_1 = get_tile(player_x_next + MARIO_WIDTH -
	ld	hl, #_player_x_next
	ld	c, (hl)
;src/player.c:371: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	hl, #_camera_x
	ld	b, (hl)
;src/player.c:372: player_y_next + PLAYER_TOP_MARGIN);
	ldhl	sp,	#3
;src/player.c:370: tile_next_1 = get_tile(player_x_next + MARIO_WIDTH -
	ld	(hl+), a
;src/player.c:371: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
;src/player.c:460: if (vel_y > 0) {
	ld	hl, #_vel_y
	ld	e, (hl)
	xor	a, a
	ld	d, a
	sub	a, (hl)
	bit	7, e
	jr	Z, 00710$
	bit	7, d
	jr	NZ, 00711$
	cp	a, a
	jr	00711$
00710$:
	bit	7, d
	jr	Z, 00711$
	scf
00711$:
	jp	NC, 00219$
;src/player.c:463: player_y_next + marioSprites_HEIGHT - 1);
	ldhl	sp,	#3
;src/player.c:461: tile_next_1 = get_tile(player_x_next + MARIO_WIDTH -
	ld	a, (hl+)
	add	a, #0x0f
	ld	e, a
;src/player.c:462: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	a, (hl+)
	add	a, #0x06
	sub	a, (hl)
	call	_get_tile
	ld	(#_tile_next_1),a
;src/player.c:465: player_y_next + marioSprites_HEIGHT - 1);
	ld	a, (_player_y_next)
	add	a, #0x0f
	ld	e, a
;src/player.c:464: tile_next_2 = get_tile(player_x_next + PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	a, (_player_x_next)
	add	a, #0x02
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_get_tile
	ld	(#_tile_next_2),a
;src/player.c:467: if (is_tile_solid(tile_next_1) || is_tile_solid(tile_next_2) ||
	ld	a, (_tile_next_1)
	call	_is_tile_solid
	bit	0,a
	jr	NZ, 00186$
	ld	a, (_tile_next_2)
	call	_is_tile_solid
	bit	0,a
	jr	NZ, 00186$
;src/player.c:468: is_tile_passthought(tile_next_1, tile_next_2)) {
	ld	a, (_tile_next_2)
	ld	e, a
	ld	a, (_tile_next_1)
	call	_is_tile_passthought
	bit	0,a
	jr	Z, 00187$
00186$:
;src/player.c:469: player_on_touch_ground();
	call	_player_on_touch_ground
;src/player.c:470: player_y = TILE_ALIGN(player_y_next) - 8;
	ld	a, (_player_y_next)
	ld	hl, #_player_y_next + 1
	ld	h, (hl)
	ld	l, a
	ld	de, #0x0007
	add	hl, de
	ld	a, l
	and	a, #0xf8
	add	a, #0xf8
	ld	c, a
	ld	a, h
	adc	a, #0xff
	ld	hl, #_player_y
	ld	(hl), c
	inc	hl
;src/player.c:471: player_y_upscaled = player_y << 4;
	ld	(hl-), a
	ld	a, (hl)
	ld	(#_player_y_upscaled),a
	ld	a, (#_player_y + 1)
	ld	(#_player_y_upscaled + 1),a
	ld	a, #0x04
00712$:
	ld	hl, #_player_y_upscaled
	sla	(hl)
	inc	hl
	rl	(hl)
	dec	a
	jr	NZ, 00712$
	jp	00220$
00187$:
;src/player.c:473: touch_ground = FALSE;
	xor	a, a
	ld	(#_touch_ground),a
;src/player.c:475: if (is_coin(tile_next_1)) {
	ld	a, (_tile_next_1)
	call	_is_coin
	bit	0,a
	jr	Z, 00184$
;src/player.c:478: player_y_next + marioSprites_HEIGHT - 1);
	ld	a, (_player_y_next)
	add	a, #0x0f
	ld	e, a
;src/player.c:476: on_get_coin_background(player_x_next + MARIO_WIDTH -
	ld	a, (_player_x_next)
	add	a, #0x06
;src/player.c:477: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_on_get_coin_background
	jr	00185$
00184$:
;src/player.c:479: } else if (is_coin(tile_next_2)) {
	ld	a, (_tile_next_2)
	call	_is_coin
	bit	0,a
	jr	Z, 00185$
;src/player.c:482: player_y_next + marioSprites_HEIGHT - 1);
	ld	a, (_player_y_next)
	add	a, #0x0f
	ld	e, a
;src/player.c:480: on_get_coin_background(player_x_next + PLAYER_HORIZONTAL_MARGIN -
	ld	a, (_player_x_next)
	add	a, #0x02
;src/player.c:481: camera_x,
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_on_get_coin_background
00185$:
;src/player.c:485: player_y_upscaled = player_y_next_upscaled;
	ld	a, (#_player_y_next_upscaled)
	ld	(#_player_y_upscaled),a
	ld	a, (#_player_y_next_upscaled + 1)
	ld	hl, #_player_y_upscaled + 1
;src/player.c:486: player_y = player_y_upscaled >> 4;
	ld	(hl-), a
	ld	a, (hl)
	ld	(#_player_y),a
	ld	a, (#_player_y_upscaled + 1)
	ld	hl, #_player_y + 1
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
	jp	00220$
00219$:
;src/player.c:488: } else if (vel_y < 0) {
	ld	a, (#_vel_y)
	bit	7, a
	jp	Z, 00220$
;src/player.c:490: player_y_next + PLAYER_TOP_MARGIN);
	ldhl	sp,	#3
;src/player.c:489: tile_next_1 = get_tile(player_x_next + PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	a, (hl+)
	add	a, #0x08
	ld	e, a
	ld	a, (hl+)
	inc	a
	inc	a
	sub	a, (hl)
	call	_get_tile
	ld	(#_tile_next_1),a
;src/player.c:493: player_y_next + PLAYER_TOP_MARGIN);
	ld	a, (_player_y_next)
	add	a, #0x08
	ld	e, a
;src/player.c:491: tile_next_2 = get_tile(player_x_next + MARIO_WIDTH -
	ld	a, (_player_x_next)
	add	a, #0x06
;src/player.c:492: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_get_tile
	ld	(#_tile_next_2),a
;src/player.c:494: if (is_tile_solid(tile_next_1) || is_tile_solid(tile_next_2)) {
	ld	a, (_tile_next_1)
	call	_is_tile_solid
	bit	0,a
	jr	NZ, 00212$
	ld	a, (_tile_next_2)
	call	_is_tile_solid
	bit	0,a
	jp	Z, 00213$
00212$:
;src/player.c:372: player_y_next + PLAYER_TOP_MARGIN);
	ld	a, (_player_y_next)
;src/player.c:370: tile_next_1 = get_tile(player_x_next + MARIO_WIDTH -
	ld	hl, #_player_x_next
	ld	b, (hl)
;src/player.c:371: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	hl, #_camera_x
	ld	c, (hl)
;src/player.c:372: player_y_next + PLAYER_TOP_MARGIN);
;src/player.c:370: tile_next_1 = get_tile(player_x_next + MARIO_WIDTH -
;src/player.c:371: PLAYER_HORIZONTAL_MARGIN - camera_x,
;src/player.c:372: player_y_next + PLAYER_TOP_MARGIN);
	add	a, #0x08
	ld	e, a
;src/player.c:495: if (tile_next_1 == TILE_INTEROGATION_BLOCK) {
	ld	a, (#_tile_next_1)
	sub	a, #0x2c
	jr	NZ, 00194$
;src/player.c:496: on_interogation_block_hit(player_x_next + PLAYER_HORIZONTAL_MARGIN -
	ld	a, b
	inc	a
	inc	a
;src/player.c:497: camera_x,
	sub	a, c
	call	_on_interogation_block_hit
	jr	00195$
00194$:
;src/player.c:499: } else if (tile_next_2 == TILE_INTEROGATION_BLOCK) {
	ld	a, (#_tile_next_2)
	sub	a, #0x2c
	jr	NZ, 00195$
;src/player.c:500: on_interogation_block_hit(player_x_next + MARIO_WIDTH -
	ld	a, b
	add	a, #0x06
;src/player.c:501: PLAYER_HORIZONTAL_MARGIN - camera_x,
	sub	a, c
	call	_on_interogation_block_hit
00195$:
;src/player.c:372: player_y_next + PLAYER_TOP_MARGIN);
	ld	a, (_player_y_next)
;src/player.c:370: tile_next_1 = get_tile(player_x_next + MARIO_WIDTH -
	ld	hl, #_player_x_next
	ld	c, (hl)
;src/player.c:371: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	hl, #_camera_x
	ld	e, (hl)
;src/player.c:372: player_y_next + PLAYER_TOP_MARGIN);
;src/player.c:370: tile_next_1 = get_tile(player_x_next + MARIO_WIDTH -
;src/player.c:371: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ldhl	sp,	#5
	ld	(hl), e
;src/player.c:372: player_y_next + PLAYER_TOP_MARGIN);
	add	a, #0x08
	ld	e, a
;src/player.c:504: if (tile_next_1 == BREAKABLE_BLOCK) {
	ld	a, (#_tile_next_1)
	sub	a, #0x2a
	jr	NZ, 00205$
;src/player.c:489: tile_next_1 = get_tile(player_x_next + PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	a, c
	inc	a
	inc	a
;src/player.c:506: on_break_tile(player_x_next + PLAYER_HORIZONTAL_MARGIN - camera_x,
	ldhl	sp,	#5
	sub	a, (hl)
	ld	b, a
;src/player.c:505: if (player_is_big) {
	ld	hl, #_player_is_big
	bit	0, (hl)
	jr	Z, 00197$
;src/player.c:506: on_break_tile(player_x_next + PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	a, b
	call	_on_break_tile
	jr	00206$
00197$:
;src/player.c:509: on_block_bump(player_x_next + PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	a, e
	push	af
	inc	sp
	push	bc
	inc	sp
	ld	e, #b_on_block_bump
	ld	hl, #_on_block_bump
	call	___sdcc_bcall_ehl
	pop	hl
	jr	00206$
00205$:
;src/player.c:512: } else if (tile_next_2 == BREAKABLE_BLOCK) {
	ld	a, (#_tile_next_2)
	sub	a, #0x2a
	jr	NZ, 00206$
;src/player.c:461: tile_next_1 = get_tile(player_x_next + MARIO_WIDTH -
	ld	a, c
	add	a, #0x06
;src/player.c:515: camera_x,
	ldhl	sp,	#5
	sub	a, (hl)
	ld	b, a
;src/player.c:513: if (player_is_big) {
	ld	hl, #_player_is_big
	bit	0, (hl)
	jr	Z, 00200$
;src/player.c:515: camera_x,
	ld	a, b
	call	_on_break_tile
	jr	00206$
00200$:
;src/player.c:519: camera_x,
	ld	a, e
	push	af
	inc	sp
	push	bc
	inc	sp
	ld	e, #b_on_block_bump
	ld	hl, #_on_block_bump
	call	___sdcc_bcall_ehl
	pop	hl
00206$:
;src/player.c:524: if (is_coin(tile_next_1)) {
	ld	a, (_tile_next_1)
	call	_is_coin
	bit	0,a
	jr	Z, 00210$
;src/player.c:527: player_y_next + PLAYER_TOP_MARGIN);
	ld	a, (_player_y_next)
	add	a, #0x08
	ld	e, a
;src/player.c:525: on_get_coin_background(player_x_next + PLAYER_HORIZONTAL_MARGIN -
	ld	a, (_player_x_next)
	add	a, #0x02
;src/player.c:526: camera_x,
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_on_get_coin_background
	jr	00211$
00210$:
;src/player.c:528: } else if (is_coin(tile_next_2)) {
	ld	a, (_tile_next_2)
	call	_is_coin
	bit	0,a
	jr	Z, 00211$
;src/player.c:531: player_y_next + PLAYER_TOP_MARGIN);
	ld	a, (_player_y_next)
	add	a, #0x08
	ld	e, a
;src/player.c:529: on_get_coin_background(player_x_next + MARIO_WIDTH -
	ld	a, (_player_x_next)
	add	a, #0x06
;src/player.c:530: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_on_get_coin_background
00211$:
;src/player.c:534: player_y_upscaled = ((player_y_next_upscaled >> 3) << 3) + 32;
	ld	hl, #_player_y_next_upscaled
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	bc, #0x0020
	add	hl, bc
	ld	e, l
	ld	d, h
	ld	hl, #_player_y_upscaled
	ld	a, e
	ld	(hl+), a
	ld	(hl), d
;src/player.c:535: player_y = player_y_upscaled >> 4;
	ld	a, (#_player_y_upscaled)
	ld	(#_player_y),a
	ld	a, (#_player_y_upscaled + 1)
	ld	hl, #_player_y + 1
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
;src/player.c:537: vel_y = 0;
;src/player.c:538: is_jumping = FALSE;
	xor	a, a
	ld	(#_vel_y), a
	ld	(#_is_jumping),a
;src/player.c:539: current_jump = 0;
	xor	a, a
	ld	hl, #_current_jump
	ld	(hl+), a
	ld	(hl), a
	jr	00220$
00213$:
;src/player.c:541: player_y_upscaled = player_y_next_upscaled;
	ld	a, (#_player_y_next_upscaled)
	ld	(#_player_y_upscaled),a
	ld	a, (#_player_y_next_upscaled + 1)
	ld	hl, #_player_y_upscaled + 1
;src/player.c:542: player_y = player_y_upscaled >> 4;
	ld	(hl-), a
	ld	a, (hl)
	ld	(#_player_y),a
	ld	a, (#_player_y_upscaled + 1)
	ld	hl, #_player_y + 1
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
00220$:
;src/player.c:546: player_x = player_x_upscaled >> 4;
	ld	a, (#_player_x_upscaled)
	ld	(#_player_x),a
	ld	a, (#_player_x_upscaled + 1)
	ld	hl, #_player_x + 1
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
;src/player.c:547: player_y = player_y_upscaled >> 4;
	ld	a, (#_player_y_upscaled)
	ld	(#_player_y),a
	ld	a, (#_player_y_upscaled + 1)
	ld	hl, #_player_y + 1
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
;src/player.c:550: player_x + DEVICE_SPRITE_PX_OFFSET_X + PLAYER_DRAW_OFFSET_X - camera_x;
	ld	a, (_player_x)
	add	a, #0x0c
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	ld	(#_player_draw_x),a
;src/player.c:551: player_draw_y = player_y + DEVICE_SPRITE_PX_OFFSET_Y + MARGIN_TOP_PX +
	ld	a, (_player_y)
	add	a, #0x28
	ld	(#_player_draw_y),a
00237$:
;src/player.c:553: }
	add	sp, #6
	ret
___str_0:
	.ascii "H px=%d py=%d tx=%d ty=%d t1=%02x t2=%02x solid=%d"
	.db 0x0a
	.db 0x00
;src/player.c:555: void player_move_vehicle(void) BANKED {
;	---------------------------------
; Function player_move_vehicle
; ---------------------------------
	b_player_move_vehicle	= 255
_player_move_vehicle::
	add	sp, #-4
;src/player.c:556: int8_t target_vel_x = 0;
	ldhl	sp,	#3
	ld	(hl), #0x00
;src/player.c:557: int8_t target_vel_y = 0;
	ld	e, #0x00
;src/player.c:562: if (joypad_current & J_RIGHT) {
	ld	a, (_joypad_current)
;src/player.c:563: max_speed = (joypad_current & J_B) ? MAX_RUN_SPEED : MAX_WALK_SPEED;
	ld	d, a
	and	a, #0x20
	ld	c, a
;src/player.c:562: if (joypad_current & J_RIGHT) {
	bit	0, d
	jr	Z, 00104$
;src/player.c:563: max_speed = (joypad_current & J_B) ? MAX_RUN_SPEED : MAX_WALK_SPEED;
	ld	a, c
	or	a, a
	ld	a, #0x1c
	jr	NZ, 00177$
	ld	a, #0x10
00177$:
	ldhl	sp,	#3
	ld	(hl), a
;src/player.c:565: marioSpritesflip = FALSE;
	xor	a, a
	ld	(#_marioSpritesflip),a
	jr	00105$
00104$:
;src/player.c:566: } else if (joypad_current & J_LEFT) {
	bit	1, d
	jr	Z, 00105$
;src/player.c:567: max_speed = (joypad_current & J_B) ? MAX_RUN_SPEED : MAX_WALK_SPEED;
	ld	a, c
	or	a, a
	ld	a, #0x1c
	jr	NZ, 00179$
	ld	a, #0x10
00179$:
	ld	b, a
;src/player.c:568: target_vel_x = -max_speed;
	xor	a, a
	sub	a, b
	ldhl	sp,	#3
	ld	(hl), a
;src/player.c:569: marioSpritesflip = TRUE;
	ld	hl, #_marioSpritesflip
	ld	(hl), #0x01
00105$:
;src/player.c:572: if (joypad_current & J_UP) {
	bit	2, d
	jr	Z, 00109$
;src/player.c:573: max_speed = (joypad_current & J_B) ? MAX_RUN_SPEED : MAX_WALK_SPEED;
	ld	a, c
	or	a, a
	ld	c, #0x1c
	jr	NZ, 00181$
	ld	c, #0x10
00181$:
;src/player.c:574: target_vel_y = -max_speed;
	xor	a, a
	sub	a, c
	ld	e, a
	jr	00110$
00109$:
;src/player.c:575: } else if (joypad_current & J_DOWN) {
	bit	3, d
	jr	Z, 00110$
;src/player.c:576: max_speed = (joypad_current & J_B) ? MAX_RUN_SPEED : MAX_WALK_SPEED;
	ld	a, c
	or	a, a
	ld	e, #0x1c
	jr	NZ, 00183$
	ld	e, #0x10
00183$:
;src/player.c:577: target_vel_y = max_speed;
00110$:
;src/player.c:580: vel_x = apply_velocity(vel_x, target_vel_x, accel, decel);
	push	de
	ld	hl, #0x302
	push	hl
	ldhl	sp,	#7
	ld	e, (hl)
	ld	a, (_vel_x)
	call	_apply_velocity
	pop	de
	ld	(#_vel_x),a
;src/player.c:581: vel_y = apply_velocity(vel_y, target_vel_y, accel, decel);
	ld	hl, #0x302
	push	hl
	ld	a, (_vel_y)
	call	_apply_velocity
	ld	hl, #_vel_y
	ld	(hl), a
;src/player.c:583: if (vel_y > MAX_FALL_SPEED)
	ld	e, (hl)
	ld	a,#0x30
	ld	d,a
	sub	a, (hl)
	bit	7, e
	jr	Z, 00419$
	bit	7, d
	jr	NZ, 00420$
	cp	a, a
	jr	00420$
00419$:
	bit	7, d
	jr	Z, 00420$
	scf
00420$:
	jr	NC, 00112$
;src/player.c:584: vel_y = MAX_FALL_SPEED;
	ld	hl, #_vel_y
	ld	(hl), #0x30
00112$:
;src/player.c:585: if (vel_y < -MAX_FALL_SPEED)
	ld	hl, #_vel_y
	ld	a, (hl)
	xor	a, #0x80
	sub	a, #0x50
	jr	NC, 00114$
;src/player.c:586: vel_y = -MAX_FALL_SPEED;
	ld	(hl), #0xd0
00114$:
;src/player.c:589: player_x_next_upscaled = player_x_upscaled + vel_x;
	ld	a, (_vel_x)
	ld	c, a
	rlca
	sbc	a, a
	ld	b, a
	ld	a, (_player_x_upscaled)
	ld	l, a
	ld	a, (_player_x_upscaled + 1)
	ld	h, a
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	hl, #_player_x_next_upscaled
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
;src/player.c:590: player_y_next_upscaled = player_y_upscaled;
	ld	a, (#_player_y_upscaled)
	ld	(#_player_y_next_upscaled),a
	ld	a, (#_player_y_upscaled + 1)
	ld	(#_player_y_next_upscaled + 1),a
;src/player.c:592: player_x_next = player_x_next_upscaled >> 4;
	ld	a, (#_player_x_next_upscaled)
	ld	(#_player_x_next),a
	ld	a, (#_player_x_next_upscaled + 1)
	ld	hl, #_player_x_next + 1
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
;src/player.c:593: player_y_next = player_y_next_upscaled >> 4;
	ld	a, (#_player_y_next_upscaled)
	ld	(#_player_y_next),a
	ld	a, (#_player_y_next_upscaled + 1)
	ld	hl, #_player_y_next + 1
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
;src/player.c:598: player_y_next + PLAYER_TOP_MARGIN);
	ld	c, (hl)
;src/player.c:596: tile_next_1 = get_tile(player_x_next + MARIO_WIDTH -
	ld	a, (#_player_x_next)
	ldhl	sp,	#1
	ld	(hl), a
;src/player.c:597: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	a, (#_camera_x)
	ldhl	sp,	#2
;src/player.c:598: player_y_next + PLAYER_TOP_MARGIN);
	ld	(hl+), a
	ld	a, c
	add	a, #0x08
	ld	(hl), a
;src/player.c:595: if (vel_x > 0) {
	ld	hl, #_vel_x
	ld	e, (hl)
	xor	a, a
	ld	d, a
	sub	a, (hl)
	bit	7, e
	jr	Z, 00421$
	bit	7, d
	jr	NZ, 00422$
	cp	a, a
	jr	00422$
00421$:
	bit	7, d
	jr	Z, 00422$
	scf
00422$:
	jp	NC, 00147$
;src/player.c:596: tile_next_1 = get_tile(player_x_next + MARIO_WIDTH -
	ldhl	sp,	#1
;src/player.c:597: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	a, (hl+)
	add	a, #0x06
	ld	c, (hl)
	inc	hl
	sub	a, c
	ld	e, (hl)
	call	_get_tile
	ld	(#_tile_next_1),a
;src/player.c:601: player_y_next + marioSprites_HEIGHT - 1);
	ld	a, (_player_y_next)
	add	a, #0x0f
	ld	e, a
;src/player.c:599: tile_next_2 = get_tile(player_x_next + MARIO_WIDTH -
	ld	a, (_player_x_next)
	add	a, #0x06
;src/player.c:600: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_get_tile
	ld	(#_tile_next_2),a
;src/player.c:602: if (is_tile_solid(tile_next_1) || is_tile_solid(tile_next_2)) {
	ld	a, (_tile_next_1)
	call	_is_tile_solid
	bit	0,a
	jr	NZ, 00130$
	ld	a, (_tile_next_2)
	call	_is_tile_solid
	bit	0,a
	jr	Z, 00131$
00130$:
;src/player.c:603: player_x = TILE_ALIGN(player_x_next) - 7;
	ld	a, (_player_x_next)
	ld	hl, #_player_x_next + 1
	ld	h, (hl)
	ld	l, a
	ld	de, #0x0007
	add	hl, de
	ld	a, l
	and	a, #0xf8
	add	a, #0xf9
	ld	c, a
	ld	a, h
	adc	a, #0xff
	ld	hl, #_player_x
	ld	(hl), c
	inc	hl
;src/player.c:604: player_x_upscaled = player_x << 4;
	ld	(hl-), a
	ld	a, (hl)
	ld	(#_player_x_upscaled),a
	ld	a, (#_player_x + 1)
	ld	(#_player_x_upscaled + 1),a
	ld	a, #0x04
00423$:
	ld	hl, #_player_x_upscaled
	sla	(hl)
	inc	hl
	rl	(hl)
;src/player.c:605: vel_x = 0;
	dec	a
	jr	NZ, 00423$
	ld	(#_vel_x),a
	jp	00148$
00131$:
;src/player.c:607: if (is_coin(tile_next_1)) {
	ld	a, (_tile_next_1)
	call	_is_coin
	bit	0,a
	jr	Z, 00118$
;src/player.c:610: player_y_next + PLAYER_TOP_MARGIN);
	ld	a, (_player_y_next)
	add	a, #0x08
	ld	e, a
;src/player.c:608: on_get_coin_background(player_x_next + MARIO_WIDTH -
	ld	a, (_player_x_next)
	add	a, #0x06
;src/player.c:609: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_on_get_coin_background
	jr	00119$
00118$:
;src/player.c:611: } else if (is_coin(tile_next_2)) {
	ld	a, (_tile_next_2)
	call	_is_coin
	bit	0,a
	jr	Z, 00119$
;src/player.c:614: player_y_next + marioSprites_HEIGHT - 1);
	ld	a, (_player_y_next)
	add	a, #0x0f
	ld	e, a
;src/player.c:612: on_get_coin_background(player_x_next + MARIO_WIDTH -
	ld	a, (_player_x_next)
	add	a, #0x06
;src/player.c:613: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_on_get_coin_background
00119$:
;src/player.c:617: if (tile_next_1 == SWITCH) {
	ld	a, (#_tile_next_1)
	sub	a, #0x3d
	jr	NZ, 00121$
;src/player.c:618: init();
	call	_init
;src/player.c:619: map_column = 0;
	xor	a, a
	ld	(#_map_column),a
;src/player.c:620: current_level = (++current_level) % NB_LEVELS;
	ld	hl, #_current_level
	inc	(hl)
	ld	a, (hl)
	ld	e, #0x0c
	call	__moduchar
	ld	hl, #_current_level
	ld	(hl), c
;src/player.c:621: level_set_current();
	call	_level_set_current
00121$:
;src/player.c:624: player_x_upscaled = player_x_next_upscaled;
	ld	a, (#_player_x_next_upscaled)
	ld	(#_player_x_upscaled),a
	ld	a, (#_player_x_next_upscaled + 1)
	ld	hl, #_player_x_upscaled + 1
;src/player.c:625: player_x = player_x_upscaled >> 4;
	ld	(hl-), a
	ld	a, (hl)
	ld	(#_player_x),a
	ld	a, (#_player_x_upscaled + 1)
	ld	hl, #_player_x + 1
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
;src/player.c:627: if (load_col_at == current_map_width_in_tiles - DEVICE_SCREEN_WIDTH + 1) {
	ld	hl, #_current_map_width_in_tiles
	ld	a, (hl+)
	add	a, #0xed
	ld	c, a
	ld	a, (hl)
	adc	a, #0xff
	ld	b, a
	ld	a, (_load_col_at)
	ld	e, a
	ld	hl, #_load_col_at + 1
	ld	d, (hl)
	ld	a, e
	sub	a, c
	jr	NZ, 00123$
	ld	a, d
	sub	a, b
	jr	NZ, 00123$
;src/player.c:628: level_end_reached = true;
	ld	hl, #_level_end_reached
	ld	(hl), #0x01
;src/player.c:629: camera_x = current_map_width - DEVICE_SCREEN_PX_WIDTH;
	ld	hl, #_current_map_width
	ld	a, (hl+)
	add	a, #0x60
	ld	c, a
	ld	a, (hl)
	adc	a, #0xff
	ld	b, a
	ld	hl, #_camera_x
	ld	a, c
	ld	(hl+), a
;src/player.c:630: move_bkg(camera_x, SCROLL_TOP_OFFSET);
	ld	a, b
	ld	(hl-), a
	ld	a, (hl)
	ldh	(_SCX_REG + 0), a
;/home/odrevet/projects/gbdk/include/gb/gb.h:1461: SCX_REG=x, SCY_REG=y;
	ld	a, #0xf0
	ldh	(_SCY_REG + 0), a
;src/player.c:630: move_bkg(camera_x, SCROLL_TOP_OFFSET);
00123$:
;src/player.c:633: if (!level_end_reached && player_x > scroll_limit) {
	ld	hl, #_level_end_reached
	bit	0, (hl)
	jp	NZ, 00125$
	ld	de, #_scroll_limit
	ld	hl, #_player_x
	ld	a, (de)
	inc	de
	sub	a, (hl)
	inc	hl
	ld	a, (de)
	sbc	a, (hl)
	jr	NC, 00125$
;src/player.c:634: int16_t player_movement = player_x - scroll_limit;
	ld	a, (#_player_x)
	ld	hl, #_scroll_limit
	sub	a, (hl)
	ld	c, a
	ld	a, (#_player_x + 1)
	ld	hl, #_scroll_limit + 1
	sbc	a, (hl)
	ld	b, a
;src/player.c:635: camera_x_upscaled += (player_movement << 4);
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	c, l
	ld	b, h
	ld	hl, #_camera_x_upscaled
	ld	a, (hl)
	add	a, c
	ld	(hl+), a
	ld	a, (hl)
	adc	a, b
;src/player.c:636: camera_x = camera_x_upscaled >> 4;
	ld	(hl-), a
	ld	a, (hl)
	ld	(#_camera_x),a
	ld	a, (#_camera_x_upscaled + 1)
	ld	hl, #_camera_x + 1
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
;src/player.c:637: move_bkg(camera_x, SCROLL_TOP_OFFSET);
	ld	a, (hl)
	ldh	(_SCX_REG + 0), a
;/home/odrevet/projects/gbdk/include/gb/gb.h:1461: SCX_REG=x, SCY_REG=y;
	ld	a, #0xf0
	ldh	(_SCY_REG + 0), a
;src/player.c:638: scroll_limit = player_x;
	ld	a, (#_player_x)
	ld	(#_scroll_limit),a
	ld	a, (#_player_x + 1)
	ld	(#_scroll_limit + 1),a
;src/player.c:639: level_load_objects(current_page * PAGE_SIZE + current_column_in_page -
	ld	a, (_current_page)
	ld	c, a
	ld	b, #0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	ld	a, (_current_column_in_page)
	ld	d, #0x00
	ld	e, a
	add	hl, de
	ld	de, #0xfff9
	add	hl, de
	ld	e, l
	ld	d, h
	call	_level_load_objects
00125$:
;src/player.c:643: if (camera_x >> 3 >= load_col_at && !level_end_reached) {
	ld	hl, #_camera_x
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	ld	hl, #_load_col_at
	ld	a, c
	sub	a, (hl)
	inc	hl
	ld	a, b
	sbc	a, (hl)
	jp	C, 00148$
	ld	hl, #_level_end_reached
	bit	0, (hl)
	jp	NZ, 00148$
;src/player.c:645: level_load_column(1, levels + current_level);
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
	ld	a, #0x01
	call	_level_load_column
;src/player.c:649: load_col_at++;
	ld	hl, #_load_col_at
	inc	(hl)
	jp	NZ, 00148$
	inc	hl
	inc	(hl)
	jp	00148$
00147$:
;src/player.c:652: } else if (vel_x < 0 && player_draw_x > PLAYER_SCREEN_LEFT_MARGIN) {
	ld	a, (#_vel_x)
	bit	7, a
	jp	Z, 00148$
	ld	a, #0x0c
	ld	hl, #_player_draw_x
	sub	a, (hl)
	jp	NC, 00148$
;src/player.c:654: get_tile(player_x_next - camera_x, player_y_next + PLAYER_TOP_MARGIN);
	ldhl	sp,	#1
	ld	a, (hl+)
	sub	a, (hl)
	inc	hl
	ld	e, (hl)
	call	_get_tile
	ld	(#_tile_next_1),a
;src/player.c:656: player_y_next + marioSprites_HEIGHT - 1);
	ld	a, (_player_y_next)
	ldhl	sp,	#3
	ld	(hl), a
	ld	a, (hl-)
	add	a, #0x0f
	ld	(hl), a
;src/player.c:655: tile_next_2 = get_tile(player_x_next - camera_x,
	ld	a, (#_player_x_next)
	ldhl	sp,	#3
	ld	(hl), a
	ld	a, (_camera_x)
	ld	c, a
	ld	a, (hl)
	sub	a, c
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	a, (hl)
	call	_get_tile
	ld	(#_tile_next_2),a
;src/player.c:657: if (is_tile_solid(tile_next_1) || is_tile_solid(tile_next_2)) {
	ld	a, (_tile_next_1)
	call	_is_tile_solid
	bit	0,a
	jr	NZ, 00139$
	ld	a, (_tile_next_2)
	call	_is_tile_solid
	bit	0,a
	jr	Z, 00140$
00139$:
;src/player.c:658: player_x = TILE_ALIGN(player_x_next);
	ld	a, (#_player_x_next)
	ldhl	sp,	#2
	ld	(hl), a
	ld	a, (#_player_x_next + 1)
	ldhl	sp,	#3
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0007
	add	hl, de
	inc	sp
	inc	sp
	push	hl
	ldhl	sp,	#0
	ld	a, (hl+)
	inc	hl
	and	a, #0xf8
	ld	(hl-), a
	ld	a, (hl+)
	inc	hl
	ld	(hl-), a
	ld	a, (hl)
	ld	(#_player_x),a
	ldhl	sp,	#3
	ld	a, (hl)
	ld	hl, #_player_x + 1
;src/player.c:659: player_x_upscaled = player_x << 4;
	ld	(hl-), a
	ld	a, (hl)
	ld	(#_player_x_upscaled),a
	ld	a, (#_player_x + 1)
	ld	(#_player_x_upscaled + 1),a
	ld	a, #0x04
00429$:
	ld	hl, #_player_x_upscaled
	sla	(hl)
	inc	hl
	rl	(hl)
;src/player.c:660: vel_x = 0;
	dec	a
	jr	NZ, 00429$
	ld	(#_vel_x),a
	jr	00148$
00140$:
;src/player.c:662: if (is_coin(tile_next_1)) {
	ld	a, (_tile_next_1)
	call	_is_coin
	bit	0,a
	jr	Z, 00137$
;src/player.c:664: player_y_next + PLAYER_TOP_MARGIN);
	ld	a, (_player_y_next)
	add	a, #0x08
	ld	e, a
;src/player.c:663: on_get_coin_background(player_x_next - camera_x,
	ld	a, (_player_x_next)
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_on_get_coin_background
	jr	00138$
00137$:
;src/player.c:665: } else if (is_coin(tile_next_2)) {
	ld	a, (_tile_next_2)
	call	_is_coin
	bit	0,a
	jr	Z, 00138$
;src/player.c:667: player_y_next + marioSprites_HEIGHT - 1);
	ld	a, (_player_y_next)
	add	a, #0x0f
	ld	e, a
;src/player.c:666: on_get_coin_background(player_x_next - camera_x,
	ld	a, (_player_x_next)
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_on_get_coin_background
00138$:
;src/player.c:670: player_x_upscaled = player_x_next_upscaled;
	ld	a, (#_player_x_next_upscaled)
	ld	(#_player_x_upscaled),a
	ld	a, (#_player_x_next_upscaled + 1)
	ld	hl, #_player_x_upscaled + 1
;src/player.c:671: player_x = player_x_upscaled >> 4;
	ld	(hl-), a
	ld	a, (hl)
	ld	(#_player_x),a
	ld	a, (#_player_x_upscaled + 1)
	ld	hl, #_player_x + 1
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
00148$:
;src/player.c:676: player_x_next_upscaled = player_x_upscaled;
	ld	a, (#_player_x_upscaled)
	ld	(#_player_x_next_upscaled),a
	ld	a, (#_player_x_upscaled + 1)
	ld	(#_player_x_next_upscaled + 1),a
;src/player.c:677: player_y_next_upscaled = player_y_upscaled + vel_y;
	ld	a, (_vel_y)
	ld	c, a
	rlca
	sbc	a, a
	ld	b, a
	ld	a, (_player_y_upscaled)
	ld	l, a
	ld	a, (_player_y_upscaled + 1)
	ld	h, a
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	hl, #_player_y_next_upscaled
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
;src/player.c:679: player_x_next = player_x_next_upscaled >> 4;
	ld	a, (#_player_x_next_upscaled)
	ld	(#_player_x_next),a
	ld	a, (#_player_x_next_upscaled + 1)
	ld	hl, #_player_x_next + 1
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
;src/player.c:680: player_y_next = player_y_next_upscaled >> 4;
	ld	a, (#_player_y_next_upscaled)
	ld	(#_player_y_next),a
	ld	a, (#_player_y_next_upscaled + 1)
	ld	hl, #_player_y_next + 1
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
;src/player.c:598: player_y_next + PLAYER_TOP_MARGIN);
	ld	a, (hl)
;src/player.c:596: tile_next_1 = get_tile(player_x_next + MARIO_WIDTH -
	ld	hl, #_player_x_next
	ld	c, (hl)
;src/player.c:597: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	hl, #_camera_x
	ld	b, (hl)
;src/player.c:598: player_y_next + PLAYER_TOP_MARGIN);
	ldhl	sp,	#1
;src/player.c:596: tile_next_1 = get_tile(player_x_next + MARIO_WIDTH -
	ld	(hl+), a
;src/player.c:597: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
;src/player.c:682: if (vel_y > 0) {
	ld	hl, #_vel_y
	ld	e, (hl)
	xor	a, a
	ld	d, a
	sub	a, (hl)
	bit	7, e
	jr	Z, 00430$
	bit	7, d
	jr	NZ, 00431$
	cp	a, a
	jr	00431$
00430$:
	bit	7, d
	jr	Z, 00431$
	scf
00431$:
	jp	NC, 00170$
;src/player.c:686: player_y_next + marioSprites_HEIGHT - 1);
	ldhl	sp,	#1
;src/player.c:684: tile_next_1 = get_tile(player_x_next + MARIO_WIDTH -
	ld	a, (hl+)
	add	a, #0x0f
	ld	e, a
;src/player.c:685: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	a, (hl+)
	add	a, #0x06
	sub	a, (hl)
	call	_get_tile
	ld	(#_tile_next_1),a
;src/player.c:688: player_y_next + marioSprites_HEIGHT - 1);
	ld	a, (_player_y_next)
	add	a, #0x0f
	ld	e, a
;src/player.c:687: tile_next_2 = get_tile(player_x_next + PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	a, (_player_x_next)
	add	a, #0x02
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_get_tile
	ld	(#_tile_next_2),a
;src/player.c:690: if (is_tile_solid(tile_next_1) || is_tile_solid(tile_next_2)) {
	ld	a, (_tile_next_1)
	call	_is_tile_solid
	bit	0,a
	jr	NZ, 00154$
	ld	a, (_tile_next_2)
	call	_is_tile_solid
	bit	0,a
	jr	Z, 00155$
00154$:
;src/player.c:691: player_y = TILE_ALIGN(player_y_next) - 8;
	ld	a, (_player_y_next)
	ld	hl, #_player_y_next + 1
	ld	h, (hl)
	ld	l, a
	ld	de, #0x0007
	add	hl, de
	ld	a, l
	and	a, #0xf8
	add	a, #0xf8
	ld	c, a
	ld	a, h
	adc	a, #0xff
	ld	hl, #_player_y
	ld	(hl), c
	inc	hl
;src/player.c:692: player_y_upscaled = player_y << 4;
	ld	(hl-), a
	ld	a, (hl)
	ld	(#_player_y_upscaled),a
	ld	a, (#_player_y + 1)
	ld	(#_player_y_upscaled + 1),a
	ld	a, #0x04
00432$:
	ld	hl, #_player_y_upscaled
	sla	(hl)
	inc	hl
	rl	(hl)
;src/player.c:693: vel_y = 0;
	dec	a
	jr	NZ, 00432$
	ld	(#_vel_y),a
	jp	00171$
00155$:
;src/player.c:695: if (is_coin(tile_next_1)) {
	ld	a, (_tile_next_1)
	call	_is_coin
	bit	0,a
	jr	Z, 00152$
;src/player.c:698: player_y_next + marioSprites_HEIGHT - 1);
	ld	a, (_player_y_next)
	add	a, #0x0f
	ld	e, a
;src/player.c:696: on_get_coin_background(player_x_next + MARIO_WIDTH -
	ld	a, (_player_x_next)
	add	a, #0x06
;src/player.c:697: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_on_get_coin_background
	jr	00153$
00152$:
;src/player.c:699: } else if (is_coin(tile_next_2)) {
	ld	a, (_tile_next_2)
	call	_is_coin
	bit	0,a
	jr	Z, 00153$
;src/player.c:702: player_y_next + marioSprites_HEIGHT - 1);
	ld	a, (_player_y_next)
	add	a, #0x0f
	ld	e, a
;src/player.c:700: on_get_coin_background(player_x_next + PLAYER_HORIZONTAL_MARGIN -
	ld	a, (_player_x_next)
	add	a, #0x02
;src/player.c:701: camera_x,
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_on_get_coin_background
00153$:
;src/player.c:705: player_y_upscaled = player_y_next_upscaled;
	ld	a, (#_player_y_next_upscaled)
	ld	(#_player_y_upscaled),a
	ld	a, (#_player_y_next_upscaled + 1)
	ld	hl, #_player_y_upscaled + 1
;src/player.c:706: player_y = player_y_upscaled >> 4;
	ld	(hl-), a
	ld	a, (hl)
	ld	(#_player_y),a
	ld	a, (#_player_y_upscaled + 1)
	ld	hl, #_player_y + 1
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
	jp	00171$
00170$:
;src/player.c:708: } else if (vel_y < 0) {
	ld	a, (#_vel_y)
	bit	7, a
	jp	Z, 00171$
;src/player.c:711: player_y_next + PLAYER_TOP_MARGIN);
	ldhl	sp,	#1
;src/player.c:710: tile_next_1 = get_tile(player_x_next + PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	a, (hl+)
	add	a, #0x08
	ld	e, a
	ld	a, (hl+)
	inc	a
	inc	a
	sub	a, (hl)
	call	_get_tile
	ld	(#_tile_next_1),a
;src/player.c:714: player_y_next + PLAYER_TOP_MARGIN);
	ld	a, (_player_y_next)
	add	a, #0x08
	ld	e, a
;src/player.c:712: tile_next_2 = get_tile(player_x_next + MARIO_WIDTH -
	ld	a, (_player_x_next)
	add	a, #0x06
;src/player.c:713: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_get_tile
	ld	(#_tile_next_2),a
;src/player.c:716: if (is_tile_solid(tile_next_1) || is_tile_solid(tile_next_2)) {
	ld	a, (_tile_next_1)
	call	_is_tile_solid
	bit	0,a
	jr	NZ, 00163$
	ld	a, (_tile_next_2)
	call	_is_tile_solid
	bit	0,a
	jr	Z, 00164$
00163$:
;src/player.c:717: player_y_upscaled = ((player_y_next_upscaled >> 3) << 3) + 32;
	ld	hl, #_player_y_next_upscaled
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	bc, #0x0020
	add	hl, bc
	ld	e, l
	ld	d, h
	ld	hl, #_player_y_upscaled
	ld	a, e
	ld	(hl+), a
	ld	(hl), d
;src/player.c:718: player_y = player_y_upscaled >> 4;
	ld	a, (#_player_y_upscaled)
	ld	(#_player_y),a
	ld	a, (#_player_y_upscaled + 1)
	ld	hl, #_player_y + 1
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
;src/player.c:719: vel_y = 0;
	xor	a, a
	ld	(#_vel_y),a
	jr	00171$
00164$:
;src/player.c:721: if (is_coin(tile_next_1)) {
	ld	a, (_tile_next_1)
	call	_is_coin
	bit	0,a
	jr	Z, 00161$
;src/player.c:724: player_y_next + PLAYER_TOP_MARGIN);
	ld	a, (_player_y_next)
	add	a, #0x08
	ld	e, a
;src/player.c:722: on_get_coin_background(player_x_next + PLAYER_HORIZONTAL_MARGIN -
	ld	a, (_player_x_next)
	add	a, #0x02
;src/player.c:723: camera_x,
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_on_get_coin_background
	jr	00162$
00161$:
;src/player.c:725: } else if (is_coin(tile_next_2)) {
	ld	a, (_tile_next_2)
	call	_is_coin
	bit	0,a
	jr	Z, 00162$
;src/player.c:728: player_y_next + PLAYER_TOP_MARGIN);
	ld	a, (_player_y_next)
	add	a, #0x08
	ld	e, a
;src/player.c:726: on_get_coin_background(player_x_next + MARIO_WIDTH -
	ld	a, (_player_x_next)
	add	a, #0x06
;src/player.c:727: PLAYER_HORIZONTAL_MARGIN - camera_x,
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	call	_on_get_coin_background
00162$:
;src/player.c:731: player_y_upscaled = player_y_next_upscaled;
	ld	a, (#_player_y_next_upscaled)
	ld	(#_player_y_upscaled),a
	ld	a, (#_player_y_next_upscaled + 1)
	ld	hl, #_player_y_upscaled + 1
;src/player.c:732: player_y = player_y_upscaled >> 4;
	ld	(hl-), a
	ld	a, (hl)
	ld	(#_player_y),a
	ld	a, (#_player_y_upscaled + 1)
	ld	hl, #_player_y + 1
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
00171$:
;src/player.c:736: player_x = player_x_upscaled >> 4;
	ld	a, (#_player_x_upscaled)
	ld	(#_player_x),a
	ld	a, (#_player_x_upscaled + 1)
	ld	hl, #_player_x + 1
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
;src/player.c:737: player_y = player_y_upscaled >> 4;
	ld	a, (#_player_y_upscaled)
	ld	(#_player_y),a
	ld	a, (#_player_y_upscaled + 1)
	ld	hl, #_player_y + 1
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
;src/player.c:740: player_x + DEVICE_SPRITE_PX_OFFSET_X + PLAYER_DRAW_OFFSET_X - camera_x;
	ld	a, (_player_x)
	add	a, #0x0c
	ld	hl, #_camera_x
	ld	c, (hl)
	sub	a, c
	ld	(#_player_draw_x),a
;src/player.c:741: player_draw_y = player_y + DEVICE_SPRITE_PX_OFFSET_Y + MARGIN_TOP_PX +
	ld	a, (_player_y)
	add	a, #0x28
	ld	(#_player_draw_y),a
;src/player.c:743: }
	add	sp, #4
	ret
;src/player.c:752: bool player_is_on_platform(void) BANKED {
;	---------------------------------
; Function player_is_on_platform
; ---------------------------------
	b_player_is_on_platform	= 255
_player_is_on_platform::
	add	sp, #-5
;src/player.c:753: for (uint8_t index_platform = 0; index_platform < platform_moving_count;
	ldhl	sp,	#4
	ld	(hl), #0x00
00108$:
	ldhl	sp,	#4
	ld	a, (hl)
	ld	hl, #_platform_moving_count
	sub	a, (hl)
	jp	NC, 00106$
;src/player.c:755: if (player_y_upscaled + 128 > platforms_moving[index_platform].y &&
	ld	a, (_player_y_upscaled)
	ld	hl, #_player_y_upscaled + 1
	ld	d, (hl)
	ld	e, a
	ld	hl, #0x0080
	add	hl, de
	inc	sp
	inc	sp
	push	hl
	ld	bc, #_platforms_moving+0
	ldhl	sp,	#4
	ld	e, (hl)
	ld	d, #0x00
	ld	l, e
	ld	h, d
	add	hl, hl
	add	hl, de
	add	hl, hl
	add	hl, de
	add	hl, hl
	add	hl, bc
	ld	c,l
	ld	b,h
	inc	hl
	inc	hl
	ld	e, l
	ld	d, h
	ld	a, (de)
	ldhl	sp,	#2
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	pop	de
	push	de
	ldhl	sp,	#2
	ld	a, (hl+)
	sub	a, e
	ld	a, (hl)
	sbc	a, d
	jp	NC, 00109$
;src/player.c:757: platforms_moving[index_platform].y + (8 * 16) &&
	dec	hl
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0080
	add	hl, de
	ld	e, l
	ld	d, h
	ldhl	sp,	#0
	ld	a, e
	sub	a, (hl)
	inc	hl
	ld	a, d
	sbc	a, (hl)
	jr	C, 00109$
;src/player.c:759: platforms_moving[index_platform].x + (3 * 8 * 16) &&
	ld	e, c
	ld	d, b
	ld	a, (de)
	ldhl	sp,	#2
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0180
	add	hl, de
	ld	a, (_player_x_upscaled)
	ld	e, a
	push	hl
	ld	hl, #_player_x_upscaled + 1
	ld	d, (hl)
	pop	hl
	ld	a, l
	sub	a, e
	ld	a, h
	sbc	a, d
	jr	C, 00109$
;src/player.c:760: player_x_upscaled > platforms_moving[index_platform].x) {
	push	de
	ldhl	sp,	#4
	ld	e, l
	ld	d, h
	ld	hl, #_player_x_upscaled
	ld	a, (de)
	inc	de
	sub	a, (hl)
	inc	hl
	ld	a, (de)
	sbc	a, (hl)
	pop	de
	jr	NC, 00109$
;src/player.c:762: player_x_upscaled += platforms_moving[index_platform].vel_x;
	ld	hl, #0x0006
	add	hl, bc
	ld	a, (hl)
	ld	l, a
	rlca
	sbc	a, a
	ld	h, a
	add	hl, de
	ld	e, l
	ld	d, h
	ld	hl, #_player_x_upscaled
	ld	a, e
	ld	(hl+), a
;src/player.c:763: player_x = player_x_upscaled >> 4;
	ld	a, d
	ld	(hl-), a
	ld	a, (hl)
	ld	(#_player_x),a
	ld	a, (#_player_x_upscaled + 1)
	ld	hl, #_player_x + 1
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
;src/player.c:764: vel_y = platforms_moving[index_platform].vel_y;
	ld	hl, #0x0007
	add	hl, bc
	ld	a, (hl)
	ld	(#_vel_y),a
;src/player.c:765: player_on_touch_ground();
	call	_player_on_touch_ground
;src/player.c:766: return TRUE;
	ld	a, #0x01
	jr	00110$
00109$:
;src/player.c:754: index_platform++) {
	ldhl	sp,	#4
	inc	(hl)
	jp	00108$
00106$:
;src/player.c:769: return FALSE;
	xor	a, a
00110$:
;src/player.c:770: }
	add	sp, #5
	ret
	.area _CODE_255
	.area _INITIALIZER
__xinit____EMU_PROFILER_INIT:
	.dw _EMU_profiler_message
__xinit__is_jumping:
	.db #0x00	;  0
__xinit__touch_ground:
	.db #0x00	;  0
__xinit__current_jump:
	.dw #0x0000
__xinit__player_frame:
	.db #0x00	; 0
__xinit__frame_counter:
	.db #0x00	; 0
__xinit__player_is_big:
	.db #0x00	;  0
	.area _CABS (ABS)
