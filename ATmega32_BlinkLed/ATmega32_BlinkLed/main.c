/*
 * ATmega32_BlinkLed.c
 *
 * Created: 17-08-2024 17:22:44
 * Author : Ezhil Bharathi
 */ 

//#include <avr/io.h>
#include<stdint.h>


int main(void)
{
	volatile uint8_t *DDRA = (volatile uint8_t *)0x1A;
	*DDRA |=(1<<0);
	volatile uint8_t *PORTA = (volatile uint8_t *)0x1B;
    /* Replace with your application code */
	*PORTA &=~(1<<0);
	volatile uint32_t i;
    while (1) 
    {
		*PORTA ^=(1<<0);
		for(i=0;i<=100000;i++);
    }
}

