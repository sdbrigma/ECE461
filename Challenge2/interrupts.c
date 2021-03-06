/*
 * interrupts.c
 *
 *  Created on: Mar 5, 2016
 *      Author: Steffon Brigman
 */

#include "msp432.h"
#include "stdint.h"
#include "driverlib.h"
#include "functions.h"
#include "macros.h"

/*void port5IsrHandler(){ // SW1
	burglar = 1;
}*/

/*void port3IsrHandler(){//SW2
	TA0CTL = TIMER_A_STOP_MODE;
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; // SysTick enable module
	SysTick->LOAD = 9; // SysTick load period for 10

	while(1){
		if(SysTick->VAL > 4){
			SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk); // disable SysTick module
			if(alarm_state){
				alarm_system_state(FALSE);
				alarm_state = 0;
			}
			else{
				alarm_system_state(TRUE);
				alarm_state = 1;
			}
			break;
		}
	}
}*/

/*void port1IsrHander(){
	while(!(P1IN & BIT1)){// S2 on msp432
		burglar = 1;
		GPIO_clearInterruptFlag(GPIO_PORT_P1,GPIO_PIN1);
	}

	while(!(P1IN & BIT4)){// S1 on msp432
		GPIO_clearInterruptFlag(GPIO_PORT_P1,GPIO_PIN4);
		TA0CTL = TIMER_A_STOP_MODE;
		SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; // SysTick enable module
		SysTick->LOAD = 9; // SysTick load period for 10

		while(1){
			if(SysTick->VAL > 0){
				SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk); // disable SysTick module
				if(alarm_state){
					alarm_state = 0;
				}
				else{
					alarm_state = 1;
				}
				break;
			}
		}
	}
}*/
volatile uint32_t adc;
void adc14IsrHandler(){
	adc = ADC14->MEM[10];
	if(adc >= BURGLAR){
		burglar = 1;
	}
	ADC14_clearInterruptFlag(ADC_INT10);
}
