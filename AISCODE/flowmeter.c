/*
 * flowmeter.c
 *
 *  Created on: Oct 25, 2017
 *      Author: jvarn
 */
#include "flowmeter.h"
#include "timerA.h"

void InitializeFlowmeter(void){
    SET_FLOW_AS_AN_INPUT;
    TURN_ON_FLOWMETER;
}

void startFlow(int pulses, int numPlants){
    // 0.485 pulses per milliliter
    int pulseCount = 0;
    int lastFlowState, x, i;
    TURN_ON_FLOWMETER;
    long timercount;
    // Track flow until required pulses are met
    for (i = 0; i < numPlants; i++){
        while(pulseCount < pulses){
            x = READ_FLOWMETER;
            if (x == lastFlowState){
            }
            else{ // flowmeter reads a high
                pulseCount++;
            }
            lastFlowState = READ_FLOWMETER;
            timercount++;
            if(timercount >= 6000000){
                pulseCount = pulses;
                timercount = 0;
            }
        }
        pulseCount = 0;
        // PrintString("\r50 pulse reached\r\n",UART); // used to calibrate with UART
    }
    TURN_OFF_FLOWMETER;
}

