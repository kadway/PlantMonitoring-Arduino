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

uint8_t new_val = 1;
uint8_t ch;
int main(void){
	uint8_t i, j, k;
    initLeds();
    initADC();
    USART_Init(MYUBRR);
    sei(); //turn on interrupts
    i=0;
   // j=0;
    k=0;
	while (1){
    	if(new_val){
    		new_val=0;
    		//humidityevaluate(sensor);
    		serial_send(sensor);
    		//for(j=0; j<; j++){
    	    	for(k=0; k<60; k++){
    	    		_delay_ms(1000);
     	   		//}
    		}
    	}
    	if(~(ADCSRA & (1<<ADSC))){
    		adc_read_int(i);
    		if(i==NSENSORS-1)
    			i=0;
    		else
    			i++;

    	}


    	//set_sleep_mode(SLEEP_MODE_IDLE);
	}
    return 0; // never reached
}

ISR(ADC_vect)
{
	sensor.val=ADC; //get conversion value
	sensor.id= ADMUX & 0x03; //get MUX id to know from which sensor data belongs to
	ADCSRA &= 0xEF; //clean interrupt bit
	new_val=1; //set flag to 1 indicating new value is available
}

ISR(TIMER1_OVF_vect) /* timer 1 interrupt service routine */
{
   timer_stop();
}
