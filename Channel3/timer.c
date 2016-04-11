/*
 * timer32.c
 *
 *  Created on: Apr 2, 2016
 *      Author: Steffon Brigman
 *      Description: File contains configuraitons for Timer32 Module and functions using the module
 */

#include "msp.h"
#include <driverlib.h>
#include <grlib.h>
#include "Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#include "functions.h"
#include "macros.h"


void Init_Timer32(void){
	// Periodic timer using 16 bit values
	Timer32_initModule(TIMER32_0_BASE,TIMER32_PRESCALER_16,TIMER32_32BIT,TIMER32_PERIODIC_MODE);

	Timer32_setCount(TIMER32_0_BASE,ONE_SECOND); // set to 1s to update LCD

	// Configure Timer32 interrupt
	Timer32_enableInterrupt(TIMER32_0_BASE);
	Timer32_registerInterrupt(TIMER32_0_INTERRUPT,Timer32_ISRhandler);

	// Must be called after setting timer count
	// Use Timer32_setCountInBackground to update timer values while timer is counting
	Timer32_startTimer(TIMER32_0_BASE,FALSE);
}