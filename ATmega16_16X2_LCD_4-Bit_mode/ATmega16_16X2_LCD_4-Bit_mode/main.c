/*
 * ATmega16_16X2_LCD_4-Bit_mode.c
 *
 * Created: 21-08-2024 22:27:31
 * Author : Ezhil Bharathi
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define RS 0
#define RW 1
#define E 2
#define data_pins PORTD
#define control_pins PORTD

void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_string(unsigned char *);
void lcd_init();

void lcd_cmd(unsigned char c){
	data_pins = (c&0xF0);   //upper nibble 
	control_pins &=~(1<<RS); //RS =0
	control_pins &=~(1<<RW); // RW = 0
	control_pins |=(1<<E);   // E = 1
	_delay_ms(10);
	control_pins &=~(1<<E);  //E = 0
	
	data_pins = ((c<<4)&0xF0);   //lower nibble 
	control_pins &=~(1<<RS); //RS =0
	control_pins &=~(1<<RW); // RW = 0
	control_pins |=(1<<E);   // E = 1
	_delay_ms(10);
	control_pins &=~(1<<E);  //E = 0
}

void lcd_data(unsigned char d){
	data_pins = (d&0xF0);   //upper nibble 
	control_pins |=(1<<RS); //RS =1
	control_pins &=~(1<<RW); // RW = 0
	control_pins |=(1<<E);   // E = 1
	_delay_ms(10);
	control_pins &=~(1<<E);  //E = 0
	
	data_pins = ((d<<4)&0xF0);   //lower nibble
	control_pins |=(1<<RS); //RS =1
	control_pins &=~(1<<RW); // RW = 0
	control_pins |=(1<<E);   // E = 1
	_delay_ms(10);
	control_pins &=~(1<<E);  //E = 0
}

void lcd_string(unsigned char *s){
	while(*s!=0){
		lcd_data(*s);
		s++;
	}
}

void lcd_init(){
	
	lcd_cmd(0x33);
	lcd_cmd(0x32);
	lcd_cmd(0x28);
	lcd_cmd(0x06);
	lcd_cmd(0x0C);
	lcd_cmd(0x01);
}
int main(void)
{
    /* Replace with your application code */
	DDRD = 0xF0; //set Port D as output
	DDRD |= (1<<RS)|(1<<RW)|(1<<E);  //set port C pin 0, 1, 2 as output pins
	
	lcd_init();
    while (1) 
    {
		lcd_cmd(0x80);
		lcd_string("EZHIL BHARATHI");
		lcd_cmd(0xC0);
		lcd_string("Embedded Dev");
		_delay_ms(1000);
    }
	return 0;
}

