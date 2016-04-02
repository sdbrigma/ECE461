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

/* This interrupt is fired whenever a conversion is completed and placed in
 * ADC_MEM2. This signals the end of conversion and the results array is
 * grabbed and placed in resultsBuffer */
void ADC14_IRQHandler(void)
{
    uint64_t status;

    status = MAP_ADC14_getEnabledInterruptStatus();
    MAP_ADC14_clearInterruptFlag(status);

    /* ADC_MEM2 conversion completed */
    if(status & ADC_INT2)
    {
        /* Store ADC14 conversion results */
        resultsBuffer[0] = ADC14_getResult(ADC_MEM0);
        resultsBuffer[1] = ADC14_getResult(ADC_MEM1);
        resultsBuffer[2] = ADC14_getResult(ADC_MEM2);

        /*
         * Draw accelerometer data on display and determine if orientation
         * change thresholds are reached and redraw as necessary
         */
        if (resultsBuffer[0] < 4900) {
            if (Lcd_Orientation != LCD_ORIENTATION_LEFT) {
                Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_LEFT);
                drawTitle();
            }
            else
                drawAccelData();
        }
        else if (resultsBuffer[0] > 11300) {
            if (Lcd_Orientation != LCD_ORIENTATION_RIGHT){
                Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_RIGHT);
                drawTitle();
            }
            else
                drawAccelData();
        }
        else if (resultsBuffer[1] < 5000) {
            if (Lcd_Orientation != LCD_ORIENTATION_UP){
                Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
                drawTitle();
            }
            else
                drawAccelData();
        }
        else if (resultsBuffer[1] > 11300) {
            if (Lcd_Orientation != LCD_ORIENTATION_DOWN){
                Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_DOWN);
                drawTitle();
            }
            else
                drawAccelData();
        }
        else
            drawAccelData();
    }
}


