
#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

/* Port Numbers */

#define DIO_PORTA   0
#define DIO_PORTB   1
#define DIO_PORTC   2
#define DIO_PORTD   3


/* Pins Numbers */

#define DIO_PIN0   	0
#define DIO_PIN1   	1
#define DIO_PIN2   	2
#define DIO_PIN3   	3
#define DIO_PIN4   	4
#define DIO_PIN5   	5
#define DIO_PIN6   	6
#define DIO_PIN7   	7

/* Directions Options */

#define  PIN_INPUT    	0
#define  PIN_OUTPUT   	1

/* Directions Options */

#define  PORT_INPUT    	0x00
#define  PORT_OUTPUT   	0xff


/* PIN Value Options */

#define   PIN_LOW    	0
#define   PIN_HIGH   	1

/* PIN Value Options */

#define   PORT_LOW    	0x00
#define   PORT_HIGH   	0xff
 
void DIO_SetPort_Direction(u8 Copy_u8PortNum , u8 Copy_u8Direction);

void DIO_SetPort_value(u8 Copy_u8PortNum , u8 Copy_u8PortValue);

void DIO_SetPin_Direction(u8 Copy_u8PortNum , u8 Copy_u8PinNum , u8 Copy_u8Direction); 

void DIO_SetPinValue(u8 Copy_u8PortNum , u8 Copy_u8PinNum , u8 Copy_u8PinValue); 

u8 	 DIO_GetPinValue(u8 Copy_u8PortNum , u8 Copy_u8PinNum );

#endif
