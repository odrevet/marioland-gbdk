;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler
; Version 4.5.1 #15267 (Linux)
;--------------------------------------------------------
	.module game
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _player_warp_to
	.globl _player_draw
	.globl _set_level
	.globl _level_set_current
	.globl _hUGE_mute_channel
	.globl _hud_update_lives
	.globl _hud_update_time
	.globl _text_print_string
	.globl _vsync
	.globl _joypad
	.globl _delay
	.globl _init
	.globl _state_title
	.globl _state_pause
	.globl _die
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
;src/game.c:10: void init(void) {
;	---------------------------------
; Function init
; ---------------------------------
_init::
;src/game.c:11: time = TIME_INITIAL_VALUE;
	ld	hl, #_time
	xor	a, a
	ld	(hl+), a
	ld	(hl), #0x32
;src/game.c:13: camera_x = 0;
	xor	a, a
	ld	hl, #_camera_x
	ld	(hl+), a
	ld	(hl), a
;src/game.c:14: camera_x_upscaled = 0;
	xor	a, a
	ld	hl, #_camera_x_upscaled
	ld	(hl+), a
	ld	(hl), a
;src/game.c:16: player_x_upscaled = (5 * TILE_SIZE) << 4;
	ld	hl, #_player_x_upscaled
	ld	a, #0x80
	ld	(hl+), a
	ld	(hl), #0x02
;src/game.c:18: if(current_level >= LEVEL_WORLD2_START && current_level <= LEVEL_WORLD2_END){
	ld	hl, #_current_level
	ld	a, (hl)
	sub	a, #0x03
	jr	C, 00102$
	ld	a, #0x05
	sub	a, (hl)
	jr	C, 00102$
;src/game.c:19: player_y_upscaled = (12 * TILE_SIZE) << 4;
	ld	hl, #_player_y_upscaled
	xor	a, a
	ld	(hl+), a
	ld	(hl), #0x06
	jr	00103$
00102$:
;src/game.c:22: player_y_upscaled = (14 * TILE_SIZE) << 4;
	ld	hl, #_player_y_upscaled
	xor	a, a
	ld	(hl+), a
	ld	(hl), #0x07
00103$:
;src/game.c:27: player_draw_x = player_x_upscaled >> 4;
	ld	hl, #_player_draw_x
	ld	(hl), #0x28
;src/game.c:28: player_draw_y = player_y_upscaled >> 4;
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
;src/game.c:29: player_x_next_upscaled = player_x_upscaled;
	ld	hl, #_player_x_next_upscaled
	ld	a, #0x80
	ld	(hl+), a
	ld	(hl), #0x02
;src/game.c:30: player_y_next_upscaled = player_y_upscaled;
	ld	a, (#_player_y_upscaled)
	ld	(#_player_y_next_upscaled),a
	ld	a, (#_player_y_upscaled + 1)
	ld	(#_player_y_next_upscaled + 1),a
;src/game.c:32: vel_x = 0;
;src/game.c:33: vel_y = 0;
	xor	a, a
	ld	(#_vel_x), a
	ld	(#_vel_y),a
;src/game.c:35: display_jump_frame = FALSE;
;src/game.c:36: display_slide_frame = FALSE;
	xor	a, a
	ld	(#_display_jump_frame), a
	ld	(#_display_slide_frame),a
;src/game.c:37: display_walk_animation = FALSE;
;src/game.c:39: frame_counter = 0;
	xor	a, a
	ld	(#_display_walk_animation), a
	ld	(#_frame_counter),a
;src/game.c:40: marioSpritesflip = FALSE;
;src/game.c:41: touch_ground = FALSE;
	xor	a, a
	ld	(#_marioSpritesflip), a
	ld	(#_touch_ground),a
;src/game.c:43: current_column_in_page = 0;
;src/game.c:44: map_column = 0;
	xor	a, a
	ld	(#_current_column_in_page), a
	ld	(#_map_column),a
;src/game.c:45: }
	ret
;src/game.c:47: void state_title(void) {
;	---------------------------------
; Function state_title
; ---------------------------------
_state_title::
;src/game.c:48: while (1) {
00105$:
;src/game.c:49: vsync();
	call	_vsync
;src/game.c:51: joypad_previous = joypad_current;
	ld	a, (#_joypad_current)
	ld	(#_joypad_previous),a
;src/game.c:52: joypad_current = joypad();
	call	_joypad
;src/game.c:53: if (joypad_current & J_START && !(joypad_previous & J_START)) {
	ld	(#_joypad_current),a
	rlca
	jr	NC, 00105$
	ld	a, (_joypad_previous)
	rlca
	jr	C, 00105$
;src/game.c:54: break;
;src/game.c:57: }
	ret
;src/game.c:59: void state_pause(void) {
;	---------------------------------
; Function state_pause
; ---------------------------------
_state_pause::
;src/game.c:60: text_print_string(DEVICE_SCREEN_WIDTH - 5, 1, "PAUSE");
	ld	de, #___str_0
	push	de
	ld	e, #0x01
	ld	a, #0x0f
	call	_text_print_string
;src/game.c:62: while (1) {
00108$:
;src/game.c:63: vsync();
	call	_vsync
;src/game.c:65: joypad_previous = joypad_current;
	ld	a, (#_joypad_current)
	ld	(#_joypad_previous),a
;src/game.c:66: joypad_current = joypad();
	call	_joypad
	ld	hl, #_joypad_current
	ld	(hl), a
;src/game.c:68: if (joypad_current & J_SELECT && !(joypad_previous & J_SELECT)) {
	bit	6, (hl)
	jr	Z, 00102$
	ld	a, (_joypad_previous)
	bit	6, a
	jr	NZ, 00102$
;src/game.c:69: map_column = 0;
	xor	a, a
	ld	(#_map_column),a
;src/game.c:70: current_level = (++current_level) % NB_LEVELS;
	ld	hl, #_current_level
	inc	(hl)
	ld	a, (hl)
	ld	e, #0x0c
	call	__moduchar
	ld	hl, #_current_level
	ld	(hl), c
;src/game.c:71: init();
	call	_init
;src/game.c:72: level_set_current();
	call	_level_set_current
00102$:
;src/game.c:75: if (joypad_current & J_START && !(joypad_previous & J_START)) {
	ld	a, (_joypad_current)
	rlca
	jr	NC, 00108$
	ld	a, (_joypad_previous)
	rlca
	jr	C, 00108$
;src/game.c:81: hUGE_mute_channel(0, HT_CH_PLAY);
	xor	a, a
	ld	e, a
	call	_hUGE_mute_channel
;src/game.c:82: hUGE_mute_channel(1, HT_CH_PLAY);
	ld	e, #0x00
	ld	a, #0x01
	call	_hUGE_mute_channel
;src/game.c:83: hUGE_mute_channel(2, HT_CH_PLAY);
	ld	e, #0x00
	ld	a, #0x02
	call	_hUGE_mute_channel
;src/game.c:84: hUGE_mute_channel(3, HT_CH_PLAY);
	ld	e, #0x00
	ld	a, #0x03
	call	_hUGE_mute_channel
;src/game.c:87: text_print_string(DEVICE_SCREEN_WIDTH - 5, 1, "     ");
	ld	de, #___str_1
	push	de
	ld	e, #0x01
	ld	a, #0x0f
	call	_text_print_string
;src/game.c:88: hud_update_time();
;src/game.c:89: }
	jp	_hud_update_time
___str_0:
	.ascii "PAUSE"
	.db 0x00
___str_1:
	.ascii "     "
	.db 0x00
;src/game.c:95: void die(void) {
;	---------------------------------
; Function die
; ---------------------------------
_die::
;src/game.c:97: hUGE_mute_channel(0, HT_CH_PLAY);
	xor	a, a
	ld	e, a
	call	_hUGE_mute_channel
;src/game.c:98: hUGE_mute_channel(1, HT_CH_PLAY);
	ld	e, #0x00
	ld	a, #0x01
	call	_hUGE_mute_channel
;src/game.c:99: hUGE_mute_channel(2, HT_CH_PLAY);
	ld	e, #0x00
	ld	a, #0x02
	call	_hUGE_mute_channel
;src/game.c:100: hUGE_mute_channel(3, HT_CH_PLAY);
	ld	e, #0x00
	ld	a, #0x03
	call	_hUGE_mute_channel
;src/game.c:105: player_frame = DEATH_ANIMATION_FRAME;  // Death pose
	ld	hl, #_player_frame
	ld	(hl), #0x06
;src/game.c:108: int16_t death_vel_y = DEATH_BOUNCE_VELOCITY;
	ld	de, #0xffd8
;src/game.c:109: uint16_t death_y = player_y_upscaled;
	ld	a, (_player_y_upscaled)
	ld	c, a
	ld	hl, #_player_y_upscaled + 1
	ld	b, (hl)
;src/game.c:113: while (player_draw_y < DEVICE_SCREEN_PX_HEIGHT ) {
00101$:
	ld	a, (#_player_draw_y)
	sub	a, #0x90
	jr	NC, 00103$
;src/game.c:115: death_vel_y += DEATH_GRAVITY;
	inc	de
	inc	de
;src/game.c:116: death_y += death_vel_y;
	ld	l, e
	ld	h, d
	add	hl, bc
	ld	c, l
	ld	b, h
;src/game.c:119: player_y = death_y >> 4;
	ld	hl, #_player_y
	ld	a, c
	ld	(hl+), a
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
;src/game.c:120: player_draw_y = player_y + DEVICE_SPRITE_PX_OFFSET_Y + 
	ld	a, (hl)
	add	a, #0x28
	ld	(#_player_draw_y),a
;src/game.c:124: player_draw(0);
	push	bc
	push	de
	xor	a, a
	call	_player_draw
	pop	de
	pop	bc
;src/game.c:127: vsync();
	call	_vsync
	jr	00101$
00103$:
;src/game.c:131: delay(2000);
	ld	de, #0x07d0
	call	_delay
;src/game.c:136: lives--;
	ld	hl, #_lives
;src/game.c:137: if (lives == 0) {
	dec	(hl)
	ld	a, (hl)
	jr	NZ, 00105$
;src/game.c:138: lives = INITIAL_LIVES;
	ld	(hl), #0x03
;src/game.c:139: current_map = 0;
	xor	a, a
	ld	hl, #_current_map
	ld	(hl+), a
	ld	(hl), a
;src/game.c:140: current_page = 0;
;src/game.c:141: current_level = 0;
	xor	a, a
	ld	(#_current_page), a
	ld	(#_current_level),a
;src/game.c:142: set_level(current_level);
	xor	a, a
	call	_set_level
00105$:
;src/game.c:145: player_warp_to(levels + current_level, 0, 5, 12);
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
	ld	hl, #0xc05
	push	hl
	xor	a, a
	call	_player_warp_to
;src/game.c:148: music_load(levels[current_level].music_bank, levels[current_level].music);
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
	ld	c, l
	ld	b, h
	ld	hl, #0x0015
	add	hl, bc
	ld	a,	(hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, c
	add	a, #0x14
	ld	c, a
	jr	NC, 00130$
	inc	b
00130$:
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
;src/game.c:151: hud_update_lives();
;src/game.c:153: }
	jp	_hud_update_lives
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
