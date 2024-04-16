/*
 * POT_Prog.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#include "POT_Interface.h"
#include "ADC_Interface.h"


void H_POt_Void_POTInit(void)
{
	M_ADC_Void_ADCInit();
}
void H_POT_Void_POTRead(u16*Copy_U16_Ptr)
{
	u16 Local_U16_ADCReading = 0;
	Local_U16_ADCReading     = M_ADC_U16_ADCRead(POT_CHANNEL);
	*Copy_U16_Ptr            = (u16)((u32)Local_U16_ADCReading * 200 ) / 1023;
	if(*Copy_U16_Ptr>200)
	{
		*Copy_U16_Ptr=200;
	}
}
