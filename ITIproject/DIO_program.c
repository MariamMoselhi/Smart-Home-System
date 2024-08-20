#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_private.h"
#include "DIO_interface.h"


void DIO_SetPort_Direction(u8 Copy_u8PortNum , u8 Copy_u8Direction)
{
	switch(Copy_u8PortNum)
	{
	case DIO_PORTA : DDRA = Copy_u8Direction ;
	break ;
	case DIO_PORTB : DDRB = Copy_u8Direction ;
	break ;
	case DIO_PORTC : DDRC = Copy_u8Direction ;
	break ;
	case DIO_PORTD : DDRD = Copy_u8Direction ;
	break ;
	}
}

void DIO_SetPort_value(u8 Copy_u8PortNum , u8 Copy_u8PortValue)
{
	switch(Copy_u8PortNum)
		{
		case DIO_PORTA : PORTA = Copy_u8PortValue ;
		break ;
		case DIO_PORTB : PORTB = Copy_u8PortValue ;
		break ;
		case DIO_PORTC : PORTC = Copy_u8PortValue ;
		break ;
		case DIO_PORTD : PORTD = Copy_u8PortValue ;
		break ;
		}
}



void DIO_SetPin_Direction(u8 Copy_u8PortNum , u8 Copy_u8PinNum , u8 Copy_u8Direction)
{
	if(Copy_u8Direction == PIN_OUTPUT)
	{
		switch(Copy_u8PortNum)
		{
		case DIO_PORTA : SET_BIT(DDRA,Copy_u8PinNum) ;
		break ;
		case DIO_PORTB : SET_BIT(DDRB,Copy_u8PinNum) ;
		break ;
		case DIO_PORTC : SET_BIT(DDRC,Copy_u8PinNum) ;
		break ;
		case DIO_PORTD : SET_BIT(DDRD,Copy_u8PinNum) ;
		break ;
		}

	}
	else if(Copy_u8Direction == PIN_INPUT)
	{
		switch(Copy_u8PortNum)
			{
				case DIO_PORTA : CLR_BIT(DDRA,Copy_u8PinNum) ;
				break ;
				case DIO_PORTB : CLR_BIT(DDRB,Copy_u8PinNum) ;
				break ;
				case DIO_PORTC : CLR_BIT(DDRC,Copy_u8PinNum) ;
				break ;
				case DIO_PORTD : CLR_BIT(DDRD,Copy_u8PinNum) ;
				break ;
			}
	}

}

void DIO_SetPinValue(u8 Copy_u8PortNum , u8 Copy_u8PinNum , u8 Copy_u8PinValue)
{
	if (Copy_u8PinValue == PIN_HIGH)
			{
				/* Check on the Required PORT Number */
				switch (Copy_u8PortNum)
				{
					case DIO_PORTA: SET_BIT(PORTA,Copy_u8PinNum); break;
					case DIO_PORTB: SET_BIT(PORTB,Copy_u8PinNum); break;
					case DIO_PORTC: SET_BIT(PORTC,Copy_u8PinNum); break;
					case DIO_PORTD: SET_BIT(PORTD,Copy_u8PinNum); break;
				}

			}

			else if (Copy_u8PinValue == PIN_LOW)
			{
				/* Check on the Required PORT Number */
				switch (Copy_u8PortNum)
				{
					case DIO_PORTA: CLR_BIT(PORTA,Copy_u8PinNum); break;
					case DIO_PORTB: CLR_BIT(PORTB,Copy_u8PinNum); break;
					case DIO_PORTC: CLR_BIT(PORTC,Copy_u8PinNum); break;
					case DIO_PORTD: CLR_BIT(PORTD,Copy_u8PinNum); break;
				}
			}

}

u8 	 DIO_GetPinValue(u8 Copy_u8PortNum , u8 Copy_u8PinNum )
{
	u8 Local_u8Result = 0 ;

	/* Check on the Required PORT Number */
			switch (Copy_u8PortNum)
			{
				case DIO_PORTA: Local_u8Result= GET_BIT(PINA,Copy_u8PinNum);
				break;
				case DIO_PORTB: Local_u8Result= GET_BIT(PINB,Copy_u8PinNum);
				break;
				case DIO_PORTC: Local_u8Result= GET_BIT(PINC,Copy_u8PinNum);
				break;
				case DIO_PORTD: Local_u8Result= GET_BIT(PIND,Copy_u8PinNum);
				break;
			}

		return Local_u8Result;
}
