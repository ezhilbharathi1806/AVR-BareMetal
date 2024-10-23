/*
 * ATmega16_ADC_UART_simple.c
 *
 * Created: 01-09-2024 20:38:43
 * Author : Ezhil Bharathi
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define F_CPU 8000000UL

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

//ADC Function declaration
void ADC_init(void);
uint16_t ADC_read(void);

//UART Function declarations
void UART_init(void);
void UART_TX(uint8_t);
uint8_t UART_RX(void);
void UART_SendString(uint8_t*);

/*======================ADC Functions======================*/
void ADC_init(){
	DDRA &=~(1<<0);  // make PA0 = 0 pin as input
	ADMUX = 0x40;   /*Vref: Avcc, ADC channel: 0, ADLAR=0 right justified*/
	ADCSRA = 0x87;   /* Enable ADC, fr/128  */
}

uint16_t ADC_read(){
	ADMUX &= 0xF0;
	ADCSRA |=(1<<ADSC);
	uint16_t val;
	while((ADCSRA&(1<<ADIF))==0);	/* Monitor end of conversion interrupt */
	_delay_us(10);
	val = (ADCH<<8)+ADCL;
	return val;
}
/*======================UART Functions======================*/
void UART_init(){
	UCSRB |= (1 << RXEN) | (1 << TXEN);/* Turn on transmission and reception */
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);/* Use 8-bit character sizes */
	UBRRL = BAUD_PRESCALE;		/* Load lower 8-bits of the baud rate value */
	UBRRH = (BAUD_PRESCALE >> 8);	/* Load upper 8-bits*/
}
void UART_TX(uint8_t ch){
	while (! (UCSRA & (1<<UDRE)));	/* Wait for empty transmit buffer*/
	UDR = ch ;
}
uint8_t UART_RX(){
	while ((UCSRA & (1 << RXC)) == 0);/* Wait till data is received */
	return(UDR);			/* Return the byte*/
}
void UART_SendString(uint8_t *s){
	while(*s !='\0'){
		UART_TX(*s);
		s++;
	}
}


int main(void)
{
    uint8_t string[5];
    uint16_t adc_value;
	
	ADC_init();
	UART_init();
	
	UART_SendString("\n\tADC Value");
    while (1) 
    {
		adc_value = ADC_read();
		itoa(adc_value,string,10);
		UART_SendString(string);
		UART_SendString("\r");
		UART_SendString("\n");
		_delay_ms(1000);
    }
	return 0;
}

