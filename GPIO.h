#include <msp430.h>
/*
 * GPIO.h
 *
 *  Created on: Nov 28, 2017
 *      Author: student
 *      Purpose: GPIO.h and GPIO.c will facilitate switching digital I/O pins
 *      between input and output mode. it will also turn on and off VCC when the
 *      pin is in output mode
 */

#ifndef GPIO_H_
#define GPIO_H_

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                 Moisture
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *               GPIO : P1.1
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define SELECT_P1_1_IO            P1SEL |= BIT1;
#define SELECT2_P1_1_IO            P1SEL2 |= BIT1;
#define SET_P1_1_AS_AN_OUTPUT     P1DIR |= BIT1;
#define SET_P1_1_AS_AN_INPUT      P1DIR &= ~BIT1;
#define SET_P1_1_INPUT_LOW       P1IN &= ~BIT1;
#define TURN_ON_VOLTAGE_P1_1     P1OUT |= BIT1;
#define TURN_OFF_VOLTAGE_P1_1    P1OUT &= ~BIT1;

#define TOGGLE_P1_1_IO    P1DIR ^= BIT1;
#define TOGGLE_P1_1_VOLTAGE    P1OUT ^= BIT1;
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                 Moisture
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *               GPIO : P1.3
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define SET_P1_3_AS_AN_OUTPUT   P1DIR |= BIT3;
#define SET_P1_3_AS_AN_INPUT     P1DIR &= ~BIT3;
#define SET_P1_3_INPUT_LOW       P1IN &= ~BIT3;
#define TURN_ON_VOLTAGE_P1_3    P1OUT |= BIT3;
#define TURN_OFF_VOLTAGE_P1_3   P1OUT &= ~BIT3;

#define TOGGLE_P1_3_IO    P1DIR ^= BIT3;
#define TOGGLE_P1_3_VOLTAGE    P1OUT ^= BIT3;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                 Light
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *              GPIO : P1.0
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define SET_P1_0_AS_AN_OUTPUT   P1DIR |= BIT0;
#define SET_P1_0_AS_AN_INPUT     P1DIR &= ~BIT0;
#define SET_P1_0_INPUT_LOW       P1IN &= ~BIT0;
#define TURN_ON_VOLTAGE_P1_0    P1OUT |= BIT0;
#define TURN_OFF_VOLTAGE_P1_0   P1OUT &= ~BIT0;

#define TOGGLE_P1_0_IO    P1DIR ^= BIT0;
#define TOGGLE_P1_0_VOLTAGE    P1OUT ^= BIT0;


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                 Other
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *              GPIO : P1.2
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define SET_P1_2_AS_AN_OUTPUT   P1DIR |= BIT2;
#define SET_P1_2_AS_AN_INPUT     P1DIR &= ~BIT2;
#define SET_P1_2_INPUT_LOW       P1IN &= ~BIT2;
#define TURN_ON_VOLTAGE_P1_2    P1OUT |= BIT2;
#define TURN_OFF_VOLTAGE_P1_2   P1OUT &= ~BIT2;

#define TOGGLE_P1_2_IO    P1DIR ^= BIT2;
#define TOGGLE_P1_2_VOLTAGE    P1OUT ^= BIT2;






//#define SET_P1_4_AS_AN_OUTPUT   P1DIR |= BIT4;
//#define TURN_ON_VOLTAGE_P1_4    P1OUT |= BIT4;

//prototypes
void InitializeLightPortPins(void);
void SetP1_1AsInput(void);
void SetP1_3AsInput(void);
void SetP1_1AsOutput(void);
void SetP1_3AsOutput(void);



#endif /* GPIO_H_ */
