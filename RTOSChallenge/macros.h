/*
 * macros.h
 *
 *  Created on: Apr 2, 2016
 *      Author: Steffon Brigman
 */

#ifndef MACROS_H_
#define MACROS_H_

/* ADC results buffer */
//extern volatile uint16_t resultsBuffer[3];

/* Graphic library context */
//extern Graphics_Context g_sContext;

extern int dataSetIndex;
extern char dataSetASCII;
extern char dataSetString[3];
extern char dataSetHundreds;
extern char dataSetTens;
extern char dataSetOnes;

extern Graphics_Context g_sContext;

#define TRUE 0x01
#define FALSE 0x00
#define ONE_SECOND 0xffffffff

#endif /* MACROS_H_ */
