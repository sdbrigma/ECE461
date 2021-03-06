/*
 * switch.c
 *
 *  Created on: Mar 15, 2016
 *      Author: marybiggs
 */

#include "msp432.h"
#include "stdint.h"
#include "functions.h"
#include "macros.h"
#include "driverlib.h"


void Switch_Process(){
	while(!(P1IN & BIT1)){// S1 on msp432
		if(!fire_signal && !burglar){// only activate doorbell if no alarms are active
			doorbell_signal = 1;
		}
	}

	while(!(P1IN & BIT4)){// S2 on msp432
		TA0CTL = TIMER_A_STOP_MODE;

		// Debouncing
		SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; // SysTick enable module
		SysTick->LOAD = 6000000; // SysTick load period value

		while(1){
			if(SysTick->VAL == 0){
				SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk); // disable SysTick module
				if(alarm_state){
					alarm_state = 0;
					alarm_system_state(alarm_state);
				}
				else{
					alarm_state = 1;
					alarm_system_state(alarm_state);
				}
				break;
			}
		}
	}
}
