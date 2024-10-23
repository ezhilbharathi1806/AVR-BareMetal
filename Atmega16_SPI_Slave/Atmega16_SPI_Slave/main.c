/*
 * ATmega16_SPI_Master.c
 *
 * Created: 07-09-2024 21:27:14
 * Author : Ezhil Bharathi
 */ 

// SPI Master
#include <avr/io.h>
#include <util/delay.h>
#define  F_CPU 8000000UL

void spi_write(unsigned char data){
	SPDR = data;
	while(!(SPSR&(1<<SPIF)));
}

unsigned char spi_read(){
	while(!(SPSR&(1<<SPIF)));
	return SPDR;
}

unsigned char data;

int main(void)
{
    /* Replace with your application code */
	DDRB &=(~(1<<DDB4))&(~(1<<DDB5))&(~(1<<DDB7));  // PB4, PB5, PB7 as Input
	DDRB |=(1<<DDB6);    //PB5 as Output
	
	//led
	DDRC |=(1<<DDC0);
	PORTC &=~(1<<0);
	
	//SPI
	SPCR |=(1<<SPE);
	SPCR &=~(1<<MSTR);
	
	
    while (1) 
    {
		data = spi_read();
		if(data == 'a'){
			PORTC|=(1<<0);
		}
		if(data == 'b'){
			PORTC&=~(1<<0);
		}
    }
}

