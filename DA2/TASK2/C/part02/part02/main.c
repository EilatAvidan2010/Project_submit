/*
 * part02.c
 *
 * Created: 3/3/2018 10:36:30 PM
 * Author : Eilat
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 500000UL	//frequency 0.5MHz
#include <util/delay.h>

int main()
{
	DDRB |=(1<<2);
	DDRD &= ~(1<<2);

	while (1)
	{
			if (PIND & 0x04){			//if switch pressed
				PORTB |= (1<<2);	//turn on LED at port B2
				_delay_ms (1000);	//wait one sec
				
			}
			else {
				PORTB &= ~(1<<2);	//turn the LED off
			}
		
	}

}


	
	


