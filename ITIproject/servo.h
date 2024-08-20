/*
 * SERVO_Interface.h
 *
 *  Created on: Jun 20, 2023
 *      Author:fatma
 */

#ifndef SERVO_H
#define SERVO_H


#include <avr/io.h>
/* Function prototypes */
void Servo_Set_Position(unsigned short angle);
u8 Servo_Open_Door(void);
u8 Servo_Close_Door(void);



#endif /* SERVO_H */

