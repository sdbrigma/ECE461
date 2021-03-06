/*
 * macros.h
 *
 *  Created on: Mar 5, 2016
 *      Author: Steffon Brigman
 */
#include "driverlib.h"
#include "msp432.h"

#ifndef CHALLENGE2_MACROS_H_
#define CHALLENGE2_MACROS_H_

#define TRUE (0x1)
#define FALSE (0x0)
#define INT_ADC14_BIT (1<<24)
#define MCLK_FREQUENCY 1500000
#define PWM_PERIOD 3200
#define DING1 12000
#define DING2 9000
#define DING3 3000
#define ONE_SEC 800000
extern uint32_t adcResult;

#define BURGLAR 16000
#define TEST_LENGTH_SAMPLES 512
#define SAMPLE_LENGTH 512

#define LIGHT_SENSOR_ADDR (0x44)

/*OPT3001 CONSTANTS*/
#define OPT3001_SLAVE_ADDRESS 0x44
#define OPT_INTERRUPT_PIN 11
#define RESULT_REG 0x00
#define CONFIG_REG 0x01
#define LOWLIMIT_REG 0x02
#define HIGHLIMIT_REG 0x03
#define MANUFACTUREID_REG 0x7E
#define DEVICEID_REG 0x7F
#define DEFAULT_CONFIG 0xCC10 // 800ms
#define DEFAULT_CONFIG_100 0xC410 // 100ms

#define FIRE 1000
#define DEBOUNCE 10

extern volatile uint32_t adc;
extern bool alarm_state;
extern bool burglar;
extern bool doorbell_signal;
extern bool fire_signal;

#endif /* CHALLENGE2_MACROS_H_ */
