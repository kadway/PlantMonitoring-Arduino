/*
 * leds.c
 *
 *  Created on: Oct 5, 2017
 *      Author: johny
 */
#include "leds.h"
#include "platform.h"
#include <avr/io.h>

void ledsON(unsigned char LED, uint8_t id){
	 if(id==2) // id 2 = sensor 3
		 PORTB |= LED;
	 else
		 PORTD |= LED;
}
void ledsOFF(unsigned char LED, uint8_t id){
	 if(id==2)
		 PORTB &= ~LED;
	 else
		 PORTD &= ~LED;
}

void ledsToggle(unsigned char LED, uint8_t id){
	 if(id==2)
		 PORTB = PORTD^LED;
	 else
		 PORTD = PORTD^LED;
}
/*
 * Led abstraction to do...
 */
//void Leds(uint8_t action, uint8_t* port_in_addr, uint8_t* port_out_addr, uint8_t* port_dir_addr, uint8_t* port_sel_addr, uint8_t* pin){
//
//	#define PORTxIN *((volatile uint8_t*)port_in_addr)
//	#define PORTx *((volatile uint8_t*)port_out_addr)
//	#define PORTxDIR (*(volatile uint8_t*)port_dir_addr)
//	#define PORTxSEL (*(volatile uint8_t*)port_sel_addr)
//
//	switch (action){
//	case SET: { PORTx |= (0x01 << pin); break;}
//	case CLR: { PORTx &= ~(0x01 << pin); break;}
//	case TOGGLE:{ PORTx ^= (0x01 << pin); break;}
//default: break;
//}
