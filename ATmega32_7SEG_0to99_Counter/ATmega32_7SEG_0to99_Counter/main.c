/*
 * ATmega32_7SEG_0to99_Counter.c
 *
 * Created: 03-10-2024 18:59:18
 * Author : Ezhil Bharathi
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 1000000UL

#define SevenSeg_Data PORTA
#define SevenSeg_Digits PORTB
#define Digit_1 ~(0x01)
#define Digit_2 ~(0x02)

uint8_t Seg_code[]= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

int main(void)
{
	DDRA = 0xFF;  //port A as input
	DDRB |=(1<<0)|(1<<1); //PB0, PB1 as output
	DDRB &= ~((1<<2)|(1<<3));  //PB2, PB3 as input
	
	uint8_t num = 12;
	
	 
    /* Replace with your application code */
    while (1) 
    {
		//Digit -1
		uint8_t temp = num;
		temp/=10;
		temp = temp%10;
		SevenSeg_Digits =Digit_1;
		SevenSeg_Data = Seg_code[temp];
		_delay_ms(10);
		
		//digit - 2
		temp = num;
		temp = temp%10;
		SevenSeg_Digits =Digit_2;
		SevenSeg_Data = Seg_code[temp];
		_delay_ms(10);
		
		if(PINB & (1<<2) == (1<<2)){
			// increment
			if(num<=99)
			num++;
			_delay_ms(10);
		}
		if(PINB & (1<<3) == (1<<3)){
			// decrement
			if(num > 0)
			num--;
			_delay_ms(10);
		}
    }
}

