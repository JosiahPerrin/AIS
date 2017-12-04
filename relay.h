#ifndef relay_h
#define relay_h

#include <msp430.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                 RELAY #1
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *   Polarity  :  Active High
 *   GPIO      :  P2.2
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#define RELAY1 1
#define RELAY1_BIT				BIT2
#define RELAY1_PORT				P2OUT
#define RELAY1_DDR				P2DIR
#define SET_RELAY1_AS_AN_OUTPUT	RELAY1_DDR |= RELAY1_BIT
#define TURN_ON_RELAY1			RELAY1_PORT &= ~RELAY1_BIT
#define TURN_OFF_RELAY1			RELAY1_PORT |= RELAY1_BIT
#define TOGGLE_RELAY1           RELAY1_PORT ^= RELAY1_BIT

// Prototypes
void InitializeRelayPortPins(void);

#endif
