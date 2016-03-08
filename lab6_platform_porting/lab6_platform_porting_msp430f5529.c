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
// MSP430 <---> MSP432 Platform Porting lab
//
//****************************************************************************
//******************************************************************************
//  MSP430 - RTC interval, ADC14, single sequence, Timer_A 3-channel PWM
//
//   This lab exercises a combination of DriverLib APIs, register accesses, as well
//   as compiler intrinsics. The goal of the lab is to convert existing MSP430 code
//   using a combination of the above SW components to MSP432. The use of device's
//   datasheet and user's guide might be required in order to complete the lab.

//   Description: Device operates in LPM3, with RTC is configured with pre-scaler
//   event interrupt once every 31ms.  RTC ISR triggers an ADC12 3-channel
//   sequence conversion, and then goes to sleep mode. ADC12 conversion completion
//   triggers ADC12 interrupt, ADC12 ISR returns to active mode.
//   Timer_A is configured with 3 PWM output channels. ADC results are converted
//   into duty cycles for the 3 PWM channels.
//
//
//
//                MSP430F5529
//             -----------------------
//         /|\|                   XIN|-
//          | |                      |
//          --|RST               XOUT|-
//            |                      |
//        >---|P6.0/A0   		     |
//        >---|P6.1/A1   (TA0.4) P1.5|-->PWM to Green LED
//            |          (TA0.3) P1.4|-->PWM to Blue LED
//
//
//
//   Dung Dang
//   Texas Instruments Inc.
//   April 2014
//   Built with Code Composer Studio V6.0Beta4
//******************************************************************************

/* @@@@@Step 1: Change header file names
 * 1) msp430.h --> msp432.h
 * 2) all driverlib header files are now combined into one: "driverlib.h"
 */
#include <msp430.h> 
#include "adc12_a.h"
#include "gpio.h"
#include "pmm.h"
#include "ucs.h"

/* @@@@Step 2: Change MCLK_FREQUENCY, we want to use 48MHz */
#define MCLK_FREQUENCY 2500000
#define PWM_PERIOD (MCLK_FREQUENCY/5000)


void Step3InitializeCoreSystem(void)
{

/* @@@@Step 3: Core system including power, clock, and memory will require
 * new code, as new platform has different requirements
 * 1) Change Voltage Core Level to 1 (MSP432 has 2 core levels)
 * 2) Change flash memory wait state to 2
 * 3) Change system DCO frequency to 48MHz
 * 4) Enable SRAM bank rententions in Deep-sleep mode */
	PMM_setVCore(PMM_CORE_LEVEL_3);
	UCS_initFLLSettle(25000,765);
}

void Step4ConfigureTimerAUsingRegisterAccess(void)
{

/* @@@@Step 4: Configure TimerA
 * 1) Check if all of Timer_A & GPIO code is compatible on MSP432 */


	/* GPIO Setup for P1.4 */
	/* Configure peripheral function for LED pins */
	P1SEL |= BIT4 ;
	P1DIR |= BIT4 ;


	/* Configure TimerA */
	TA0CCR0 = PWM_PERIOD;                   // PWM Period
	TA0CCTL3 = OUTMOD_7;                    // TA0CCR3 reset/set
	TA0CCR3 = PWM_PERIOD/2;                 // TA0CCR3 PWM duty cycle
	TA0CTL = TASSEL__SMCLK | MC__UP | TACLR;  // SMCLK, up mode, clear TAR
}

void Step5ConfigureRtcUsingRegisterAccess()
{
/* @@@@Step 5: Configure RTC
 * 1) Check if all of RTC code is compatible on MSP432
 * 2) Don't forget the extra NVIC step to enable interrupt */

    RTCCTL01 = RTCHOLD;                     //  RTC hold
    /* Enable prescaler interrupt, interval  = (1/32)s */
    RTCPS0CTL = 0;
    RTCPS1CTL = RT1SSEL_2 | RT1PSDIV0 | RT1PSDIV1  | RT1PSIE;
    RTCCTL01 &= ~(RTCHOLD);                  // Start RTC
}

void Step6ConfigureADC14UsingDriverLib()
{
/* @@@@Step 6: ADC12 --> ADC14, this will require some API updates
 * 1) Does the GPIO API work?
 * 2) We will use 14-bit resolution for MSP432, so change resolution setting
 * 3) Any change in the ADC14_Init function?
 * 4) Any change in the ADC14_setupSamplingTimer?
 * 5) Any change in the ADC14_memoryConfigure?
 * 6) What about interrupts?
 * 7) What about NVIC? */

	/* Pin P6.0 = X-axis  -->  Channel A0
	 * @@@Note:It could be different Pins for MSP432 (P6.0,4.0 & 4.2)
	 * Homework: add a 2nd ADC14 channel
	 * Pin P6.1 = Y-axis  -->  Channel A1
	 * Pin P6.2 = Z-axis  -->  Channel A2
	 */

	/* Configuring GPIOs for Analog In */
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN0 );

	ADC12_A_setResolution(ADC12_A_BASE, ADC12_A_RESOLUTION_12BIT);
	ADC12_A_init(ADC12_A_BASE, ADC12_A_SAMPLEHOLDSOURCE_SC, ADC12_A_CLOCKSOURCE_ADC12OSC, ADC12_A_CLOCKDIVIDER_1);



	/* Configuring ADC Memory ADC_MEM0 with no repeat with VCC reference */
	ADC12_A_setupSamplingTimer(ADC12_A_BASE, ADC12_A_CYCLEHOLD_16_CYCLES,
							   ADC12_A_CYCLEHOLD_4_CYCLES, ADC12_A_MULTIPLESAMPLESDISABLE);

	ADC12_A_memoryConfigure(ADC12_A_BASE, ADC12_A_MEMORY_0, ADC12_A_INPUT_A0,
							ADC12_A_VREFPOS_AVCC, ADC12_A_VREFNEG_AVSS, ADC12_A_ENDOFSEQUENCE);

	/* Enable memory buffer 0 interrupt */
	 ADC12_A_clearInterrupt(ADC12_A_BASE, ADC12_A_IFG0);
	 ADC12_A_enableInterrupt(ADC12_A_BASE, ADC12_A_IE0);

	 ADC12_A_enable(ADC12_A_BASE);

}
int main(void) {
    int16_t xAxis, dutyCycle;
    volatile uint32_t i;

    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    Step1InitializeCoreSystem();
    Step2ConfigureTimerAUsingRegisterAccess();
    Step3ConfigureRtcUsingRegisterAccess();
    Step4ConfigureADC14UsingDriverLib();


    while (1)
    {

/* @@@@Step 7: What is the MSP432 equivalent of this intrinsic? */
        //Enter LPM3, Enable interrupts
        __bis_SR_register(LPM3_bits + GIE);



/* @@@@Step 8: Double-check application code for compatibility */
        xAxis= ADC12MEM0 - 2048;
        if (xAxis<0)
           xAxis =- xAxis;

        /* Map the x-axis accelerometer result to PWM duty cycle */
        dutyCycle = PWM_PERIOD * xAxis / 1750;
        if (dutyCycle == 0)
           dutyCycle  = 5;
        TA0CCR3 = dutyCycle;                // Change PWM duty cycle based on ADC result
    }
}


/* @@@@@Step 9: #pragma vector support for MSP432 is still under work
 * 1) Remove #pragma vector & __interrupt
 * 2) Insert the ADC ISR stub into the interrupt vector table inside the msp432_startup_ccs.c
 */
#pragma vector=ADC12_VECTOR
__interrupt
void adc12IsrHandler(void)
{
/* @@@@@Step 10: ADC14 interrupt handler
 * 1) Option 1: using register access code
 *    Note that ADC14 has a clear interrupt flag register that requires writing 1 
 *    to instead of clearing the bit
 *    Option 2: using ADC14 DriverLib API    
 * 2) Use SLEEPONEXIT feature of MSP432 instead of the __bic_SR_register_on_exit() intrinsic
 */
	ADC12IFG &= ~(ADC12IFG0);
	__bic_SR_register_on_exit(LPM3_bits);
}
/* @@@@@Step 11: #pragma vector support for MSP432 is still under work
 * 1) Remove #pragma vector & __interrupt
 * 2) Insert the RTC ISR stub into the interrupt vector table inside the msp432_startup_ccs.c
 */
#pragma vector=RTC_VECTOR
__interrupt
void rtcIsrHandler(void)
{
/* @@@@@Step 12: RTC interrupt handler
 * 1) Double-check the ISR handler for RTC
 * 2) ADC12 API might need some update too
 */

    /* Clear RTC pre-scaler event interrupt flag */

    RTCPS1CTL &= ~ RT1PSIFG;
    ADC12_A_startConversion(ADC12_A_BASE, ADC12_A_MEMORY_0, ADC12_A_SINGLECHANNEL);
    // Go back to sleep

}
