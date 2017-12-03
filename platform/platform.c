/*
 * platform.c
 *
 *  Created on: Oct 3, 2017
 *      Author: johny
 */

#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include "platform.h"
#include "leds.h"
#include "../atmega328p/uart.h"

void initLeds(void)
{
DDRD |= G1|Y1|W1|G2|Y2|W2; //leds for sensor 1 & 2
DDRB |= G3|Y3|W3; 		   //leds for sensor 3
ledsOFF(LEDS_PD, 1); 	   //leds off
ledsOFF(LEDS_PB, 2);	   //leds off
}

void humidityevaluate(waterSensor sensor){
	// still to adapt to new defines and LED abstraction...

//			if (sensor.val<=340){
//				if(sensor.id==2){
//					ledsON(G3, 2);
//					ledsOFF(Y3|W3, 2);
//				}
//				else{
//					ledsON()
//				}
//			else if (sensor.val>340 && sensor.val <680){
//				ledsON(YELLOW_S1,sensor.id);
//				ledsOFF(GREEN_S1|WHITE_S1, sensor.id);
//				}
//			else if (sensor.val>=680){
//				ledsON(WHITE_S1, sensor.id);
//				ledsOFF(GREEN_S1|YELLOW_S1, sensor.id);
//			}
	return;
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
