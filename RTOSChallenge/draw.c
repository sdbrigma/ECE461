/*
 * draw.c
 *
 *  Created on: Apr 2, 2016
 *      Author: Steffon Brigman
 */

#include "msp.h"
#include <driverlib.h>
#include <grlib.h>
#include "Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#include "functions.h"
#include "macros.h"

/* Graphic library context */
Graphics_Context g_sContext;

//volatile uint16_t resultsBuffer[3];

/*
 * Redraw accelerometer data
 */
void drawAccelData(uint16_t val1,uint16_t val2,uint16_t val3)
{
	//static uint16_t resultsBuffer[3];
    char string[8];
    sprintf(string, "X: %5d", val1);
    Graphics_drawString(&g_sContext,
                                    (int8_t *)string,
                                    8,
                                    20,
                                    30,
                                    OPAQUE_TEXT);

    sprintf(string, "Y: %5d", val2);
    Graphics_drawString(&g_sContext,
                                    (int8_t *)string,
                                    8,
                                    20,
                                    50,
                                    OPAQUE_TEXT);

    sprintf(string, "Z: %5d", val3);
    Graphics_drawString(&g_sContext,
                                    (int8_t *)string,
                                    8,
                                    20,
                                    70,
                                    OPAQUE_TEXT);

}


/*
 * Clear display and redraw title + accelerometer data
 */
void drawTitle()
{
    Graphics_clearDisplay(&g_sContext);
    Graphics_drawString(&g_sContext,
                                    "Accelerometer:",
                                    AUTO_STRING_LENGTH,
                                    20,
                                    10,
                                    OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext,
                                    "Sensor:",
                                    AUTO_STRING_LENGTH,
                                    64,
                                    90,
                                    OPAQUE_TEXT);
    //drawAccelData();
}

void drawData()
{
	static char *dataSetHundreds;
	static char *dataSetTens;
	static char *dataSetOnes;

	char string[8];
    sprintf(string, "%s%s%s", dataSetHundreds, dataSetTens, dataSetOnes); //print all 3 data set values
    Graphics_drawString(&g_sContext,
                                    (char *)string,
                                    8,
                                    20,
                                    100,
                                    OPAQUE_TEXT);
}
