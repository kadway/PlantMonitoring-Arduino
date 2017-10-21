/*
 * platform.h
 *
 *  Created on: Oct 3, 2017
 *      Author: johny
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define NSENSORS 3
// PD0 & PD1 -> RX TX IO0 & IO1

#define G1 0X04 // LED is on PD2 IO 2
#define Y1 0X08 // LED is on PD3 IO 3
#define W1 0X10 // LED is on PD4 IO 4

#define G2 0X20 // LED is on PD5 IO 5
#define Y2 0X40 // LED is on PD6 IO 6
#define W2 0X80 // LED is on PD7 IO 7

#define G3 0X01 // LED is on PB0 IO 8
#define Y3 0X02 // LED is on PB1 IO 9
#define W3 0X04 // LED is on PB2 IO 10

#define LEDS_PD G1|Y1|W1|G2|Y2|W2
#define LEDS_PB G1|Y1|W1|G2|Y2|W2

typedef struct waterSensors{
	uint16_t val;
	uint8_t id;
}waterSensor;

void initLeds(void);
void serial_init(void);
void humidityevaluate(waterSensor sensor);
void serial_send(waterSensor sensor);

#endif /* PLATFORM_H_ */


