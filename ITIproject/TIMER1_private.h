/*
 * TIMER1_private.h
 *
 *  Created on: Aug 16, 2024
 *      Author: Fatma
 */

#ifndef TIMER1_PRIVATE_H_
#define TIMER1_PRIVATE_H_

#define TIMSK   *((volatile u8 *) 0x59 )
#define TIMSK_TICIE1		5							/*Timer/Counter1, Input Capture Interrupt Enable*/
#define TIMSK_OCIE1A		4                           /*Timer/Counter1, Output Compare A Match Interrupt Enable*/
#define TIMSK_OCIE1B		3                           /*Timer/Counter1, Output Compare B Match Interrupt Enable*/
#define TIMSK_TOIE1			2
#define TIFR    *((volatile u8 *) 0x58 )

#define TCNT1H   *((volatile u8 *) 0x4D)
#define TCNT1L   *((volatile u8 *) 0x4C)

#define OCR1AH   *((volatile u8 *) 0x4B)
#define OCR1AL   *((volatile u8 *) 0x4A)

#define OCR1BH   *((volatile u8 *) 0x49)
#define OCR1BL   *((volatile u8 *) 0x48)

#define ICR1H    *((volatile u8 *) 0x47)
#define ICR1L    *((volatile u8 *) 0x46)

#define TCCR1A   (*((volatile u8 *) 0x4F))
#define TCCR1A_COM1A1		7							/*Compare Output Mode for Channel A*/
#define TCCR1A_COM1A0		6							/*Compare Output Mode for Channel A*/
#define TCCR1A_COM1B1		5							/*Compare Output Mode for Channel B*/
#define TCCR1A_COM1B0		4							/*Compare Output Mode for Channel B*/
#define TCCR1A_FOC1A		3							/* Force Output Compare for Channel A*/
#define TCCR1A_FOC1B		2							/* Force Output Compare for Channel B*/
#define TCCR1A_WGM11		1							/*Waveform Generation Mode*/
#define TCCR1A_WGM10		0
#define TCCR1B   (*((volatile u8 *) 0x4E))
#define TCCR1B_ICNC1		7                           /*Input Capture Noise Canceler*/
#define TCCR1B_ICES1		6                           /*Input Capture Edge Select*/
#define TCCR1B_WGM13		4                           /*Waveform Generation Mode*/
#define TCCR1B_WGM12		3                           /*Waveform Generation Mode*/
#define TCCR1B_CS12			2							/*Clock Selection Bit_3*/
#define TCCR1B_CS11			1							/*Clock Selection Bit_2*/
#define TCCR1B_CS10			0


#define TCNT1		    	(*((volatile u16*)0x4C))
#define OCR1A		    	*((volatile u16*)0x4A)
#define OCR1B		    	*((volatile u16*)0x48)
#define ICR1		    	(*((volatile u16*)0x46))


#endif /* TIMER1_PRIVATE_H_ */
