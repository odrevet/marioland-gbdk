;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler
; Version 4.5.1 #15267 (Linux)
;--------------------------------------------------------
	.module text
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _set_win_tile_xy
	.globl _text_print_char
	.globl _text_print_string
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
;src/text.c:3: void text_print_char(uint8_t x, uint8_t y, unsigned char chr) {
;	---------------------------------
; Function text_print_char
; ---------------------------------
_text_print_char::
	ld	c, a
;src/text.c:6: if (chr >= '1' && chr <= '9') {
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x31
	jr	C, 00136$
	ld	a, #0x39
	sub	a, (hl)
	jr	C, 00136$
;src/text.c:7: tile = chr - '0';
	ld	a, (hl)
	add	a, #0xd0
	jp	00137$
00136$:
;src/text.c:9: switch (chr) {
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x20
	jp	Z, 00132$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x21
	jp	Z, 00130$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x2c
	jp	Z, 00129$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x2d
	jp	Z, 00127$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x2e
	jp	Z, 00128$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x30
	jp	Z, 00101$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x3f
	jp	Z, 00131$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x41
	jp	Z, 00102$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x42
	jp	Z, 00103$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x43
	jp	Z, 00104$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x44
	jp	Z, 00105$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x45
	jp	Z, 00106$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x46
	jp	Z, 00107$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x47
	jp	Z, 00108$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x48
	jp	Z, 00109$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x49
	jp	Z, 00110$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x4b
	jp	Z, 00111$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x4c
	jp	Z, 00112$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x4d
	jp	Z, 00113$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x4e
	jp	Z, 00114$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x4f
	jp	Z, 00115$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x50
	jp	Z, 00116$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x51
	jp	Z, 00117$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x52
	jp	Z, 00118$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x53
	jp	Z, 00119$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x54
	jr	Z, 00120$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x55
	jr	Z, 00121$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x56
	jr	Z, 00122$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x57
	jr	Z, 00123$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x59
	jr	Z, 00124$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x5a
	jr	Z, 00125$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x78
	jr	Z, 00126$
	jp	00133$
;src/text.c:10: case '0':
00101$:
;src/text.c:11: tile = LETTERS_STARTS_AT + 13;
	ld	a, #0x17
;src/text.c:12: break;
	jp	00137$
;src/text.c:13: case 'A':
00102$:
;src/text.c:14: tile = LETTERS_STARTS_AT + 0;
	ld	a, #0x0a
;src/text.c:15: break;
	jr	00137$
;src/text.c:16: case 'B':
00103$:
;src/text.c:17: tile = LETTERS_STARTS_AT + 1;
	ld	a, #0x0b
;src/text.c:18: break;
	jr	00137$
;src/text.c:19: case 'C':
00104$:
;src/text.c:20: tile = LETTERS_STARTS_AT + 2;
	ld	a, #0x0c
;src/text.c:21: break;
	jr	00137$
;src/text.c:22: case 'D':
00105$:
;src/text.c:23: tile = LETTERS_STARTS_AT + 3;
	ld	a, #0x0d
;src/text.c:24: break;
	jr	00137$
;src/text.c:25: case 'E':
00106$:
;src/text.c:26: tile = LETTERS_STARTS_AT + 4;
	ld	a, #0x0e
;src/text.c:27: break;
	jr	00137$
;src/text.c:28: case 'F':
00107$:
;src/text.c:29: tile = LETTERS_STARTS_AT + 5;
	ld	a, #0x0f
;src/text.c:30: break;
	jr	00137$
;src/text.c:31: case 'G':
00108$:
;src/text.c:32: tile = LETTERS_STARTS_AT + 6;
	ld	a, #0x10
;src/text.c:33: break;
	jr	00137$
;src/text.c:34: case 'H':
00109$:
;src/text.c:35: tile = LETTERS_STARTS_AT + 7;
	ld	a, #0x11
;src/text.c:36: break;
	jr	00137$
;src/text.c:37: case 'I':
00110$:
;src/text.c:38: tile = LETTERS_STARTS_AT + 8;
	ld	a, #0x12
;src/text.c:39: break;
	jr	00137$
;src/text.c:40: case 'K':
00111$:
;src/text.c:41: tile = LETTERS_STARTS_AT + 9;
	ld	a, #0x13
;src/text.c:42: break;
	jr	00137$
;src/text.c:43: case 'L':
00112$:
;src/text.c:44: tile = LETTERS_STARTS_AT + 10;
	ld	a, #0x14
;src/text.c:45: break;
	jr	00137$
;src/text.c:46: case 'M':
00113$:
;src/text.c:47: tile = LETTERS_STARTS_AT + 11;
	ld	a, #0x15
;src/text.c:48: break;
	jr	00137$
;src/text.c:49: case 'N':
00114$:
;src/text.c:50: tile = LETTERS_STARTS_AT + 12;
	ld	a, #0x16
;src/text.c:51: break;
	jr	00137$
;src/text.c:52: case 'O':
00115$:
;src/text.c:53: tile = LETTERS_STARTS_AT + 13;
	ld	a, #0x17
;src/text.c:54: break;
	jr	00137$
;src/text.c:55: case 'P':
00116$:
;src/text.c:56: tile = LETTERS_STARTS_AT + 14;
	ld	a, #0x18
;src/text.c:57: break;
	jr	00137$
;src/text.c:58: case 'Q':
00117$:
;src/text.c:59: tile = LETTERS_STARTS_AT + 15;
	ld	a, #0x19
;src/text.c:60: break;
	jr	00137$
;src/text.c:61: case 'R':
00118$:
;src/text.c:62: tile = LETTERS_STARTS_AT + 16;
	ld	a, #0x1a
;src/text.c:63: break;
	jr	00137$
;src/text.c:64: case 'S':
00119$:
;src/text.c:65: tile = LETTERS_STARTS_AT + 17;
	ld	a, #0x1b
;src/text.c:66: break;
	jr	00137$
;src/text.c:67: case 'T':
00120$:
;src/text.c:68: tile = LETTERS_STARTS_AT + 18;
	ld	a, #0x1c
;src/text.c:69: break;
	jr	00137$
;src/text.c:70: case 'U':
00121$:
;src/text.c:71: tile = LETTERS_STARTS_AT + 19;
	ld	a, #0x1d
;src/text.c:72: break;
	jr	00137$
;src/text.c:73: case 'V':
00122$:
;src/text.c:74: tile = LETTERS_STARTS_AT + 20;
	ld	a, #0x1e
;src/text.c:75: break;
	jr	00137$
;src/text.c:76: case 'W':
00123$:
;src/text.c:77: tile = LETTERS_STARTS_AT + 21;
	ld	a, #0x1f
;src/text.c:78: break;
	jr	00137$
;src/text.c:79: case 'Y':
00124$:
;src/text.c:80: tile = LETTERS_STARTS_AT + 22;
	ld	a, #0x20
;src/text.c:81: break;
	jr	00137$
;src/text.c:82: case 'Z':
00125$:
;src/text.c:83: tile = LETTERS_STARTS_AT + 23;
	ld	a, #0x21
;src/text.c:84: break;
	jr	00137$
;src/text.c:85: case 'x':
00126$:
;src/text.c:86: tile = LETTERS_STARTS_AT + 24;
	ld	a, #0x22
;src/text.c:87: break;
	jr	00137$
;src/text.c:88: case '-':
00127$:
;src/text.c:89: tile = LETTERS_STARTS_AT + 25;
	ld	a, #0x23
;src/text.c:90: break;
	jr	00137$
;src/text.c:91: case '.':
00128$:
;src/text.c:92: tile = LETTERS_STARTS_AT + 26;
	ld	a, #0x24
;src/text.c:93: break;
	jr	00137$
;src/text.c:94: case ',':
00129$:
;src/text.c:95: tile = LETTERS_STARTS_AT + 27;
	ld	a, #0x25
;src/text.c:96: break;
	jr	00137$
;src/text.c:97: case '!':
00130$:
;src/text.c:98: tile = LETTERS_STARTS_AT + 28;
	ld	a, #0x26
;src/text.c:99: break;
	jr	00137$
;src/text.c:100: case '?':
00131$:
;src/text.c:101: tile = LETTERS_STARTS_AT + 29;
	ld	a, #0x27
;src/text.c:102: break;
	jr	00137$
;src/text.c:103: case ' ':
00132$:
;src/text.c:104: tile = 0;
	xor	a, a
;src/text.c:105: break;
	jr	00137$
;src/text.c:106: default:
00133$:
;src/text.c:107: tile = LETTERS_STARTS_AT + 29;
	ld	a, #0x27
;src/text.c:108: }
00137$:
;src/text.c:111: set_win_tile_xy(x, y, tile + textTileset_TILE_ORIGIN);
	push	af
	inc	sp
	ld	a, c
	call	_set_win_tile_xy
;src/text.c:113: }
	pop	hl
	inc	sp
	jp	(hl)
;src/text.c:115: void text_print_string(uint8_t x, uint8_t y, unsigned char *string) {
;	---------------------------------
; Function text_print_string
; ---------------------------------
_text_print_string::
	add	sp, #-4
	ldhl	sp,	#1
	ld	(hl-), a
;src/text.c:116: uint8_t offset_x = 0;
	ld	a, e
	ld	(hl+), a
	inc	hl
;src/text.c:119: while (string[0]) {
	xor	a, a
	ld	(hl+), a
	ld	(hl), a
00104$:
	ldhl	sp,#6
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
;src/text.c:120: if (string[0] == '\n') {
	ld	b,a
	or	a,a
	jr	Z, 00107$
	sub	a, #0x0a
	jr	NZ, 00102$
;src/text.c:121: offset_x = 0;
	ldhl	sp,	#2
;src/text.c:122: offset_y++;
	xor	a, a
	ld	(hl+), a
	inc	(hl)
	jr	00103$
00102$:
;src/text.c:124: text_print_char(x + offset_x, y + offset_y, (unsigned char)string[0]);
	ldhl	sp,	#0
	ld	a, (hl)
	ldhl	sp,	#3
	add	a, (hl)
	dec	hl
	dec	hl
	ld	e, a
	ld	a, (hl+)
	add	a, (hl)
	push	bc
	inc	sp
	call	_text_print_char
;src/text.c:125: offset_x++;
	ldhl	sp,	#2
	inc	(hl)
00103$:
;src/text.c:128: string += 1;
	ldhl	sp,	#6
	inc	(hl)
	jr	NZ, 00104$
	inc	hl
	inc	(hl)
	jr	00104$
00107$:
;src/text.c:130: }
	add	sp, #4
	pop	hl
	pop	af
	jp	(hl)
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
