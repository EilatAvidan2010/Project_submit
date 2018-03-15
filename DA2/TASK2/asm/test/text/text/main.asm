;
; text.asm
;
; Created: 3/7/2018 4:15:37 PM
; Author : Eilat
;


.org 0x00
	LDI R16, (1<<2)
	out DDRB , R16
LP:
	SBI PORTB, 2
	CBI PORTB, 2
	RJMP LP
