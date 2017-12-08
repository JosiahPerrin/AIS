#include <msp430.h>
#include "timerA.h"
#include "ADC.h"
#include "GPIO.h"
#include "LCD.h"
#include "DemoButton.h"
#include "DemoCode.h"
#include "relay.h"


int counter = 0;
extern volatile int array[2];
extern int light0;
extern char SatLevel;
extern char LightLevel;
extern int moisture1;
extern unsigned int moistureReading;
extern volatile int FULL_LIGHT_THRESHOLD;
extern volatile int INTERVALS_FULL_LIGHT;

void ConfigureTimerA0()
{
    // Timer0_A3 Control Register
    TA0CTL |= MC_0;     // Stop the timer
    TA0CTL |= TACLR;    // Clear the timer

    TA0CTL |= TASSEL_2 | ID_3 | MC_1;
    /* TASSEL1 = 0x0200 Timer A clock source select 0
     * TASSEL0 = 0x0100 Timer A clock source select 1
     *  00 = TACLK
     *  01 = ACLK
     *  10 = SMCLK
     *  11 = INCLK
     * ID1 = 0x0080 Timer A clock input divider 1
     * ID0 = 0x0040 Timer A clock input divider 0
     *  00 => Input divider = 1
     *  01 => Input divider = 2
     *  10 => Input divider = 4
     *  11 => Input divider = 8
     * MC1 = 0x0020 Timer A mode control 1
     * MC0 = 0x0010 Timer A mode control 0
     *  00 = Stop
     *  01 = Up
     *  10 = Continuous
     *  11 = Up/Down
     * TACLR = 0x0004 Timer A counter clear
     * TAIE = 0x0002 Timer A counter interrupt enable
     * TAIFG = 0x0001 Timer A counter interrupt flag
     */

    // Assign a value to TA0CCR0
    TA0CCR0 = 10000;
    // Enable TACCR0 Compare/Capture Interrupt Flag (CCIFG0)
    TA0CCTL0 |= CCIE;
}
void ConfigureTimerA1(void){
    TA1CTL = (MC_0 | TACLR);     // Stop & clear timer
    TA0CTL |= TASSEL_2 | ID_3 | MC_1; //SMCLK, DIV 8, Up Mode
    TA0CCR0 = 62499;
    TA0CCTL0 |= CCIE;
}
void WaitOneMinute(){
    int i = 0;

    while (i<240) {
        TimeDelay(250,999);
        ++i;
    }
}
void TimeDelay(unsigned int delay, unsigned int resolution){
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

void WaitFiveMinutes(void){
    WaitOneMinute();
    WaitOneMinute();
    WaitOneMinute();
    WaitOneMinute();
    WaitOneMinute();
}

void WaitNMinutes(int n){
    int i;
    for (i = 0; i < n; i++){
        WaitOneMinute();
    }
}
#pragma vector = TIMER0_A0_VECTOR
// Interrupt service routine for CCIFG0
__interrupt void TimerA0_routine(void)
{

}

#pragma vector = TIMER0_A1_VECTOR
// Interrupt service routine for CCIFG0
__interrupt void TimerA1_routine(void)
{
    counter++;
    if(counter >= 600){
        Start_Conversion();
        light0 = array[1];
        counter = 0;
        if(light0 > FULL_LIGHT_THRESHOLD){
            INTERVALS_FULL_LIGHT++;
        }
    }
}


