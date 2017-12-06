#include <msp430.h>
#include "timerA.h"
#include "ADC.h"
#include "GPIO.h"
#include "LCD.h"
#include "DemoButton.h"
#include "DemoCode.h"
#include "relay.h"

// Function Prototypes
void ConfigureClockModule();

volatile int array[4];
volatile int MOISTURE_THRESHOLD;
volatile int FULL_LIGHT_THRESHOLD;
volatile int INTERVALS_FULL_LIGHT;
volatile int demoOn;

void main(void) {


	//approach: repeated iterations of one-time multiple channel conversion

    WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
    ConfigureClockModule();         //configure clocks
	ConfigureADC();                 // ADC configuration
	InitializeRelayPortPins();      // set relays active
	ConfigureTimerA();              // Timer configuration
	_enable_interrupts();           //interrupt enabling


	//variables to be declared for function use
	/*int light0;
	int moisture3;
	int moisture1;
	unsigned int moistureReading;*/

	//set port 2 pins 0 and 1 as outputs
	P2DIR |= BIT0;
	P2DIR |= BIT1;

	//turn on P2.0, turn off P2.1
	P2OUT |= BIT0;
	P2OUT &= ~BIT1;

//WHILE LOOP START
	while(1) {


//****DEMO CODE FOR FRIDAY DECEMBER 8th*******************************************************************
	    SET_DEMOBUTTON_AS_AN_INPUT;
	    TURN_ON_DEMOBUTTON;

	    demoOn = READ_DEMOBUTTON; //this function checks the demo button that is from the 3.3V line to pin 2.5 on MSP
	    if(demoOn >= 1){          //if you want to just run the demo, make this if statement:: if(1){RunDemo();}
	                RunDemo();
	            }
	        //End of DEMO CODE



//****REAL CODE FOR SYSTEM RUNNING************************************************************************

    //SENSING SECTION*************************************************************************************
		/*Start_Conversion();

    	//moisture3 = array[0];
    	//moisture1 = array[1];
    	//moistureReading = moisture3 - moisture1;

    	_nop();*/

    //PLUMBING SECTION************************************************************************************


    //LCD SECTION*****************************************************************************************

        //volatile char buttstuff = 'h';

    	               //we need to figure out a way with delays and such, where the strings for our data values are loaded into the buffer
    	               // I was thinking a for loop that sends individual characters out one at a time, then outside of the for loop
    	               // there will be say a 5 minutes delay time, and then the while loop will make sure the for loop gets proc'd again
    	               // after the delay

        //WriteDatatoLCD(buttstuff);

    //LIGHTING SECTION************************************************************************************

	} //End of REAL CODE and WHILE LOOP

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


}

void ConfigureClockModule()
{
	// Configure Digitally Controlled Oscillator (DCO) using factory calibrations
	DCOCTL  = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;
	//BCSCTL1 |= DIVS_3;
}



