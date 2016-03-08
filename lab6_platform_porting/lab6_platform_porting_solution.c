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
//  MSP430 - RTC interval, ADC14, 3-channel sequence, Timer_A 3-channel PWM
//
//   Lab Description:
//   The goal of the lab is to convert existing MSP430 code in
//   lab6_platform_porting_msp430f5529 project to MSP432 platform  using a
//   combination of DriverLib APIs, register accesses, as well as compiler
//   intrinsics. In addition to exercising the SW components listed, the use
//   of datasheet and user's guide might be required in order to complete the lab.
//
//   Project Description:
//   Device operates in DSL, with RTC is configured with pre-scaler
//   event interrupt once every 31ms.  RTC ISR triggers an ADC14 3-channel
//   sequence conversion, and then goes to LPM0 mode. ADC14 conversion completion
//   triggers ADC14 interrupt, ADC14 ISR returns to active mode.
//   Timer_A is configured with 3 PWM output channels. ADC results are converted
//   into duty cycles for the 3 PWM channels.
//
//   Fill in the A?? below based on the datasheet device pin-out.
//
//                MSP432P401R
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//        >---|P6.1/A??     P2.0|-->PWM to Red LED(homework)
//        >---|P4.0/A??     P2.1|-->PWM to Green LED(homework)
//        >---|P4.1/A??     P2.2|-->PWM to Blue LED
//
//
//
//   Dung Dang
//   Texas Instruments Inc.
//   April 2014
//   Built with Code Composer Studio V6.0
//******************************************************************************

/* @@@@Step 1: Change header file names
 * 1) msp430.h --> msp432.h
 * 2) all driverlib header files are now combined into one: "driverlib.h"
 */
#include "msp432.h"
#include "driverlib.h"



/* @@@@Step 2: Change MCLK_FREQUENCY, we want to use 48MHz */
#define MCLK_FREQUENCY 48000000
#define PWM_PERIOD (MCLK_FREQUENCY/5000)


void Step3InitializeCoreSystem(void)
{

/* @@@@Step 3: Core system including power, clock, and memory will require
 * new code, as new platform has different requirements
 * 1) Change Voltage Core Level to 1 (MSP432 has 2 core levels)
 * 2) Change flash memory wait state to 2
 * 3) Change system DCO frequency to 48MHz
 * 4) Enable SRAM bank rententions in LPM3 mode */
    
    /* Power module: VCore level = 1 */
    PCM_setCoreVoltageLevel(PCM_VCORE1);

	/* Flash module: Wait states = 2 */
    /* Using DriverLib for Bank 0 */
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    /* Using register access for Bank 1 */
    FlashCtl_setWaitState(FLASH_BANK1, 2);

    /* Clock module: DCO = 48MHz */
    CS_setDCOCenteredFrequency (CS_DCO_FREQUENCY_48);

    /* Enable SRAM bank rententions in LPM3 mode*/
    SysCtl_enableSRAMBankRetention(SYSCTL_SRAM_BANK7);
}

void Step4ConfigureTimerAUsingRegisterAccess(void)
{

/* @@@@Step 4: Configure TimerA
 * 1) Check if all of Timer_A & GPIO code is compatible on MSP432 */

	/* GPIO Setup for Pin2.2 */
    /* Configure peripheral function AND drive-strength for LED pins */
    P2SEL0 |= BIT2;
    P2SEL1 &= ~BIT2;
    P2DIR |= BIT2;
    /* Port Map setup for Pin2.2 */
    PMAPKEYID = 0x2D52;                      // Enable Write-access to modify port mapping registers
    P2MAP23 = PM_TA0CCR3A;                   // P2.2 <--- PM_TA0.3
    // Note that P2.3 is not used

    PMAPKEYID = 0;                            // Disable Write-Access to modify port mapping registers

    /* Configure TimerA */
    TA0CCR0 = PWM_PERIOD;                   // PWM Period
    TA0CCTL3 = OUTMOD_7;                    // CCR3 reset/set
    TA0CCR3 = PWM_PERIOD/2;                 // CCR3 PWM duty cycle
    TA0CTL = TASSEL__SMCLK | MC__UP | TACLR;  // SMCLK, up mode, clear TAR
}

void Step5ConfigureRtcUsingRegisterAccess()
{
/* @@@@Step 5: Configure RTC
 * 1) Check if all of RTC code is compatible on MSP432
 * 2) Don't forget the extra NVIC step to enable interrupt */

    RTCCTL0_H = RTCKEY_H;                   // Unlock RTC
    RTCCTL1 |= RTCHOLD;                     // RTC hold
    /* Enable prescaler interrupt, interval  = (1/32)s, dividied by 16 */
    RTCPS1CTL = RT1IP__16 | RT1PSIE;
    RTCCTL1 &= ~(RTCHOLD);                  // Start RTC
    RTCCTL0_H = 0;                          // Lock RTC module

    NVIC_ISER0 = 1 << ((INT_RTC_C - 16) & 31); // Enable RTC interrupt in NVIC module
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

	/* Pin P6.1 = X-axis  -->  Channel A14
	 * @@@Note:It could be different Pins for MSP432
	 * Homework: add a 2nd ADC14 channel
	 * Pin P4.0 = Y-axis  -->  Channel A13
	 * Pin P4.2 = Z-axis  -->  Channel A11
	 */

    /* Configuring GPIOs for Analog In */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,
            GPIO_PIN1, GPIO_TERTIARY_MODULE_FUNCTION);

    /* Change resolution setting to 14-bit */
    MAP_ADC14_setResolution(ADC_14BIT);

    /* Init ADC14 */
    MAP_ADC14_initModule(ADC_CLOCKSOURCE_SYSOSC, ADC_PREDIVIDER_1, ADC_DIVIDER_1, 0);

    /* Configuring ADC Memory ADC_MEM0 with no repeat with VCC reference */
    ADC14_configureSingleSampleMode(ADC_MEM0, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM0,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A14, false);

    MAP_ADC14_setSampleHoldTime(ADC_PULSE_WIDTH_16, ADC_PULSE_WIDTH_16);

    /* Setting up the sample timer to automatically step through the sequence
     * convert.
     */
    MAP_ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

    /* Enabling the interrupt when a conversion on channel 0 
     *  is complete and enabling conversions */
    MAP_ADC14_enableInterrupt(ADC_INT0);
    /* Enabling Interrupts */
    MAP_Interrupt_enableInterrupt(INT_ADC14);
    Interrupt_enableInterrupt(INT_ADC14);
    SCB_SCR &= ~SCB_SCR_SLEEPONEXIT;        // Wake up on exit from ISR
    __enable_interrupt();                   // intrinsic to enable NVIC global/master interrupt
    /* Alternatively, you can also use the DriverLib API */
    // MAP_Interrupt_enableMaster();        //

    MAP_ADC14_enableModule();

}
int main(void) {
    int16_t xAxis, dutyCycle;
    volatile uint32_t i;

    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    Step3InitializeCoreSystem();
    Step4ConfigureTimerAUsingRegisterAccess();
    Step5ConfigureRtcUsingRegisterAccess();
    Step6ConfigureADC14UsingDriverLib();


    while (1)
    {

/* @@@@Step 7: What is the MSP432 equivalent of this intrinsic? */
        //Enter LPM3, Enable interrupts
    	__low_power_mode_3();               // Goto LPm3 w/o SW checking
        /* Alternatively, a more fool-proof API with error/state checking can be used */
        // PCM_gotoLPM3();             // Go to deep sleep



/* @@@@Step 8: Double-check application code for compatibility */        

        /* Retrieving ADC14 memory results */
        xAxis= (ADC14MEM0 &0x3FFF) - 8192;
        if (xAxis<0)
            xAxis =- xAxis;

        /* Map the x-axis accelerometer results to PWM duty cycles */
        dutyCycle = PWM_PERIOD * xAxis / 7000;
        if (dutyCycle == 0)
            dutyCycle  = 5;
        TA0CCR3 = dutyCycle;                // Change PWM duty cycle based on ADC result
    }
}

/* @@@@@Step 9: #pragma vector support for MSP432 is still under work
 * 1) Remove #pragma vector & __interrupt
 * 2) Insert the ADC ISR stub into the interrupt vector table inside the msp432_startup_ccs.c
 */
void adc14IsrHandler(void)
{
/* @@@@@Step 10: ADC14 interrupt handler
 * 1) Option 1: using register access code
 *    Note that ADC14 has a clear interrupt flag register that requires writing 1 
 *    to instead of clearing the bit
 *    Option 2: using ADC14 DriverLib API    
 * 2) Use SLEEPONEXIT feature of MSP432 instead of the __bic_SR_register_on_exit() intrinsic
 */
    /* Clear ADC14 IFG */
    ADC14_clearInterruptFlag(ADC_INT0);

    Interrupt_disableSleepOnIsrExit();      // Device to wake up from this ISR
    /* Alternatively, you can also use the following register-access code line */
    //SCS_SCR &= ~SCS_SCR_SLEEPONEXIT;      // Device to wake up from this ISR
}
/* @@@@@Step 11: #pragma vector support for MSP432 is still under work
 * 1) Remove #pragma vector & __interrupt
 * 2) Insert the RTC ISR stub into the interrupt vector table inside the msp432_startup_ccs.c
 */
void rtcIsrHandler(void)
{
/* @@@@@Step 12: RTC interrupt handler
 * 1) Double-check the ISR handler for RTC
 * 2) ADC12 API might need some update too
 */

    /* Clear RTC pre-scaler event interrupt flag */
    RTCCTL0_H = RTCKEY_H;
    RTCPS1CTL &= ~ RT1PSIFG;
    RTCCTL0_H = 0;                          // Lock RTC module
    //RTC_C_clearInterruptFlag(RTC_C_PRESCALE_TIMER1_INTERRUPT);

    /* Triggering the start of the ADC14 sample sequence*/
    MAP_ADC14_enableConversion();
    MAP_ADC14_toggleConversionTrigger();

    // Go back to sleep
    SCB_SCR |= SCB_SCR_SLEEPONEXIT;        // Device not to wake up from this ISR
    /* Make sure device goes back to sleep, not deep-sleep mode */
    SCB_SCR &= ~ SCB_SCR_SLEEPDEEP;



}
