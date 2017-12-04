#include "ADC.h"

extern volatile int array[4];

void ConfigureADC(void)
{
	/* ADC10 Control register 0
	 * SREF_0: Choose supply voltages as reference.
	 * ADC10SHT_2: sample + hold @ 16 ADC10CLKs
	 * ADC10ON: Turn on ADC.
	 */
	ADC10CTL0 = (SREF_1 +  REFON + REF2_5V + ADC10SHT_2 + ADC10ON + MSC);

	// ADC10 Control register 1
	// ADC10OSC as ADC10CLK; Single-channel-single-conversion
    ADC10CTL1 = ADC10_ANALOG_INPUT_SELECT + ADC10SSEL_3 + CONSEQ_1;

	// Enable the analog inputs.
	ADC10AE0 |= ADC10_ANALOG_INPUT_BIT_0;
	ADC10AE0 |= ADC10_ANALOG_INPUT_BIT_1;
	ADC10AE0 |= ADC10_ANALOG_INPUT_BIT_2;
	ADC10AE0 |= ADC10_ANALOG_INPUT_BIT_3;

	__delay_cycles(128);            // Delay to allow Ref to settle

	ADC10DTC1 = 0x04;
}

void Start_Conversion(){

	ADC10SA = (unsigned int) array;

    // X axis measurement
    ADC10CTL0 &= ~ENC;
    ADC10CTL0 |=  (ENC | ADC10SC);      // Enable and begin sampling
    while(ADC10CTL1 & ADC10BUSY);
}

