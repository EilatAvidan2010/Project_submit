/*
 * part03.c
 *
 * Created: 4/12/2018 9:45:35 PM
 * Author : Eilat
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

int ADCvalue; 


int main(void)
{
	TCCR1A |= (1<<COM1A1) | (1<<COM1B1)| (1<<WGM11);				//TIMER1
	TCCR1B |= (1<<WGM13)| (1<<WGM12)| (1<<CS11)|(1<<CS10);		//prescaler 64
	ICR1 = 2500;		//fPWM = 50Hz, period 20ms
	DDRB= 0xFF;
	DDRC = 0x00;		//set port c as an input
	DDRD = 0xFF;		//set port d as an output
	ADMUX = 0x00;		//use ADC0 connected to the potentiometer
	ADMUX |= (1<<REFS0);	//AVcc
	ADMUX |= (1<<ADLAR);	//right adjust
	ADCSRA |= (1<<ADPS2) |(1<<ADPS1) |(1<<ADPS0); //prescaler of 128
	ADCSRA |= (1<<ADEN);		//ADC enable
	ADCSRA |= (1<<ADATE);		//auto trigger enable
	ADCSRB = 0;		//free mode
	ADCSRA |= (1<<ADIE);		//enable interrupt
	ADCSRA |= (1<<ADSC);
	OCR1A = 63; //0 degree, min value
	sei();	
	while (1)
	{
		OCR1A = ADCvalue; //motor gets ADC value
		_delay_ms(10);
	
	}
}

ISR(ADC_vect)
{
	ADCvalue = ADCH;			// Output ADCH to ADC value 
}


	


