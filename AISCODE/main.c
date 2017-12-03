#include <msp430.h>
#include "timerA.h"
#include "ADC.h"
#include "GPIO.h"
#include "LCD.h"

// Function Prototypes
void ConfigureClockModule();
void WaterPlants();

volatile int array[4];
volatile int MOISTURE_THRESHOLD;
volatile int FULL_LIGHT_THRESHOLD;
volatile int INTERVALS_FULL_LIGHT;

void main(void) {


	//approach: repeated iterations of one-time multiple channel conversion

    WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
    ConfigureClockModule();

	ConfigureADC();

	ConfigureTimerA();

	_enable_interrupts();

	int light0;
	int moisture3;
	int moisture1;
	unsigned int moistureReading;

	//set port 2 pins 0 and 1 as outputs
	P2DIR |= BIT0;
	P2DIR |= BIT1;

	//turn on P2.0, turn off P2.1
	P2OUT |= BIT0;
	P2OUT &= ~BIT1;

	while(1) {

		Start_Conversion();

    	moisture3 = array[0];
    	moisture1 = array[1];
    	moistureReading = moisture3 - moisture1;
    	_nop();
	}

   /* if(moistureReading < MOISTURE_THRESHOLD) {

    	WaterPlants();
    }

    int i;
    for (i=0; i<20; ++i ){

    	Start_Conversion();
    	light0 = array[3];

    	if(light0 > FULL_LIGHT_THRESHOLD){

    		++INTERVALS_FULL_LIGHT;
    	}
    	int j = 0;
    	while(j <5){
    		WaitOneMinute();
    		++j;
    	}
    }
	*/

//*****************************************************LCD SECTION*************************************************
	// I know this needs to be in the while loop above on line 43, but using this to work on LCD section separately
	char buttstuff = 'hello';
	while (1)
	       {
	           //we need to figure out a way with delays and such, where the strings for our data values are loaded into the buffer
	           // I was thinking a for loop that sends individual characters out one at a time, then outside of the for loop
	           // there will be say a 5 minutes delay time, and then the while loop will make sure the for loop gets proc'd again
	           // after the delay
	        WriteDatatoLCD(buttstuff);

	       }
}

void ConfigureClockModule()
{
	// Configure Digitally Controlled Oscillator (DCO) using factory calibrations
	DCOCTL  = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;
	//BCSCTL1 |= DIVS_3;
}
void WaterPlants(){

}


