#include "relay.h"
#include "uart.h"
#include "flowmeter.h"
#include "timerA.h"

void InitializeRelayPortPins(void)
{
	// Set the initial value and port pin direction for the Relays.
	TURN_OFF_RELAY1;
	SET_RELAY1_AS_AN_OUTPUT;
	/*
	TURN_OFF_RELAY2;
	SET_RELAY2_AS_AN_OUTPUT;
	TURN_OFF_RELAY3;
    SET_RELAY3_AS_AN_OUTPUT;
    TURN_OFF_RELAY4;
    SET_RELAY4_AS_AN_OUTPUT;
    */
}
