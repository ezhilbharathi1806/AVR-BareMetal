/*
 * ATmega16_SPI_Master_LCD.c
 *
 * Created: 08-09-2024 12:25:54
 * Author : Ezhil Bharathi
 */ 

#include <avr/io.h>

#include "LCD_8-bitmode.h"
#define  F_CPU 8000000UL

void spi_write(unsigned char data){
	SPDR = data;
	while(!(SPSR&(1<<SPIF)));
}

unsigned char spi_read(){
	SPDR =0xFF;
	while(!(SPSR&(1<<SPIF)));
	return SPDR;

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

