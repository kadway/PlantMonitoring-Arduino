/*
 * platform.c
 *
 *  Created on: Oct 3, 2017
 *      Author: johny
 */

#include <stdio.h>
#include <avr/io.h>

#include "platform.h"
#include "leds.h"

void initLeds(void)
{
DDRD |= 0xFF; // complete PORTD as output for leds (8 leds)
DDRB |= WHITE_S3; //led is on PORTB or IO8 of the board
ledsOFF(0XFF, 0); // all leds off
ledsOFF(WHITE_S3, 2); // last led in PORTB off
}

void humidityevaluate(waterSensor sensor){
	switch (sensor.id){
	case 0:{
			if (sensor.val<=340){
				ledsON(GREEN_S1, sensor.id);
				ledsOFF(YELLOW_S1|WHITE_S1, sensor.id);
				}
			else if (sensor.val>340 && sensor.val <680){
				ledsON(YELLOW_S1,sensor.id);
				ledsOFF(GREEN_S1|WHITE_S1, sensor.id);
				}
			else if (sensor.val>=680){
				ledsON(WHITE_S1, sensor.id);
				ledsOFF(GREEN_S1|YELLOW_S1, sensor.id);
			}
			break;
		}
	case 1:{
			if (sensor.val<=340){
				ledsON(GREEN_S2, sensor.id);
				ledsOFF(YELLOW_S2|WHITE_S2, sensor.id);
			}
			else if (sensor.val>340 && sensor.val <680){
				ledsON(YELLOW_S2,sensor.id);
				ledsOFF(GREEN_S2|WHITE_S2, sensor.id);
			}
			else if (sensor.val>=680){
				ledsON(WHITE_S2, sensor.id);
				ledsOFF(GREEN_S2|YELLOW_S2, sensor.id);
			}
			break;
	}
	case 2:{
			if (sensor.val<=340){
				ledsON(GREEN_S3, sensor.id);
				ledsOFF(YELLOW_S3, sensor.id);
				ledsOFF(WHITE_S3, sensor.id);
				}
			else if (sensor.val>340 && sensor.val <680){
				ledsON(YELLOW_S3,sensor.id);
				ledsOFF(GREEN_S3, sensor.id);
				ledsOFF(WHITE_S3, sensor.id);
				}
			else if (sensor.val>=680){
				ledsON(WHITE_S3, sensor.id);
				ledsOFF(GREEN_S3|YELLOW_S3, sensor.id);
				}
			break;
	}
	default: break;
	}
	return;
}
