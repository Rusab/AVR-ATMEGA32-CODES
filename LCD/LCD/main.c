/*
 * LCD.c
 *
 * Created: 1/4/2018 4:24:43 PM
 * Author : Rusab
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

int main(void)
{

   
				
	initLCD();

	
	
// 	sendFloat(32.23, 2);
// 	_delay_us(50);
	
/*	char b[7]={0x10,0x10,0x16,0x19,0x11,0x11,0x1E};  //'b' Character Pattern*/
// 			
//  	customChar(1, b);
// // 	
// 	sendCom(1);
// 	_delay_us(50);

/*	setCursor(5, 2);*/


	
	//sendCom(0);
	
//	sendStr("BitechX");
 	sendFloat(754.23, 2);

	
	
    while (1) 
    {
		
// 		sendFloat(754.23 + x, 2);	
// 		x += 0.01;
// 		_delay_ms(200);
// 		clearDisplay();
		
    }
}
