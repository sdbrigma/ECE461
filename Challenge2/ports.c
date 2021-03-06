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
	Init_Port1();
	//Init_Port3();
	Init_Port4();
	Init_Port5();
}

void Init_Port1(){

	//S1 port configuration
	P1DIR &= ~BIT1;			// make P1.4 and input
	P1REN |= BIT1;			// enable pull resistor on P1.4
	P1OUT |= BIT1;			// make it a pull-up resistor
	P1IE |= BIT1;			// enable p1.4 interrupt
	P1IES |= BIT1;			// P1.4 rising edge interrupt

	//S2 Port configuration
	P1DIR &= ~BIT4;			// make P1.4 and input
	P1REN |= BIT4;			// enable pull resistor on P1.4
	P1OUT |= BIT4;			// make it a pull-up resistor
	P1IE |= BIT4;			// enable p1.4 interrupt
	P1IES |= BIT4;			// P1.4 rising edge interrupt
}

void Init_Port2(){
    /* Configure GPIO */
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN7,
            GPIO_PRIMARY_MODULE_FUNCTION);// buzzer

    P2DIR |= BIT0;	// red RGB LED output
    P2DIR |= BIT1;	// green RGB LED output
}

/*void Init_Port3(){
	GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P3, GPIO_PIN5); // SW1 input at p3.5
	GPIO_clearInterruptFlag(GPIO_PORT_P3, GPIO_PIN5);
	GPIO_enableInterrupt(GPIO_PORT_P3, GPIO_PIN5);
	GPIO_interruptEdgeSelect(GPIO_PORT_P3, GPIO_PIN5, GPIO_HIGH_TO_LOW_TRANSITION);
	Interrupt_enableInterrupt(INT_PORT3);
}*/

void Init_Port4(){
    /* Configure GPIO input for ADC channel 10 microphone */
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN3,
			GPIO_TERTIARY_MODULE_FUNCTION);

}

void Init_Port5(){
    P5SEL0 |= BIT6;	// blue LED
    P5SEL1 &= ~BIT6;
    P5DIR |= BIT6;
    P5OUT &= ~BIT6; // turn off

    	/*GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN1); // SW2 input at p5.1
	GPIO_clearInterruptFlag(GPIO_PORT_P5, GPIO_PIN1);
	GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN1);
	GPIO_interruptEdgeSelect(GPIO_PORT_P5, GPIO_PIN1, GPIO_HIGH_TO_LOW_TRANSITION);
	Interrupt_enableInterrupt(INT_PORT5);*/
}


