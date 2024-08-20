/*
 * USART_interface.c
 *
 *      Author  : Jimmy
        SWC     : USART
        Version : 01
 */


#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "USART_private.h"
#include "USART_config.h"
#include "USART_interface.h"



void USART_voidINIT(void)
{
	u8 Local_u8TempUCSRCValue = 0 ;

	/* Set UCSRC by Register Select */
	SET_BIT(Local_u8TempUCSRCValue,UCSRC_URSEL);
	/* Choose Asynchronous */
	CLR_BIT(Local_u8TempUCSRCValue,UCSRC_UMSEL);

	/* Disable Parity mode */

	CLR_BIT(Local_u8TempUCSRCValue,UCSRC_UPM1);
	CLR_BIT(Local_u8TempUCSRCValue,UCSRC_UPM0);

	/* Stop Bit -> 1 */
	CLR_BIT(Local_u8TempUCSRCValue,UCSRC_USBS);

	/* Data Bits -> 8 Bits */

	SET_BIT(Local_u8TempUCSRCValue,UCSRC_UCSZ1);
	SET_BIT(Local_u8TempUCSRCValue,UCSRC_UCSZ0);

	UCSRC = Local_u8TempUCSRCValue ;

	/* Baud Rate -> 9600 */

	UBRRL = 51 ;

	/* Enable Receiver */
	SET_BIT(UCSRB,UCSRB_RXEN);

	/* Enable Transmitter */
	SET_BIT(UCSRB,UCSRB_TXEN);

}

void USART_voidSendSynhronous(u8 Copy_u8Data)
{
	while( ( (GET_BIT(UCSRA,UCSRA_UDRE ) ) == 0));
	UDR = Copy_u8Data ;
}

u8 USART_u8ReceiveSynhronous(void)
{
	while(( ( GET_BIT(UCSRA,UCSRA_RXC ) ) == 0));
	return UDR ;
}

