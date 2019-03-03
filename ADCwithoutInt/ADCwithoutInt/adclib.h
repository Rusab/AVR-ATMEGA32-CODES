


void initADC(void);
void initADC8bit(void);
uint16_t readADC(uint8_t pin);
uint8_t readADC8bit(uint8_t pin);

void initADC8bit(void)
{
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);	//128 Prescalar selection
	ADMUX |= (1 << ADLAR) | (1 << REFS0) ;					//8bit Left shit and Capacitor AVCC reference
	ADCSRA |= (1 << ADEN);									//turn on adc feature and interupt
	

	
	ADCSRA |= (1 << ADSC);									//first conversion
}

void initADC(void)
{
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);	//128 Prescalar selection
	ADMUX |= (1 << REFS0) ;					//Capacitor AVCC reference
	ADMUX &= ~(1 << ADLAR);					//10bit right shift
	ADCSRA |= (1 << ADEN);									//turn on adc feature and interupt
	

	
	ADCSRA |= (1 << ADSC);									//first conversion
}

uint8_t readADC8bit(uint8_t pin)
{
	ADMUX &= 0xF0;								//Clearing MUX3-0 bits (MUX4 left unchanged)
	ADMUX |= pin;								//selecting Analog Pin
	ADCSRA |= (1 << ADSC);						//start conversion
	
	while(!( bit_is_clear(ADCSRA, ADSC)));		//waiting until conversion is done
	
	return ADCH;
	
}



uint16_t readADC(uint8_t pin)
{
	ADMUX &= 0xF0;								//Clearing MUX3-0 bits (MUX4 left unchanged)
	ADMUX |= pin;								//selecting Analog Pin
	ADCSRA |= (1 << ADSC);						//start conversion
	
	while(!( bit_is_clear(ADCSRA, ADSC)));		//waiting until conversion is done
	
	uint8_t low = ADCL;
	
	uint16_t adcVal = (ADCH << 8) | low;
	
	return adcVal;
	
}

