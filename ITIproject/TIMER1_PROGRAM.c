/*
 * TIMER1_PROGRAM.c
 *
 *  Created on: Aug 16, 2024
 *      Author: Fatma
 */

#include"TIMER1_private.h"
#include"TIMER1_interface.h"
#include "BIT_MATH.h"
#include"STD_TYPES.h"

void Timer1_Fast_PWM_Init(u8 duty_cycle)
{
	TCNT1 = 0;       /* Set Timer1 initial count to zero */
    ICR1 = PWM_PERIOD; /* Set TOP count for Timer1 in ICR1 register */

    OCR1A = (duty_cycle); /* Set the compare value */

    /* Configure Timer1 for Fast PWM Mode */
    TCCR1A = (1<<TCCR1A_WGM11) | (1<<TCCR1A_COM1A1);  /* Non-inverting mode, PWM with TOP in ICR1 */
    TCCR1B = (1<<TCCR1B_WGM12) | (1<<TCCR1B_WGM13)| (1<<TCCR1B_CS10)| (1<<TCCR1B_CS11); /* Fast PWM, Prescaler = 64 */
}

