#include "STD_TYPES.h"
#include "MAP.h"

s32 Map(s32 Input_Min , s32 Input_Max , s32 Output_Min ,s32 Output_Max , s32 Input_Val)
{
    s32 Local_s32ReturnOutput = 0 ;

    Local_s32ReturnOutput = ( ( (Input_Val - Input_Min) * (Output_Max - Output_Min) ) / (Input_Max - Input_Min) )  + Output_Min ;
    
    return Local_s32ReturnOutput ;
}
