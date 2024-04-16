/*
 ===================================================================================================
 Module      : KEYPAD
 File Name   : Keypad_prog.c
 Author      : Mohamed Samy
  ===================================================================================================
 */
#include "BitMath.h"
#include "STD.h"
#include "Keypad_interface.h"
#include "Keypad_config.h"
#include "Keypad_private.h"
#include "DIO_Interface.h"
#include <util/delay.h>
/*
 *  H_KPD_void_Init
 *  	-> This function shall initialize the Keypad i.e., sets all Rows as o/P
 *  	   and all Columns as Pulled-up I/P.
 */
void KPD_voidInit(void)
{
	M_DIO_Void_SetPinDirection(KEYPAD_R0_PORT,KEYPAD_R0_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(KEYPAD_R1_PORT,KEYPAD_R1_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(KEYPAD_R2_PORT,KEYPAD_R2_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(KEYPAD_R3_PORT,KEYPAD_R3_PIN,OUTPUT);

	M_DIO_Void_SetPinDirection(KEYPAD_C0_PORT,KEYPAD_C0_PIN,INPUT);
	M_DIO_Void_SetPinDirection(KEYPAD_C1_PORT,KEYPAD_C1_PIN,INPUT);
	M_DIO_Void_SetPinDirection(KEYPAD_C2_PORT,KEYPAD_C2_PIN,INPUT);
	M_DIO_Void_SetPinDirection(KEYPAD_C3_PORT,KEYPAD_C3_PIN,INPUT);

	M_DIO_Void_SetPinValue(KEYPAD_R0_PORT,KEYPAD_R0_PIN,HIGH);
	M_DIO_Void_SetPinValue(KEYPAD_R1_PORT,KEYPAD_R1_PIN,HIGH);
	M_DIO_Void_SetPinValue(KEYPAD_R2_PORT,KEYPAD_R2_PIN,HIGH);
	M_DIO_Void_SetPinValue(KEYPAD_R3_PORT,KEYPAD_R3_PIN,HIGH);
}
/*
 *  H_KPD_void_GetPressedKey
 *  	-> This function shall return the value of the pressed key
 *  	   or KPD_NOT_PRESSED otherwise.
 */
u8 KPD_voidGetPressedKey(void)
{
	u8 Local_U8_Arr[4][4] = {{ '1' , '2' , '3' , 'A' },
			                 { '4' , '5' , '6' , 'B' },
							 { '7' , '8' , '9' , 'C' },
							 { '*' , '0' , '#' , 'D' }};
	u8 Local_U8_Reading = KPD_NOT_PRESSED;
	u8 Local_U8_Col     = 0;
	u8 Local_U8_Row     = 0;
	u8 Local_u8_colPin[4]={KEYPAD_C0_PIN ,KEYPAD_C1_PIN,KEYPAD_C2_PIN,KEYPAD_C3_PIN };

	for(Local_U8_Row = KEYPAD_R0_PIN ; Local_U8_Row >= KEYPAD_R3_PIN ; Local_U8_Row--)
	{
		M_DIO_Void_SetPinValue(KEYPAD_R0_PORT,Local_U8_Row,LOW);
		for(Local_U8_Col = 0 ; Local_U8_Col <= 3 ; Local_U8_Col++)
		{
			if(M_DIO_U8_GetPinValue(KEYPAD_C0_PORT,Local_u8_colPin[Local_U8_Col]) == KPD_PRESSED)
			{
				_delay_ms(KEYPAD_DEBOUNCING_TIME);
				if(M_DIO_U8_GetPinValue(KEYPAD_C0_PORT,Local_u8_colPin[Local_U8_Col]) == KPD_PRESSED)
				{
					Local_U8_Reading = Local_U8_Arr[KEYPAD_R0_PIN - Local_U8_Row][Local_U8_Col];
					if(Local_U8_Reading=='4'||Local_U8_Reading=='5'||Local_U8_Reading=='6'||Local_U8_Reading=='7'||Local_U8_Reading=='8'||Local_U8_Reading=='9')
					{
						while(M_DIO_U8_GetPinValue(KEYPAD_C0_PORT,Local_u8_colPin[Local_U8_Col]) == KPD_PRESSED);
						Local_U8_Reading = Local_U8_Arr[KEYPAD_R0_PIN - Local_U8_Row][Local_U8_Col];
					}
					else if(Local_U8_Reading=='2'/*||Local_U8_Reading!='1'*/)
					{
						/*1 represent brake 2 represente LCD display menus*/
					   Local_U8_Reading = Local_U8_Arr[KEYPAD_R0_PIN - Local_U8_Row][Local_U8_Col];

					}
					break;
				}
			}
		}
		M_DIO_Void_SetPinValue(KEYPAD_R0_PORT,Local_U8_Row,HIGH);
		if(Local_U8_Reading != KPD_NOT_PRESSED)
		{
			break;
		}
	}
	return Local_U8_Reading;
}
