#ifndef LCD16x2_8Bit
#define LCD16x2_8Bit

#include <util/delay.h>
#define RS 0
#define RW 1
#define E 2

void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_string(unsigned char *);
void lcd_init();

void lcd_cmd(unsigned char c){
	PORTD = c;
	PORTC &=~(1<<RS); //RS =0
	PORTC &=~(1<<RW); // RW = 0
	PORTC |=(1<<E);   // E = 1
	_delay_ms(10);
	PORTC &=~(1<<E);  //E = 0
}

void lcd_data(unsigned char d){
	PORTD = d;
	PORTC |=(1<<RS); //RS =1
	PORTC &=~(1<<RW); // RW = 0
	PORTC |=(1<<E);   // E = 1
	_delay_ms(10);
	PORTC &=~(1<<E);  //E = 0
}

void lcd_string(unsigned char *s){
	while(*s!=0){
		lcd_data(*s);
		s++;
	}
}

void lcd_init(){
	lcd_cmd(0x38);
	lcd_cmd(0x06);
	lcd_cmd(0x0C);
	lcd_cmd(0x01);
}

#endif
