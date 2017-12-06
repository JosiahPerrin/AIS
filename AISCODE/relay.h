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
#define RELAY1_BIT              BIT2
#define RELAY1_PORT             P2OUT
#define RELAY1_DDR              P2DIR
#define SET_RELAY1_AS_AN_OUTPUT RELAY1_DDR |= RELAY1_BIT
#define TURN_ON_RELAY1          RELAY1_PORT &= ~RELAY1_BIT
#define TURN_OFF_RELAY1         RELAY1_PORT |= RELAY1_BIT
#define TOGGLE_RELAY1           RELAY1_PORT ^= RELAY1_BIT

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                 RELAY #2
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *   Polarity  :  Active High
 *   GPIO      :  P2.3
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#define RELAY2 2
#define RELAY2_BIT              BIT3
#define RELAY2_PORT             P2OUT
#define RELAY2_DDR              P2DIR
#define SET_RELAY2_AS_AN_OUTPUT RELAY2_DDR |= RELAY2_BIT
#define TURN_ON_RELAY2          RELAY2_PORT &= ~RELAY2_BIT
#define TURN_OFF_RELAY2         RELAY2_PORT |= RELAY2_BIT
#define TOGGLE_RELAY2           RELAY2_PORT ^= RELAY2_BIT

// Prototypes
void InitializeRelayPortPins(void);

#endif
