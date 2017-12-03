/*
 * timer.c
 *
 *  Created on: Oct 22, 2017
 *      Author: johny
 */
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

#define T1_MAX 0xFFFFUL
#define T1_PRESCALER 1024
#define T1_TICK_US (T1_PRESCALER/(F_CPU/1000000UL)) /* 64us @ 16MHz */
#define T1_MAX_US (T1_TICK_US * T1_MAX) /* ~4.2s @ 16MHz */

void timer_stop(void){
    TCCR1B = ~(_BV(CS10)|_BV(CS11)|_BV(CS12)); /* stop timer clock */
    TIMSK1 = ~_BV(TOIE1); /* disable interrupt */
    TIFR1 |= _BV(TOV1); /* clear interrupt flag */
}

void timer_init(void){
    /* normal mode */
    TCCR1A = ~(_BV(WGM10)|_BV(WGM11));
    TCCR1B = ~(_BV(WGM13)|_BV(WGM12));
    timer_stop();
}

void timer_start(unsigned long us){
    unsigned long ticks_long;
    unsigned short ticks;

    ticks_long = us / T1_TICK_US;
    if (ticks_long == T1_MAX){
        ticks = T1_MAX;
    }
    else
    {
        ticks = ticks_long;
    }
    TCNT1 = T1_MAX - ticks; /* overflow in ticks*1024 clock cycles */

    TIMSK1 |= _BV(TOIE1); /* enable overflow interrupt */
    /* start timer clock */
    TCCR1B = ~(_BV(CS10)|_BV(CS11)|_BV(CS12));
    TCCR1B |= _BV(CS10)|_BV(CS12); /* prescaler: 1024 */
}

void timer_start_ms(unsigned short ms){
    timer_start(ms * 1000UL);
}


