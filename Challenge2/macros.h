/*
 * macros.h
 *
 *  Created on: Mar 5, 2016
 *      Author: Steffon Brigman
 */

#ifndef CHALLENGE2_MACROS_H_
#define CHALLENGE2_MACROS_H_


#define INT_ADC14_BIT (1<<24)
#define MCLK_FREQUENCY 1500000
#define PWM_PERIOD 3200
#define DING1 12000
#define DING2 9000
#define DING3 3000
#define ONE_SEC 800000

#define BURGLAR 1000
#define TEST_LENGTH_SAMPLES 512
#define SAMPLE_LENGTH 512

extern volatile uint32_t adcResult;

#endif /* CHALLENGE2_MACROS_H_ */
