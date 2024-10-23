/*
 * ATmega2560_External Interrupt.c
 *
 * Created: 24-08-2024 21:50:00
 * Author : Ezhil Bharathi
 */ 

//#include <avr/io.h>
//#include <avr/interrupt.h>


int main(void)
{
    /* Replace with your application code */
	volatile char *_DDRF=(volatile char*)0x30;
	*_DDRF |=(1<<0);

	volatile char *_EIMSK = (volatile char *)0x3D;
	*_EIMSK |= 0x03; // set INT0, INT1 as 1
	
	volatile char *ECIRA = (volatile char *)0x69;
	*ECIRA |= 0x0F; //set ISC00, ISC01,ISC10,ISC11 as 1
	
	//volatile char *EIFR = (volatile char *)0x3C;
	//*EIFR |= 0x0F;

	volatile char *_SREG =(volatile char *)0x5F;
	*_SREG |=(1<<7);
    while (1) 
    {
    }
}

/*ISR(INT0_vect){
	volatile char *PortF =(volatile char *)0x31;
	*PortF |=(1<<0);
}
ISR(INT1_vect){
	volatile char *PortF =(volatile char *)0x31;
	*PortF &= ~(1<<0);
}*/

// Interrupt Service Routine for INT0
void __vector_1(void) __attribute__((signal, used));
void __vector_1(void) {
	volatile char *PortF =(volatile char *)0x31;
	*PortF |=(1<<0);
}

// Interrupt Service Routine for INT1
void __vector_2(void) __attribute__((signal, used));
void __vector_2(void) {
	volatile char *PortF =(volatile char *)0x31;
	*PortF &= ~(1<<0);
}
