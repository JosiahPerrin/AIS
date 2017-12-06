/*
 * flowmeter.h
 *
 *  Created on: Oct 25, 2017
 *      Author: jvarn
 */

#ifndef FLOWMETER_H_
#define FLOWMETER_H_

#include <msp430.h>

/*
 * For setting flowmeter as an input on P2.0
 */
#define FLOWMETER_BIT               BIT0
#define FLOWMETER_PORT              P2IN
#define FLOWMETER_DDR               P2DIR
#define SET_FLOW_AS_AN_INPUT        FLOWMETER_DDR &= ~FLOWMETER_BIT
#define TURN_ON_FLOWMETER           FLOWMETER_PORT |= FLOWMETER_BIT
#define TURN_OFF_FLOWMETER          FLOWMETER_PORT &= ~FLOWMETER_BIT
#define READ_FLOWMETER              FLOWMETER_PORT & FLOWMETER_BIT;

void InitializeFlowmeter(void);
void startFlow(int pulses,int numPlants);

#endif /* FLOWMETER_H_ */
