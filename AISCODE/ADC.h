#ifndef ADC_H
#define ADC_H

#include <msp430.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *      ADC10 Analog Input
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *   GPIO      :  P1.0-P1.3
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define ADC10_ANALOG_INPUT_BIT_0    	BIT0
#define ADC10_ANALOG_INPUT_BIT_1        BIT1
#define ADC10_ANALOG_INPUT_BIT_2        BIT2
#define ADC10_ANALOG_INPUT_BIT_3        BIT3
#define ADC10_ANALOG_INPUT_SELECT       INCH_1

// Prototypes
void ConfigureADC(void);
void Start_Conversion(void);

#endif
