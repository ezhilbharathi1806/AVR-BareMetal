/*
 * ATmega2560_BlinkLed.c
 *
 * Created: 19-08-2024 17:28:28
 * Author : Ezhil Bharathi
 */ 

//#include <avr/io.h>


int main(void)
{
	volatile char *DDRF = (volatile char *)0x30;
	*DDRF |=(1<<0);
	volatile char *PORTA = (volatile char *)0x31;
	volatile long i;
    /* Replace with your application code */
    while (1) {
		*PORTA |=(1<<0);
		for(i=0; i<=10000; i++);
		*PORTA &=~(1<<0);
		for(i=0; i<=10000; i++);
    }
}

