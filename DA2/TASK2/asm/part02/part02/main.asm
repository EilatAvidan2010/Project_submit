;
; part02.asm
;
; Created: 3/5/2018 12:33:24 PM
; Author : Eilat
;

.org 0
	SBI DDRB, 2		;PB2 as output
	LDI R17,0		;needed to toogle led
	OUT PORTB,R17 
	CBI DDRD, 2
	SBI PORTD, 2	;port D2 pull up 
	LDI R20,2		;to set prescaler
	STS TCCR1B,R20	;Prescaler: 8
begin:
	in R19, PORTB
	CPI R19, 2
	BRNE begin
	RCALL delay		;calling timer to wait for 1 sec
	EOR R17,R16		;XOR to toogle led
	OUT PORTB,R17
start:
	in R18, PORTB
	CPI R18, 4
	BREQ start
	EOR R17,R16		;XOR to toogle led
	OUT PORTB,R17
	RJMP begin		;repeating i.e, while(1)
delay:
	LDS R29, TCNT1H ;loading upper bit of counter to R29
	LDS R28, TCNT1L ;loading lower bit of counter to R28
	CPI R28,0x3e ;comparing if lower is 0xC6
	BRSH body
	RJMP delay
body:
	CPI R29,0x0f
	BRSH done
	RJMP delay
done:
	LDI R20,0x00
	STS TCNT1H,R20 ;resetting the counter to 0 for next round
	LDI R20,0x00
	STS TCNT1L,R20 ;resetting the counter to 0 for next round
	RET
	.ORG 0
	; Initialize stack
	LDI		R16, HIGH(RAMEND)
	OUT		SPH, R16
	LDI		R16, LOW(RAMEND)
	OUT		SPL, R16

	; Port initialization
	CBI		DDRD, 2		; Set PORTD.2 as an input
	SBI		PORTD, 2	; Pull up the resistor of PORTD.2
	SBI		DDRB, 2		; Set PORTB.2 as an output

POLL:
	SBIC	PIND, 2		; Poll until PIND.2 is low
	RJMP	POLL
	SBI		PORTB, 2	; Light up the LED
	CALL	DELAY		; Delay for 1 second
	CBI		PORTB, 2	; Turn off the LED
	RJMP	POLL

	; Delay subroutine (F = 0.5 MHz)
DELAY:
	; Set the TCNT1 = 65536-62500 = 3036
	LDI		R20, HIGH(-62500)
	STS		TCNT1H, R20
	LDI		R20, LOW(-62500)
	STS		TCNT1L, R20
	; Set timer control register
	LDI		R20, 0x00
	STS		TCCR1A, R20
	LDI		R20, 0x02
	STS		TCCR1B, R20	; Start the timer with a prescalar of 8
LOOP:
	IN		R20, TIFR1	; Check for the TOV flag
	SBRS	R20, TOV0
	RJMP	LOOP
	; Stop timer and clear TOV flag
	LDI		R20, 0x0
	STS		TCCR1B, R20
	LDI		R20, (1<<TOV0)
	OUT		TIFR1, R20
	RET

