/*
 * ATmega16_ADC_10Bit_Potentiometer.c
 *
 * Created: 29-08-2024 19:17:24
 * Author : Ezhil Bharathi
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>


int main(void)
{
    /*============== ADC ==============*/
	
	//Enable the Global Interrupt Enable Bit
	sei();
	
	//Set reference to NO AVCC and input to ADC0
	ADMUX = 0x00;
	
	//Enable ADC
	ADCSRA |= (1<<ADEN)|(1<<ADATE);
	
	//Set frequency of ADC Conversion
	ADCSRA |=(1<<ADPS2);
	ADCSRA &= (~(1<<ADPS1))& (~(1<<ADPS0));
	
	//Start ADC conversion
	ADCSRA |=(1<<ADSC);
	
	/*============== PWM ==============*/
	//Set mode of timer
	TCCR1A |= (1<<WGM10)|(1<<WGM11);
	TCCR1B |=(1<<WGM12);
	TCCR1B &= ~(1<<WGM13);   // FAst PWM 10-Bit Mode
	
	//Set PWM Mode
	TCCR1A &= ~(1<<COM1A0);
	TCCR1A |= (1<<COM1A1);   //PWM in Non-Inverting Mode
	
	//Set Prescalar for the Timer
	//16MHz/64 = 250KHz
	TCCR1B |= (1<<CS10)|(1<<CS11);
	TCCR1B &= ~(1<<CS12); //prescalar = 64
	
	//Configuring OC1A pin As output pin
	DDRD |= (1<<DDD5);
	
	//Set Duty cycle
	//Since 10-Bit PWM )to 1023 for Setting duty cycle of PWM
	//OCR1A = 512;  // 50% Duty cycle
	
    while (1) 
    {
    }
}

ISR(ADC_vect){
	OCR1A=ADC;  //ADC register contains 10-Bit ADC value
}

