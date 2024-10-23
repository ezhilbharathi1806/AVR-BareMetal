/*
 * ATmega16_Fast_PWM_10BitMode.c
 *
 * Created: 27-08-2024 22:02:34
 * Author : Ezhil Bharathi
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
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
		int i;
		for(i=0;i<1023;i++){
			OCR1A = i;
			_delay_ms(2);
		}
		_delay_ms(1000);
		for(i=1023;i<0;i--){
			OCR1A = i;
			_delay_ms(2);
		}
		_delay_ms(1000);
    }
}

