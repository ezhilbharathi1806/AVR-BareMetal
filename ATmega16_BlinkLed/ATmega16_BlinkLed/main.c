/*
 * ATmega16_BlinkLed.c
 *
 * Created: 18-08-2024 07:00:42
 * Author : Ezhil Bharathi
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	//volatile char *DDRA = (volatile char *)0x1A;
	DDRA |=(1<<0);  // set PA0 pin as output pin
	//volatile char *PORTA = (volatile char *)0x1B;
	//volatile long i;
    while (1) 
    {
		PORTA |=(1<<0);
		_delay_ms(1000);
		//for(i=0; i<=1000000; i++);
		PORTA &=~(1<<0);
		_delay_ms(1000);
		//for(i=0; i<=1000000; i++);
    }
}

