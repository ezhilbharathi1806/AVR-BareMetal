/*
 * ATmega16_ADC-Potentiometer_LCD.c
 *
 * Created: 30-08-2024 21:57:57
 * Author : Ezhil Bharathi
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD_8-bitmode.h"

#define  F_CPU 8000000UL

volatile unsigned int ADC_value;

int main(void)
{
    /*============== ADC ==============*/
    
    //Enable the Global Interrupt Enable Bit
    sei();
    
    //Set reference to NO AVCC and input to ADC0
    ADMUX = 0x00;
    
    //Enable ADC
    ADCSRA |= (1<<ADEN)|(1<<ADIE);
    
    //Set frequency of ADC Conversion
    ADCSRA |=(1<<ADPS2)|(1<<ADPS1);
    ADCSRA &= ~(1<<ADPS0);
    
    
/*  LCD 16x2  */
    DDRD = 0xFF; //set Port D as output
    DDRC |= (1<<RS)|(1<<RW)|(1<<E);  //set port C pin 0, 1, 2 as output pins
    
    lcd_init();
	
	unsigned char String[5];
	
    while (1)
    {
		//Start ADC conversion
		ADCSRA |=(1<<ADSC);
		
		itoa(ADC_value,String,10);
	    lcd_cmd(0x80);
		lcd_string("ADC Value");
		lcd_cmd(0xC0);
		lcd_string(String);
		_delay_ms(100);
		
	    
    }
	return 0;
}

ISR(ADC_vect){
	ADC_value = (ADCH<<8)+ADCL;  //ADC register contains 10-Bit ADC value
}