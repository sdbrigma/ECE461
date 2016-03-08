/*
 * functions.h
 *
 *  Created on: Mar 5, 2016
 *      Author: Steffon Brigman
 */

#ifndef CHALLENGE2_FUNCTIONS_H_
#define CHALLENGE2_FUNCTIONS_H_

void Init_Ports(void);
void Init_Port4(void);
void Init_Timers(void);
void Init_Clocks(void);
void Init_Adc(void);
void Switch_Process(void);
void Init_Port2(void);
void Init_Port5(void);
void Init_Port6(void);
void Init_Dma(void);

void delay_1sec(void);
void delay_200ms(void);
void delay(int time);

// buzzer functions
void burglar_alarm(void);
void fire_alarm(void);
void doorbell(void);


#endif /* CHALLENGE2_FUNCTIONS_H_ */