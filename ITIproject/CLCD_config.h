/*
 * CLCD_interface.h
 *
 *      Author  : Jimmy
        SWC     : CLCD
        Version : 01
 */
 
#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

#define CLCD_DATA_PORT    		DIO_PORTC
#define CLCD_CONTROL_PORT		DIO_PORTB
#define CLCD_RS_PIN				DIO_PIN0
#define CLCD_RW_PIN				DIO_PIN1
#define CLCD_E_PIN				DIO_PIN2
/*
 * EIGHT_BIT
 * FOUR_BIT*/
#define CLCD_MODE         FOUR_BIT

#endif /* CLCD_CONFIG_H_ */
