#include "uart.h"
#include "LED.h"

#define TRUE 1
#define FALSE 0

// Global variable
extern char CharacterHasNotBeenReceived;
extern char ReceivedCharacter;

/*
 * USCI_A0 initialization and reset for UART mode. See Section 15.3.1 of users' guide.
*/
void InitializeUART()
{
	// Select UART functionality, Rxd and Txd, for port pins (versus default I/O).
	USCIA0_RXD_P1SEL2 |= USCIA0_RXD_BIT;
	USCIA0_RXD_P1SEL |= USCIA0_RXD_BIT;

	USCIA0_TXD_P1SEL2 |= USCIA0_TXD_BIT;
	USCIA0_TXD_P1SEL |= USCIA0_TXD_BIT;

	// Software reset enabled. USCI logic held in reset state.
	UCA0CTL1 = UCSWRST;
	
	UCA0CTL0 = 0x00; // Initialize control register 0.
	/* UCPEN = 0x80 Async. Mode: Parity enable
	 * UCPAR = 0x40 Async. Mode: Parity     0:odd / 1:even
	 * UCMSB = 0x20 Async. Mode: MSB first  0:LSB / 1:MSB
	 * UC7BIT = 0x10 Async. Mode: Data Bits  0:8-bits / 1:7-bits
	 * UCSPB = 0x08 Async. Mode: Stop Bits  0:one / 1: two
	 * UCMODE1 = 0x04 Async. Mode: USCI Mode 1
	 * UCMODE0 = 0x02 Async. Mode: USCI Mode 0
	 * UCSYNC = 0x01 Sync-Mode  0:UART-Mode / 1:SPI-Mode
	 */

	// Use SMCLK
	UCA0CTL1 |= UCSSEL1; UCA0CTL1 &= ~UCSSEL0;
	/* UCSSEL1 = 0x80 USCI 0 Clock Source Select 1
	 * UCSSEL0 = 0x40 USCI 0 Clock Source Select 0
	 * 	00 = UCLK
	 *  01 = ACLK
	 *  10 = SMCLK
	 *  11 = SMCLK
	 * UCRXEIE = 0x20 RX Error interrupt enable
	 * UCBRKIE = 0x10 = Break interrupt enable
	 * UCDORM = 0x08 Dormant (Sleep) Mode
	 * UCTXADDR = 0x04 Send next Data as Address
	 * UCTXBRK = 0x02 Send next Data as Break
	 * UCSWRST = 0x01 USCI Software Reset
	 */
	
	UCA0BR1 = UCA0BR1_VALUE; UCA0BR0 = UCA0BR0_VALUE;
	UCA0MCTL = (UCBRF_0 + UCBRS_1);
	/*
	 * UCBRF3 = 0x80 USCI First Stage Modulation Select 3
	 * UCBRF2 = 0x40 USCI First Stage Modulation Select 2
	 * UCBRF1 = 0x20 USCI First Stage Modulation Select 1
	 * UCBRF0 = 0x10 USCI First Stage Modulation Select 0
	 * UCBRS2 = 0x08 USCI Second Stage Modulation Select 2
	 * UCBRS1 = 0x04 USCI Second Stage Modulation Select 1
	 * UCBRS0 = 0x02 USCI Second Stage Modulation Select 0
	 * UCOS16 = 0x01 USCI 16-times Oversampling enable
	 */
	
	// Software reset disabled. USCI logic released for operation.
    UCA0CTL1 &= ~UCSWRST;
	
	// Enable USCI_A0 RX interrupt
    // TX does not need an ISR
    IE2 |= UCA0RXIE;
}

// This routine turns off the UART and returns the I/O pins to GPIO functionality.
void ShutdownUART()
{
	// Wait for any remaining characters to transmit
	while (!(IFG2 & UCA0TXIFG));
	
	// Hold USCI module in reset
    UCA0CTL1 |= UCSWRST;
	
	// Pins back to digital I/O
	USCIA0_RXD_P1SEL2 &= ~USCIA0_RXD_BIT;
	USCIA0_RXD_P1SEL &= ~USCIA0_RXD_BIT;

	USCIA0_TXD_P1SEL2 &= ~USCIA0_TXD_BIT;
	USCIA0_TXD_P1SEL &= ~USCIA0_TXD_BIT;
}

void WriteCharacterUART(char data)
{
	// Wait for transmitter to finish current operation
	// TXIFG is set when the buffer is EMPTY
	while (!(IFG2 & UCA0TXIFG));
	
	// Then, assign input character to transmit buffer.
	UCA0TXBUF = data;
}

void WriteStringUART(char *pt)
{ 
	unsigned short i;
	
	/* Note that the correct operation of this function depends on the input
	 * string pointed to by pt to be a null-terminated string (that is, the last
	 * character in the string equals zero).
	 */
	for (i = 0; *(pt+i); i++) {
		WriteCharacterUART(*(pt+i));
	}
}

// Interrupt handler for RX on USCI A and B.
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	// Store character from RX buffer register in receive_char,
	// and then store the character in the receive buffer.
	ReceivedCharacter = UCA0RXBUF;
	CharacterHasNotBeenReceived = FALSE;

	// NOTE: The USCA0RXIFG flag is automatically cleared when UCA0RXBUF is read,
	//       no need to clear in manually. 
}
