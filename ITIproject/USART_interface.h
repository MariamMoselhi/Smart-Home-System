/*
 * USART_interface.h
 *
 *      Author  : Jimmy
        SWC     : USART
        Version : 01
 */
 
#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_


void USART_voidINIT(void);
void USART_voidSendSynhronous(u8 Copy_u8Data);
u8 USART_u8ReceiveSynhronous(void);




#endif /* USART_INTERFACE_H_ */
