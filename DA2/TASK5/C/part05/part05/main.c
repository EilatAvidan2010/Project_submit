/*
 * part05.c
 *
 * Created: 3/5/2018 11:17:28 AM
 * Author : Eilat
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL	//frequency 1MHz
#include <util/delay.h>

int main()
{
	DDRB |=(1<<2);		//portb sets as an output
	DDRD &= ~(1<<2);	//protd as an input
	EIMSK = (1<<INT0); //int0 is pin B2
	EICRA = (1<<ISC01) | (1<<ISC00); //rising edge
	sei ();			//enable interrupt
	while (1)
	{
		//do nothing
	}

}

ISR (INT0_vect)		//interrupt, turn on LED
{
	EIFR |=(1<<INTF0);
	PORTB |= (1<<2);	//turn on LED at port B2
	_delay_ms (1000);	//wait one sec
	PORTB &= ~(1<<2);	//turn the LED off
	
	
}
