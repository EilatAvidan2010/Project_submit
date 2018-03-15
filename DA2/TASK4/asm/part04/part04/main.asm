;
; part04.asm
;
; Created: 3/11/2018 8:20:26 PM
; Author : Eilat
;

.include "M328DEF.INC"
.org 0
	jmp main

.org 0X20
	jmp TIMER0_OV_ISR

.org 0x100
main:
	LDI R20, HIGH(RAMEND)	;initalize the stack
	OUT SPH, R20
	LDI R20, LOW(RAMEND)
	OUT SPL, R20

	LDI R16, (1<<2)
	SBI DDRB , 2		;set PB2 as an output
	LDI R17 , 0			; using for out
	OUT PORTB, R17
begin:
	LDI R28, 134		;load 134 (TCNT value) to the register
	OUT TCNT0, R28		;load the value to TCNT0
	;timer int init
	LDI R20, (1<<TOIE0)
	STS TIMSK0, R20
	SEI			;interrupt

	LDI R20, 0			
	OUT TCCR0A, R20		
	LDI R20, 5			;5- 1024 prescaler (make the value less than 255- 8 bits)
	OUT TCCR0B, R20		;Timer0, normal mode, int clk, 1024 prescaler

lp:
	RJMP lp				;an infinit loop

TIMER0_OV_ISR:
	LDI R20, (1<<TOV0)
	OUT TIFR0, R20		;clear flag by writing 1 to TIFR
	EOR R17, R16		;xor to toggle the LED
	OUT PORTB, R17
	LDI R28, 134		;load 134 (TCNT value) to the register
	OUT TCNT0, R28		;load the value to TCNT0
	RETI