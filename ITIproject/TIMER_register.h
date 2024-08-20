/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal    ************/
/****************************     Layer  : MCAL             ************/
/****************************     swc    : TIMER            ************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/

#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_

#define 	TCCR0     				*((volatile u8*)0x53) 			/* Timer 0 control register */
#define 	TCCR0_WGM00				6								/* Waveform generation mode bit0 */
#define 	TCCR0_COM01				5								/* Compare Match Output Mode bit1 */
#define 	TCCR0_COM00				4								/* Compare Match Output Mode bit0 */
#define 	TCCR0_WGM01				3								/* Waveform generation mode bit1 */
#define 	TCCR0_CS02				2								/* Prescaler bit2 */
#define 	TCCR0_CS01				1								/* Prescaler bit1 */
#define 	TCCR0_CS00				0								/* Prescaler bit0 */


#define 	OCR0     				*((volatile u8*)0x5C)			/* Output Compare register 0 */

#define 	TCNT0 					*((volatile u8*)0x52)

#define 	TIMSK     				*((volatile u8*)0x59)			/* Timer Mask */
#define 	TIMSK_OCIE0     		1								/* Output Compare 0 interrupt Enable */
#define 	TIMSK_TOIE0				0								/* Normal Mode Tim 0 interrupt Enable */

#endif
