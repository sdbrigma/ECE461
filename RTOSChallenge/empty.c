/*
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== main.c ========
 */

// Usual includes
#include "msp.h"
#include <driverlib.h>
#include "grlib.h"
#include "Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#include "functions.h"
#include "macros.h"

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/cfg/global.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Idle.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Mailbox.h>

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>
// #include <ti/drivers/I2C.h>
// #include <ti/drivers/SDSPI.h>
// #include <ti/drivers/SPI.h>
// #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>
// #include <ti/drivers/WiFi.h>

/* Board Header file */
#include "Board.h"
#include "functions.h"
#include "macros.h"

typedef struct MsgObj {
	uint16_t val0;            		// message value
	uint16_t val1;
	uint16_t val2;
} MsgObj, *Msg;


Graphics_Context g_sContext;
Void clk0Fxn(UArg arg0);

Clock_Struct clk0Struct;
Clock_Handle clk0Handle;

int dataSetIndex;
char dataSetASCII;
char dataSetHundreds;
char dataSetTens;
char dataSetOnes;
int receiveData;
int dataCounter = 0;
int timerCounter = 0;
bool ticks0 = 0;

int main(void){
	/* Construct BIOS Objects */
	    Clock_Params clkParams;

	/* Call board init functions */
	Board_initGeneral();
	//Board_initGPIO();
	init_All();
	// Board_initI2C();
	// Board_initSDSPI();
	// Board_initSPI();
	 //Board_initUART();
	// Board_initWatchdog();
	// Board_initWiFi();
	drawTitle();		// Set titles for LCD

	// Clock configuration used to create 1s interrupt
	Clock_Params_init(&clkParams);
	clkParams.period = 1000; // period for one second
	clkParams.startFlag = TRUE;
	Clock_construct(&clk0Struct, (Clock_FuncPtr)clk0Fxn, 1000, &clkParams);
	clk0Handle = Clock_handle(&clk0Struct);
	Clock_start(clk0Handle);

	/* Start BIOS */
	BIOS_start();

	return (0);
}

void Idle_fcxn(void){
	// Idle function
	while(1);
}

 void averageCalcTask(void){
// This function is used to calculate the absolute average of the accelerometer and displays
// it to the LCD.

	 MsgObj msg; // message object used by ADC interrupt to send data to mailbox

	 // Utility variables used in calculations
	 static uint16_t lastX;
	 static uint16_t lastY;
	 static uint16_t lastZ;
	 static uint16_t avgX;
	 static uint16_t avgY;
	 static uint16_t avgZ;
	 while(1){
		 // use of semaphore to set inital values before taking a running average
		 if(Semaphore_getCount(LCDsemaphore) == 0){
			 Mailbox_pend(adc_mailbox, &msg, BIOS_WAIT_FOREVER);
			 avgX = (lastX - msg.val0) > 1;
			 avgY = (lastY - msg.val1) > 1;
			 avgZ = (lastZ - msg.val2) > 1;

			 lastX = msg.val0;
			 lastY = msg.val1;
			 lastZ = msg.val2;
			 if(ticks0 == 1){// flag set by 1 second clock interrupt
				 drawAccelData(avgX,avgY,avgZ);
				 ticks0 = 0;
			 }
		 }
		 else{
			 // decrements semaphore used to set intial value for absolute average
			 Semaphore_pend(LCDsemaphore,BIOS_WAIT_FOREVER);
			 Mailbox_pend(adc_mailbox, &msg, BIOS_WAIT_FOREVER);
			 lastX = msg.val0;
			 lastY = msg.val1;
			 lastZ = msg.val2;
		 }
	 }
 }

Void clk0Fxn(UArg arg0){// clock interrupt
	//GPIO_toggleOutputOnPin(GPIO_PORT_P5,GPIO_PIN6);
	ticks0 = 1; // clock interrupt flag
}

void ADC_HWI(void){
	uint64_t status;
	MsgObj msg;
	status = MAP_ADC14_getEnabledInterruptStatus();
	MAP_ADC14_clearInterruptFlag(status);

	/* ADC_MEM2 conversion completed */
	if(status & ADC_INT2)
	{
		/* Store ADC14 conversion results */
		msg.val0 = ADC14_getResult(ADC_MEM0);
		msg.val1 = ADC14_getResult(ADC_MEM1);
		msg.val2 = ADC14_getResult(ADC_MEM2);
		Mailbox_post(adc_mailbox,&msg,0); // Send the ADC message using the mailbox
	}
}

/* EUSCI A0 UART ISR - Echoes data back to PC host */
void EUSCIA2_IRQHandler(void)
{
    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A2_BASE);

    MAP_UART_clearInterruptFlag(EUSCI_A2_BASE, status);

    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT)
    {
    		if (timerCounter == 0){
    			timerCounter = 1;
    		}
    		receiveData = UCA2RXBUF;				//the value from the receive buffer will be placed into a receiveData variable
    		dataSetASCII = (char)receiveData;	//we cast this value as a char* and place into dataSetASCII

    		if(dataSetASCII == 'A'){ BIOS_exit(0); } // ending character used to signify EOF

    		if(dataSetASCII == 0xA || dataSetASCII == 0xD){			//if a new line character is found,
    			dataCounter = 3;					//send it to counter 3 location to print the number to the screen
    		}
    		else if (dataCounter == 0)
		{
    			dataSetOnes = dataSetASCII;		//we save the value into the ones place
    			dataCounter++;
		}
    		else if (dataCounter == 1)
    		{
    			dataSetTens = dataSetOnes;		//we have a tens digit, so we move the first number into the tens place
    			dataSetOnes = dataSetASCII;
    			dataCounter++;
    		}
    		else if (dataCounter == 2)
    		{
    			dataSetHundreds = dataSetTens;	//we have a hundreds digit, so we move the second number into the hundreds place
    			dataSetTens = dataSetOnes;
    			dataSetOnes = dataSetASCII;
    			dataCounter++;
    		}
    		else if (dataCounter == 3){
    			dataCounter = 0;					//clear dataCounter
    			drawData();						//write data to the display
    			dataSetOnes = '0';				//clear out all of our old values
    			dataSetTens = ' ';
    			dataSetHundreds = ' ';
    		}
    }
}

void drawAccelData(uint16_t xData, uint16_t yData, uint16_t zData){
	// Function used to update the LCD with data from the accelerometer
	char string[8];
	sprintf(string, "X: %5d", xData);
	Graphics_drawString(&g_sContext, (int8_t *)string,8,20,30,OPAQUE_TEXT);

	sprintf(string, "Y: %5d", yData);
	Graphics_drawString(&g_sContext,(int8_t *)string,8,20,50,OPAQUE_TEXT);

	sprintf(string, "Z: %5d", zData);
	Graphics_drawString(&g_sContext,(int8_t *)string, 8,20,70,OPAQUE_TEXT);
}

void drawSensorData(char dataSetHundreds, char dataSetTens, char dataSetOnes){
	// Function used to update LCD with data from the transmitted data set
	char string[3];
	char data[3];
	data[0] = dataSetHundreds;
	data[1] = dataSetTens;
	data[2] = dataSetOnes;
	sprintf(string, "%s", data); //print all 3 data set values
	Graphics_drawString(&g_sContext,(int8_t *)string, 8,20,100, OPAQUE_TEXT);
}


/*
 * Clear display and redraw title + accelerometer data
 */
void drawTitle(void){
	Graphics_clearDisplay(&g_sContext);
	Graphics_drawString(&g_sContext,"Accelerometer:",AUTO_STRING_LENGTH,20, 10, OPAQUE_TEXT);
	Graphics_drawStringCentered(&g_sContext,"Sensor:", AUTO_STRING_LENGTH,64,90,OPAQUE_TEXT);
}

void drawData()
{// Used by UART HWI to clear part of the LCD before writing new data to it
	char string[3];
	char data[3];
	data[0] = dataSetHundreds;
	data[1] = dataSetTens;
	data[2] = dataSetOnes;
	sprintf(string, "%s", data); //print all 3 data set values
    Graphics_drawString(&g_sContext,
                                    (int8_t *)string,
                                    3,
                                    20,
                                    100,
                                    OPAQUE_TEXT);
}
