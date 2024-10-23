/*
 * ATmega16_Clock_I2C_RTC_LCD.c
 *
 * Created: 13-09-2024 23:18:08
 * Author : Ezhil Bharathi
 */ 


#include <avr/io.h>
#include <stdio.h>
#include <string.h>

#include "LCD16x2_4Bit_h.h"
#include "RTC_H_file.h"

#define F_CPU 8000000UL

int main(void)
{
	rtc_t rtc;
	
	uint8_t buffer[20];
	
	I2C_Init();			/* Initialize I2C */
	lcd_init();			/* Initialize LCD16x2 */
	rtc_init();
	
	rtc.hour = 0x10; //  10:40:20 am
	rtc.min =  0x40;
	rtc.sec =  0x00;

	rtc.date = 0x01; //1st Jan 2016
	rtc.month = 0x01;
	rtc.year = 0x16;
	rtc.weekday = 5; // Friday: 5th day of week considering monday as first day.
	
	rtc_write_setTimeDate(&rtc);
	

    while(1)
    {
		rtc_readTimeData(&rtc);
		
		sprintf(buffer, "time:%2x:%2x:%2x  \nDate:%2x/%2x/%2x",(uint8_t)rtc.hour,(uint8_t)rtc.min,(uint8_t)rtc.sec);
		lcd_print_xy(0,0,buffer);
		
		sprintf(buffer, "Date:%02x-%02x-%02x",(uint8_t)rtc.date,(uint8_t)rtc.month,(uint16_t)rtc.year);
		lcd_print_xy(1,0,buffer);
    }
}

