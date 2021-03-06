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
// MSP432 ADC14 Lab
//
//****************************************************************************
//******************************************************************************
//  MSP432 - ADC14, Sample A15, AVcc Ref, Drive PWM output to an LED
//
//   Description: A single sample is made on A15 with reference to AVcc.
//   Manually trigger the conversion. ADC14 sourced by SYSCLK sample (96x)
//   and conversion. In Mainloop MSP432 triggers one conversion, goes to sleep,
//   ADC14 ISR to wake up upon conversion completion. ADC14 result is fed into
//   the PWM output on TimerA2_CCR1. Device delays for ~10ms before triggering
//   the next conversion.
//   This version of the lab uses direct register accesses to control the core, the
//   ADC14, TimerA, & other peripherals.
//
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
#include "stdint.h"
#include "functions.h"
#include "driverlib.h"
#include "macros.h"

extern bool alarm_state = FALSE;
extern bool burglar = FALSE;
extern bool doorbell_signal = FALSE;
extern bool fire_signal = FALSE;
uint32_t lux;
extern volatile uint32_t adc;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    Init_Clocks();
    Init_Ports();
    Init_Adc();
    Init_Timers();
    /* Initialize I2C communication */
    Init_I2C_GPIO();
    I2C_init();
    /* Initialize OPT3001 digital ambient light sensor */
    OPT3001_init();

    alarm_system_state(alarm_state); // activate alarm

    WDTCTL = WDTPW |WDTSSEL_3|WDTIS_4|WDTCNTCL;		//start WDT counter with a 1 second expiration

    //MAP_PCM_gotoLPM0(); // enter low power mode

    while (1)
    {
    		MAP_WDT_A_clearTimer();
    		lux = OPT3001_getLux();
    		Switch_Process();
    		if(alarm_state && !burglar && !fire_signal){// do not activate burglar alarm if fire alarm is already active
    			burglar_alarm();
    			//burglar = 1;
    		}
    		if(lux > FIRE){
    			TA0CTL = TIMER_A_STOP_MODE;
    			fire_alarm();
    			fire_signal = TRUE;
    			while(1){
    				if(!fire_signal){break;}
    				//TA0CTL = TIMER_A_STOP_MODE;  //stop buzzer
    				MAP_WDT_A_clearTimer();
    				Switch_Process();
    			}
    			fire_signal = FALSE;
    		}
    		ADC14_toggleConversionTrigger();        // Trigger the initial conversion
    		if(doorbell_signal){
    			doorbell();
    			doorbell_signal = 0;
    		}
    }

}
