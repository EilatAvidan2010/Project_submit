/*
 * part04.c
 *
 * Created: 3/5/2018 11:19:58 AM
 * Author : Eilat
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
volatile int counter = 0;


int main()
{
	DDRB = 0x02;		//set DE2 as an output
	PORTB = 0x00;		//initialize output to zero
	TCNT0 = 134;		//load 134 to the counter
	TIMSK0 = (1<<TOIE0);	//start timer
	TCCR0A = 0;
	TCCR0B = 5;			//timer0, normal mode, prescaler of 1024
	sei();				//interrupt
	while (1)
	{
		// do nothing		
	}
}

ISR (TIMER1_OVF_vect) {
	TIFR0 = (1<<0);
	if (counter == 134) {
		PORTB ^= (1<<2);		//toggle the LED portb 2
		counter = 0;
	}
	else
		counter++; 
}



