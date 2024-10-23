/*
 * ATmega16_UART_RX_Simple.c
 *
 * Created: 31-08-2024 18:43:31
 * Author : Ezhil Bharathi
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

volatile unsigned char data;

void UART_init(long USART_BAUDRATE)
{
	UCSRB |= (1 << RXEN) | (1 << RXCIE);   /* Turn on the transmission and reception */
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); /* Use 8-bit character sizes */

	UBRRL = BAUD_PRESCALE; 					/* Load lower 8-bits of the baud rate value */
	UBRRH = (BAUD_PRESCALE >> 8);			/*Load upper 8-bits*/
}

ISR(USART_RXC_vect)
{
	data=UDR;
}

int main()
{
	UART_init(9600);
	sei();
	DDRB=0xFF;
	
	while(1)
	{
		if(data =='a'){
			PORTB |=(1<<0);
		}
		if(data =='b'){
			PORTB &=(~(1<<0));
		}
	}
}
