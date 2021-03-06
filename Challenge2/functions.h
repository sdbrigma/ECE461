/*
 * functions.h
 *
 *  Created on: Mar 5, 2016
 *      Author: Steffon Brigman
 */

#include "driverlib.h"
#include "msp432.h"

#ifndef CHALLENGE2_FUNCTIONS_H_
#define CHALLENGE2_FUNCTIONS_H_

void Init_Ports(void);
void Init_Port4(void);
void Init_Port1(void);
void Init_Timers(void);
void Init_Clocks(void);
void Init_Adc(void);
void Switch_Process(void);
void Init_Port2(void);
//void Init_Port3(void);
void Init_Port5(void);
void Init_SysTick(uint32_t period);

void Switch_Process();

// buzzer functions
void burglar_alarm(void);
void fire_alarm(void);
void doorbell(void);
void alarm_system_state(bool state);

void OPT3001_init(void);
unsigned long int OPT3001_getLux(void);
unsigned int OPT3001_readManufacturerId(void);
unsigned int OPT3001_readDeviceId(void);
unsigned int OPT3001_readConfigReg(void);
unsigned int OPT3001_readLowLimitReg(void);
unsigned int OPT3001_readHighLimitReg(void);

void Init_I2C_GPIO(void);
void I2C_init(void);
int I2C_read16(unsigned char);
void I2C_write16(unsigned char pointer, unsigned int writeByte);
void I2C_setslave(unsigned int slaveAdr);


#endif /* CHALLENGE2_FUNCTIONS_H_ */
