;
; part05.asm
;
; Created: 3/14/2018 1:36:50 PM
; Author : Eilat
;


; Replace with your application code
.include "M328DEF.INC"
.org 0
	jmp main
.org 0X02				;location for ext_int0
	jmp EX_int0
main:
	LDI R20, HIGH(RAMEND)	;initalize the stack
	OUT SPH, R20
	LDI R20, LOW(RAMEND)
	OUT SPL, R20
	SBI DDRB, 2			;PB2 as output
	LDI R17,0			;needed to toogle led
	OUT PORTB,R17 
	LDI R20,3			;to set prescaler
	STS TCCR1B,R20		;Prescaler: 64
	LDI R20, (1<<INT0)
	STS EIMSK, R20		;set external interrupt
	SEI	
here:
	jmp here
delay:
	LDS R29, TCNT1H		 ;loading upper bit of counter to R29
	LDS R28, TCNT1L		;loading lower bit of counter to R28
	CPI R28,0x84			;comparing if lower is 0x84
	BRSH body
	RJMP delay
body:
	CPI R29,0x1E
	BRSH done
	RJMP delay

EX_int0:
	SBI		PORTB, 2	; Turn on the LED
begin:
	SBIS	PIND2, 2
	RJMP begin
	call delay
	CBI		PORTB, 2	; Turn off the LED
	LDI R21, (1<<INTF0)
	STS EIFR, R21
	RETI
done:
	LDI R20,0x00
	STS TCNT1H,R20 		;resetting the counter to 0 for next round
	LDI R20,0x00
	STS TCNT1L,R20 		;resetting the counter to 0 for next round
	ret

	

