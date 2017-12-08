#include "msp430g2553.h"
#include "LCD.h"

#define TXLED BIT0
#define TXD BIT2

char CharacterHasNotBeenReceived;
char ReceivedCharacter;
char Shit[5];
char string[] = { "Hello World\r\n" };

unsigned int i = 0; //Counter

void WriteDatatoLCD(char data){

    //while (!(IFG2 & UCA0TXIFG)); // loading the buffer to be sent
   // UC0IE |= UCA0TXIE;
    //UCA0TXBUF = string[i++];
}

void InitUART(void)
{
   string[0] = 0xFE;
   string[1] = 0x7C;
   string[2] = 0x9D;
   //P2DIR |= 0xFF; // All P2.x outputs (I think we dont want to do this anymore because we will be turning on the uart in the middle of the program)
   //P2OUT &= 0x00; // All P2.x reset   (same as above, we should reset all the pins, that could fuck everything up. Leaving it commented out JIC)

   P1SEL |= TXD ; // P1.2=TXD
   P1SEL2 |= TXD ; // P1.2=TXD
   P1DIR |= TXLED;
   P1OUT &= 0x00;

   UCA0CTL1 |= UCSSEL_2; // SMCLK
   UCA0BR0 = 104; // 1MHz 9600 per data sheet
   UCA0BR1 = 0; // 1MHz 9600 per data sheet
   UCA0MCTL |= UCBRS1;
   UCA0MCTL |= UCBRF0;
   UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
   UC0IE |= UCA0TXIE; // Enable USCI_A0 TX interrupt
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{
       P1OUT |= TXLED;
       UCA0TXBUF = string[i++]; // TX next character
       if (i == sizeof string - 1) // TX over?
           //UC0IE &= ~UCA0TXIE; // Disable USCI_A0 TX interrupt
           i = 0;
       P1OUT &= ~TXLED;
}

