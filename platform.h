/*
 * platform.h
 *
 *  Created on: Oct 3, 2017
 *      Author: johny
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

// everything in PORTD except WHITE_S3 which is PORTB

#define YELLOW_S1 0X01 // LED is on Pin 1
#define GREEN_S1 0X02 // LED is on Pin 2
#define WHITE_S1 0X04 // LED is on Pin 3

#define YELLOW_S2 0X08 // LED is on Pin 4
#define GREEN_S2 0X10 // LED is on Pin 5
#define WHITE_S2 0X20 // LED is on Pin 6

#define YELLOW_S3 0X40 // LED is on Pin 7
#define GREEN_S3 0X80 // LED is on Pin 8
#define WHITE_S3 0X01 // LED is on Pin 9

typedef struct waterSensors{
	uint16_t val;
	uint8_t id;
}waterSensor;

void initLeds(void);
void serial_init(void);
void humidityevaluate(waterSensor sensor);

#endif /* PLATFORM_H_ */


