/*
 * main.c
 *
 *  Created on: Mar 18, 2024
 *      Author: Mark
 */


#include"ADAS.h"
#include "util/delay.h"
#include "STD.h"
#include "BitMath.h"

int main()
{
	u8 Switch_Flag=0;
	A_CSS_void_Init();
	while(1)
	{
		_delay_ms(500);
		Switch_Flag=A_ADAS_Void_KeyPadUpdate();
		switch(Switch_Flag)
		{
		case(1):
				A_CSS_VoidUpdateTask();
				break;
		case(2):
				A_BAS_VoidUpdateTask();
				break;
		case(3):
				A_SL_VoidUpdateTask();
				break;
		case(4):
				A_SL_VoidIncreaseFunction();
				break;
		case(5):
				A_SL_VoidDecreaseFunction();
		        break;
		case(6):
				A_LCD_Void_SwitchTask();
		break;
		case(7):
				A_DM_VoidUpdateTask();
		break;
		}
	}
}
