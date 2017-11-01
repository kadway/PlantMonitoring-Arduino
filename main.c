/*
 * main.c
 *
 *  Created on: Oct 3, 2017
 *      Author: johny
 */

//#ifndef __AVR_ATmega328P__
//#define __AVR_ATmega328P__
//#endif

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "platform.h"
#include "usart.h"
#include "adc.h"
#include "leds.h"
#include "debug.h"
#include "timer.h"

waterSensor sensor;

uint8_t new_val = 0;
uint8_t ch;
int main(void){
	uint8_t i, j;
    initLeds();
    initADC();
    USART_Init(MYUBRR);
    sei(); //turn on interrupts
    i=0;
	while (1){
    	if(new_val){
    		new_val=0;
    		serial_send(sensor);
    	}
    	if((~(ADCSRA & (1<<ADSC)))&&(~new_val)){
    		if(i==NSENSORS){
    			i=0;
    			for(j=0; j<60;j++)
    				_delay_ms(5000);
    		}
    		adc_read_int(i);
    		i++;
    	}
    	//set_sleep_mode(SLEEP_MODE_IDLE);
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

ISR(TIMER1_OVF_vect) /* timer 1 interrupt service routine */
{
   timer_stop();
}
