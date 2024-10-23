/*
 * ATmega16_I2C_24AA256_EEPROM.c
 *
 * Created: 04-09-2024 20:59:56
 * Author : Ezhil Bharathi
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "LCD_8-bitmode.h"
#define F_CPU 8000000UL


//I2c Function declarations
void I2C_init();
uint8_t I2C_start(uint8_t write_address);
uint8_t I2C_repeated_start(uint8_t read_address);
void I2C_stop();
uint8_t I2C_write(uint8_t data);
uint8_t I2C_read_ACK();
uint8_t I2C_read_NACK();

uint8_t decimal_to_BCD(uint8_t value);
void hex_to_ascii(uint8_t value);

//I2C Function Definitions
void I2C_init(){    /* Initialize I2C*/
	TWSR = 0;
	TWBR = ((F_CPU/100000)-16)/(2*pow(4,TWSR&(1<<TWPS1)|(1<<TWPS0)));  /*Get bit rate register value by formula*/
}
uint8_t I2C_start(uint8_t write_address){
	TWCR |= (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
	while(!(TWCR&(1<<TWINT)));
	TWDR = write_address;
	TWCR |= (1<<TWEN)|(1<<TWINT);
	while(!(TWCR&(1<<TWINT)));
}
uint8_t I2C_repeated_start(uint8_t read_address){
	TWCR |= (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
	while(!(TWCR&(1<<TWINT)));
	TWDR = read_address;
	TWCR |= (1<<TWEN)|(1<<TWINT);
	while(!(TWCR&(1<<TWINT)));
}
void I2C_stop(){
	TWCR |=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
}
uint8_t I2C_write(uint8_t data){
	TWDR = decimal_to_BCD(data);
	TWCR |= (1<<TWEN)|(1<<TWINT);
	while(!(TWCR&(1<<TWINT)));
}
uint8_t I2C_read_ACK(){
	TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);
	while(!(TWCR&(1<<TWINT)));
	return TWDR;
}
uint8_t I2C_read_NACK(){
	TWCR = (1<<TWEN)|(1<<TWINT);
	while(!(TWCR&(1<<TWINT)));
	return TWDR;
}


void hex_to_ascii(uint8_t value){
	uint8_t bcd;
	bcd=value;
	bcd = bcd & 0xF0;
	bcd = bcd>>4;
	bcd = bcd|0x30;
	lcd_data(bcd);
	bcd=value;
	bcd = bcd & 0x0F;
	bcd = bcd|0x30;
	lcd_data(bcd);
}
uint8_t decimal_to_BCD(uint8_t value){
	uint8_t msb,lsb,hex;
	msb=value/10;
	lsb=value%10;
	hex = ((msb<<4)+lsb);
	return hex;
}


uint8_t data;

int main(void)
{
    sei();
	DDRA = 0xFF;   //PORTA as output
	DDRB |= (1<<0)|(1<<1)|(1<<2);
	DDRC = 0x00;
	PORTC = 0xFF;
	
	lcd_init();
	lcd_cmd(0x80);
	lcd_string("EEPROM VALUE:");
	
	I2C_init();
	// I2C write data 98 on address 0x3245
	I2C_start(0xA0);
	I2C_write(32);
	I2C_write(45);
	I2C_write(98);
	I2C_stop();
	_delay_ms(1000);
	// I2C read data from address 0x3245
	I2C_start(0xA0);
	I2C_write(32);
	I2C_write(45);
	I2C_repeated_start(0xA1);
	data = I2C_read_NACK();
	I2C_stop();
	
	
	lcd_cmd(0xC0);
	hex_to_ascii(data);
	
	while (1) 
    {
    }
	return 0;
}

