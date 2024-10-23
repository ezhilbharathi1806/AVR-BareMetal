/*
 * ATmega16_TimerCTCInterrupt_1sec.c
 *
 * Created: 25-08-2024 09:21:01
 * Author : Ezhil Bharathi
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>


int main(void)
{
    //Enable the Global Interrupt Enable bit
	sei();
	
	//Enable the required Timer Interrupt
	TIMSK |= (1<<OCIE1A);
	
	//Set Mode for Timer
	TCCR1A &= (~(1<<WGM10)) & (~(1<<WGM11));
	TCCR1B &= ~(1<<WGM13);
	TCCR1B |= (1<<WGM12);  
	TCCR1A |=(1<<COM1A0);
	TCCR1A &= ~(1<<COM1A1);
		
	//Set the Prescalar for the Timer
	TCCR1B |= (1<<CS12) | (1<<CS10);
	TCCR1B &= ~(1<<CS11);  //1024
	
	//Start the Timer with Initial Value
	TCNT1 = 0;
	
	//Load the period for the timer to generate 1 second
	//16000000/1024 = 15625 hz
	//1/15625 = 64us for 1tick
	// For generating 1 second no of ticks required = 1/64us = 15625 ticks required
	OCR1A = 15625;
	
	//Configure port D 5th pin as Output Pin 
	DDRD |=(1<<5);
    while (1) 
    {
    }
}

ISR(TIMER1_COMPA_vect){
	PORTD ^=(1<<5);
	TCNT1 = 0;
	OCR1A = 15625;
}

