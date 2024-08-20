/*
 * TIMER1_interface.h
 *
 *  Created on: Aug 16, 2024
 *      Author: Fatma
 */

#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_


#include "STD_TYPES.h"
#define SERVO_0_DEGREE 187   /* 1 ms pulse */
#define SERVO_90_DEGREE 250  /* 1.5 ms pulse */
#define SERVO_180_DEGREE 125 /* 2 ms pulse */
#define PWM_PERIOD 2499   /* TOP count for Timer1 (8 MHz) */


void Timer1_Fast_PWM_Init(u8 duty_cycle);

#endif /* TIMER1_INTERFACE_H_ */
