/*
 * ATmega16_Input_Capture_Mode.c
 *
 * Created: 25-08-2024 21:27:04
 * Author : Ezhil Bharathi
 */ 

#include <avr/io.h>
#include "LCD16x2_8Bit.h"
#include <avr/interrupt.h>
int main(void)
{
	//Enable Global Interrupt Enable I in SREG
	sei();
	
	//Set Mode of Timer
	TCCR1A &= (~(1<<WGM10)) & (~(1<<WGM11));
	TCCR1B &= (~(1<<WGM12)) & (`(1<<WGM13));
	
	//Set the PreScalar for the Timer
	TCCR1B |= (1<<CS12)|(1<<CS10);
	TCCR1B &= ~(1<<CS11);
	
	//Start the timer with Initial Value
	TCNT1=0;
	
	//Select the edge of capture
	TCCR1B |=(1<<ICES1);
    
	
	DDRD = 0xFF; //set Port D as output
	DDRC |= (1<<RS)|(1<<RW)|(1<<E);  //set port C pin 0, 1, 2 as output pins
	
	lcd_init();
	while (1)
	{
		lcd_cmd(0x80);
		lcd_string("EMBEDDED");
		lcd_cmd(0xC0);
		lcd_string("Systems");
		_delay_ms(1000);
	}
}

unsigned int capture;
ISR(TIMER1_CAPT_vect){
	capture = ICR1;
	
}