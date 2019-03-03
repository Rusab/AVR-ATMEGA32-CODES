#ifndef LCD
#define LCD


#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void checkBusy(void);
void enbFlash(void);
void sendChar(unsigned char x);
void sendCom(unsigned char x);
void clearDisplay(void);
void shiftCursor(int pos, int count);
void shiftDisplay(int pos, int count);
void setCursor(int x, int y);
void initLCD(void);
void initLCDBlink(void);

void sendStr(char *str);
void cursorHide(void);
void customChar(int add, char cc[]);
void sendNum(int num);


void checkBusy(void)
{
	DD_LCDData = 0x00;
	LCDControl |= (1 << RW);
	LCDControl &= ~(1 << RS);
	while(LCDData >= 0x80)
	{
		enbFlash();
	}
	
	DD_LCDData = 0xFF;
}

void enbFlash(void)
{
	
	LCDControl |= (1 << ENB);
	_delay_us(1640);
	asm volatile ("nop");
	asm volatile ("nop");
	LCDControl &= ~(1 << ENB);
}

void sendChar(unsigned char x)
{
	
	checkBusy();
	LCDData = x;
	LCDControl &= ~(1 << RW);
	LCDControl |=  (1 << RS);
	
	enbFlash();
	
	LCDData = 0;
	
}

void sendCom(unsigned char x)
{
	checkBusy();
	LCDData = x;
	
	LCDControl &= ~( (1 << RW) | (1 << RS) );
	
	enbFlash();
	
	LCDData = 0;
}


void clearDisplay(void)
{
	sendCom(0x01);
	_delay_us(1650);
	
	
}

void shiftCursor(int pos, int count)
{
	for(int i = 0; i < count; i++)
	{
		if(pos == 0)
		{
			sendCom(0x10);
			_delay_us(50);
		}
		
		else
		{
			sendCom(0x14);
			_delay_us(50);
		}
	}
	
	checkBusy();
	LCDControl &= ~(1 << RW);
	LCDControl |=  (1 << RS);
	

}


void shiftDisplay(int pos, int count)
{
	for(int i = 0; i < count; i++)
	{
		if(pos == 0)
		{
			sendCom(0x18);
			_delay_us(140);
		}
		
		else
		{
			sendCom(0x1C);
			_delay_us(140);
		}
	}
	
	checkBusy();
	LCDControl &= ~(1 << RW);
	LCDControl |=  (1 << RS);
}

//initializes LCD at 5x8 dot matrix 2 line mode for 8 bit configuration without blinking cursor
void initLCD(void)
{
	DD_LCDControl |= (1 << ENB) | (1 << RW) | (1 << RS);
	_delay_ms(15);
	
	sendCom(0x3C);
	_delay_us(50);
	sendCom(0x0E);
	_delay_us(50);

}

//initializes LCD at 5x8 dot matrix 2 line mode for 8 bit configuration with blinking cursor
void initLCDBlink(void)
{
	DD_LCDControl |= (1 << ENB) | (1 << RW) | (1 << RS);
	_delay_ms(15);
	
	sendCom(0x3C);
	_delay_us(50);
	sendCom(0x0F);
	_delay_us(50);

}

void setCursor(int x, int y)
{
	sendCom(0x02);
	_delay_us(1650);
	
	if(x > 16 || y > 2 || x <= 0 || y <= 0)
	{
		return;
	}
	
	if(y > 1)
	{
		x += 40;
	}
	

	shiftCursor(1, x-1);
}


void sendStr(char *str)
{
	while(*str != 0)
	{
		sendChar(*str);
		str++;
	}
}

void cursorHide(void)
{
	sendCom(0x0C);
	_delay_us(50);
}

void customChar(int add, char cc[])
{
	sendCom(0x40 + add*8);
	_delay_us(50);
	for(int i = 0; i < 6; i++)
	{
		sendChar(cc[i]);
		
	}
	
	
}

void sendNum(int num)
{
	char str[15];
	itoa(num, str, 10);
	sendStr(str);
	
}

void sendFloat(float num, int approx)
{
	char str[15];
	char str2[15];
	int x = (int)num;
	itoa(x, str, 10);
	
	
	num -= x;
	strcat(str, ".");
	
	for(int i = 0; i < approx; i++)
	{
		num *= 10;
	}
	
	num = ceil(num);
	
	x = (int)num;
	
	
	
	itoa(x, str2, 10);
	strcat(str, str2);
	
	
	sendStr(str);
	
	
}

#endif