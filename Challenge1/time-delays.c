/*
 * time-delays.c
 *
 *  Created on: Feb 5, 2016
 *      Author: Steffon Brigman
 */

#include "msp432.h"
#include "driverlib.h"

#include "string.h"
#include "macros.h"
#include "functions.h"

void delay_1sec(void)      	// 1 second delay for 1.5 MHz clock
{
	int  dcntr;			// delay counter variable

	for (dcntr=0;dcntr<(800000);dcntr++);		//~1 second delay loop
	return;
}

void delay_200ms(void)		// 1 ms delay for 1.5 MHz system clock
{
	int  dcntr;			// delay counter variable

	for (dcntr=0;dcntr<(800000/4);dcntr++);	// ~0.20 second delay loop
	return;
}


