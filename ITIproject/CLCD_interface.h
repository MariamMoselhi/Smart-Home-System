/*
 * CLCD_interface.h
 *
 *      Author  : Jimmy
        SWC     : CLCD
        Version : 01
 */

 
#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

void CLCD_voidINIT(void);
void CLCD_voidSendCommand(u8 Copy_u8Command);
void CLCD_voidSendData(u8 Copy_u8Data);
void CLCD_voidSendString(u8 * Copy_u8String);

void CLCD_voidGOTOXY(u8 Copy_u8row , u8 Copy_u8col);
void CLCD_voidWriteNumber(u32 Copy_u32Number , u8 Copy_u8X , u8 Copy_u8Y );
void CLCD_clear(void);

#endif /* CLCD_INTERFACE_H_ */
