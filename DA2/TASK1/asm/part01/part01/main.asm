;
; part01.asm
;
; Created: 3/3/2018 4:02:21 PM
; Author : Eilat
;


.org 0
	LDI R16, (1<<2)
	SBI DDRB , 2		;set PB2 as an output
	LDI R17 , 0			; using for out
	out PORTB, R17
begin:
	RCALL delay			;calling timer to wait 0.25 sec
	EOR R17, R16		;xor to toggle the LED
	out PORTB, R17
	RJMP begin
delay:
	LDS R29, TCNT1H		;loading upper bit of counter to R29
	LDS R28, TCNT1L 	;loading lower bit of counter to R28
	LDI R20, 0
	STS TCCR1A, R20		;using control timer register
	LDI R20, 2			;set prescaler of 8
	STS TCCR1B, R20		;start the clock
	CPI R28,0x08		;comparing if lower is 0xC6
	BRSH body
	RJMP delay
body:
	CPI R29,0x3D
	BRSH done
	RJMP delay
done:
	LDI R20,0x00
	STS TCNT1H,R20		;resetting the counter to 0 for next round
	LDI R20,0x00
	STS TCNT1L,R20		;resetting the counter to 0 for next round
	RET
	
