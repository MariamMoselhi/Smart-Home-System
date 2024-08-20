
/*
 * servo.c
 *
 *  Created on: Aug 16, 2024
 *      Author: Fatma
 */

#include "BIT_Math.h"
#include "STD_TYPES.h"

#include "servo.h"

#include "DIO_interface.h"
#include "TIMER1_interface.h"

#include <util/delay.h> /* Include Delay header file */





/* Function to set the servo position */
void Servo_Set_Position(unsigned short angle)
{
    Timer1_Fast_PWM_Init(angle);
}

/* Function to open the door (set servo to 90 degrees) */
u8 Servo_Open_Door(void)
{

    Servo_Set_Position(SERVO_90_DEGREE);
    _delay_ms(3000); /* Keep the door open for 3 seconds */
    return 1;
}

/* Function to close the door (set servo to 0 degrees) */
u8 Servo_Close_Door(void)
{

    Servo_Set_Position(SERVO_0_DEGREE);
    _delay_ms(1000); /* Keep the door closed for 3 seconds */
    return 0;
}





