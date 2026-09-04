;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler
; Version 4.5.1 #15267 (Linux)
;--------------------------------------------------------
	.module lookup_table_1_3
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _level_1_3_lookup
	.globl b___func_level_1_3_lookup
	.globl ___func_level_1_3_lookup
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
	.area _CODE_255
;src/lookup_table_1_3.c:5: BANKREF(level_1_3_lookup)
;	---------------------------------
; Function __func_level_1_3_lookup
; ---------------------------------
	b___func_level_1_3_lookup	= 255
___func_level_1_3_lookup::
	.local b___func_level_1_3_lookup 
	___bank_level_1_3_lookup = b___func_level_1_3_lookup 
	.globl ___bank_level_1_3_lookup 
	.area _CODE_255
_level_1_3_lookup:
	.dw #0x009b
	.db #0x0b	; 11
	.db #0x00	; 0
	.db #0x05	; 5
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x00bb
	.db #0x0a	; 10
	.db #0x00	; 0
	.db #0x01	; 1
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x00ce
	.db #0x0b	; 11
	.db #0x01	; 1
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x00fb
	.db #0x0c	; 12
	.db #0x00	; 0
	.db #0x05	; 5
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x0114
	.db #0x0b	; 11
	.db #0x00	; 0
	.db #0x05	; 5
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x0124
	.db #0x0b	; 11
	.db #0x00	; 0
	.db #0x05	; 5
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.area _INITIALIZER
	.area _CABS (ABS)
