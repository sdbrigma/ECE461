/*
 * interrupts.c
 *
 *  Created on: Feb 14, 2016
 *      Author: marybiggs
 */

#include "msp432.h"
#include "driverlib.h"

#include "string.h"
#include "macros.h"
#include "functions.h"



void Port1IsrHandler(void)
{
	uint32_t status;
	status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
	GPIO_clearInterruptFlag(GPIO_PORT_P1, status);
	//disable interrupt for a while
	GPIO_disableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
	/* Toggling the output on the LED */
	//buttonPushed = 1;
	/* Wake up from GPIO interrupt */
	P1OUT |= BIT0;				// turn red LED on
	delay_1sec();				// wait 1 second
	P1OUT &= ~BIT0;				// turn red LED off
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	WDTCTL = WDTPW |WDTSSEL_3|WDTIS_4|WDTCNTCL;		//start WDT counter with a 1 second expiration
	__no_operation();
	Interrupt_disableSleepOnIsrExit();
}