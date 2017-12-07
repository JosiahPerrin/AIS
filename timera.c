#include "timera.h"
#include "LED.h"
#include <msp430.h>

extern int blink;

void TimeDelay(unsigned int delay, unsigned int resolution)
{
	//stop timer and clear it
	TA0CTL |= (MC_0 | TACLR);
	//assign capture and control register 0 to 999 (999+1=1000 us -> 1 MHz)
	TACCR0 = resolution;
	//start timer
	TA0CTL |= (TASSEL_2 | MC_1);

	int i;
	for(i=0;i<delay;i++){
		//use timerA - poll TAIFG. check value of timer A control register and see if it equals TA flag value
		//when they are same, keep checking. once they are different, reset the flag
		while( (TA0CTL & TAIFG) == 0 ){
		}
		//reset flag
		TA0CTL &= ~TAIFG;
	}
	//stop and clear timer
	TA0CTL |= (MC_0 | TACLR);
}

void ConfigureTimerA(void)
{
	// stop the timer and clear it. MCx bits are used to select the mode of the time. MC_0 corresponds to "stop"
	// TACLR resets clock divider, the TAR, and the count direction
	TA0CTL |= (MC_0 | TACLR);

	// set the timer in up mode with the subsystem master clock
	// MC_1 corresponds to up mode. but, when starting timer in up mode, need to specify which clock to use
	// in this case, use subsystem master clock (SMCLK). the TASSELx bits are used to specify the clock source. (TASSEL = TimerA Source Select)
	// TASSEL_2 corresponds to SMCLK
	TA0CTL |= (TASSEL_2 | MC_1);

	// ID_3 is timer input divider by 8
	TA0CTL |= ID_3;

	// now, can input (250,000 / 8 - 1) [see equation for period in slides]
	TA0CCR0 = ( 62500/2 - 1 );

	//enable the capture/compare register0 interrupt
	TA0CCTL0 |= CCIE;


}

void WaitOneMinute(void){

	int i = 0;

	while (i<240) {
		TimeDelay(250,999);
		++i;
	}
}
#pragma vector = TIMER0_A0_VECTOR //interrupt vector
// Timer a interrupt service routine
	__interrupt void TimerA0_routine(void)
{
		//TOGGLE_LED1;
}
