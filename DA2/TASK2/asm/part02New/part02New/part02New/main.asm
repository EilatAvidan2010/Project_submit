;
; part02New.asm
;
; Created: 3/7/2018 4:06:49 PM
; Author : Eilat
;

.org 0
	SBI DDRB, 2		;PB2 as output
	LDI R17,0		;needed to toogle led
	OUT PORTB,R17 
	CBI DDRD, 2
	SBI PORTD, 2	;port D2 pull up 
	LDI R20,3		;to set prescaler
	STS TCCR1B,R20	;Prescaler: 64

start:
	SBIC	PIND, 2		; skip when PIND2 is low
	RJMP	start
	SBI		PORTB, 2	; Turn on the LED
	SBIC	PIND, 2		; skip when PIND2 is low
	RJMP	start
	CALL	DELAY		; Delay for 1 second
	CBI		PORTB, 2	; Turn off the LED
	RJMP	start
	
delay:
	LDS R29, TCNT1H		 ;loading upper bit of counter to R29
	LDS R28, TCNT1L		;loading lower bit of counter to R28
	CPI R28,0x84	;comparing if lower is 0x23
	BRSH body
	RJMP delay
body:
	CPI R29,0x1E
	BRSH done
	RJMP delay
done:
	LDI R20,0x00
	STS TCNT1H,R20 ;resetting the counter to 0 for next round
	LDI R20,0x00
	STS TCNT1L,R20 ;resetting the counter to 0 for next round
	RET
