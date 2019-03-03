/*
 * ADC.c
 *
 * Created: 1/13/2018 12:30:28 AM
 * Author : Shabab
 */ 

#define F_CPU 16000000UL

#define LCDData			PORTB
#define DD_LCDData		DDRB
#define LCDControl		PORTD
#define DD_LCDControl	DDRD
#define RS				2
#define RW				7
#define ENB				5


#include <avr/io.h>
#include <avr/interrupt.h>

#include "liqDis.h"


int main(void)
{

	initLCD();
	clearDisplay();
	

	
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);	//128 Prescalar selection
	ADMUX |= (1 << ADLAR) | (1 << REFS0) ;					//8bit Left shit and Capacitor AVCC reference
 	ADCSRA |= (1 << ADIE) | (1 << ADEN);					//turn on adc feature and interupt
	
	sei(); 
	
	ADCSRA |= (1 << ADSC);									//first conversion
    while (1) 
    {
    }
}


ISR(ADC_vect)
{
	sendNum(ADCH);
	setCursor(1,1);
	
	ADCSRA |= (1 << ADSC);									//second conversion
}
