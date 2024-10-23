/*
 * ATmega16_7Seg.c
 *
 * Created: 20-08-2024 22:43:04
 * Author : Ezhil Bharathi
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	DDRC = 0xFF;
	unsigned char seg[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
    while (1) 
    {
		for(unsigned int i=0; i<10; i++){
			PORTC =seg[i];
			_delay_ms(1000);
		}
    }
}

