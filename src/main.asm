.equ iVal = 39998	 ;Loop constant
.include"m32Adef.inc"
.cseg

.org 0
;
; µC to EEPROM.asm
;
; Created: 23-01-2022 15:05:11
; Author : prince
;
; --------------------DISABLE JTAG TO USE PINC AND PORTC--------
LDI R20,0x81
OUT MCUCSR, R20
OUT MCUCSR, R20
CLR R20

; ----------------------------Headers--------------------------------
OUT DDRA, R16	;Address bus Always Input
OUT DDRB, R16	;Address bus Always Input

LDI R16, 0xF0

OUT DDRC, R16	;Control Bus [Last Bits (c3, c2, c1, c0)] Always Input
LDI R16, 0x01	;	Only for Security Reasons
OUT MCUCSR, R16
CLR R16

LDI R16, 0xFF
OUT DDRD, R16
CLR R16
OUT PORTD, R16
; -------------------------------------------------------------------

/*			Control_Bus
--------------------------------------------------
	C0 -> CE		Chip Enable		|
	C1 -> OE		Output Enable	|
	C2 -> WE		Write Enable	|
	C3 -> ED		Erase Data		|
--------------------------------------------------*/

;-------------------------------------This is Main Function(looped) Starting----------------------------------------
start:
	
	IN R16, PINC
	LDI R17, 0x0B			;0000 1011 Write2
	;---------------
	CP R16,R17
	BREQ WRITE
	;---------------
	LDI R19, 0x0D			;0000 1101 Read
	CP R16,R19
	BREQ READ

    rjmp start

;-------------------------------------This is Main Function(looped) Ending----------------------------------------

;-------------------------------------Read Function---------------------------------------------------------------
READ:

	CLR R17
	LDI R17, 0xFF
	OUT DDRD, R17
RESET_READ:					;Our Memory is Quiet Busy
	SBIC EECR,1
	RJMP RESET_READ

	CLR R17
	CLR R19
	IN R17, PINA	;address
	IN R19, PINB	;address

	OUT EEARL,R17
	OUT EEARH, R18

	SBI EECR,0x01		      ;SET-UP TO READ
	IN  R20,EEDR           ;READ THE DATA REGISTER
	OUT PORTD, R20

	
	NOP
	NOP
	NOP
	NOP
	NOP

	SBI EECR, 0

	RET
;-------------------------------------Read Function---------------------------------------------------------------

;-------------------------------------Write Function--------------------------------------------------------------
WRITE:
	
	CLR R17
	OUT DDRD, R17
RESET_WRITE:
	SBIC EECR,1
	RJMP RESET_WRITE

	CLR R17
	CLR R19
	IN R17, PINA	;address
	IN R19, PINB	;address

	OUT EEARL,R17
	OUT EEARH, R18

	LDI R17, 0x00
	IN R17, PIND

	OUT EEDR, R17

	SBI EECR,2
	SBI EECR,1
	OUT 0x3F, R17

	NOP
	NOP
	NOP
	NOP
	NOP

	SBI EECR, 0

	RET
;-------------------------------------Write Function--------------------------------------------------------------

;--------------------------------------This is Delay Section----------------------------------------------

; Don't Use Registers [24,25,18] Specially While Using Loop condition. Or Set there value 0x00 after the use and before the loop.
delay10ms:
	ldi	r24,LOW(iVal)	; intialize inner loop count in inner
	ldi	r25,HIGH(iVal)	; loop high and low registers

iLoop:
	sbiw	r24,1		; decrement inner loop registers
	brne	iLoop			; branch to iLoop if iLoop registers != 0

	dec	r18			; decrement outer loop register
	brne	delay10ms		; branch to oLoop if outer loop register != 0
	nop				; no operation
	ret

; Use this to Execute loop Condition----------------
	;ldi	r18,2		; initialize delay multiple for 0.5 sec
	;rcall	delay10ms
;--------------------------------------This is Delay Section----------------------------------------------
