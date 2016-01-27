//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp.h"

void main(void)
{
    int i;
    WDTCTL = WDTPW | WDTHOLD;
    P1DIR |= BIT0;
    P1OUT |= BIT0;
    for(i=10000; i>0; i--);
    P1OUT &= ~BIT0;
    while(1);
	
}
