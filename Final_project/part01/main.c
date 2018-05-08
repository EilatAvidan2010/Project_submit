/*
 * part01.c
 *
 * Created: 5/5/2018 12:26:02 PM
 * Author : Eilat
 */ 

#define F_CPU 8000000UL
#define UBRR_9600 51 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdint.h>

volatile unsigned int adc_speed;		//global variables
char outs[20];


void adc_init(void)
{
	ADMUX = (0<<REFS1)| 	// Reference Selection Bits
	(1<<REFS0)|				// AVcc - external cap at AREF
	(1<<ADLAR)| 			// ADC left Adjust Result
	(0<<MUX2)| 				// Analog Channel Selection Bits
	(0<<MUX1)| 				// ADC0 Pin
	(0<<MUX0);

	ADCSRA = (1<<ADEN)| 	// ADC ENable
	(1<<ADSC)| 				// ADC Start Conversion
	(1<<ADATE)| 			// ADC Auto Trigger Enable
	(0<<ADIF)| 				// ADC Interrupt Flag
	(0<<ADIE)| 				// ADC Interrupt Enable
	(1<<ADPS2)| 			// ADC Prescaler Select Bits
	(0<<ADPS1)|
	(1<<ADPS0);

}

void read_adc(void)
{
	unsigned char i =4;					//set i to 4- make 4 readings
	adc_speed = 0;						//initialize ADC_TEMP
	while (i--)
	{
		ADCSRA |= (1<<ADSC);
		while((ADCSRA & (1<<ADIF)) == 0);
		adc_speed += ADCH;					//sum up 4 readings
		_delay_ms(50);
	}
	adc_speed = adc_speed / 4; 				// Average of four samples
}


void USART_init( unsigned int ubrr )
{
	UBRR0H = (unsigned char)(ubrr>>8);			//set baud rate
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << TXEN0) | (1 <<RXEN0); 		// Enable receiver, transmitter
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01); 	//asynchronous 8-bit data 1 stop bit
}

void USART_tx_string( char *data )
{
	while ((*data != '\0'))
	{
		while (!(UCSR0A & (1 <<UDRE0)));	//wait for the transmit buffer to empty
		UDR0 = *data;						//put the data into the empty buffer, which sends the data
		_delay_ms(125); 					// wait a bit
		data++;
	}
}
/*
unsigned char USART_Receive( void )
{

	while ( !(UCSR0A & (1<<RXC)) )
	{
		// Wait for data
	}

	return UDR0;
}
*/
int main()
{
		adc_init(); 			// Initialize the ADC (Analog / Digital Converter)
		USART_init(UBRR_9600); 	// Initialize the USART (RS232 interface)
		USART_tx_string("DC motor with encoder:\r\n"); 	
		_delay_ms(125); 					// wait a bit
		TCCR0A |= (1 << WGM00);		//fast pwm mode
		TCCR0A |= (1 << WGM01);		//fast pwm mode
		TCCR0A |= (1 << COM0A0);	//compare output mode
		TCCR0A |= (1 << COM0A1);	//compare output mode
		TCCR0B |= (1 << CS00);		//set timer counter
		TCCR0B &= ~(1 << CS01);
		TCCR0B &= ~(1 << CS02);
		OCR0A = 128;						//50 % duty cycle 
		
		sei();
		while(1)
		{
			// wait for interrupt
		}

}

ISR (TIMER0_OVF_vect)					//overflow interrupt
{
	TCCR0B = 0;							//stop the counter
	read_adc();
	snprintf(outs,sizeof(outs),"%3d\r\n", adc_speed);	// print ADC value
	USART_tx_string(outs);
	_delay_ms(125); 					// wait a bit
	TCNT0 = 128;
}

