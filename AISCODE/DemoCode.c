/*
 * DemoCode.c
 *
 *  Created on: Dec 5, 2017
 *      Author: josiah
 */

#ifndef DEMOCODE_C_
#define DEMOCODE_C_

#include <msp430.h>
#include "timerA.h"
#include "ADC.h"
#include "GPIO.h"
#include "LCD.h"
#include "DemoButton.h"
#include "DemoCode.h"
#include "flowmeter.h"
#include "relay.h"

extern volatile int array[2];
extern int light0;
extern char SatLevel;
extern char LightLevel;
extern int moisture1;
extern unsigned int moistureReading;

void RunDemo(void){
    Start_Conversion();                                                     //take ADC values for moisture and light for startup
    moisture1 = array[0];
    light0 = array[1];
    moistureReading = ConvertReadingToPercentage(moisture1);                //do conversions
    //STILL NEED****** convert moistureReading to SatLevel (int to char)
    //STILL NEED****** convert light0 to LightLevel (int to char)
    //WriteDatatoLCD(SatLevel);
    //WriteDatatoLCD(LightLevel);

    WaterPlants();                                                          //send a little water to the plants
    Start_Conversion();                                                     //take ADC values for moisture and light after watering
    moisture1 = array[0];
    moistureReading = ConvertReadingToPercentage(moisture1);                //do conversions
    //STILL NEED****** convert moistureReading to SatLevel (int to char)
    //WriteDatatoLCD(SatLevel);
    //WriteDatatoLCD(LightLevel);

    TURN_ON_RELAY2; //turn on the light
    Start_Conversion();
    light0 = array[1];
    moisture1 = array[0];
    //STILL NEED****** convert light0 to LightLevel (int to char)
    //WriteDatatoLCD(LightLevel);
    _delay_cycles(5000000); //delay for "showing off" if we don't have a delay, lights will cycle almost instantaneously
    TURN_OFF_RELAY2;

}

void WaterPlants(){
    const int pulses = 25;
    const int numplants = 4;

    TURN_ON_RELAY1;
    startFlow(pulses, numplants); //this is turned off for testing purposes - you need actual water to flow for the loop to conclude
    TURN_OFF_RELAY1;

}

int ConvertReadingToPercentage(int MRI1){
    int Final = MRI1; //temp variable
    Final = (Final >> 10) * 100; //convert from ADC value to VWC percentage
    _delay_cycles(128);
    return(Final);
}

#endif /* DEMOCODE_C_ */
