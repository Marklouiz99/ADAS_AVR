/*
 * GIE_Prog.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */


#include "GIE_Interface.h"
#include "GIE_Private.h"

void M_GIE_Void_GlobalIntEnable(void)
{
	SET_BIT(SREG_REG,7);
}
void M_GIE_Void_GlobalIntDisable(void)
{
	CLR_BIT(SREG_REG,I_BIT);
}
