#ifndef LCD16x2_4Bit_h
#define  LCD16x2_4Bit_h

#include <avr/io.h>
#include <util/delay.h>
#define RS 0
#define RW 1
#define E 2
#define data_direction_register_D DDRD
#define data_pins PORTD
#define control_pins PORTD

void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_string(unsigned char *);
void lcd_print_xy(uint8_t row,uint8_t pos, char *str);
void lcd_init();

void lcd_cmd(unsigned char c){
	data_pins = (c&0xF0);   //upper nibble
	control_pins &=~(1<<RS); //RS =0
	control_pins &=~(1<<RW); // RW = 0
	control_pins |=(1<<E);   // E = 1
	_delay_ms(1);
	control_pins &=~(1<<E);  //E = 0
	
	data_pins = ((c<<4)&0xF0);   //lower nibble
	control_pins &=~(1<<RS); //RS =0
	control_pins &=~(1<<RW); // RW = 0
	control_pins |=(1<<E);   // E = 1
	_delay_ms(1);
	control_pins &=~(1<<E);  //E = 0
}

void lcd_data(unsigned char d){
	data_pins = (d&0xF0);   //upper nibble
	control_pins |=(1<<RS); //RS =1
	control_pins &=~(1<<RW); // RW = 0
	control_pins |=(1<<E);   // E = 1
	_delay_ms(1);
	control_pins &=~(1<<E);  //E = 0
	
	data_pins = ((d<<4)&0xF0);   //lower nibble
	control_pins |=(1<<RS); //RS =1
	control_pins &=~(1<<RW); // RW = 0
	control_pins |=(1<<E);   // E = 1
	_delay_ms(1);
	control_pins &=~(1<<E);  //E = 0
}

void lcd_string(unsigned char *s){
	while(*s!=0){
		lcd_data(*s);
		s++;
	}
}

void lcd_print_xy(uint8_t row,uint8_t pos, char *str){	/* Send string to LCD with xy position */
	if (row == 0 && pos<16)
	lcd_cmd((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	lcd_cmd((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	lcd_string(str);		/* Call LCD string function */
}

void lcd_init(){
	data_direction_register_D = 0xF0; //set Port D as output
	data_direction_register_D |= (1<<RS)|(1<<RW)|(1<<E);  //set port C pin 0, 1, 2 as output pins
	
	lcd_cmd(0x33);
	lcd_cmd(0x32);
	lcd_cmd(0x28);
	lcd_cmd(0x06);
	lcd_cmd(0x0C);
	lcd_cmd(0x01);
}

#endif