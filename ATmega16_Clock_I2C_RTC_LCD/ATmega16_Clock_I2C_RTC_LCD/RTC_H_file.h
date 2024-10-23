#ifndef RTC_H_file
#define RTC_H_file

#include "I2C_Master_H_file.h"

typedef struct{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t weekday;
	uint8_t date;
	uint8_t month;
	uint8_t year;
	} rtc_t;

#define DS3232_Device_Write_address	0xD0u	/* Define RTC DS1307 slave write address */
#define DS3232_Device_Read_address	0xD1u	/* Make LSB bit high of slave address for read */

#define  DS3232_SecondRegAddress 0x00
#define  DS3232_DateRegAddress 0x04
#define  DS3232_controlRegAddress 0x07

void rtc_init(void);
void rtc_write_setTimeDate(rtc_t *);
void rtc_readTimeData(rtc_t *);

void rtc_init(){
	I2C_Init();
	I2C_Start();
	
	I2C_Write(DS3232_Device_Write_address);
	I2C_Write(DS3232_controlRegAddress);
	
	I2C_Write(0x00);         // Write 0x00 to Control register to disable SQW-Out

	I2C_Stop();
}


void rtc_write_setTimeDate(rtc_t *rtc){
	I2C_Start();
	
	I2C_Write(DS3232_Device_Write_address); // connect to DS1307 by sending its ID on I2c Bus
	I2C_Write(DS3232_SecondRegAddress);  // Request sec RAM address at 00H
	
	I2C_Write(rtc->sec);
	I2C_Write(rtc->min);
	I2C_Write(rtc->hour);
	I2C_Write(rtc->weekday);
	I2C_Write(rtc->date);
	I2C_Write(rtc->month);
	I2C_Write(rtc->year);
	
	I2C_Stop();
}
void rtc_readTimeData(rtc_t *rtc){
	I2C_Start();
	
	I2C_Write(DS3232_Device_Write_address); // connect to DS1307 by sending its ID on I2c Bus
	I2C_Write(DS3232_SecondRegAddress);  // Request sec RAM address at 00H
	
	I2C_Stop();
	
	I2C_Start();
	I2C_Write(DS3232_Device_Read_address);
	
	rtc->sec=I2C_Read_Ack();
	rtc->min=I2C_Read_Ack();
	rtc->hour=I2C_Read_Ack();
	rtc->weekday=I2C_Read_Ack();
	rtc->date=I2C_Read_Ack();
	rtc->month=I2C_Read_Ack();
	rtc->year=I2C_Read_Nack();
	
	I2C_Stop();
	
	
}

#endif