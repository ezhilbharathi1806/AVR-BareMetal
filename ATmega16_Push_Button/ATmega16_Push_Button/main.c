/*
 * ATmega16_Push_Button.c
 *
 * Created: 21-08-2024 21:54:52
 * Author : Ezhil Bharathi
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	DDRA &=~(1<<0); //PA0 as input
	DDRA |=(1<<1); //PA1 as output
    while (1) 
    {
		if((PINA & 0x01) == 0x01){
			PORTA |=(1<<1);  //Set PA1 as "1"
		}
		else{
			PORTA &=~(1<<1);  // reset PA1 "0"
		}
    }
}

