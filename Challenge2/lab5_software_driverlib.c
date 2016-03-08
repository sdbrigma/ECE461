//*****************************************************************************
//
// Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/ 
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
//
//  Redistributions of source code must retain the above copyright 
//  notice, this list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright
//  notice, this list of conditions and the following disclaimer in the 
//  documentation and/or other materials provided with the   
//  distribution.
//
//  Neither the name of Texas Instruments Incorporated nor the names of
//  its contributors may be used to endorse or promote products derived
//  from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
//
// 
//****************************************************************************
//******************************************************************************
//  MSP432 - ADC14, Sample A15, AVcc Ref, Drive PWM output to an LED
//
//   Description: A single sample is made on A15 with reference to AVcc.
//   Manually trigger the conversion. ADC14 sourced by SYSCLK sample (96x)
//   and conversion. In Mainloop MSP432 triggers one conversion, goes to sleep,
//   ADC14 ISR to wake up upon conversion completion. ADC14 result is fed into
//   the PWM output on Timer_A2_CCR1. Device delays for ~10ms before triggering
//   the next conversion
//
//   This version of the lab uses DriverLib APIs to control the core, the
//   ADC14, Timer_A, & other peripherals.
//
//                MSP432P401R
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//        >---|P6.0/A15     P5.6|-->PWM to Blue LED
//
//   Dung Dang
//   Texas Instruments Inc.
//   April 2014
//   Built with Code Composer Studio V6.0
//******************************************************************************

#include "msp432.h"
#include "driverlib.h"

#define MCLK_FREQUENCY 1500000
#define PWM_PERIOD (MCLK_FREQUENCY/5000)

//![Simple Timer_A Config]
/* Timer_A PWM Configuration Parameter */
Timer_A_PWMConfig pwmConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_1,
        PWM_PERIOD,
        TIMER_A_CAPTURECOMPARE_REGISTER_1,
        TIMER_A_OUTPUTMODE_RESET_SET,
        PWM_PERIOD/2,
};

int main(void)
{
    uint32_t adcResult;
    volatile uint32_t i;
    WDT_A_holdTimer();                        // Hold the watchdog


    /* Configure GPIO */
    /* Configure P5.6 as TA2CCR1 PWM output */
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P5, GPIO_PIN6,
            GPIO_PRIMARY_MODULE_FUNCTION);
    /* Configure P6.0 as ADC14 input channel */
    #error "Add DriverLib call to configure P6.0 as ADC14 input channel"
    /* Hint: Use device datasheet I/O schematics to find out which (primary - 0x01,
     * secondary - 0x02, tertiary - 0x03) peripheral function the port pin has for ADC14
     */

    /* Configure Timer_A PWM Module */
    TimerA_generatePWM(TIMER_A2_MODULE,&pwmConfig);


    /* Configure ADC14 Module */
    ADC14_enableModule();
    ADC14_initModule(ADC_CLOCKSOURCE_SYSOSC, ADC_PREDIVIDER_1, ADC_DIVIDER_1, 0);

    /* ADC Memory (ADC_MEM0 A0) in single conversion mode with AVCC reference */
    ADC14_configureSingleSampleMode(ADC_MEM0, false);

    /* Configure conversion memory for ADC_MEM0, AVCC as reference,
     * single-input channel for A15*/
    #error "Add DriverLib call configure conversion memory for ADC_MEM0, AVCC, A15, non-repeated"
    /* Hint: parameters include: MEM0, VREFPOS=AVCC, input channel = A15,
     *                           single conversion (non-repeated)
     */

    /* Configure sample hold time to be 96x ADC_CLK */
    ADC14_setSampleHoldTime(ADC_PULSE_WIDTH_96, ADC_PULSE_WIDTH_96);

    /* Enabling sample timer in manual mode */
    ADC14_enableSampleTimer(ADC_MANUAL_ITERATION);

    /*Enable ADC14 interrupt for memory ADC14MEM0 conversion completion*/
    #error "Add DriverLib call to enable ADC14 interrupt for memory ADC14MEM0 conversion completion"

    /* Enable ADC14 conversion */
    ADC14_enableConversion();

    /* Enabling Interrupts */

    /* Enable ADC14 interrupt in NVIC module*/
    #error "Add DriverLib API (Interrupt_ module prefix) to enable ADC14 interrupt in the NVIC"
    /* Hint: DriverLib module for NVIC uses the Interrupt_ prefix.
     *       See example below for Interrupt_enableMaster()
     */

    /* Enable NVIC master interrupt */
    Interrupt_enableMaster();


    /* Disable device from sleeping after servicing ISR */
    Interrupt_disableSleepOnIsrExit();



    while (1)
    {
        ADC14_toggleConversionTrigger();        // Trigger the initial conversion
        PCM_gotoLPM0();	                		// alternatively __sleep(); also works

        /* Get ADC14 conversion result for ADC14MEM0, finish the code below */
        #error "Uncomment the line below, use DriverLib call to store ADC14MEM0 conversion result to adcResult"
        // adcResult =

        /* Convert result in the range of [0,16384] to [0,2000]
         * for the PWM duty cycle
         */

        pwmConfig.dutyCycle = PWM_PERIOD * adcResult / 16384;
        if (pwmConfig.dutyCycle == 0)
            pwmConfig.dutyCycle  = 1;

		/* Change Timer_A2, CCR1 value to new dutyCycle value */
        Timer_A_setCompareValue(TIMER_A2_MODULE, TIMER_A_CAPTURECOMPARE_REGISTER_1, pwmConfig.dutyCycle);


        /* Delay ~10ms until the next ADC sample */
        for (i=0;i<3000;i++);

        /* Optional exercise: add another Timer_A instance as an interval timer
        * and use sleep mode*/

    }

}

void adc14IsrHandler(void)
{
    ADC14_clearInterruptFlag(ADC_INT0);
}
