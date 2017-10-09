/*
 * leds.c
 *
 *  Created on: Oct 5, 2017
 *      Author: johny
 */
#include "leds.h"
#include "platform.h"
//specific for PORTD
void ledsON(unsigned char LED, uint8_t id){
	 if((id==2) & (LED==WHITE_S3)) // id 2 = sensor 3
		 PORTB |= LED;
	 else
		 PORTD |= LED;
}
void ledsOFF(unsigned char LED, uint8_t id){
	 if((id==2) & (LED==WHITE_S3))
		 PORTB &= ~LED;
	 else
		 PORTD &= ~LED;
}

void ledsToggle(unsigned char LED, uint8_t id){
	 if((id==2) & (LED==WHITE_S3))
		 PORTB = PORTD^LED;
	 else
		 PORTD = PORTD^LED;
}
