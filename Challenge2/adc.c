/*
 * adc.c
 *
 *  Created on: Mar 5, 2016
 *      Author: Steffon Brigman
 */

#include "msp432.h"
#include "stdint.h"
#include "driverlib.h"
#include "functions.h"
#include "macros.h"

void Init_Adc(){
    /* Configure ADC14 Module */
    ADC14_enableModule();
    ADC14_initModule(ADC_CLOCKSOURCE_SYSOSC, ADC_PREDIVIDER_1, ADC_DIVIDER_1, 0);

    /* ADC Memory (ADC_MEM0 A10) in single conversion mode with AVCC reference for mic*/
    ADC14_configureSingleSampleMode(ADC_MEM10,false);
    ADC14_configureConversionMemory(ADC_MEM10, ADC_VREFPOS_AVCC_VREFNEG_VSS,
               ADC_INPUT_A10, false);

    /* Set ADC result format to unsigned binary */
    ADC14_setResultFormat(ADC_UNSIGNED_BINARY);
    ADC14->MCTL[10] = ADC_INPUT_A10; // set ADC10 as input channel

    /* Enabling sample timer in manual mode and interrupts*/
    ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
    ADC14_enableInterrupt(ADC_INT10);
    ADC14_enableConversion();

    /* Enabling Interrupts */

    Interrupt_enableInterrupt(INT_ADC14);
    Interrupt_enableMaster();
    Interrupt_disableSleepOnIsrExit();      // Wake up on exit from ISR
}

