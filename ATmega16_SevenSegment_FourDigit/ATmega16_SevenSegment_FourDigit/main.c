/*
 * ATmega16_SevenSegment_FourDigit.c
 *
 * Created: 30-09-2024 15:30:11
 * Author : Ezhil Bharathi
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define F_CPU 1000000UL

#define Seven_Segment_Data PORTB
#define Seven_Segment_Digits PORTA
// since its Common Cathode we are using bitwise '~'
#define digit_1 ~(0x01)
#define digit_2 ~(0x02)
#define digit_3 ~(0x04)
#define digit_4 ~(0x08)

void display_FourDigit_number(uint32_t num);
void display_TwoDigit_number(uint32_t);

 uint8_t seg_code[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

int main(void)
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	
	//uint32_t num;
	
    while (1) 
    {
		display_FourDigit_number(1234);
		_delay_ms(10);
		
    }
	
}

void display_FourDigit_number(uint32_t num){
	for(uint8_t i=0; i<=100;i++){
		uint32_t temp;
		
		// extract digit-1
		temp = num;
		temp = (uint32_t)temp/1000;
		temp = temp%10;
		Seven_Segment_Digits = digit_1;
		Seven_Segment_Data = seg_code[temp];
		_delay_ms(1);
		
		// extract digit-2
		temp = num;
		temp = (uint32_t)temp/100;
		temp = temp%10;
		Seven_Segment_Digits = digit_2;
		Seven_Segment_Data = seg_code[temp];
		_delay_ms(1);
		
		// extract digit-3
		temp = num;
		temp = (uint32_t)temp/10;
		temp = temp%10;
		Seven_Segment_Digits = digit_3;
		Seven_Segment_Data = seg_code[temp];
		_delay_ms(1);
		
		// extract digit-4
		temp = num;
		//temp = temp/1000;
		temp = temp%10;
		Seven_Segment_Digits = digit_4;
		Seven_Segment_Data = seg_code[temp];
		_delay_ms(1);
	}
}