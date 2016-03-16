/*
 * alarm-state.c
 *
 *  Created on: Mar 9, 2016
 *      Author: Steffon Brigman
 */

#include "msp432.h"
#include "stdint.h"
#include "driverlib.h"
#include "functions.h"
#include "macros.h"

void alarm_system_state(bool state){
	if(state){// activate if true
		//P2DIR &= ~BIT0;
	    P2OUT &= ~BIT0;	// red LED
		//P2DIR |= BIT1;
		P2OUT |= BIT1;	// green LED
		TA0CTL = TIMER_A_STOP_MODE; // turn off alarm;
		alarm_state = 1;
		fire_signal = 1;
	}
	else{
		//P2DIR &= ~BIT1;
		P2OUT &= ~BIT1;	// green LED
		//P2DIR |= BIT0;
		P2OUT |= BIT0;	// red LED
	    TA0CTL = TIMER_A_STOP_MODE; // turn off alarm;
	    alarm_state = 0;
	    fire_signal = 1;
	}
}
