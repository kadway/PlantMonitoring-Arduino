/*
 * usart.c
 *
 *  Created on: Oct 3, 2017
 *      Author: johny
 */
#include <avr/io.h>
#include "usart.h"
#include <avr/power.h>

unsigned char serial_poll_recv(unsigned char *a_data, unsigned int a_size) {
	unsigned int cnt = a_size;

	while (a_size) {
		/* Wait for data to be received */
		while ( !(UCSR0A & (1<<RXC0)) );

		/* Get and return received data from buffer */
		*a_data = UDR0;
		a_data++;
		a_size--;
	}

	return cnt;
}


unsigned int serial_poll_send(void *data, unsigned int a_size) {
	unsigned int i = 0x00;
	while (i < a_size) {
		// wait until usart buffer is empty
		while ( bit_is_clear(UCSR0A, UDRE0) );

		// send the data
		UDR0 = ((unsigned char *)data)[i++];
	}

	return i;
}


void USART_Init( unsigned int ubrr){
power_usart0_enable();
/*Set baud rate */
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;
/*Enable receiver and transmitter */
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
/* Set frame format: 8data, 2stop bit */
UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit( unsigned char data ){
/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) );
/* Put data into buffer, sends the data */
UDR0 = data;
}


void serial_init(void) {

    power_usart0_enable();

    // configure ports double mode
    UCSR0A = _BV(U2X0);

    // configure the ports speed
    UBRR0H = 0x00;
    UBRR0L = 34;

    // asynchronous, 8N1 mode
    UCSR0C |= 0x06;

    // rx/tx enable
    UCSR0B |= _BV(RXEN0);
    UCSR0B |= _BV(TXEN0);
}

char *ftoa(char *a, double f, int precision)
{
 long p[] = {0,10,100,1000,10000,100000,1000000,10000000,100000000};

 char *ret = a;
 long heiltal = (long)f;
 itoa(heiltal, a, 10);
 while (*a != '\0') a++;
 *a++ = '.';
 long desimal = abs((long)((f - heiltal) * p[precision]));
 itoa(desimal, a, 10);
 return ret;
}



