/*
 * EXTI_interface.c
 *
 *      Author  : Jimmy
        SWC     : EXTI
        Version : 01
 */
 
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "EXTI_private.h"
#include "EXTI_config.h"
#include "EXTI_interface.h"

static void (*PTRtoFUNC_INT_0) (void) = NULL ;
static void (*PTRtoFUNC_INT_1) (void) = NULL ;
static void (*PTRtoFUNC_INT_2) (void) = NULL ;

 void EXTIvoid_Enable(u8 Copy_u8EXTINum,u8 Copy_u8SenseControl)
 {
	 switch(Copy_u8EXTINum)
	 {
	 	 case	0 : SET_BIT(GICR,GICR_INT0) ;
	 	 	 	 	switch(Copy_u8SenseControl)
	 	 	 	 	{
	 	 	 	 	case 0 : CLR_BIT(MCUCR,MCUCR_ISC00);
	 	 	 	 			 CLR_BIT(MCUCR,MCUCR_ISC01);
	 	 	 	 			 break ;
	 	 	 	 	case 1 : SET_BIT(MCUCR,MCUCR_ISC00);
	 	 	 	 	 	 	 CLR_BIT(MCUCR,MCUCR_ISC01);
	 	 	 	 	 	 	  break ;
	 	 	 	    case 2 : CLR_BIT(MCUCR,MCUCR_ISC00);
	 	 	 	 	 	 	 SET_BIT(MCUCR,MCUCR_ISC01);
	 	 	 	 	 	 	 break ;
	 	 	 	    case 3 : SET_BIT(MCUCR,MCUCR_ISC00);
	 	 	 	 	 	 	 SET_BIT(MCUCR,MCUCR_ISC01);
	 	 	 	 	 	 	 break ;
	 	 	 	 	}
	 	 	 	 	 break ;
	 	 case   1 :
	 		SET_BIT(GICR,GICR_INT1) ;
	 		 	 switch(Copy_u8SenseControl)
	 		 	 {
						case 0 : CLR_BIT(MCUCR,MCUCR_ISC10);
								 CLR_BIT(MCUCR,MCUCR_ISC11);
								 break ;
						case 1 : SET_BIT(MCUCR,MCUCR_ISC10);
								 CLR_BIT(MCUCR,MCUCR_ISC11);
								  break ;
						case 2 : CLR_BIT(MCUCR,MCUCR_ISC10);
								 SET_BIT(MCUCR,MCUCR_ISC11);
								 break ;
						case 3 : SET_BIT(MCUCR,MCUCR_ISC10);
								 SET_BIT(MCUCR,MCUCR_ISC11);
								 break ;
	 	 	}
	 	 break ;
	 	 case 	2 :
	 		SET_BIT(GICR,GICR_INT2) ;
	 		 switch(Copy_u8SenseControl)
	 	 	{
	 	 	case 0 : CLR_BIT(MCUCSR,MCUCSR_ISC2);
	 	 			 break ;
	 	 	case 1 : SET_BIT(MCUCSR,MCUCSR_ISC2);
	 	 	 	 	  break ;
	 	 	}
	 	 break ;
	 }
 }
void EXTIvoid_Disable(u8 Copy_u8EXTINum)
{
	switch(Copy_u8EXTINum)
	{
	case 0 : CLR_BIT(GICR,GICR_INT0) ; break ;
	case 1 : CLR_BIT(GICR,GICR_INT1) ; break ;
	case 2 : CLR_BIT(GICR,GICR_INT2) ; break ;
	}
}



void EXTI_Set_voidCallBackINT0(void (*Copy_ptrISR_FUNC)(void))
{
	PTRtoFUNC_INT_0 = Copy_ptrISR_FUNC ;
}
void EXTI_Set_voidCallBackINT1(void (*Copy_ptrISR_FUNC)(void))
{
	PTRtoFUNC_INT_1 = Copy_ptrISR_FUNC ;
}
void EXTI_Set_voidCallBackINT2(void (*Copy_ptrISR_FUNC)(void))
{
	PTRtoFUNC_INT_2 = Copy_ptrISR_FUNC ;
}
void   EXTI_voidClearFlag         ( u8 Copy_u8Line )
{
	switch (Copy_u8Line){
	case EXTI_0 : SET_BIT(GIFR,GIFR_INTF0);  break;
	case EXTI_1 : SET_BIT(GIFR,GIFR_INTF1);  break;
	case EXTI_2 : SET_BIT(GIFR,GIFR_INTF2);  break;
}
}
u8 EXTI_u8GetFlag( u8 Copy_u8Line ){
	u8 flag;
		switch (Copy_u8Line){
	case EXTI_0 : flag=GET_BIT(GIFR,GIFR_INTF0);  break;
	case EXTI_1 : flag=GET_BIT(GIFR,GIFR_INTF1);  break;
	case EXTI_2 : flag=GET_BIT(GIFR,GIFR_INTF2);  break;
		}
	return flag;
}

void __vector_1 (void)    __attribute__((signal)) ;
void __vector_1 (void)
{
	if(PTRtoFUNC_INT_0 != NULL)
	{
		PTRtoFUNC_INT_0();
	}
	else
	{
		/* DO NOTHING */
	}
}

void __vector_2 (void)    __attribute__((signal)) ;
void __vector_2 (void)
{
	if(PTRtoFUNC_INT_1 != NULL)
		{
			PTRtoFUNC_INT_1();
		}
		else
		{
			/* DO NOTHING */
		}
}

void __vector_3 (void)    __attribute__((signal)) ;
void __vector_3 (void)
{
	if(PTRtoFUNC_INT_2 != NULL)
		{
		PTRtoFUNC_INT_2();
		}
		else
		{
			/* DO NOTHING */
		}
}
