/*
 * part01.c
 *
 * Created: 4/12/2018 9:30:14 PM
 * Author : Eilat
 */ 


#include <avr/io.h>
#define  F_CPU 8000000UL
#include <avr/interrupt.h>
#include <util/delay.h>



int main()
{
	
	ADCSRA = 0x87;			//ADC enable, prescaler 128
	ADMUX = 0x60;			//AVcc,  left justified
	DDRB = 0xFF;			// PORTB as output
	PORTD |= (1<<2);		//set up pull up resistor
	OCR1A = 0;				//0% duty cycle initially
	TCCR1B = 0x0D;			//prescaler of 1024
	TCCR1A = 0x83;			//non-inverting mode, fast PWM 10 bit
	EIMSK |= (1<<INT0);		//enable external interrupt 0
	EICRA |= (1<<ISC01);		//falling edge trigger
	sei();
	
	while (1)
	{
		ADCSRA |= (1<<ADSC);			//start conversion
		while ((ADCSRA & (1<<ADIF)) == 0)
		{
			//wait for conversion to finish
		}
		
	}
}
ISR (INT0_vect)
{
	
	EIFR |= (1<<INTF0);		//reset flag
		if((PORTB & 0b00000001) == 0b00000000)	
			PORTB |= (1<<0);
			else
			PORTB &= ~(1<<0);
		
		if(ADCH > 220){
		OCR1A = 600;		//95% duty cycle
		_delay_ms(2000);
		}
		else
		OCR1A = 0;		//0% duty cycle
	
}






