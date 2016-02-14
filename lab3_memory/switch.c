/*
 * switch.c
 *
 *  Created on: Feb 14, 2016
 *      Author: Steffon Brigman
 */

#include "msp432.h"
#include "driverlib.h"

#include "string.h"
#include "macros.h"
#include "functions.h"

void Switch_Process(){
	uint32_t buttonPushed = 0;
	while(!(P1IN & BIT4)){
		P1OUT |= BIT0;				// turn red LED on
		delay_1sec();				// wait 1 second
		P1OUT &= ~BIT0;				// turn red LED off
		WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
		WDTCTL = WDTPW |WDTSSEL_3|WDTIS_4|WDTCNTCL;		//start WDT counter with a 1 second expiration
		buttonPushed = 1;
	}
}

