/*
 * part03.c
 *
 * Created: 3/5/2018 11:18:46 AM
 * Author : Eilat
 */ 

#include <avr/io.h>
void delay();

int main()
{
	
	DDRB |= 0x04;		//set DE2 as an output
	PORTB = 0x00;		//initialize output to zero
	while (1)
	{
	delay();
	PORTB ^= 0x04;	//xor to toggle LED portb 2
	}
}

void delay (){
	TCNT0 = 0x86;
	TCCR0A |= 0;
	TCCR0B |= (1 << CS02) | (1 << CS00);	//1024 prescaler   
	while ((TIFR0 & 0x01)== 0)
	{
		//DO nothing
	}
	TCCR0A = 0x00;		//stop timer
	TIFR0 |= (1<<TOV0);
}



