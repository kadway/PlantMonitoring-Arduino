/*
 * adc.h
 *
 *  Created on: Oct 5, 2017
 *      Author: johny
 */

#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
uint16_t adc_read(uint8_t ch);
void adc_read_int(uint8_t ch);
void initADC(void);
#endif /* ADC_H_ */




//ADMUX = 0b01000000;
/*		 	bit 7 REFS1  = 0: x
			bit 6 REFS0  = 1: } A/D reference voltage = Vcc with external capacitor at AREF pin
			bit 5 ADLAR  = 0: leave 10-bit result right adjusted
			bit 4 -----  = 0:
			bit 3 MUX3   = 0: x
			bit 2 MUX2   = 0: x
			bit 1 MUX1   = 0: x
			bit 0 MUX0   = 0: } Channel selection 0000 = ADC0, 0001 = ADC1 ... 0111 = ADC7
*/

//ADCSRA = 0b10001111;
/*		 	bit 7 ADEN   = 1: enable the A/D converter
			bit 6 ADSC   = 0: 0 = stop conversion, 1 = start conversion
			bit 5 ADFR   = 0: do not run in free running mode
			bit 4 ADIF   = 0: interrupt flag bit
			bit 3 ADIE   = 1: enable A/D interrupt on complete
			bit 2 ADPS2  = 1: x
			bit 1 ADPS1  = 1: x
			bit 0 ADPS0  = 1: } A/D clock Prescaler = 128 (gives A/D clock of 125kHz using 16MHz system clock)
*/
