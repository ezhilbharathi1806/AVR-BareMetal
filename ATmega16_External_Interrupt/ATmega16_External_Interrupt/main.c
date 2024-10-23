/*
 * ATmega16_External_Interrupt.c
 *
 * Created: 23-08-2024 20:01:26
 * Author : Ezhil Bharathi
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
    /* Replace with your application code */
	DDRB |=(1<<DDB0); //Set PB0 as 1 (output pin)
	sei();  // set I =1 in Sreg register
	GICR |= (1<<INT0)|(1<<INT1);
	MCUCR |= (1<<ISC10)|(1<<ISC11)|(1<<ISC00)|(1<<ISC01);
    while (1) 
    {
    }

}

ISR(INT0_vect){
	PORTB |=(1<<PB0);
}
ISR(INT1_vect){
	PORTB &= ~(1<<PB0);
}

