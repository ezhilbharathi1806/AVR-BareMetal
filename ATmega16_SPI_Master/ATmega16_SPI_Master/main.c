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
	SPDR =0xFF;
	while(!(SPSR&(1<<SPIF)));
	return SPDR;
}
int main(void)
{
    /* Replace with your application code */
	DDRB |=(1<<DDB4)|(1<<DDB5)|(1<<DDB7);  // PB4, PB5, PB7 as output
	DDRB &= ~(1<<DDB6);    //PB5 as input
	
	SPCR |=(1<<SPE)|(1<<MSTR)|(1<<SPR0);
	SPSR &= ~(1<<SPI2X);
	
    while (1) 
    {
		PORTB &=~(1<<PB4);
		spi_write('a');
		PORTB |=(1<<PB4);
		_delay_ms(1000);
		
		PORTB &=~(1<<PB4);
		spi_write('b');
		PORTB |=(1<<PB4);
		_delay_ms(1000);
    }
}

