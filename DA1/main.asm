;
; AssemblerApplication1.asm
;
; Created: 2/17/2018 1:22:14 PM
; Author : Eilat
;

;part 1 of assignment 1, store 300 numbers starting from 0x0222 address location

.ORG 0
LDI R27, 0x02	;store required address to store 300 numbers in XH register
LDI R26, 0x22	;store required address to store 300 numbers in XL register
LDI R29, 0x04	;store required address for divisible by 5 numbers in YH register
LDI R28, 0x00	;store required address for divisible by 5 numbers in YL register
LDI R31, 0x06	;store required address in ZH register (not divisible by 5)
LDI R30, 0x00	;store required address in ZL register (not divisible by 5)
LDI R25, 0		;counter up to 300, resets at 255
LDI R21, 255	;limit the counter in order to reset
LDI R20, 0		;counter to check how many times jumping to this loop
LDI R23, 5		;to check is a number is divisible by five
LDI R16, 0		;initialize sum
LDI R17, 0		;initialize sum
LDI R18, 0		;initialize sum
LDI R19, 0		;initialize sum

	mov R24, R27	;copy value between two registers 
	add R24, R26	;add high and low starting address
StartLp:
	inc R24			;move to the next value
	st X+, r24		;storing the value and incament to the next address location
	mov R22, R24	;copy the value to check id divisible by 5
subFive:
	CPI R22, 5
	BRLO badNum
	CPI R22, 5
	BREQ goodNum
	subi R22, 5		;subtrart 5 until getting negative number
	jmp subFive
contLp:
	inc R25				;increment the counter 
	cp  R25, R21		;check if counter reached 255
	BRSH ResetLp	;if so, reset the counter
	JMP StartLp		;if not, jump to start loop to grab new value
ResetLp:
	LDI R25, 0		;reset the counter
	LDI R21, 46		;reset limiting counter to 45 (255+45=300 total values)
	INC R20			;first time reseting	
	cpi R20, 2		;if it is the second time in the loop, we are done
	BRSH DoneLp
	jmp StartLp		;otherwise, go grab neww value
goodNum:
	st Y+, R24		;store good number
	add R16,R24		;running sum until 255
	brcc noCarry	;if carry, incrament higher register
	inc R17
	jmp contLp		;continue to next value
noCarry:
	jmp contLp
badNum:
	st Z+, R24		;store bad number
	add R18,R24		;running sum until 255
	brcc noCarry	;if carry, incrament higher register
	inc R19
	jmp contLp		;;continue to next value
DoneLp:
	


