/*
 * ADCwithoutInt.c
 *
 * Created: 1/13/2018 10:10:48 PM
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
#include <util/delay.h>


#include "liqDis.h"
#include "adclib.h"

int main(void)
{

	initLCD();
	clearDisplay();
	
	initADC();

	

    while (1) 
    {

		sendNum(readADC(1));
		sendStr("    ");
		setCursor(1,1);
    }
}

