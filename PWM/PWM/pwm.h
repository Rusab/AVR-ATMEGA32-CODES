#ifndef PWM
#define PWM

#include <avr/io.h>

void initPWM(int pin)
{
	//~16us period non inverting 8 bit Fast PWM 
	switch(pin)
		case PIND7:
			TCCR2 = (1 << WGM20 | 1 << WGM21 | 1 << COM21 | 1 << CS20);
			break;
	
		case PINB3:
			TCCR0 = (1 < WGM01 | 1 << WGM00 | 1 << COM01 | 1 << CS00);
			break;
			
		case PIND5:
			TCCR1A |= (1 << WGM10 | 1 << COM1A1);
			TCCR1B |= (1 << WGM12 | 1 << CS10);
			break;
			
		case PIND4:
			TCCR1A |= (1 << WGM10 | 1 << COM1B1);
			TCCR1B |= (1 << WGM12 | 1 << CS10);
			break;	
	
}




void analogWrite(int pin, int width)
{
switch(pin)
{	
	case PIND7:
	OCR2 = width;
	break;
	
	case PINB3:
	OCR0 = width;
	break;
	
	case PIND5:
	OCR1A = width;
	break;
	
	case PIND4:
	OCR1B = width;
	break;
}

}



#endif