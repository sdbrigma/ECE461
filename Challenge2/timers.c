/*
 * timers.c
 *
 *  Created on: Mar 5, 2016
 *      Author: Steffon Brigman
 */


#include "msp432.h"
#include "stdint.h"
#include "functions.h"
#include "macros.h"
#include "driverlib.h"

Timer_A_PWMConfig pwmConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_1,
        PWM_PERIOD,
        TIMER_A_CAPTURECOMPARE_REGISTER_4,
        TIMER_A_OUTPUTMODE_RESET_SET,
        PWM_PERIOD/2,
};

void Init_Timers(){
    /* Configure Timer_A PWM Module */
    Timer_A_generatePWM(TIMER_A0_BASE,&pwmConfig);
    TA0CTL = TIMER_A_STOP_MODE;
    //TA0CTL = TIMER_A_UP_MODE;
}

void Init_SysTick(uint32_t period){
	// Systick configuration
	SysTick_enableModule();
	SysTick_setPeriod(period);
}

