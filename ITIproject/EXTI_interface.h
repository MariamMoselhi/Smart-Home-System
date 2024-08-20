/*
 * EXTI_interface.h
 *
 *      Author  : Jimmy
        SWC     : EXTI
        Version : 01
 */
 
#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#define EXTI_0		0
#define EXTI_1		1
#define EXTI_2		2



/* FOR INTERRUPT 0 & 1 */
#define SENSE_CONTROL_LOW_LEVEL        0
#define SENSE_CONTROL_ON_CHANGE        1
#define SENSE_CONTROL_FALLING_EDGE     2
#define SENSE_CONTROL_RISING_EDGE      3


/* FOR INTERRUPT 2 */

#define SENSE_CONTROL_INT_2_FALLING_EDGE      0
#define SENSE_CONTROL_INT_2_RISING_EDGE       1


void EXTIvoid_Enable(u8 Copy_u8EXTINum,u8 Copy_u8SenseControl);
void EXTIvoid_Disable(u8 Copy_u8EXTINum);

void EXTI_Set_voidCallBackINT0(void (*ISR_FUNC)(void));
void EXTI_Set_voidCallBackINT1(void (*ISR_FUNC)(void));
void EXTI_Set_voidCallBackINT2(void (*ISR_FUNC)(void));

void   EXTI_voidClearFlag         ( u8 Copy_u8Line );
u8 EXTI_u8GetFlag( u8 Copy_u8Line );

#endif /* EXTI_INTERFACE_H_ */
