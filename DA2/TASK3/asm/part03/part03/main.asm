;
; part03.asm
;
; Created: 3/10/2018 12:55:18 PM
; Author : Eilat
;

.include "M328DEF.INC"
.org 0

	LDI R16, (1<<2)
	SBI DDRB , 2		;set PB2 as an output
	LDI R17 , 0			; using for out
	OUT PORTB, R17
begin:
	RCALL delay			;calling timer to wait 0.25 sec
	EOR R17, R16		;xor to toggle the LED
	out PORTB, R17
	RJMP begin
delay:
	LDI R28, 0x86		;load 134 (TCNT value) to the register
	OUT TCNT0, R28		;load the value to TCNT0
	LDI R20, 0			
	OUT TCCR0A, R20		
	LDI R20, 5			;5- 1024 prescaler (make the value less than 255- 8 bits)
	OUT TCCR0B, R20		;Timer0, normal mode, int clk, 1024 prescaler
lp:
	IN R20, TIFR0		;check if TOV in TIFR register is set to one
	SBRS R20, TOV0		;if so, skip next instruction
	RJMP lp
done:
	LDI R20,0x00
	OUT TCCR0A, R20		;stop timer
	OUT TCCR0B, R20		;stop timer
	LDI R20, (1<<TOV0)
	OUT TIFR0, R20		;clear flag by writing 1 to TIFR
	RET
