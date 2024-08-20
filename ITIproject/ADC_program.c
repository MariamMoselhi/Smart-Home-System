#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"ADC_private.h"
#include"ADC_interface.h"





void ADC_voidINIT(){
	/*setting the adc to AVCC with external capacitor at AREF pin*/
	CLR_BIT(ADMUX,ADMUX_REFS1);
	SET_BIT(ADMUX,ADMUX_REFS0);
/*greatest division factor as time doesn't matter here*/
	SET_BIT(ADCSRA, ADCSRA_ADPS0);
	SET_BIT(ADCSRA, ADCSRA_ADPS1);
	SET_BIT(ADCSRA, ADCSRA_ADPS2);







/*enabling ADC*/
	SET_BIT(ADCSRA, ADCSRA_ADEN);
}

u16 ADC_u16GetChannelReading(u8 Copy_u8ChannelNUM){
/*anding with zeroes to clear the channels
 * while conserving the AVCC and AREF pins selection
 *  and conserving the left or right adjustment ADLAR pin
 *  here it doesn't matter because we are working on 10 bits resoln
 *  and reading them*/
	ADMUX &= 0b11100000;
	/*if we want to read only 8 bits
	 * we will set the ADLAR to 1 'left adjustment',
	 * read ADCH only
	 * and shift the reading to the right 2 bits*/


	/*setting the channel we selected*/
	ADMUX |= Copy_u8ChannelNUM;
	//start first conversion
	SET_BIT(ADCSRA, ADCSRA_ADSC);

	/*while the conversion is not complete, wait*/
	while( (GET_BIT(ADCSRA, ADCSRA_ADIF) )== 0);
	/*when the conversion is complete,
	 *  clear the flag by setting it to one
	 *  'as described in the datasheet'*/
	SET_BIT(ADCSRA, ADCSRA_ADIF);

	/*return the full ADC 'ADCH + ADCL'*/
	return ADC;


}
