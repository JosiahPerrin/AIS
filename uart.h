#ifndef USCI_UART_H
#define USCI_UART_H
#include <msp430.h>

#define BUFFER_SIZE 80
#define TRUE 1
#define FALSE 0
#define UART 0

/* Baud rate = SMCLK / 104 = ~9600 for SMCLK = 1 MHz in low-frequency mode
 * (UCOS16 = 0). Also, UCBRSx = 1 and UCBRFx = 0 (ignored for UCOS16 = 0).
 * See Table 15-4 in the MSP430x2xx Family User's Guide (104 = 0x0068)
 */
//Baud rate 9600 with 1MHz clock-> 104 = BR0 + 256*BR1
#define UCA0BR1_VALUE 0
#define UCA0BR0_VALUE 104

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * USCI A0 UART mode: receive data input
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * GPIO      :  P1.1
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define USCIA0_RXD_BIT		BIT1
#define USCIA0_RXD_P1SEL    P1SEL
#define USCIA0_RXD_P1SEL2   P1SEL2

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * USCI A0 USCI_A0 UART mode: transmit data output
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * GPIO      :  P1.2
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define USCIA0_TXD_BIT		BIT2
#define USCIA0_TXD_P1SEL    P1SEL
#define USCIA0_TXD_P1SEL2   P1SEL2

void InitializeUART(void);
void ShutdownUART(void);
void WriteStringUART(char *pt);
void WriteCharacterUART(char data);
  
#endif /* USCI_UART_H */
