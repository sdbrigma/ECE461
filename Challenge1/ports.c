/*
 * ports.c
 *
 *  Created on: Feb 5, 2016
 *      Author: Steffon Brigman
 */

#include "msp432.h"
#include "driverlib.h"

#include "string.h"
#include "macros.h"
#include "functions.h"

void Init_Ports()			//	port initialization function
{
	Init_Port1();
	Init_Port2();
}

void Init_Port1(){
	P1DIR |= BIT0;			// make P1.0 an output

	//P1IV |= BIT4;
	P1DIR &= ~BIT4;			// make P1.4 and input
	P1REN |= BIT4;			// enable pull resistor on P1.4
	P1OUT |= BIT4;			// make it a pull-up resistor
	P1IE |= BIT4;			// enable p1.4 interrupt
	P1IES |= BIT4;			// P1.4 rising edge interrupt
}

void Init_Port2(){
	P2DIR |= BIT1;			// make P2.1 an output
}
