/*
 * main.c
 *
 *  Created on: Oct 3, 2017
 *      Author: johny
 */


#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include "platform/platform.h"
#include "platform/leds.h"

#include "atmega328p/adc.h"
#include "atmega328p/uart.h"

waterSensor sensor;

uint8_t new_val = 0;
uint8_t ch;

int main(void){
	char buf[32];
	uint8_t next_val = 0;

	platformInit();

	while (1){
		if(new_val){
			sprintf(buf, "Sensor %d: %d \n", sensor.id, sensor.val);
			uartSendString(buf);
			cleanBuf(buf);
			new_val=0;
			next_val++;
		}
		if(~new_val && next_val < NSENSORS){
			//sprintf(buf, " ADC read sensor: %d.\n", next_val);
			//uartSendString(buf);
			//cleanBuf(buf);
			adc_read_int(next_val);
			_delay_ms(50);
		}
		else if(next_val==NSENSORS){
			readTemperatureRTC();
			_delay_ms(50);
			goToSleep();
			next_val=0;
		}
	}
	return 0; // never reached
}

ISR(ADC_vect)
{
	sensor.val=ADC; //get conversion value
	sensor.id= ADMUX & 0x07; //get MUX id to know from which sensor data belongs to
	ADCSRA &= 0xEF; //clean interrupt bit
	new_val=1; //set flag to 1 indicating new value is available
}

ISR(INT0_vect)
{

}

//ISR(TIMER1_OVF_vect) /* timer 1 interrupt service routine */
//{
//   timer_stop();
//}
