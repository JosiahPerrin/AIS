#include <msp430.h>
#include "myLED.h"

int lowMoisture = 350;
int mediumMoisture = 500;
int highMoisture = 650;

void InitializeLEDPortPins() {

	// Set the initial value and port pin direction for the LEDs.
	TURN_OFF_LED1;
	SET_LED1_AS_AN_OUTPUT;
	TURN_OFF_LED2;
	SET_LED2_AS_AN_OUTPUT;


}

void MoistureDisplay(int moisture) {

	// plenty of water
	if (moisture > highMoisture) {

		TURN_OFF_LED1;
		TURN_OFF_LED2;
		TURN_ON_LED3;
	}

	// water too low
	else if(moisture < lowMoisture) {

		TURN_ON_LED1;
		TURN_OFF_LED2;
		TURN_OFF_LED3;

	}

	// otherwise in the middle
	else {

		TURN_OFF_LED1;
		TURN_ON_LED2;
		TURN_OFF_LED3;
	}


}
/*
 * myLED.c
 *
 *  Created on: Dec 7, 2017
 *      Author: student
 */




