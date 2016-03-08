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
	Timer_A_PWMConfig doorbell1 =
	{
	        TIMER_A_CLOCKSOURCE_SMCLK,
	        TIMER_A_CLOCKSOURCE_DIVIDER_1,
	        32000,
	        TIMER_A_CAPTURECOMPARE_REGISTER_4,
	        TIMER_A_OUTPUTMODE_RESET_SET,
	        DING1,
	};
	Timer_A_generatePWM(TIMER_A0_MODULE,&doorbell1);
	delay_200ms();

	Timer_A_PWMConfig doorbell2 =
	{
	        TIMER_A_CLOCKSOURCE_SMCLK,
	        TIMER_A_CLOCKSOURCE_DIVIDER_1,
	        32000,
	        TIMER_A_CAPTURECOMPARE_REGISTER_4,
	        TIMER_A_OUTPUTMODE_RESET_SET,
	        DING2,
	};
	Timer_A_generatePWM(TIMER_A0_MODULE,&doorbell2);
	delay_200ms();

	Timer_A_PWMConfig doorbell3 =
	{
	        TIMER_A_CLOCKSOURCE_SMCLK,
	        TIMER_A_CLOCKSOURCE_DIVIDER_1,
	        32000,
	        TIMER_A_CAPTURECOMPARE_REGISTER_4,
	        TIMER_A_OUTPUTMODE_RESET_SET,
	        DING3,
	};
	Timer_A_generatePWM(TIMER_A0_MODULE,&doorbell3);
	delay_200ms();
    TA0CTL = TIMER_A_STOP_MODE;
}

void doorbell(){
	TA0CTL = TIMER_A_UP_MODE;
	Timer_A_PWMConfig doorbell1 =
	{
	        TIMER_A_CLOCKSOURCE_SMCLK,
	        TIMER_A_CLOCKSOURCE_DIVIDER_1,
	        32000,
	        TIMER_A_CAPTURECOMPARE_REGISTER_4,
	        TIMER_A_OUTPUTMODE_RESET_SET,
	        DING1,
	};
	Timer_A_generatePWM(TIMER_A0_MODULE,&doorbell1);
	delay(ONE_SEC*2);

	Timer_A_PWMConfig doorbell2 =
	{
	        TIMER_A_CLOCKSOURCE_SMCLK,
	        TIMER_A_CLOCKSOURCE_DIVIDER_1,
	        1000,
	        TIMER_A_CAPTURECOMPARE_REGISTER_4,
	        TIMER_A_OUTPUTMODE_RESET_SET,
	        50,
	};
	Timer_A_generatePWM(TIMER_A0_MODULE,&doorbell2);
	delay(ONE_SEC);
	TA0CTL = TIMER_A_STOP_MODE;

}

void burglar_alarm(){
	TA0CTL = TIMER_A_UP_MODE;
	Timer_A_PWMConfig firealarm =
	{
	        TIMER_A_CLOCKSOURCE_SMCLK,
	        TIMER_A_CLOCKSOURCE_DIVIDER_1,
	        32000,
	        TIMER_A_CAPTURECOMPARE_REGISTER_4,
	        TIMER_A_OUTPUTMODE_RESET_SET,
	        DING2,
	};
	Timer_A_generatePWM(TIMER_A0_MODULE,&firealarm);
}

