;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler
; Version 4.5.1 #15267 (Linux)
;--------------------------------------------------------
	.module lookup_table_underground
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _underground_0_lookup
	.globl b___func_underground_lookup
	.globl ___func_underground_lookup
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
;src/lookup_table_underground.c:4: BANKREF(underground_lookup)
;	---------------------------------
; Function __func_underground_lookup
; ---------------------------------
	b___func_underground_lookup	= 255
___func_underground_lookup::
	.local b___func_underground_lookup 
	___bank_underground_lookup = b___func_underground_lookup 
	.globl ___bank_underground_lookup 
	.area _CODE_255
_underground_0_lookup:
	.dw #0x0010
	.db #0x0d	; 13
	.db #0x05	; 5
	.dw #0x0002
	.db #0x0a	; 10
	.dw (_levels + 0)
	.db #0x02	; 2
	.db #0x00	; 0
	.area _INITIALIZER
	.area _CABS (ABS)
