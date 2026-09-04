;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler
; Version 4.5.1 #15267 (Linux)
;--------------------------------------------------------
	.module musicmanager
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _hUGE_dosound
	.globl _hUGE_init
	.globl _sfx_play_isr
	.globl _music_tick_mask
	.globl _music_sfx_priority
	.globl _music_play_isr_pause
	.globl _music_play_isr_counter
	.globl _music_mute_mask
	.globl _music_current_track_bank
	.globl _music_next_track
	.globl _music_play_isr
	.globl _music_pause
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area _HRAM
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_music_next_track::
	.ds 2
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
_music_current_track_bank::
	.ds 1
_music_mute_mask::
	.ds 1
_music_play_isr_counter::
	.ds 1
_music_play_isr_pause::
	.ds 1
_music_sfx_priority::
	.ds 1
_music_tick_mask::
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
;sm83/musicmanager.c:19: void music_play_isr(void) NONBANKED {
;	---------------------------------
; Function music_play_isr
; ---------------------------------
_music_play_isr::
;sm83/musicmanager.c:20: if (sfx_play_bank != SFX_STOP_BANK) {
	ld	a, (#_sfx_play_bank)
	inc	a
	jr	Z, 00104$
;sm83/musicmanager.c:22: hUGE_mute_mask = music_mute_mask;
	ld	a, (#_music_mute_mask)
	ld	(#_hUGE_mute_mask),a
;sm83/musicmanager.c:24: if (!sfx_play_isr()) {
	call	_sfx_play_isr
;sm83/musicmanager.c:26: hUGE_mute_mask = MUTE_MASK_NONE, hUGE_reset_wave();
	or	a,a
	jr	NZ, 00104$
	ld	(#_hUGE_mute_mask),a
;sm83/hUGEDriver.h:139: hUGE_current_wave = 100;
	ld	hl, #_hUGE_current_wave
	ld	(hl), #0x64
;sm83/musicmanager.c:31: music_mute_mask = MUTE_MASK_NONE;
;sm83/musicmanager.c:32: music_sfx_priority = MUSIC_SFX_PRIORITY_MINIMAL;
	xor	a, a
	ld	(#_music_mute_mask), a
	ld	(#_music_sfx_priority),a
;sm83/musicmanager.c:33: sfx_play_bank = SFX_STOP_BANK;
	ld	hl, #_sfx_play_bank
	ld	(hl), #0xff
00104$:
;sm83/musicmanager.c:36: if (music_play_isr_pause) return;
	ld	a, (#_music_play_isr_pause)
	or	a, a
	ret	NZ
;sm83/musicmanager.c:37: if (music_current_track_bank == MUSIC_STOP_BANK) return;
	ld	a, (#_music_current_track_bank)
	inc	a
	ret	Z
;sm83/musicmanager.c:38: if (++music_play_isr_counter & music_tick_mask) return;
	ld	hl, #_music_play_isr_counter
	inc	(hl)
	ld	a, (hl)
	ld	hl, #_music_tick_mask
	and	a, (hl)
	ret	NZ
;sm83/musicmanager.c:39: uint8_t save_bank = _current_bank;
	ldh	a, (__current_bank + 0)
	ld	c, a
;sm83/musicmanager.c:40: SWITCH_ROM(music_current_track_bank);
	ld	hl, #_music_current_track_bank
	ld	a, (hl)
	ldh	(__current_bank + 0), a
	ld	a, (hl)
	ld	(#_rROMB0),a
;sm83/musicmanager.c:41: if (music_next_track) {
	ld	hl, #_music_next_track + 1
	ld	a, (hl-)
	or	a, (hl)
	jr	Z, 00112$
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
;sm83/musicmanager.c:44: hUGE_init(music_next_track);
	push	bc
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	call	_hUGE_init
	pop	bc
;sm83/musicmanager.c:46: music_next_track = 0;
	xor	a, a
	ld	hl, #_music_next_track
	ld	(hl+), a
	ld	(hl), a
	jr	00113$
00112$:
;sm83/musicmanager.c:49: hUGE_dosound();
	push	bc
	call	_hUGE_dosound
	pop	bc
00113$:
;sm83/musicmanager.c:52: SWITCH_ROM(save_bank);
	ld	a, c
	ldh	(__current_bank + 0), a
	ld	hl, #_rROMB0
	ld	(hl), c
;sm83/musicmanager.c:53: }
	ret
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;sm83/musicmanager.c:55: void music_pause(uint8_t pause) {
;	---------------------------------
; Function music_pause
; ---------------------------------
_music_pause::
;sm83/musicmanager.c:56: if (music_play_isr_pause = pause) music_sound_cut();
	ld	(#_music_play_isr_pause),a
	or	a, a
	ret	Z
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
;sm83/musicmanager.c:56: if (music_play_isr_pause = pause) music_sound_cut();
;sm83/musicmanager.c:57: }
	ret
	.area _CODE
	.area _INITIALIZER
__xinit__music_current_track_bank:
	.db #0xff	; 255
__xinit__music_mute_mask:
	.db #0x00	; 0
__xinit__music_play_isr_counter:
	.db #0x00	; 0
__xinit__music_play_isr_pause:
	.db #0x00	; 0
__xinit__music_sfx_priority:
	.db #0x00	; 0
__xinit__music_tick_mask:
	.db #0x03	; 3
	.area _CABS (ABS)
