/*
 * part02.c
 *
 * Created: 4/12/2018 9:41:51 PM
 * Author : Eilat
 */ 


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

void delay_count();
int ADCvalue;

int main(void)
{
	DDRC = 0x00;				//set port c as an input
	DDRD = 0xFF;				//set port d as an output
	ADMUX = 0x00;				//use ADC0 connected to the potentiometer
	ADMUX |= (1<<REFS0);		//AVcc
	ADMUX |= (1<<ADLAR);		//right adjust
	ADCSRA |= (1<<ADPS2) |(1<<ADPS1) |(1<<ADPS0); //prescaler of 128
	ADCSRA |= (1<<ADEN);		//ADC enable
	ADCSRA |= (1<<ADATE);		//auto trigger enable
	ADCSRB = 0;					//free mode
	ADCSRA |= (1<<ADIE);		//enable interrupt
	ADCSRA |= (1<<ADSC);		//start conversion
	sei();						//enable interrupt
	 
	while (1)
	{
		{
			PORTD = 0x03;		//clockwise direction 
			delay_count();;
			PORTD = 0x42;
			delay_count();
			PORTD = 0xC0;
			delay_count();
			PORTD = 0x81;
			delay_count();
			
		}
		
	}
}


void delay_count ()
{
	TCNT0 = 0;						//initial count value
	OCR0A = ADCvalue/7;				//compare value
	TCCR0A = (1<<WGM01);			// Configure timer0 for CTC mode.
	TCCR0B = (1<<CS02) |  (1<<CS00) ;	// prescaler 1024
	while ((TIFR0 & (1<<OCR0A)) == 0);
	TCCR0B = 0;							//stop timer
	TIFR0 = (1<<OCR0A);					//reset flag
	
} 

ISR(ADC_vect)
{
	ADCvalue = ADCH;			// Output ADCH to ADCvalue variable
}



