/*
 * PWM.c
 *
 * Created: 6/11/2018 12:51:18 PM
 * Author : Bushra
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	//setting PWM pin (PD5) as output
    DDRD |= (1 << PIND5);
	
	//setting PWM type: Inverting Fast PWM with ICR1 as top value and setting a prescalar of 8
	TCCR1A |= (1 << WGM11 | 1 << COM1A1 | 1 << COM1A0);
	TCCR1B |= (1 << WGM12 | 1 << WGM13 | 1 << CS11);
	
	ICR1 = 39999; //PWM period counting from 0

	
    while (1) 
    {
		OCR1A = ICR1 - 4000;	
		_delay_ms(2000);
		OCR1A = ICR1 - 2000;
		_delay_ms(2000);			
    }
}

