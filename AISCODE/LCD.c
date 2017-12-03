#include "msp430g2553.h"

#define TXLED BIT0
#define TXD BIT2

void WriteDatatoLCD(char data){

    InitUART();

    UCA0TXBUF = data; // loading the buffer to be sent

}

void InitUART(void)
{
   P2DIR |= 0xFF; // All P2.x outputs
   P2OUT &= 0x00; // All P2.x reset
   P1SEL |= TXD ; // P1.2=TXD
   P1SEL2 |= TXD ; // P1.2=TXD
   P1DIR |= TXLED;
   P1OUT = 0x00;

   UCA0CTL1 |= UCSSEL_2; // SMCLK
   UCA0BR0 = 104; // 1MHz 9600 per data sheet
   UCA0BR1 = 0; // 1MHz 9600 per data sheet
   UCA0MCTL = UCBRS1;
   UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
   UC0IE |= UCA0RXIE; // Enable USCI_A0 RX interrupt
}

