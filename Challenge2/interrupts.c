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


void port5IsrHandler(){
	doorbell();
}

void port3IsrHandler(){
	burglar_alarm();
}

volatile uint32_t adcResult;
void adc14IsrHandler(){
	adcResult = ADC14_getResult(ADC_MEM10);
	if(adcResult >= BURGLAR){
		fire_alarm();
	}
	ADC14_clearInterruptFlag(ADC_INT10);
}