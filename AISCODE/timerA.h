#ifndef TIMER_A_H
#define TIMER_A_H

#include <msp430.h>

/*
 * The timer A clock frequency determines the value for TACCR0 so that the global timer, g1msTimer,
 * is updated every millisecond.  For example, SMCLK = 2 MHz (16 MHz divided by 8). Thus,
 * CCR0+1 = 2 MHz/1 kHz = 2000 => CCR0 = 1999
 */
#define TA0CCR0_VALUE 1999	// Timer A period is TACCR0+1

// Prototypes
void ConfigureTimerA0(void);
void ConfigureTimerA1(void);
void WaitOneMinute(void);
void TimeDelay(unsigned int delay, unsigned int resolution);
void WaitFiveMinutes(void);
void WaitNMinutes(int n);

#endif
