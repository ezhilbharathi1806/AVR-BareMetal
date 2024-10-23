#ifndef LCD_8-bitmode
#define LCD_8-bitmode

#include <avr/io.h>
#include <util/delay.h>
#define RS 0
#define RW 1
#define E 2

void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_string(unsigned char *);
void lcd_init();

void lcd_cmd(unsigned char c){
	PORTA = c;
	PORTB &=~(1<<RS); //RS =0
	PORTB &=~(1<<RW); // RW = 0
	PORTB |=(1<<E);   // E = 1
	_delay_ms(10);
	PORTB &=~(1<<E);  //E = 0
}

void lcd_data(unsigned char d){
	PORTA = d;
	PORTB |=(1<<RS); //RS =1
	PORTB &=~(1<<RW); // RW = 0
	PORTB |=(1<<E);   // E = 1
	_delay_ms(10);
	PORTB &=~(1<<E);  //E = 0
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