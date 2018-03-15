/*
 * part1.c
 *
 * Created: 3/3/2018 3:55:55 PM
 * Author : Eilat
 */ 

#include <avr/io.h>
#define  F_CPU 5000000UL
#include <util/delay.h>


int main()
{
    DDRB = 0x04;		//set DE2 as an output
	PORTB = 0x00;		//initialize output to zero
    while (1) 
    {
		PORTB |= (1<<2);	//turn on LED portb 2
		_delay_ms(250);		//delay of 0.25 seconds
		PORTB &= ~(1<<2);	//turn off the LED
		_delay_ms(250);		//delay of 0.25 seconds
		
    }
}

