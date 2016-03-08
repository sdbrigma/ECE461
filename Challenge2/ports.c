/*
 * ports.c
 *
 *  Created on: Mar 5, 2016
 *      Author: Steffon Brigman
 */

#include "msp432.h"
#include "stdint.h"
#include "functions.h"
#include "macros.h"
#include "driverlib.h"

void Init_Ports(){
	Init_Port2();
	Init_Port4();
	Init_Port5();
	//Init_Port6();
}

void Init_Port2(){
    /* Configure GPIO */
    /* Configure P2.7 as TA2CCR1 PWM output */
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN7,
            GPIO_PRIMARY_MODULE_FUNCTION);

    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN6); // red LED
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN4); // green LED
}

void Init_Port4(){
    /* Configure GPIO */
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN3,
			GPIO_TERTIARY_MODULE_FUNCTION);

}

void Init_Port5(){
    P5SEL0 |= BIT6;						    // Configure P5.6 as Timer A PWM output
    P5SEL1 &= ~BIT6;
    P5DIR |= BIT6;

    	GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN1); // SW2 input at p5.1
	GPIO_clearInterruptFlag(GPIO_PORT_P5, GPIO_PIN1);
	GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN1);
	GPIO_interruptEdgeSelect(GPIO_PORT_P5, GPIO_PIN1, GPIO_HIGH_TO_LOW_TRANSITION);
	Interrupt_enableInterrupt(INT_PORT5);

	GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P3, GPIO_PIN5); // SW2 input at p3.5
	GPIO_clearInterruptFlag(GPIO_PORT_P3, GPIO_PIN5);
	GPIO_enableInterrupt(GPIO_PORT_P3, GPIO_PIN5);
	GPIO_interruptEdgeSelect(GPIO_PORT_P3, GPIO_PIN5, GPIO_HIGH_TO_LOW_TRANSITION);
	Interrupt_enableInterrupt(INT_PORT3);
}

void Init_Port6(){
    /* GPIO Setup */
    P6SEL1 |= BIT0;                         // Configure P6.0 for ADC
    P6SEL0 |= BIT0;
}


