/*
 * usart.h
 *
 *  Created on: Oct 3, 2017
 *      Author: johny
 */

#ifndef USART_H_
#define USART_H_
#include <stdlib.h>

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init( unsigned int ubrr);
unsigned char serial_poll_recv(unsigned char *a_data, unsigned int a_size);
unsigned int serial_poll_send(void *data, unsigned int a_size);
char *ftoa(char *a, double f, int precision);

#endif /* USART_H_ */
