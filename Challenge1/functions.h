/*
 * functions.h
 *
 *  Created on: Feb 5, 2016
 *      Author: marybiggs
 */

#ifndef CHALLENGE1_FUNCTIONS_H_
#define CHALLENGE1_FUNCTIONS_H_


void ProgramFlash(void);
void EraseFlash(void);
void TestSRAMBankEnable(void);

void delay_200ms(void);
void delay_1sec(void);

void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);

void clear_watchdog_timer(void);

void Init_Timers(void);

void Switch_Process(void);

#endif /* CHALLENGE1_FUNCTIONS_H_ */
