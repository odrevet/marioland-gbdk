;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler
; Version 4.5.1 #15267 (Linux)
;--------------------------------------------------------
	.module main
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _enemy_collide
	.globl _powerups_collide
	.globl _interruptVBL
	.globl _interruptLCD
	.globl _die
	.globl _state_pause
	.globl _state_title
	.globl _init
	.globl _hud_update_lives
	.globl _hud_update_time
	.globl _hud_update_score
	.globl b_player_move_vehicle
	.globl _player_move_vehicle
	.globl b_player_move
	.globl _player_move
	.globl _player_draw
	.globl _update_frame_counter
	.globl _text_print_string
	.globl _level_set_current
	.globl _on_get_coin
	.globl b_block_bump_draw
	.globl _block_bump_draw
	.globl b_block_bump_update
	.globl _block_bump_update
	.globl _powerup_draw
	.globl _powerup_update
	.globl _platform_moving_draw
	.globl _platform_moving_update
	.globl _enemy_draw
	.globl b_enemy_update
	.globl _enemy_update
	.globl b_enemy_stomp
	.globl _enemy_stomp
	.globl b_enemy_reset_all
	.globl _enemy_reset_all
	.globl _music_pause
	.globl _music_play_isr
	.globl _memset
	.globl _coin_animated_draw
	.globl _coin_animated_update
	.globl _set_sprite_data
	.globl _set_win_tile_xy
	.globl _set_win_tiles
	.globl _set_bkg_tiles
	.globl _set_bkg_data
	.globl _vsync
	.globl _set_interrupts
	.globl _joypad
	.globl _delay
	.globl _add_low_priority_TIM
	.globl _add_LCD
	.globl _add_VBL
	.globl _window_location
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
;src/main.c:46: void interruptLCD(void) {
;	---------------------------------
; Function interruptLCD
; ---------------------------------
_interruptLCD::
;src/main.c:47: while (STAT_REG & 3)
00101$:
	ldh	a, (_STAT_REG + 0)
	and	a, #0x03
	jr	NZ, 00101$
;src/main.c:49: HIDE_WIN;
	ldh	a, (_LCDC_REG + 0)
	and	a, #0xdf
	ldh	(_LCDC_REG + 0), a
;src/main.c:50: }
	ret
_window_location:
	.db #0x10	; 16
;src/main.c:52: void interruptVBL(void) { SHOW_WIN; }
;	---------------------------------
; Function interruptVBL
; ---------------------------------
_interruptVBL::
	ldh	a, (_LCDC_REG + 0)
	or	a, #0x20
	ldh	(_LCDC_REG + 0), a
	ret
;src/main.c:55: bool powerups_collide() {
;	---------------------------------
; Function powerups_collide
; ---------------------------------
_powerups_collide::
	add	sp, #-10
;src/main.c:56: if (!powerup_active) {
	ld	hl, #_powerup_active
	bit	0, (hl)
	jr	NZ, 00102$
;src/main.c:57: return false;
	xor	a, a
	jp	00125$
00102$:
;src/main.c:60: uint16_t powerup_left = (powerup.x >> 4);
	ld	hl, #_powerup
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
	inc	sp
	inc	sp
	push	bc
;src/main.c:61: uint16_t powerup_right = (powerup.x >> 4) + TILE_SIZE;
	ld	hl, #0x0008
	add	hl, bc
	ld	c, l
	ld	b, h
	ldhl	sp,	#2
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
;src/main.c:62: uint16_t powerup_top = (powerup.y >> 4);
	ld	hl, #_powerup + 2
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
	ldhl	sp,	#4
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
;src/main.c:63: uint16_t powerup_bottom = (powerup.y >> 4) + TILE_SIZE;
	ld	hl, #0x0008
	add	hl, bc
	ld	c, l
	ld	b, h
	ldhl	sp,	#6
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
;src/main.c:65: uint16_t player_right = player_x + TILE_SIZE;
	ld	a, (_player_x)
	ld	c, a
	ld	hl, #_player_x + 1
	ld	b, (hl)
	ld	hl, #0x0008
	add	hl, bc
	ld	c, l
	ld	b, h
	ldhl	sp,	#8
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
;src/main.c:66: uint16_t player_top = player_y + 8;
	ld	a, (_player_y)
	ld	c, a
	ld	hl, #_player_y + 1
	ld	b, (hl)
	ld	hl, #0x0008
	add	hl, bc
	ld	e, l
	ld	d, h
;src/main.c:67: uint16_t player_bottom = player_y + marioSprites_HEIGHT;
	ld	hl, #0x0010
	add	hl, bc
	ld	c, l
	ld	b, h
;src/main.c:69: if (player_x < powerup_right && player_right > powerup_left &&
	push	de
	ld	de, #_player_x
	ldhl	sp,	#4
	ld	a, (de)
	inc	de
	sub	a, (hl)
	inc	hl
	ld	a, (de)
	sbc	a, (hl)
	pop	de
	jp	NC, 00107$
	push	de
	ldhl	sp,	#2
	ld	e, l
	ld	d, h
	ldhl	sp,	#10
	ld	a, (de)
	inc	de
	sub	a, (hl)
	inc	hl
	ld	a, (de)
	sbc	a, (hl)
	pop	de
	jp	NC, 00107$
;src/main.c:70: player_top < powerup_bottom && player_bottom > powerup_top) {
	ldhl	sp,	#6
	ld	a, e
	sub	a, (hl)
	inc	hl
	ld	a, d
	sbc	a, (hl)
	jr	NC, 00107$
	ldhl	sp,	#4
	ld	a, (hl+)
	sub	a, c
	ld	a, (hl)
	sbc	a, b
	jr	NC, 00107$
;src/main.c:72: if (powerup.type == POWERUP_MUSHROOM) {
	ld	a, (#(_powerup + 8) + 0)
	or	a, a
	jr	NZ, 00104$
;src/main.c:73: player_is_big = TRUE;
	ld	hl, #_player_is_big
	ld	(hl), #0x01
	jr	00105$
00104$:
;src/main.c:75: on_get_coin();
	call	_on_get_coin
00105$:
;src/main.c:79: music_play_sfx(BANK(sound_coin), sound_coin, SFX_MUTE_MASK(sound_coin),
	ld	c, #<(___mute_mask_sound_coin)
	ld	b, #<(___bank_sound_coin)
;sm83/musicmanager.h:105: if (music_sfx_priority > priority) return;
	ld	a, #0x04
	ld	hl, #_music_sfx_priority
	sub	a, (hl)
	jr	C, 00124$
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
	jr	NC, 00114$
	xor	a, a
	ldh	(_NR12_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR14_REG + 0), a
00114$:
;sm83/sfxplayer.h:48: if (mask & SFX_CH_2) NR22_REG = 0, NR24_REG = SFX_CH_RETRIGGER;
	bit	1, e
	jr	Z, 00116$
	xor	a, a
	ldh	(_NR22_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR24_REG + 0), a
00116$:
;sm83/sfxplayer.h:49: if (mask & SFX_CH_3) NR32_REG = 0;
	bit	2, e
	jr	Z, 00118$
	xor	a, a
	ldh	(_NR32_REG + 0), a
00118$:
;sm83/sfxplayer.h:50: if (mask & SFX_CH_4) NR42_REG = 0, NR44_REG = SFX_CH_RETRIGGER;
	bit	3, e
	jr	Z, 00120$
	xor	a, a
	ldh	(_NR42_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR44_REG + 0), a
00120$:
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
;src/main.c:80: MUSIC_SFX_PRIORITY_NORMAL);
00124$:
;src/main.c:83: return true;
	ld	a, #0x01
	jr	00125$
00107$:
;src/main.c:86: return false;
	xor	a, a
00125$:
;src/main.c:87: }
	add	sp, #10
	ret
;src/main.c:91: bool enemy_collide() {
;	---------------------------------
; Function enemy_collide
; ---------------------------------
_enemy_collide::
	add	sp, #-8
;src/main.c:92: for (uint8_t enemy_index = 0; enemy_index < ENEMY_MAX; enemy_index++) {
	ldhl	sp,	#0
	ld	(hl), #0x00
	ldhl	sp,	#7
	ld	(hl), #0x00
00146$:
	ldhl	sp,	#7
	ld	a, (hl)
	sub	a, #0x04
	jp	NC, 00116$
;src/main.c:93: if (!enemies[enemy_index].active || enemies[enemy_index].stomped) {
	ld	c, (hl)
	xor	a, a
	ld	l, c
	ld	h, a
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	a, l
	add	a, #<(_enemies)
	ld	c, a
	ld	a, h
	adc	a, #>(_enemies)
	ld	b, a
	ld	hl, #0x000f
	add	hl, bc
	bit	0, (hl)
	jp	Z, 00115$
	ld	hl, #0x000d
	add	hl, bc
	bit	0, (hl)
	jp	NZ, 00115$
;src/main.c:97: uint16_t enemy_left = (enemies[enemy_index].x >> 4);
	ld	l, c
	ld	h, b
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
	ldhl	sp,	#1
	ld	a, e
	ld	(hl+), a
	ld	(hl), d
;src/main.c:98: uint16_t enemy_right = (enemies[enemy_index].x >> 4) + TILE_SIZE;
	ld	hl, #0x0008
	add	hl, de
	ld	e, l
	ld	a, h
	ldhl	sp,	#3
	ld	(hl), e
	inc	hl
	ld	(hl), a
;src/main.c:99: uint16_t enemy_top = (enemies[enemy_index].y >> 4);
	ld	l, c
	ld	h, b
	inc	hl
	inc	hl
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
	ldhl	sp,	#5
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
;src/main.c:100: uint16_t enemy_bottom = (enemies[enemy_index].y >> 4) + enemiesSprites_HEIGHT;
	ld	hl, #0x0010
	add	hl, bc
	ld	c, l
	ld	b, h
;src/main.c:102: if (player_x < enemy_right && player_x + TILE_SIZE > enemy_left &&
	ld	de, #_player_x
	ldhl	sp,	#3
	ld	a, (de)
	inc	de
	sub	a, (hl)
	inc	hl
	ld	a, (de)
	sbc	a, (hl)
	jp	NC, 00115$
	ld	a, (_player_x)
	ld	hl, #_player_x + 1
	ld	d, (hl)
	add	a, #0x08
	ld	e, a
	jr	NC, 00289$
	inc	d
00289$:
	ldhl	sp,	#1
	ld	a, (hl+)
	sub	a, e
	ld	a, (hl)
	sbc	a, d
	jp	NC, 00115$
;src/main.c:103: player_y < enemy_bottom &&
	ld	hl, #_player_y
	ld	a, (hl+)
	sub	a, c
	ld	a, (hl)
	sbc	a, b
	jp	NC, 00115$
;src/main.c:104: player_y + marioSprites_HEIGHT > enemy_top + ENEMY_TOP_MARGIN) {
	dec	hl
	ld	a, (hl+)
	ld	b, (hl)
	add	a, #0x10
	ld	c, a
	jr	NC, 00290$
	inc	b
00290$:
	ldhl	sp,	#5
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x0008
	add	hl, de
	ld	a, l
	sub	a, c
	ld	a, h
	sbc	a, b
	jp	NC, 00115$
;src/main.c:106: if (player_y + marioSprites_HEIGHT < enemy_top + ENEMY_TOP_MARGIN + 4) {
	ld	hl, #0x000c
	add	hl, de
	ld	a, c
	sub	a, l
	ld	a, b
	sbc	a, h
	jp	NC, 00108$
;src/main.c:107: uint8_t _saved_bank = _current_bank;
	ldh	a, (__current_bank + 0)
	ld	c, a
;src/main.c:108: SWITCH_ROM(BANK(enemy));
	ld	a, #<(___bank_enemy)
	ldh	(__current_bank + 0), a
	ld	(#_rROMB0),a
;src/main.c:109: enemy_stomp(enemy_index);
	push	bc
	ldhl	sp,	#9
	ld	a, (hl)
	push	af
	inc	sp
	ld	e, #b_enemy_stomp
	ld	hl, #_enemy_stomp
	call	___sdcc_bcall_ehl
	inc	sp
	pop	bc
;src/main.c:110: SWITCH_ROM(_saved_bank);
	ld	a, c
	ldh	(__current_bank + 0), a
	ld	hl, #_rROMB0
	ld	(hl), c
;src/main.c:112: current_jump = 0;
	xor	a, a
	ld	hl, #_current_jump
	ld	(hl+), a
	ld	(hl), a
;src/main.c:113: is_jumping = TRUE;
	ld	hl, #_is_jumping
	ld	(hl), #0x01
;src/main.c:114: display_jump_frame = TRUE;
	ld	hl, #_display_jump_frame
	ld	(hl), #0x01
;src/main.c:115: vel_y = -16;
	ld	hl, #_vel_y
	ld	(hl), #0xf0
;src/main.c:116: touch_ground = FALSE;
	xor	a, a
	ld	(#_touch_ground),a
;src/main.c:119: SFX_MUTE_MASK(sound_squish), MUSIC_SFX_PRIORITY_NORMAL);
	ld	b, #<(___mute_mask_sound_squish)
;src/main.c:118: music_play_sfx(BANK(sound_squish), sound_squish,
	ldhl	sp,	#6
	ld	(hl), #<(___bank_sound_squish)
;sm83/musicmanager.h:105: if (music_sfx_priority > priority) return;
	ld	a, #0x04
	ld	hl, #_music_sfx_priority
	sub	a, (hl)
	jp	C, 00115$
;sm83/musicmanager.h:106: sfx_play_bank = SFX_STOP_BANK;
	ld	hl, #_sfx_play_bank
	ld	(hl), #0xff
;sm83/musicmanager.h:107: music_sfx_priority = priority;
	ld	hl, #_music_sfx_priority
	ld	(hl), #0x04
;sm83/musicmanager.h:108: music_sound_cut_mask(music_mute_mask);
	ld	a, (_music_mute_mask)
;sm83/musicmanager.h:80: sfx_sound_cut_mask(mask);
	ld	d, a
;sm83/sfxplayer.h:47: if (mask & SFX_CH_1) NR12_REG = 0, NR14_REG = SFX_CH_RETRIGGER;
	rrca
	jr	NC, 00120$
	xor	a, a
	ldh	(_NR12_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR14_REG + 0), a
00120$:
;sm83/sfxplayer.h:48: if (mask & SFX_CH_2) NR22_REG = 0, NR24_REG = SFX_CH_RETRIGGER;
	bit	1, d
	jr	Z, 00122$
	xor	a, a
	ldh	(_NR22_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR24_REG + 0), a
00122$:
;sm83/sfxplayer.h:49: if (mask & SFX_CH_3) NR32_REG = 0;
	bit	2, d
	jr	Z, 00124$
	xor	a, a
	ldh	(_NR32_REG + 0), a
00124$:
;sm83/sfxplayer.h:50: if (mask & SFX_CH_4) NR42_REG = 0, NR44_REG = SFX_CH_RETRIGGER;
	bit	3, d
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
	ld	(hl), b
;sm83/sfxplayer.h:64: sfx_play_bank = SFX_STOP_BANK, sfx_frame_skip = 0, sfx_play_sample = sample, sfx_play_bank = bank;
	ld	hl, #_sfx_play_bank
	ld	(hl), #0xff
	xor	a, a
	ld	(#_sfx_frame_skip),a
	ld	hl, #_sfx_play_sample
	ld	a, #<(_sound_squish)
	ld	(hl+), a
	ld	(hl), #>(_sound_squish)
	ldhl	sp,	#6
	ld	a, (hl)
	ld	(#_sfx_play_bank),a
;src/main.c:121: continue;
	jp	00115$
00108$:
;src/main.c:123: if(player_is_big){
	ld	hl, #_player_is_big
	bit	0, (hl)
	jp	Z, 00105$
;src/main.c:124: player_is_big = FALSE;
	ld	(hl), #0x00
;src/main.c:127: SFX_MUTE_MASK(sound_pipe), MUSIC_SFX_PRIORITY_NORMAL);
	ld	c, #<(___mute_mask_sound_pipe)
;src/main.c:126: music_play_sfx(BANK(sound_pipe), sound_pipe,
	ld	e, #<(___bank_sound_pipe)
;sm83/musicmanager.h:105: if (music_sfx_priority > priority) return;
	ld	a, #0x04
	ld	hl, #_music_sfx_priority
	sub	a, (hl)
	jr	C, 00144$
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
	jr	NC, 00134$
	xor	a, a
	ldh	(_NR12_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR14_REG + 0), a
00134$:
;sm83/sfxplayer.h:48: if (mask & SFX_CH_2) NR22_REG = 0, NR24_REG = SFX_CH_RETRIGGER;
	bit	1, b
	jr	Z, 00136$
	xor	a, a
	ldh	(_NR22_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR24_REG + 0), a
00136$:
;sm83/sfxplayer.h:49: if (mask & SFX_CH_3) NR32_REG = 0;
	bit	2, b
	jr	Z, 00138$
	xor	a, a
	ldh	(_NR32_REG + 0), a
00138$:
;sm83/sfxplayer.h:50: if (mask & SFX_CH_4) NR42_REG = 0, NR44_REG = SFX_CH_RETRIGGER;
	bit	3, b
	jr	Z, 00140$
	xor	a, a
	ldh	(_NR42_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR44_REG + 0), a
00140$:
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
	ld	(hl), #<(_sound_pipe)
	inc	hl
	ld	(hl), #>(_sound_pipe)
	ld	hl, #_sfx_play_bank
	ld	(hl), e
;src/main.c:127: SFX_MUTE_MASK(sound_pipe), MUSIC_SFX_PRIORITY_NORMAL);
00144$:
;src/main.c:132: uint8_t _saved_bank = _current_bank;
	ldh	a, (__current_bank + 0)
	ld	c, a
;src/main.c:133: SWITCH_ROM(BANK(enemy));
	ld	a, #<(___bank_enemy)
	ldh	(__current_bank + 0), a
	ld	(#_rROMB0),a
;src/main.c:134: enemy_stomp(enemy_index);
	push	bc
	ldhl	sp,	#2
	ld	a, (hl)
	push	af
	inc	sp
	ld	e, #b_enemy_stomp
	ld	hl, #_enemy_stomp
	call	___sdcc_bcall_ehl
	inc	sp
	pop	bc
;src/main.c:135: SWITCH_ROM(_saved_bank);
	ld	a, c
	ldh	(__current_bank + 0), a
	ld	hl, #_rROMB0
	ld	(hl), c
	jr	00109$
00105$:
;src/main.c:139: die();
	call	_die
;src/main.c:140: uint8_t _saved_bank = _current_bank;
	ldh	a, (__current_bank + 0)
	ld	c, a
;src/main.c:141: SWITCH_ROM(BANK(enemy));
	ld	a, #<(___bank_enemy)
	ldh	(__current_bank + 0), a
	ld	(#_rROMB0),a
;src/main.c:142: enemy_reset_all();
	push	bc
	ld	e, #b_enemy_reset_all
	ld	hl, #_enemy_reset_all
	call	___sdcc_bcall_ehl
	pop	bc
;src/main.c:143: SWITCH_ROM(_saved_bank);
	ld	a, c
	ldh	(__current_bank + 0), a
	ld	hl, #_rROMB0
	ld	(hl), c
00109$:
;src/main.c:146: return true;
	ld	a, #0x01
	jr	00147$
00115$:
;src/main.c:92: for (uint8_t enemy_index = 0; enemy_index < ENEMY_MAX; enemy_index++) {
	ldhl	sp,	#7
	inc	(hl)
	ld	a, (hl)
	ldhl	sp,	#0
	ld	(hl), a
	jp	00146$
00116$:
;src/main.c:149: return false;
	xor	a, a
00147$:
;src/main.c:150: }
	add	sp, #8
	ret
;src/main.c:152: void main(void) {
;	---------------------------------
; Function main
; ---------------------------------
_main::
	add	sp, #-45
;src/main.c:154: STAT_REG = 0x40;
	ld	a, #0x40
	ldh	(_STAT_REG + 0), a
;src/main.c:155: LYC_REG = 0x0F;
	ld	a, #0x0f
	ldh	(_LYC_REG + 0), a
;/home/odrevet/projects/gbdk/include/gb/gb.h:811: __asm__("di");
	di
;src/main.c:158: set_interrupts(VBL_IFLAG | LCD_IFLAG);
	ld	a, #0x03
	call	_set_interrupts
;src/main.c:159: add_LCD(interruptLCD);
	ld	de, #_interruptLCD
	call	_add_LCD
;/home/odrevet/projects/gbdk/include/gb/gb.h:795: __asm__("ei");
	ei
;sm83/musicmanager.h:61: music_current_track_bank = MUSIC_STOP_BANK;
	ld	hl, #_music_current_track_bank
	ld	(hl), #0xff
;sm83/sfxplayer.h:25: NR52_REG = SFX_CH_ENABLE, NR51_REG = 0xFF, NR50_REG = 0x77;  // enable sound
	ld	a, #0x80
	ldh	(_NR52_REG + 0), a
	ld	a, #0xff
	ldh	(_NR51_REG + 0), a
	ld	a, #0x77
	ldh	(_NR50_REG + 0), a
;sm83/sfxplayer.h:59: sfx_play_bank = SFX_STOP_BANK, sfx_play_sample = NULL;
	ld	hl, #_sfx_play_bank
	ld	(hl), #0xff
	xor	a, a
	ld	hl, #_sfx_play_sample
	ld	(hl+), a
	ld	(hl), a
;sm83/sfxplayer.h:32: NR12_REG = NR22_REG = NR32_REG = NR42_REG = 0;
	xor	a, a
	ldh	(_NR42_REG + 0), a
	xor	a, a
	ldh	(_NR32_REG + 0), a
	xor	a, a
	ldh	(_NR22_REG + 0), a
	xor	a, a
	ldh	(_NR12_REG + 0), a
;sm83/sfxplayer.h:33: NR14_REG = NR24_REG = NR44_REG = SFX_CH_RETRIGGER;
	ld	a, #0xc0
	ldh	(_NR44_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR24_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR14_REG + 0), a
;sm83/sfxplayer.h:34: NR51_REG = 0xFF;
	ld	a, #0xff
	ldh	(_NR51_REG + 0), a
;src/main.c:167: }
	di
;sm83/musicmanager.h:50: music_setup_timer_ex((_cpu == CGB_TYPE) && (*(UBYTE *)0x0143 & 0x80));
	ld	a, (#__cpu)
	sub	a, #0x11
	jr	NZ, 00197$
	ld	a, (#0x0143)
	rlca
	jr	C, 00198$
00197$:
	xor	a, a
	jr	00199$
00198$:
	ld	a, #0x01
00199$:
;sm83/musicmanager.h:39: TMA_REG = (is_fast) ? 0x80u : 0xC0u;
	or	a, a
	ld	a, #0x80
	jr	NZ, 00201$
	ld	a, #0xc0
00201$:
	ldh	(_TMA_REG + 0), a
;sm83/musicmanager.h:40: TAC_REG = 0x07u;
	ld	a, #0x07
	ldh	(_TAC_REG + 0), a
;sm83/musicmanager.h:44: music_tick_mask = MUSIC_TICK_MASK_256HZ;
	ld	hl, #_music_tick_mask
	ld	(hl), #0x03
;src/main.c:166: add_low_priority_TIM(music_play_isr);
	ld	de, #_music_play_isr
	call	_add_low_priority_TIM
	ei
;src/main.c:168: set_interrupts(IE_REG | TIM_IFLAG);
	ldh	a, (_IE_REG + 0)
	set	2, a
	call	_set_interrupts
;src/main.c:171: joypad_previous, joypad_current = 0;
	xor	a, a
	ld	(#_joypad_current),a
;src/main.c:173: init();
	call	_init
;src/main.c:187: DISPLAY_ON;
	ldh	a, (_LCDC_REG + 0)
	or	a, #0x80
	ldh	(_LCDC_REG + 0), a
;src/main.c:188: SHOW_BKG;
	ldh	a, (_LCDC_REG + 0)
	or	a, #0x01
	ldh	(_LCDC_REG + 0), a
;src/main.c:190: SHOW_WIN;
	ldh	a, (_LCDC_REG + 0)
	or	a, #0x20
	ldh	(_LCDC_REG + 0), a
;src/main.c:193: SHOW_SPRITES;
	ldh	a, (_LCDC_REG + 0)
	or	a, #0x02
	ldh	(_LCDC_REG + 0), a
;src/main.c:194: SPRITES_8x8;
	ldh	a, (_LCDC_REG + 0)
	and	a, #0xfb
	ldh	(_LCDC_REG + 0), a
;src/main.c:198: uint8_t anim_frame_counter = 0;
	ldhl	sp,	#44
	ld	(hl), #0x00
;src/main.c:200: uint8_t _saved_bank = _current_bank;
	ldh	a, (__current_bank + 0)
	ldhl	sp,	#40
	ld	(hl), a
;src/main.c:202: SWITCH_ROM(BANK(textTileset));
	ld	c, #<(___bank_textTileset)
	ld	a, c
	ldh	(__current_bank + 0), a
	ld	hl, #_rROMB0
	ld	(hl), c
;src/main.c:203: set_bkg_data(textTileset_TILE_ORIGIN, textTileset_TILE_COUNT, textTileset_tiles);  
	ld	de, #_textTileset_tiles
	push	de
	ld	hl, #0x2800
	push	hl
	call	_set_bkg_data
	add	sp, #4
;src/main.c:205: SWITCH_ROM(BANK(TitleScreen));
	ld	a, #<(___bank_TitleScreen)
	ldh	(__current_bank + 0), a
	ld	(#_rROMB0),a
;src/main.c:206: set_bkg_data(TitleScreen_TILE_ORIGIN, TitleScreen_TILE_COUNT, TitleScreen_tiles);
	ld	de, #_TitleScreen_tiles
	push	de
	ld	hl, #0x6400
	push	hl
	call	_set_bkg_data
	add	sp, #4
;src/main.c:207: set_bkg_tiles(0, 0, 20, 18, TitleScreen_map);
	ld	de, #_TitleScreen_map
	push	de
	ld	hl, #0x1214
	push	hl
	xor	a, a
	rrca
	push	af
	call	_set_bkg_tiles
	add	sp, #6
;src/main.c:209: state_title();
	push	bc
	call	_state_title
	pop	bc
;src/main.c:211: SWITCH_ROM(BANK(textTileset));
	ld	a, c
	ldh	(__current_bank + 0), a
	ld	hl, #_rROMB0
	ld	(hl), c
;src/main.c:212: set_bkg_data(textTileset_TILE_ORIGIN, textTileset_TILE_COUNT, textTileset_tiles); 
	ld	de, #_textTileset_tiles
	push	de
	ld	hl, #0x2800
	push	hl
	call	_set_bkg_data
	add	sp, #4
;src/main.c:214: SWITCH_ROM(BANK(commonTileset));
	ld	a, #<(___bank_commonTileset)
	ldh	(__current_bank + 0), a
	ld	(#_rROMB0),a
;src/main.c:215: set_bkg_data(commonTileset_TILE_ORIGIN, commonTileset_TILE_COUNT, commonTileset_tiles);
	ld	de, #_commonTileset_tiles
	push	de
	ld	hl, #0x3828
	push	hl
	call	_set_bkg_data
	add	sp, #4
;src/main.c:217: SWITCH_ROM(BANK(marioSprites));
	ldhl	sp,	#41
	ld	(hl), #<(___bank_marioSprites)
	ld	a, (hl)
	ldh	(__current_bank + 0), a
	ld	a, (hl)
	ld	(#_rROMB0),a
;src/main.c:218: set_sprite_data(marioSprites_TILE_ORIGIN, marioSprites_TILE_COUNT, marioSprites_tiles);
	ld	de, #_marioSprites_tiles
	push	de
	ld	hl, #0x3500
	push	hl
	call	_set_sprite_data
	add	sp, #4
;src/main.c:220: SWITCH_ROM(BANK(enemiesSprites));
	ld	a, #<(___bank_enemiesSprites)
	ldh	(__current_bank + 0), a
	ld	(#_rROMB0),a
;src/main.c:221: set_sprite_data(enemiesSprites_TILE_ORIGIN, enemiesSprites_TILE_COUNT, enemiesSprites_tiles);
	ld	de, #_enemiesSprites_tiles
	push	de
	ld	hl, #0x735
	push	hl
	call	_set_sprite_data
	add	sp, #4
;src/main.c:223: SWITCH_ROM(BANK(enemiesBirabutoSprites));
	ld	a, #<(___bank_enemiesBirabutoSprites)
	ldh	(__current_bank + 0), a
	ld	(#_rROMB0),a
;src/main.c:224: set_sprite_data(enemiesBirabutoSprites_TILE_ORIGIN, enemiesBirabutoSprites_TILE_COUNT, enemiesBirabutoSprites_tiles);
	ld	de, #_enemiesBirabutoSprites_tiles
	push	de
	ld	hl, #0x1c49
	push	hl
	call	_set_sprite_data
	add	sp, #4
;src/main.c:226: SWITCH_ROM(BANK(commonSprites));
	ld	a, #<(___bank_commonSprites)
	ldh	(__current_bank + 0), a
	ld	(#_rROMB0),a
;src/main.c:228: commonSprites_tiles);
;src/main.c:227: set_sprite_data(commonSprites_TILE_ORIGIN, commonSprites_TILE_COUNT,
	ld	de, #_commonSprites_tiles
	push	de
	ld	hl, #0xd3c
	push	hl
	call	_set_sprite_data
	add	sp, #4
;src/main.c:230: SWITCH_ROM(_saved_bank);
	ldhl	sp,	#40
	ld	a, (hl)
	ldh	(__current_bank + 0), a
	ld	a, (hl)
	ld	hl, #_rROMB0
	ld	(hl), a
;/home/odrevet/projects/gbdk/include/gb/gb.h:811: __asm__("di");
	di
;src/main.c:234: add_VBL(interruptVBL);
	ld	de, #_interruptVBL
	call	_add_VBL
;/home/odrevet/projects/gbdk/include/gb/gb.h:1461: SCX_REG=x, SCY_REG=y;
	ld	a, #0x00
	ldh	(_SCX_REG + 0), a
	ld	a, #0xf0
	ldh	(_SCY_REG + 0), a
;/home/odrevet/projects/gbdk/include/gb/gb.h:795: __asm__("ei");
	ei
;src/main.c:239: current_level = 0;
;src/main.c:240: map_column = 0;
	xor	a, a
	ld	(#_current_level), a
	ld	(#_map_column),a
;src/main.c:241: level_set_current();
	call	_level_set_current
;src/main.c:243: score = 0;
	xor	a, a
	ld	hl, #_score
	ld	(hl+), a
	ld	(hl), a
;src/main.c:244: lives = INITIAL_LIVES;
	ld	hl, #_lives
	ld	(hl), #0x03
;src/main.c:245: coins = 0;
	xor	a, a
	ld	(#_coins),a
;src/main.c:248: memset(windata, 15, WINDOW_SIZE);
	ldhl	sp,	#0
	ld	c, l
	ld	b, h
	ld	e, c
	ld	d, b
	ld	hl, #0x0028
	push	hl
	ld	l, #0x0f
	push	hl
	push	de
	call	_memset
	add	sp, #6
;src/main.c:250: set_win_tiles(0, 0, WINDOW_WIDTH_TILE, WINDOW_HEIGHT_TILE, windata);
	push	bc
	ld	hl, #0x214
	push	hl
	xor	a, a
	rrca
	push	af
	call	_set_win_tiles
	add	sp, #6
;/home/odrevet/projects/gbdk/include/gb/gb.h:1739: WX_REG=x, WY_REG=y;
	ld	a, #0x07
	ldh	(_WX_REG + 0), a
	xor	a, a
	ldh	(_WY_REG + 0), a
;src/main.c:252: text_print_string(0, 0, "MARIOx00  WORLD TIME");
	ld	de, #___str_0
	push	de
	xor	a, a
	ld	e, a
	call	_text_print_string
;src/main.c:253: text_print_string(0, 1, "     0  x00 1-1  000");
	ld	de, #___str_1
	push	de
	ld	e, #0x01
	xor	a, a
	call	_text_print_string
;src/main.c:255: set_win_tile_xy(7, 1, TILE_COIN);
	ld	a, #0x37
	push	af
	inc	sp
	ld	e, #0x01
	ld	a, #0x07
	call	_set_win_tile_xy
;src/main.c:256: hud_update_time();
	call	_hud_update_time
;src/main.c:257: hud_update_lives();
	call	_hud_update_lives
;src/main.c:260: while (1) {
00137$:
;src/main.c:261: joypad_previous = joypad_current;
	ld	a, (#_joypad_current)
	ld	(#_joypad_previous),a
;src/main.c:262: joypad_current = joypad();
	call	_joypad
	ld	hl, #_joypad_current
	ld	(hl), a
;src/main.c:264: if (joypad_current & J_START && !(joypad_previous & J_START)) {
	ld	a, (hl)
	rlca
	jr	NC, 00102$
	ld	a, (_joypad_previous)
	rlca
	jr	C, 00102$
;src/main.c:266: music_pause(TRUE);
	ld	a, #0x01
	call	_music_pause
;src/main.c:267: music_play_sfx(BANK(sound_pause), sound_pause, SFX_MUTE_MASK(sound_pause),
	ldhl	sp,	#42
	ld	(hl), #<(___mute_mask_sound_pause)
	inc	hl
	ld	(hl), #<(___bank_sound_pause)
;sm83/musicmanager.h:105: if (music_sfx_priority > priority) return;
	ld	a, #0x04
	ld	hl, #_music_sfx_priority
	sub	a, (hl)
	jr	C, 00164$
;sm83/musicmanager.h:106: sfx_play_bank = SFX_STOP_BANK;
	ld	hl, #_sfx_play_bank
	ld	(hl), #0xff
;sm83/musicmanager.h:107: music_sfx_priority = priority;
	ld	hl, #_music_sfx_priority
	ld	(hl), #0x04
;sm83/musicmanager.h:108: music_sound_cut_mask(music_mute_mask);
	ld	a, (_music_mute_mask)
;sm83/musicmanager.h:80: sfx_sound_cut_mask(mask);
	ld	c, a
;sm83/sfxplayer.h:47: if (mask & SFX_CH_1) NR12_REG = 0, NR14_REG = SFX_CH_RETRIGGER;
	rrca
	jr	NC, 00154$
	xor	a, a
	ldh	(_NR12_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR14_REG + 0), a
00154$:
;sm83/sfxplayer.h:48: if (mask & SFX_CH_2) NR22_REG = 0, NR24_REG = SFX_CH_RETRIGGER;
	bit	1, c
	jr	Z, 00156$
	xor	a, a
	ldh	(_NR22_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR24_REG + 0), a
00156$:
;sm83/sfxplayer.h:49: if (mask & SFX_CH_3) NR32_REG = 0;
	bit	2, c
	jr	Z, 00158$
	xor	a, a
	ldh	(_NR32_REG + 0), a
00158$:
;sm83/sfxplayer.h:50: if (mask & SFX_CH_4) NR42_REG = 0, NR44_REG = SFX_CH_RETRIGGER;
	bit	3, c
	jr	Z, 00160$
	xor	a, a
	ldh	(_NR42_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR44_REG + 0), a
00160$:
;sm83/sfxplayer.h:51: NR51_REG = 0xFF;
	ld	a, #0xff
	ldh	(_NR51_REG + 0), a
;sm83/musicmanager.h:109: music_mute_mask = mute_mask;
	ldhl	sp,	#42
	ld	a, (hl)
	ld	(#_music_mute_mask),a
;sm83/sfxplayer.h:64: sfx_play_bank = SFX_STOP_BANK, sfx_frame_skip = 0, sfx_play_sample = sample, sfx_play_bank = bank;
	ld	hl, #_sfx_play_bank
	ld	(hl), #0xff
	xor	a, a
	ld	(#_sfx_frame_skip),a
	ld	hl, #_sfx_play_sample
	ld	(hl), #<(_sound_pause)
	inc	hl
	ld	(hl), #>(_sound_pause)
	ldhl	sp,	#43
	ld	a, (hl)
	ld	(#_sfx_play_bank),a
;src/main.c:268: MUSIC_SFX_PRIORITY_NORMAL);
00164$:
;src/main.c:269: state_pause();
	call	_state_pause
;src/main.c:270: music_pause(FALSE);
	xor	a, a
	call	_music_pause
00102$:
;src/main.c:274: enemy_collide();
	call	_enemy_collide
;src/main.c:276: SWITCH_ROM(BANK(marioSprites));
	ldhl	sp,	#41
	ld	a, (hl)
	ldh	(__current_bank + 0), a
	ld	a, (hl)
	ld	(#_rROMB0),a
;src/main.c:277: if(IS_VEHICLE_LEVEL(current_level)){
	ld	a, (#_current_level)
	sub	a, #0x05
	jr	Z, 00104$
	ld	a, (#_current_level)
	sub	a, #0x0b
	jr	NZ, 00105$
00104$:
;src/main.c:278: player_move_vehicle();
	ld	e, #b_player_move_vehicle
	ld	hl, #_player_move_vehicle
	call	___sdcc_bcall_ehl
	jr	00106$
00105$:
;src/main.c:281: player_move();
	ld	e, #b_player_move
	ld	hl, #_player_move
	call	___sdcc_bcall_ehl
00106$:
;src/main.c:283: SWITCH_ROM(_saved_bank);
	ldhl	sp,	#40
	ld	a, (hl)
	ldh	(__current_bank + 0), a
	ld	a, (hl)
	ld	(#_rROMB0),a
;src/main.c:286: if (display_jump_frame) {
	ld	hl, #_display_jump_frame
	bit	0, (hl)
	jr	Z, 00115$
;src/main.c:287: player_frame = 4;
	ld	hl, #_player_frame
	ld	(hl), #0x04
	jr	00116$
00115$:
;src/main.c:288: } else if (display_slide_frame) {
	ld	hl, #_display_slide_frame
	bit	0, (hl)
	jr	Z, 00112$
;src/main.c:290: music_play_sfx(BANK(sound_skid), sound_skid, SFX_MUTE_MASK(sound_skid),
	ld	c, #<(___mute_mask_sound_skid)
	ld	e, #<(___bank_sound_skid)
;sm83/musicmanager.h:105: if (music_sfx_priority > priority) return;
	ld	a, #0x04
	ld	hl, #_music_sfx_priority
	sub	a, (hl)
	jr	C, 00178$
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
	jr	NC, 00168$
	xor	a, a
	ldh	(_NR12_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR14_REG + 0), a
00168$:
;sm83/sfxplayer.h:48: if (mask & SFX_CH_2) NR22_REG = 0, NR24_REG = SFX_CH_RETRIGGER;
	bit	1, b
	jr	Z, 00170$
	xor	a, a
	ldh	(_NR22_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR24_REG + 0), a
00170$:
;sm83/sfxplayer.h:49: if (mask & SFX_CH_3) NR32_REG = 0;
	bit	2, b
	jr	Z, 00172$
	xor	a, a
	ldh	(_NR32_REG + 0), a
00172$:
;sm83/sfxplayer.h:50: if (mask & SFX_CH_4) NR42_REG = 0, NR44_REG = SFX_CH_RETRIGGER;
	bit	3, b
	jr	Z, 00174$
	xor	a, a
	ldh	(_NR42_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR44_REG + 0), a
00174$:
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
	ld	a, #<(_sound_skid)
	ld	(hl+), a
	ld	(hl), #>(_sound_skid)
	ld	hl, #_sfx_play_bank
	ld	(hl), e
;src/main.c:291: MUSIC_SFX_PRIORITY_NORMAL);
00178$:
;src/main.c:293: player_frame = 5;
	ld	hl, #_player_frame
	ld	(hl), #0x05
	jr	00116$
00112$:
;src/main.c:294: } else if (display_walk_animation) {
	ld	hl, #_display_walk_animation
	bit	0, (hl)
	jr	Z, 00109$
;src/main.c:295: update_frame_counter();
	call	_update_frame_counter
	jr	00116$
00109$:
;src/main.c:297: player_frame = 0;
	xor	a, a
	ld	(#_player_frame),a
00116$:
;src/main.c:300: SWITCH_ROM(BANK(enemy));
	ld	a, #<(___bank_enemy)
	ldh	(__current_bank + 0), a
	ld	(#_rROMB0),a
;src/main.c:301: enemy_update();
	ld	e, #b_enemy_update
	ld	hl, #_enemy_update
	call	___sdcc_bcall_ehl
;src/main.c:302: SWITCH_ROM(_saved_bank);
	ldhl	sp,	#40
	ld	a, (hl)
	ldh	(__current_bank + 0), a
	ld	a, (hl)
	ld	(#_rROMB0),a
;src/main.c:304: platform_moving_update();
	call	_platform_moving_update
;src/main.c:305: player_draw(0);
	xor	a, a
	call	_player_draw
;src/main.c:306: base_sprite = enemy_draw(MARIO_SPRITE_COUNT);
	ld	a, #0x04
	call	_enemy_draw
;src/main.c:307: base_sprite = platform_moving_draw(base_sprite);
	call	_platform_moving_draw
	ldhl	sp,	#43
	ld	(hl), a
;src/main.c:308: if (powerup_active) {
	ld	hl, #_powerup_active
	bit	0, (hl)
	jr	Z, 00118$
;src/main.c:309: powerup_update();
	call	_powerup_update
;src/main.c:310: base_sprite = powerup_draw(base_sprite);
	ldhl	sp,	#43
	ld	a, (hl)
	call	_powerup_draw
	ldhl	sp,	#43
	ld	(hl), a
00118$:
;src/main.c:313: coin_animated_update();
	call	_coin_animated_update
;src/main.c:314: base_sprite = coin_animated_draw(base_sprite);
	ldhl	sp,	#43
	ld	a, (hl)
	call	_coin_animated_draw
	ldhl	sp,	#43
	ld	(hl), a
;src/main.c:315: block_bump_update();
	ld	e, #b_block_bump_update
	ld	hl, #_block_bump_update
	call	___sdcc_bcall_ehl
;src/main.c:316: base_sprite = block_bump_draw(base_sprite);
	ldhl	sp,	#43
	ld	a, (hl)
	push	af
	inc	sp
	ld	e, #b_block_bump_draw
	ld	hl, #_block_bump_draw
	call	___sdcc_bcall_ehl
	inc	sp
	ld	c, a
;src/main.c:318: if (powerup_active && powerups_collide()) {
	ld	hl, #_powerup_active
	bit	0, (hl)
	jr	Z, 00120$
	push	bc
	call	_powerups_collide
	ld	e, a
	pop	bc
	bit	0, e
	jr	Z, 00120$
;src/main.c:319: powerup_active = FALSE;
	xor	a, a
	ld	(#_powerup_active),a
;src/main.c:320: hide_metasprite(commonSprites_metasprites[0], base_sprite - 1);
	dec	c
	ld	hl, #_commonSprites_metasprites
	ld	a, (hl+)
	ld	b, a
	ld	a, (hl)
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:306: __current_metasprite = metasprite;
	ld	hl, #___current_metasprite
	ld	(hl), b
	inc	hl
	ld	(hl), a
;/home/odrevet/projects/gbdk/include/gb/metasprites.h:307: __hide_metasprite(base_sprite);
	ld	a, c
	call	___hide_metasprite
;src/main.c:321: powerup.x = 0;
	ld	hl, #_powerup
	xor	a, a
	ld	(hl+), a
	ld	(hl), a
;src/main.c:322: powerup.draw_x = 0;
	ld	hl, #_powerup + 4
	ld	(hl), #0x00
;src/main.c:323: powerup.y = 0;
	ld	hl, #(_powerup + 2)
	xor	a, a
	ld	(hl+), a
;src/main.c:324: powerup.draw_y = 0;
	ld	(hl+), a
	inc	hl
	ld	(hl), #0x00
00120$:
;src/main.c:327: time--;
	ld	hl, #_time
	ld	a, (hl+)
	ld	e, a
	ld	a, (hl-)
	ld	d, a
	dec	de
	ld	a, e
	ld	(hl+), a
	ld	(hl), d
;src/main.c:328: hud_update_time();
	call	_hud_update_time
;src/main.c:329: if (time == 0) {
	ld	hl, #_time + 1
	ld	a, (hl-)
;src/main.c:330: time = TIME_INITIAL_VALUE;
	or	a, (hl)
	jr	NZ, 00123$
	ld	(hl+), a
	ld	(hl), #0x32
;src/main.c:331: lives--;
	ld	hl, #_lives
	dec	(hl)
;src/main.c:332: hud_update_lives();
	call	_hud_update_lives
00123$:
;src/main.c:335: if (player_draw_y > DEVICE_SCREEN_PX_HEIGHT) {
	ld	a, #0x90
	ld	hl, #_player_draw_y
	sub	a, (hl)
	jr	NC, 00125$
;src/main.c:336: player_y = 0;
	xor	a, a
	ld	hl, #_player_y
	ld	(hl+), a
	ld	(hl), a
00125$:
;src/main.c:339: if (level_end_reached && player_draw_x >= DEVICE_SCREEN_WIDTH << 3) {
	ld	hl, #_level_end_reached
	bit	0, (hl)
	jp	Z, 00130$
	ld	a, (#_player_draw_x)
	sub	a, #0xa0
	jp	C, 00130$
;src/main.c:341: music_load(BANK(music_stage_clear), &music_stage_clear);
	ld	a, #<(___bank_music_stage_clear)
;sm83/musicmanager.h:88: music_current_track_bank = MUSIC_STOP_BANK, music_next_track = data; music_current_track_bank = bank;
	ld	hl, #_music_current_track_bank
	ld	(hl), #0xff
	ld	hl, #_music_next_track
	ld	(hl), #<(_music_stage_clear)
	inc	hl
	ld	(hl), #>(_music_stage_clear)
	ld	(#_music_current_track_bank),a
;src/main.c:344: delay(4500);
	ld	de, #0x1194
	call	_delay
;src/main.c:346: while (time >> TIME_SHIFT > 0) {
00126$:
	ld	hl, #_time
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
	srl	b
	rr	c
	ld	a, b
	or	a, c
	jp	Z, 00128$
;src/main.c:347: time -= 32;
	dec	hl
	ld	a, (hl+)
	ld	b, (hl)
	dec	hl
	add	a, #0xe0
	ld	c, a
	ld	a, b
	adc	a, #0xff
	ld	(hl), c
	inc	hl
	ld	(hl), a
;src/main.c:348: score += 1;
	ld	a, (_score)
	ld	hl, #_score + 1
	ld	b, (hl)
	dec	hl
	ld	c, a
	inc	bc
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
;src/main.c:349: hud_update_time();
	call	_hud_update_time
;src/main.c:350: hud_update_score();
	call	_hud_update_score
;src/main.c:352: music_play_sfx(BANK(sound_coin), sound_coin, SFX_MUTE_MASK(sound_coin),
	ldhl	sp,	#42
	ld	(hl), #<(___mute_mask_sound_coin)
	inc	hl
	ld	(hl), #<(___bank_sound_coin)
;sm83/musicmanager.h:105: if (music_sfx_priority > priority) return;
	ld	a, #0x04
	ld	hl, #_music_sfx_priority
	sub	a, (hl)
	jr	C, 00194$
;sm83/musicmanager.h:106: sfx_play_bank = SFX_STOP_BANK;
	ld	hl, #_sfx_play_bank
	ld	(hl), #0xff
;sm83/musicmanager.h:107: music_sfx_priority = priority;
	ld	hl, #_music_sfx_priority
	ld	(hl), #0x04
;sm83/musicmanager.h:108: music_sound_cut_mask(music_mute_mask);
	ld	a, (_music_mute_mask)
;sm83/musicmanager.h:80: sfx_sound_cut_mask(mask);
	ld	c, a
;sm83/sfxplayer.h:47: if (mask & SFX_CH_1) NR12_REG = 0, NR14_REG = SFX_CH_RETRIGGER;
	rrca
	jr	NC, 00184$
	xor	a, a
	ldh	(_NR12_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR14_REG + 0), a
00184$:
;sm83/sfxplayer.h:48: if (mask & SFX_CH_2) NR22_REG = 0, NR24_REG = SFX_CH_RETRIGGER;
	bit	1, c
	jr	Z, 00186$
	xor	a, a
	ldh	(_NR22_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR24_REG + 0), a
00186$:
;sm83/sfxplayer.h:49: if (mask & SFX_CH_3) NR32_REG = 0;
	bit	2, c
	jr	Z, 00188$
	xor	a, a
	ldh	(_NR32_REG + 0), a
00188$:
;sm83/sfxplayer.h:50: if (mask & SFX_CH_4) NR42_REG = 0, NR44_REG = SFX_CH_RETRIGGER;
	bit	3, c
	jr	Z, 00190$
	xor	a, a
	ldh	(_NR42_REG + 0), a
	ld	a, #0xc0
	ldh	(_NR44_REG + 0), a
00190$:
;sm83/sfxplayer.h:51: NR51_REG = 0xFF;
	ld	a, #0xff
	ldh	(_NR51_REG + 0), a
;sm83/musicmanager.h:109: music_mute_mask = mute_mask;
	ldhl	sp,	#42
	ld	a, (hl)
	ld	(#_music_mute_mask),a
;sm83/sfxplayer.h:64: sfx_play_bank = SFX_STOP_BANK, sfx_frame_skip = 0, sfx_play_sample = sample, sfx_play_bank = bank;
	ld	hl, #_sfx_play_bank
	ld	(hl), #0xff
	xor	a, a
	ld	(#_sfx_frame_skip),a
	ld	hl, #_sfx_play_sample
	ld	a, #<(_sound_coin)
	ld	(hl+), a
	ld	(hl), #>(_sound_coin)
	ldhl	sp,	#43
	ld	a, (hl)
	ld	(#_sfx_play_bank),a
;src/main.c:353: MUSIC_SFX_PRIORITY_NORMAL);
00194$:
;src/main.c:355: delay(10);
	ld	de, #0x000a
	call	_delay
	jp	00126$
00128$:
;src/main.c:358: HIDE_SPRITES;
	ldh	a, (_LCDC_REG + 0)
	and	a, #0xfd
	ldh	(_LCDC_REG + 0), a
;src/main.c:359: HIDE_BKG;
	ldh	a, (_LCDC_REG + 0)
	and	a, #0xfe
	ldh	(_LCDC_REG + 0), a
;src/main.c:361: init();
	call	_init
;src/main.c:362: current_level = (++current_level) % NB_LEVELS;
	ld	hl, #_current_level
	inc	(hl)
	ld	a, (hl)
	ld	e, #0x0c
	call	__moduchar
	ld	hl, #_current_level
	ld	(hl), c
;src/main.c:363: level_set_current();
	call	_level_set_current
;src/main.c:365: SHOW_SPRITES;
	ldh	a, (_LCDC_REG + 0)
	or	a, #0x02
	ldh	(_LCDC_REG + 0), a
;src/main.c:366: SHOW_BKG;
	ldh	a, (_LCDC_REG + 0)
	or	a, #0x01
	ldh	(_LCDC_REG + 0), a
00130$:
;src/main.c:369: if (current_level == LEVEL_WORLD1_END) {
	ld	a, (#_current_level)
	sub	a, #0x02
	jr	NZ, 00135$
;src/main.c:370: uint8_t _saved_bank = _current_bank;
	ldh	a, (__current_bank + 0)
	ld	c, a
;src/main.c:371: anim_frame_counter++;
	ldhl	sp,	#44
	inc	(hl)
;src/main.c:372: if (anim_frame_counter >= 12) {
	ld	a, (hl)
	sub	a, #0x0c
	jr	C, 00133$
;src/main.c:373: anim_frame_counter = 0;
	ld	(hl), #0x00
;src/main.c:374: background_animation_counter ^= 1;
00133$:
;src/main.c:386: SWITCH_ROM(_saved_bank);
	ld	a, c
	ldh	(__current_bank + 0), a
	ld	hl, #_rROMB0
	ld	(hl), c
00135$:
;src/main.c:389: vsync();
	call	_vsync
	jp	00137$
;src/main.c:391: }
	add	sp, #45
	ret
___str_0:
	.ascii "MARIOx00  WORLD TIME"
	.db 0x00
___str_1:
	.ascii "     0  x00 1-1  000"
	.db 0x00
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
