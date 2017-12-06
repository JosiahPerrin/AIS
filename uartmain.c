//
// This program presents a simple User Interface (UI) for controlling the LEDs.
//
#include <msp430.h>
#include <stdio.h>

#include "LED.h"
#include "uart.h"

#define BUFFER_SIZE 80
#define TRUE 1
#define FALSE 0
#define UART 0

// Global variable
char CharacterHasNotBeenReceived;
char ReceivedCharacter = (char) NULL;;

// Function prototypes
void ConfigureClockModule(void);
void PrintString(char *, unsigned char);
void PrintCharacter(char, unsigned char);
//void blinkLEDs(char);

void main(void)
{
    int ledChoice,blink; // initialized variables

    // Stop the watchdog timer, and configure the clock module.
	WDTCTL = WDTPW + WDTHOLD;
	ConfigureClockModule();

    // Initialize LEDs
    InitializeLEDPortPins();

	// Initialize USCI A0 to use UART.
	InitializeUART();

	_enable_interrupts();

    // "Clear" the screen with a carriage return ('\r') and line feed ('\n'),
	// followed by the prompt string.
    // Wait for a character to be entered.

	// Continue with the UI indefinitely.
	while (TRUE) {
		// Echo character
	    PrintString("\rChoose your destiny: \r\n",UART);
        PrintString("\r(1)Turn on an LED\r\n",UART);
        PrintString("\r(2)Turn off LEDs\r\n",UART);
        PrintString("\r(3)Blink LED\r\n",UART);
        PrintString("\r(x)Exit\r\n",UART);
		CharacterHasNotBeenReceived = TRUE;
        while (CharacterHasNotBeenReceived);

		switch(ReceivedCharacter){
		// Give choices to turn on LED, then turn on that LED
		case '1':
		    PrintString("\r(1)Turn on LED1\r\n",UART);
		    PrintString("\r(2)Turn on LED2\r\n",UART);
		    CharacterHasNotBeenReceived = TRUE;
            while (CharacterHasNotBeenReceived);
		    switch(ReceivedCharacter){
		        case '1': TURN_ON_LED1;
		            break;
		        case '2': TURN_ON_LED2;
		            break;
		        default: break;
		    }
		    break;

		// Turns off LEDs
		case '2':
		    TURN_OFF_LED1;
		    TURN_OFF_LED2;
		    break;

		// Give choice to blink an LED. Make LED Blink certain # of times
		case '3':
		    PrintString("\r\nBlink which LED? \r\n",UART);
		    PrintString("(1)Red\r\n",UART);
		    PrintString("(2)Green\r\n",UART);
		    CharacterHasNotBeenReceived = TRUE;
		    while (CharacterHasNotBeenReceived);
		    ledChoice = ReceivedCharacter;

		    // LED1 (RED) Blinks
		    if (ledChoice == '1'){
                for(blink=0;blink<5;blink++){
                    TOGGLE_LED1;
                    _delay_cycles(250000);
                    TOGGLE_LED1;
                    _delay_cycles(250000);
                }
            }

		    // LED 2 (GREEN) Blinks
            else if (ledChoice == '2'){
                for(blink=0;blink<5;blink++){
                    TOGGLE_LED2;
                    _delay_cycles(250000);
                    TOGGLE_LED2;
                    _delay_cycles(250000);
                }
            }
		    break;

		// Close out of program
		case 'x':
		    PrintString("\r\n*** PROGRAM EXITED ***",UART);
		    ShutdownUART();
		    break;
		default:
		    break;
		}
	}
}


void ConfigureClockModule()
{
	// Configure Digitally Controlled Oscillator (DCO) to use factory calibrations.
	DCOCTL  = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;
}


void PrintString(char * StringToPrint, unsigned char PrintDeviceType)
{
	unsigned short i;                     // Used for indexing
	char StringBuffer[BUFFER_SIZE];    // Character buffer to hold each string to be printed

	for (i = 0; i < BUFFER_SIZE; i++) StringBuffer[i] = (char) NULL;
	sprintf(StringBuffer, StringToPrint);
	switch (PrintDeviceType) {
	case UART:
		WriteStringUART(StringBuffer);
		break;
	default: break;
	}
}

void PrintCharacter(char CharacterToPrint, unsigned char PrintDeviceType)
{
	switch (PrintDeviceType) {
	case UART:
		WriteCharacterUART(CharacterToPrint);
		break;
	default: break;
	}
}
