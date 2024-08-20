/*
 * USART_interface.h
 *
 *      Author  : Jimmy
        SWC     : USART
        Version : 01
 */
 
#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_


#define UDR      		*((volatile u8*) 0x2C)
#define UCSRA       	*((volatile u8*) 0x2B)
#define UCSRA_RXC 		7
#define UCSRA_TXC 		6
#define UCSRA_UDRE 		5


#define UCSRB       	*((volatile u8*) 0x2A)
#define UCSRB_RXEN 		4
#define UCSRB_TXEN 		3
#define UCSRB_UCSZ2 	2

#define UBRRL       	*((volatile u8*) 0x29)

#define UCSRC       	*((volatile u8*) 0x40)
#define UCSRC_URSEL 	7
#define UCSRC_UMSEL 	6
#define UCSRC_UPM1 		5
#define UCSRC_UPM0 		4
#define UCSRC_USBS 		3
#define UCSRC_UCSZ1 	2
#define UCSRC_UCSZ0 	1



#endif /* USART_PRIVATE_H_ */
