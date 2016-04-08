/*
 * interrupts.c
 *
 *  Created on: Apr 2, 2016
 *      Author: Steffon Brigman
 */

#include "functions.h"
#include "msp.h"
#include <driverlib.h>
#include <grlib.h>
#include "Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#include "macros.h"
#include <string.h>
#include <stdio.h>

int dataSetIndex;
char *dataSetASCII;
char *dataSetHundreds;
char *dataSetTens;
char *dataSetOnes;
int receiveData;
int dataCounter = 0;

/* This interrupt is fired whenever a conversion is completed and placed in
 * ADC_MEM2. This signals the end of conversion and the results array is
 * grabbed and placed in resultsBuffer */
bool avg = FALSE;
void ADC14_IRQHandler(void)
{
    uint64_t status;

    status = MAP_ADC14_getEnabledInterruptStatus();
    MAP_ADC14_clearInterruptFlag(status);

    /* ADC_MEM2 conversion completed */
    if(status & ADC_INT2)
    {
        /* Store ADC14 conversion results */
    		// Take running average of ADC14 values so they can be updated
		resultsBuffer[0] = ADC14_getResult(ADC_MEM0);
		resultsBuffer[1] = ADC14_getResult(ADC_MEM1);
		resultsBuffer[2] = ADC14_getResult(ADC_MEM2);

    		/*if(avg){
    			avg = FALSE;
    			resultsBuffer[0] = (ADC14_getResult(ADC_MEM0) + resultsBuffer[0]) > 1;
			resultsBuffer[1] = (ADC14_getResult(ADC_MEM1) + resultsBuffer[1]) > 1;
			resultsBuffer[2] = (ADC14_getResult(ADC_MEM2) + resultsBuffer[2]) > 1;
    		}
    		else {
    			avg = TRUE;
    			resultsBuffer[0] = ADC14_getResult(ADC_MEM0);
			resultsBuffer[1] = ADC14_getResult(ADC_MEM1);
			resultsBuffer[2] = ADC14_getResult(ADC_MEM2);
    		}*/

        /*
         * Draw accelerometer data on display and determine if orientation
         * change thresholds are reached and redraw as necessary
         */
        if (resultsBuffer[0] < 4900) {
            if (Lcd_Orientation != LCD_ORIENTATION_LEFT) {
                Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_LEFT);
                drawTitle();
            }
            //else
                //drawAccelData();
        }
        else if (resultsBuffer[0] > 11300) {
            if (Lcd_Orientation != LCD_ORIENTATION_RIGHT){
                Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_RIGHT);
                drawTitle();
            }
            //else
                //drawAccelData();
        }
        else if (resultsBuffer[1] < 5000) {
            if (Lcd_Orientation != LCD_ORIENTATION_UP){
                Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
                //drawTitle();
            }
            //else
                //drawAccelData();
        }
        else if (resultsBuffer[1] > 11300) {
            if (Lcd_Orientation != LCD_ORIENTATION_DOWN){
                Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_DOWN);
                drawTitle();
            }
            //else
                //drawAccelData();
        }
        //else
            //drawAccelData();
    }
}

void Timer32_ISRhandler(void){
	uint64_t status = Timer32_getInterruptStatus(TIMER32_0_BASE);
	Timer32_clearInterruptFlag(TIMER32_0_BASE);
	if(status){
		//GPIO_toggleOutputOnPin(GPIO_PORT_P5,GPIO_PIN6);
		drawAccelData();
	}
}

/* EUSCI A0 UART ISR - Echoes data back to PC host */
void EUSCIA2_IRQHandler(void)
{
    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A2_BASE);

    MAP_UART_clearInterruptFlag(EUSCI_A2_BASE, status);

    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT)
    {
    		receiveData = UCA2RXBUF;				//the value from the receive buffer will be placed into a receiveData variable
    		dataSetASCII = (char*)receiveData;	//we cast this value as a char* and place into dataSetASCII
    		if(dataSetASCII == "\n"){			//if a new line character is found,
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
    			dataSetOnes = '\0';				//clear out all of our old values
    			dataSetTens = '\0';
    			dataSetHundreds = '\0';
    		}
    }
}

