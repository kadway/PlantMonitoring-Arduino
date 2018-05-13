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
#include "chips/rtc_ds3231/rtc.h"
#include "atmega328p/adc.h"
#include "atmega328p/uart.h"

//uint8_t ch = 0;
uint8_t adcval;
uint8_t temp;
struct tm* tm;
int main(void){
	char buf[32];
	platformInit();

	while (1){
			adc_read_int(0);
			_delay_ms(1000);
#ifdef debug
			sprintf(buf, " New loop and Light is: %d.%d \n", adcval);
			uartSendString(buf);
			cleanBuf(buf);
			tm = rtc_get_time();
			sprintf(buf, " Time is %d:%d:%d \n", tm->hour, tm->min, tm->sec);
			uartSendString(buf);
			cleanBuf(buf);
#endif
			if(adcval < 45){
			   ledsON(G3, 2); 	   //leds on (id=2 for port B)
#ifdef debug
			   sprintf(buf, " Light: %d.%d\n Led ON and Going to sleep now \n", adcval);
			   uartSendString(buf);
			   cleanBuf(buf);
			   _delay_ms(1000);
#endif
			   goToSleep();
				}
			else{
					ledsOFF(G3, 2); 	   //leds on (id=2 for port B)
#ifdef debug
				    sprintf(buf, " Light: %d.%d\n Led OFF and Going to sleep now \n", adcval);
					uartSendString(buf);
					cleanBuf(buf);
					_delay_ms(1000);
#endif
					goToSleep();
				}
			_delay_ms(1000);
			//uartSendString(buf);
			//cleanBuf(buf);
			//readTemperatureRTC();
			//_delay_ms(1);
			//sprintf(buf, "Temp: %d.%d\n", temp);
			//uartSendString(buf);
			//cleanBuf(buf);
			//goToSleep();
	}
	return 0; // never reached
}

ISR(ADC_vect)
{
	adcval=ADC; //get conversion value
	//ch= ADMUX & 0x07; //get MUX id to know from which sensor data belongs to
	ADCSRA &= 0xEF; //clean interrupt bit
}

ISR(INT0_vect)
{

}

//ISR(TIMER1_OVF_vect) /* timer 1 interrupt service routine */
//{
//   timer_stop();
//}
