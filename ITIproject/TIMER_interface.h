/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal    ************/
/****************************     Layer  : MCAL             ************/
/****************************     swc    : TIMER            ************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_



void Timer0_voidInit(void);

void Timer0_voidSetCompMatchValue(u8 Copy_u8CompMatchValue );


void Timer0_voidInterruptEnable(void);

void Timer0_voidSetPrescalerValue(u8 Copy_u8PrescalerValue);

u8 Timer0_u8SetCallBack(void (*Copy_pvCallBackFunc)(void));

void Timer0void_ModifyPreloadValue( u8 Copy_u8PreloadValue );

#endif 


