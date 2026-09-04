;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler
; Version 4.5.1 #15267 (Linux)
;--------------------------------------------------------
	.module lookup_table_1_1
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _level_1_1_lookup
	.globl b___func_level_1_1_lookup
	.globl ___func_level_1_1_lookup
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
;src/lookup_table_1_1.c:4: BANKREF(level_1_1_lookup)
;	---------------------------------
; Function __func_level_1_1_lookup
; ---------------------------------
	b___func_level_1_1_lookup	= 255
___func_level_1_1_lookup::
	.local b___func_level_1_1_lookup 
	___bank_level_1_1_lookup = b___func_level_1_1_lookup 
	.globl ___bank_level_1_1_lookup 
	.area _CODE_255
_level_1_1_lookup:
	.dw #0x0016
	.db #0x09	; 9
	.db #0x01	; 1
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x0017
	.db #0x0d	; 13
	.db #0x00	; 0
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x0029
	.db #0x0c	; 12
	.db #0x04	; 4
	.dw #0x0002
	.db #0x02	; 2
	.dw (_undergrounds + 0)
	.db #0x00	; 0
	.db #0x00	; 0
	.dw #0x0042
	.db #0x0a	; 10
	.db #0x00	; 0
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x0050
	.db #0x04	; 4
	.db #0x00	; 0
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x0052
	.db #0x04	; 4
	.db #0x00	; 0
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x005f
	.db #0x06	; 6
	.db #0x01	; 1
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x0075
	.db #0x0d	; 13
	.db #0x00	; 0
	.db #0x01	; 1
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x009c
	.db #0x0d	; 13
	.db #0x00	; 0
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x00a6
	.db #0x0d	; 13
	.db #0x00	; 0
	.db #0x02	; 2
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x00a9
	.db #0x0d	; 13
	.db #0x00	; 0
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x00ae
	.db #0x06	; 6
	.db #0x01	; 1
	.db #0x01	; 1
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x00ba
	.db #0x0a	; 10
	.db #0x00	; 0
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x00c3
	.db #0x0a	; 10
	.db #0x00	; 0
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x00cd
	.db #0x0d	; 13
	.db #0x00	; 0
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x00d2
	.db #0x0d	; 13
	.db #0x00	; 0
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x00ea
	.db #0x0d	; 13
	.db #0x00	; 0
	.db #0x02	; 2
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x00f5
	.db #0x0d	; 13
	.db #0x00	; 0
	.db #0x02	; 2
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x0119
	.db #0x03	; 3
	.db #0x02	; 2
	.db #0x06	; 6
	.db #0x00	; 0
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.dw #0x011b
	.db #0x01	; 1
	.db #0x02	; 2
	.db #0x06	; 6
	.db #0x01	; 1
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.area _INITIALIZER
	.area _CABS (ABS)
