/*
 * main2.c
 *
 *  Created on: Oct 3, 2017
 *      Author: johny
 */

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "platform.h"
#include "usart.h"
#include "adc.h"
#include "leds.h"
#include "debug.h"

waterSensor sensor;
uint8_t i;
uint8_t new_val = 1;
uint8_t ch;

int main(void){

    initLeds();
    initADC();
   // USART_Init(MYUBRR);
    sei(); //turn on dem interrupts!
    i=0;
	while (1){
    	if(new_val){
    		new_val=0;
    		humidityevaluate(sensor);
    	}
    	if(~(ADCSRA & (1<<ADSC))){
    		adc_read_int(i);
    		if(i==2)
    			i=0;
    		else
    			i++;
    	}
    	_delay_ms(1000);
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
