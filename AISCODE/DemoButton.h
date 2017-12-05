/*
 * DemoButton.h
 *
 *  Created on: Dec 5, 2017
 *      Author: josiah
 */

#ifndef DEMOBUTTON_H_
#define DEMOBUTTON_H_


#include <msp430.h>

/*
 * For setting DEMOBUTTON as an input on P2.0
 */
#define DEMOBUTTON_BIT               BIT5
#define DEMOBUTTON_PORT              P2IN
#define DEMOBUTTON_DDR               P2DIR
#define SET_DEMOBUTTON_AS_AN_INPUT         DEMOBUTTON_DDR &= ~DEMOBUTTON_BIT
#define TURN_ON_DEMOBUTTON           DEMOBUTTON_PORT |= DEMOBUTTON_BIT
#define TURN_OFF_DEMOBUTTON          DEMOBUTTON_PORT &= ~DEMOBUTTON_BIT
#define READ_DEMOBUTTON              DEMOBUTTON_PORT & DEMOBUTTON_BIT

void InitializeDEMOBUTTON(void);

#endif /* DEMOBUTTON_H_ */
