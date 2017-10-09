/*
 * debug.c
 *
 *  Created on: Oct 7, 2017
 *      Author: johny
 */
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include "usart.h"

char text[]={"\nADC="};
char unit[]={"V\n"};
char buffer[5];

void adc_uart_debug(uint16_t sensor){
	//serial_poll_send(text, sizeof(text));
	//itoa(sensor, buffer, 10);
	//serial_poll_send(buffer, sizeof(buffer));
	itoa(sensor, buffer, 10);
	serial_poll_send(text, sizeof(text));
	serial_poll_send(buffer, sizeof(buffer));
	serial_poll_send(unit, sizeof(unit));
}
