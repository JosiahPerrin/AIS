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


volatile int MOISTURE_THRESHOLD = 400;
volatile int FULL_LIGHT_THRESHOLD = 920;
volatile int INTERVALS_FULL_LIGHT;
volatile int demoOn;
volatile int array[2];
int light0;
char SatLevel = '0';
char LightLevel = '0';
int moisture1;
unsigned int moistureReading;

void main(void) {


	//approach: repeated iterations of one-time multiple channel conversion

    WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
    ConfigureClockModule();         //configure clocks
	ConfigureADC();                 // ADC configuration
	InitializeRelayPortPins();      // set relays active
	//ConfigureTimerA0();           // don't set - timerA0 used for wait minute function
	ConfigureTimerA1();
	InitUART();
	_enable_interrupts();           // Timer configuration for light check interrupt

//WHILE LOOP START
	while(1) {


//****DEMO CODE FOR FRIDAY DECEMBER 8th*******************************************************************
	    SET_DEMOBUTTON_AS_AN_INPUT;
	    TURN_ON_DEMOBUTTON;

	    demoOn = READ_DEMOBUTTON; //this function checks the demo button that is from the 3.3V line to pin 2.5 on MSP
	    if(demoOn < 1){          //if you want to just run the demo, make this if statement:: if(1){RunDemo();}
	                RunDemo();
        }
//******End of DEMO CODE**********************************************************************************

//****REAL CODE FOR SYSTEM RUNNING************************************************************************
//	 Variable Declaration
	    int light0;
        char SatLevel = '0';
        char LightLevel = '0';
        int moisture1;
        unsigned int moistureReading;
        int night = 0;

    //SENSING SECTION*************************************************************************************

	    Start_Conversion();                                                     //take ADC values for moisture and light for startup
        moisture1 = array[0];
        light0 = array[1];
        moistureReading = ConvertReadingToPercentage(moisture1);                //do conversions


    //PLUMBING SECTION************************************************************************************

        if(moisture1 < MOISTURE_THRESHOLD) {
            while(moisture1 < (MOISTURE_THRESHOLD+200)){
                WaterPlants();
                WaitOneMinute();
                Start_Conversion();                                             //take ADC values for moisture check
                moisture1 = array[0];
            }
        }

    //LCD SECTION*****************************************************************************************

        //STILL NEED****** convert moistureReading to SatLevel (int to char)
        //STILL NEED****** convert light0 to LightLevel (int to char)
        WriteDatatoLCD(SatLevel);
        WriteDatatoLCD(LightLevel);

    //LIGHTING SECTION************************************************************************************
        Start_Conversion();                                                     //take ADC values for light check (night/day)
        light0 = array[1];
        if(light0 < 300){
            night = 1;
        }

        if(night == 1 && INTERVALS_FULL_LIGHT < 72){
            TURN_ON_RELAY2;
            WaitNMinutes((72 - INTERVALS_FULL_LIGHT)+(72 - INTERVALS_FULL_LIGHT)+(72 - INTERVALS_FULL_LIGHT)+(72 - INTERVALS_FULL_LIGHT)+(72 - INTERVALS_FULL_LIGHT));
            TURN_OFF_RELAY2;
            INTERVALS_FULL_LIGHT = 72;
        }

        Start_Conversion();                                                     //take ADC values for light check (night/day)
        light0 = array[1];
        if(light0 > 550){
            night = 0;
            INTERVALS_FULL_LIGHT = 0;
        }

	} //End of REAL CODE and WHILE LOOP
}

void ConfigureClockModule()
{
	// Configure Digitally Controlled Oscillator (DCO) using factory calibrations
	DCOCTL  = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;
	//BCSCTL1 |= DIVS_3;
}



