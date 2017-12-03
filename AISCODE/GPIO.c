#include "GPIO.h"
/*
 * GPIO.c
 *
 *  Created on: Nov 28, 2017
 *      Author: student
 *      Purpose: GPIO.h and GPIO.c will facilitate switching digital I/O pins
 *      between input and output mode. it will also turn on and off VCC when the
 *      pin is in output mode
 */

void InitializeLightPortPins(){

	SET_P1_0_AS_AN_INPUT;
	//SET_P1_0_INPUT_LOW;

}

void SetP1_1AsInput(){

	//messing around with all the different bits to try to turn off voltage
	TURN_OFF_VOLTAGE_P1_1;
	SELECT_P1_1_IO;
	SELECT2_P1_1_IO;
	SET_P1_1_AS_AN_INPUT;
	SET_P1_1_INPUT_LOW;
	TURN_OFF_VOLTAGE_P1_1;

}

void SetP1_3AsInput(){

	TURN_OFF_VOLTAGE_P1_3;
	SET_P1_3_AS_AN_INPUT;
	SET_P1_3_INPUT_LOW;
}


void SetP1_1AsOutput(){

	SET_P1_1_AS_AN_OUTPUT;
	TURN_ON_VOLTAGE_P1_1;
	SET_P1_1_INPUT_LOW;
}

void SetP1_3AsOutput(){

	SET_P1_3_AS_AN_OUTPUT;
	TURN_ON_VOLTAGE_P1_3;
}

