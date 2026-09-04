;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler
; Version 4.5.1 #15267 (Linux)
;--------------------------------------------------------
	.module lookup_table_3_3
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _level_3_3_lookup
	.globl b___func_level_3_3_lookup
	.globl ___func_level_3_3_lookup
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
;src/lookup_table_3_3.c:5: BANKREF(level_3_3_lookup)
;	---------------------------------
; Function __func_level_3_3_lookup
; ---------------------------------
	b___func_level_3_3_lookup	= 255
___func_level_3_3_lookup::
	.local b___func_level_3_3_lookup 
	___bank_level_3_3_lookup = b___func_level_3_3_lookup 
	.globl ___bank_level_3_3_lookup 
	.area _CODE_255
_level_3_3_lookup:
	.dw #0x0017
	.db #0x0a	; 10
	.db #0x02	; 2
	.db #0x06	; 6
	.db #0x00	; 0
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x0020
	.db #0x0b	; 11
	.db #0x02	; 2
	.db #0x06	; 6
	.db #0x00	; 0
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x0024
	.db #0x02	; 2
	.db #0x02	; 2
	.db #0x06	; 6
	.db #0x00	; 0
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x002d
	.db #0x03	; 3
	.db #0x02	; 2
	.db #0x06	; 6
	.db #0x00	; 0
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x004c
	.db #0x0e	; 14
	.db #0x02	; 2
	.db #0x06	; 6
	.db #0x00	; 0
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x004e
	.db #0x06	; 6
	.db #0x03	; 3
	.byte #0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x004f
	.db #0x06	; 6
	.db #0x03	; 3
	.byte #0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x0050
	.db #0x0b	; 11
	.db #0x00	; 0
	.db #0x01	; 1
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x0051
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x03	; 3
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x006a
	.db #0x0e	; 14
	.db #0x00	; 0
	.db #0x0d	; 13
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x006d
	.db #0x05	; 5
	.db #0x00	; 0
	.db #0x01	; 1
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x0072
	.db #0x0e	; 14
	.db #0x00	; 0
	.db #0x0d	; 13
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x0077
	.db #0x0c	; 12
	.db #0x02	; 2
	.db #0x06	; 6
	.db #0x00	; 0
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x00b5
	.db #0x0e	; 14
	.db #0x02	; 2
	.db #0x06	; 6
	.db #0x00	; 0
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x00ba
	.db #0x0e	; 14
	.db #0x02	; 2
	.db #0x06	; 6
	.db #0x00	; 0
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x00de
	.db #0x0d	; 13
	.db #0x00	; 0
	.db #0x09	; 9
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x00e4
	.db #0x0d	; 13
	.db #0x00	; 0
	.db #0x0b	; 11
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x0111
	.db #0x05	; 5
	.db #0x00	; 0
	.db #0x09	; 9
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x0125
	.db #0x0c	; 12
	.db #0x00	; 0
	.db #0x0e	; 14
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.area _INITIALIZER
	.area _CABS (ABS)
