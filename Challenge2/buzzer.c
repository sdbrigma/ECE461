/*
 * buzzer.c
 *
 *  Created on: Mar 5, 2016
 *      Author: Steffon Brigman
 */

#include "msp432.h"
#include "stdint.h"
#include "functions.h"
#include "macros.h"
#include "driverlib.h"

void fire_alarm(){
	TA0CTL = TIMER_A_UP_MODE;
	Timer_A_PWMConfig firealarm =
	{
	        TIMER_A_CLOCKSOURCE_SMCLK,
	        TIMER_A_CLOCKSOURCE_DIVIDER_1,
	        32000,
	        TIMER_A_CAPTURECOMPARE_REGISTER_4,
	        TIMER_A_OUTPUTMODE_RESET_SET,
	        DING3/2,
	};
	Timer_A_generatePWM(TIMER_A0_BASE,&firealarm);
    //TA0CTL = TIMER_A_STOP_MODE;
}

void doorbell(){
	TA0CTL = TIMER_A_STOP_MODE;
	Timer_A_PWMConfig doorbell1 =
	{
	        TIMER_A_CLOCKSOURCE_SMCLK,
	        TIMER_A_CLOCKSOURCE_DIVIDER_4,
	        32000,
	        TIMER_A_CAPTURECOMPARE_REGISTER_4,
	        TIMER_A_OUTPUTMODE_RESET_SET,
	        3200,
	};
	TA0CTL = TIMER_A_UP_MODE;
	Timer_A_generatePWM(TIMER_A0_BASE,&doorbell1);

	Init_SysTick(16777215);
	bool i = TRUE;

	while(i){// wait so that the buzzer tone lasts for 2 seconds
		if((SysTick->VAL) == 160){
			SysTick_disableModule();
			i = FALSE;
		}
	}

	TA0CTL = TIMER_A_STOP_MODE;
}

void burglar_alarm(){
	TA0CTL = TIMER_A_UP_MODE;
	Timer_A_PWMConfig burglar =
	{
	        TIMER_A_CLOCKSOURCE_SMCLK,
	        TIMER_A_CLOCKSOURCE_DIVIDER_1,
	        32000,
	        TIMER_A_CAPTURECOMPARE_REGISTER_4,
	        TIMER_A_OUTPUTMODE_RESET_SET,
	        DING2,
	};
	Timer_A_generatePWM(TIMER_A0_BASE,&burglar);
	//TA0CTL = TIMER_A_STOP_MODE;
}


