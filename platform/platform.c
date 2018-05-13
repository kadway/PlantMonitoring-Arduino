/*
 * platform.c
 *
 *  Created on: Oct 3, 2017
 *      Author: johny
 */

#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "platform.h"
#include "leds.h"

#include "../chips/rtc_ds3231/rtc.h"
#include "../atmega328p/uart.h"
#include "../atmega328p/adc.h"
#include "../atmega328p/twi.h"
extern struct tm time;

void platformInit(void){
	initLeds();
	initADC();
	uartInit();
#ifdef debug
	uartSendString(" Init Uart done.. \n");
#endif
	wakeInterruptInit(); //arduino side
	twi_init_master();
#ifdef debug
	uartSendString(" Init Two-Wire-Interface done.. \n");
#endif
	rtc_init(); //init DS3231
	rtc_SQW_enable(0); //disable SQW
	rtc_alarm_enable(1); //enable alarm
#ifdef debug
		uartSendString(" RTC init done..\n");
#endif
#ifdef SET_TIME
	setTimeRTC();
#endif
}


void initLeds(void)
{
	//DDRD |= G1; //led 1
	DDRB |= G3; 		   //set as output
	ledsON(G3, 2); 	   //leds on (id=2 for port B)
	//ledsOFF(LEDS_PB, 2);	   //leds off
}

void wakeInterruptInit(void){
	DDRD &= ~(1 << DDD2);     // Clear the PD2 pin
	// PD2 (PCINT0 pin) is now an input
	PORTD |= (1 << PORTD2);    // turn On the Pull-up
	EICRA |=  (1<<ISC01);	// Trigger INT0 on falling edge
	EIMSK |= (1 << INT0);     // Turns on INT0
}

void setTimeRTC(){
#ifdef debug
	char buf[32];
#endif
	//update these with actual time to be set to RTC
	time.sec=00;      // 0 to 59
	time.min=30;      // 0 to 59
	time.hour=14;     // 0 to 23
	time.mday=12;     // 1 to 31
	time.mon=5;      // 1 to 12
	time.year=18;     // year-99
	time.wday=4;     // 1-7
	// 12-hour clock data
	time.am=0; // true for AM, false for PM

	rtc_set_time(&time);

#ifdef debug
	sprintf(buf, " The time is now %d:%d:%d\n", time.hour, time.min, time.sec);
	uartSendString(buf);
	uartSendString(" \n");
#endif
}

void setWakeAlarm(){
#ifdef debug
	char buf[32];
#endif
	//get actual time
	rtc_get_time();

	//set the alarm for the next minute based on the actual time
	time.min = time.min+1;
	if(time.min>59){
		time.min=1;
		time.hour=time.hour+1;
		if(time.hour>23){
			time.hour=0;
		}
	}

	//set the alarm
	rtc_set_alarm_s(time.hour, time.min, time.sec);


#ifdef debug
	//check the new alarm
	rtc_get_alarm_s(&(time.hour), &(time.min), &(time.sec));
	sprintf(buf, "Alarm is set to %d:%d:%d \n", time.hour, time.min, time.sec);
	uartSendString(buf);
	cleanBuf(buf);
	_delay_ms(1000);
	rtc_get_time();
	sprintf(buf, "And time is %d:%d:%d \n", time.hour, time.min, time.sec);
	uartSendString(buf);
	cleanBuf(buf);
#endif
}

void readTemperatureRTC(){
	char buf[32];
	int8_t integer;
	uint8_t fractional;
	rtc_force_temp_conversion(1);
	ds3231_get_temp_int(&integer, &fractional);
	sprintf(buf, "Temp: %d.%d\n", integer, fractional);
	uartSendString(buf);
};

void goToSleep(){
	setWakeAlarm();
#ifdef debug

	uartSendString(" Going to sleep...\n");
	_delay_ms(1000);
#endif
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	cli();
	sleep_enable();
	sei();
	sleep_cpu();
	sleep_disable();
#ifdef debug
	_delay_ms(1000);
	uartSendString(" \nWake up!\n");
#endif
}

void cleanBuf(char *buf){
	sprintf(buf,"                                ");
}
/*void serial_send(waterSensor sensor){
	char start[5]={"start"};
	//char id[2]= {"  "};
	//char value[4] = {"    "};
	//itoa(sensor.id, id, 10);
	//itoa(sensor.val, value, 10);
	//USART_Transmit(0x83);
	serial_poll_send(start, sizeof(start));
	//serial_poll_send(id, sizeof(id));
	//serial_poll_send(value, sizeof(value));
	serial_poll_send(&sensor.id, sizeof(uint8_t));
	serial_poll_send(&sensor.val, sizeof(uint16_t));
}*/
