/*
 * leds.h
 *
 *  Created on: Oct 5, 2017
 *      Author: johny
 */

#ifndef LEDS_H_
#define LEDS_H_
#include <avr/io.h>

void ledsON(unsigned char LED, uint8_t id);
void ledsOFF(unsigned char LED, uint8_t id);
void ledsToggle(unsigned char LED, uint8_t id);

#endif /* LEDS_H_ */
