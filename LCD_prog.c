/*
 ===================================================================================================
 Module      : LCD
 File Name   : LCD_prog.c
 Author      : Mohamed Samy
  ===================================================================================================
 */
#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"
#include "DIO_Interface.h"
#include <util/delay.h>
void LCD_voidInit(void)
{
	M_DIO_Void_SetPinDirection(LCD_D4_PORT,LCD_D4_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D5_PORT,LCD_D5_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D6_PORT,LCD_D6_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D7_PORT,LCD_D7_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_RS_PORT,LCD_RS_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_EN_PORT,LCD_EN_PIN,OUTPUT);
	_delay_ms(30);
	LCD_voidWriteCommand(FUNCTION_SET_4BIT_2LINES_5X7_DOTS);
	_delay_ms(2);

	LCD_voidWriteCommand(DISPLAY_ON_CURSOR_OFF);
	_delay_ms(2);
	LCD_voidWriteCommand(DISPLAY_CLEAR);
	_delay_ms(2);
	LCD_voidWriteCommand(RETURN_HOME);

}

static void LCD_voidWriteBitsToSend(u8 Copy_U8_Character)
{
	M_DIO_Void_SetPinValue(LCD_D4_PORT,LCD_D4_PIN,GET_BIT(Copy_U8_Character,4));
	M_DIO_Void_SetPinValue(LCD_D5_PORT,LCD_D5_PIN,GET_BIT(Copy_U8_Character,5));
	M_DIO_Void_SetPinValue(LCD_D6_PORT,LCD_D6_PIN,GET_BIT(Copy_U8_Character,6));
	M_DIO_Void_SetPinValue(LCD_D7_PORT,LCD_D7_PIN,GET_BIT(Copy_U8_Character,7));

	M_DIO_Void_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,HIGH);
	_delay_ms(1);
	M_DIO_Void_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,LOW);
	_delay_ms(5);

	M_DIO_Void_SetPinValue(LCD_D4_PORT,LCD_D4_PIN,GET_BIT(Copy_U8_Character,0));
	M_DIO_Void_SetPinValue(LCD_D5_PORT,LCD_D5_PIN,GET_BIT(Copy_U8_Character,1));
	M_DIO_Void_SetPinValue(LCD_D6_PORT,LCD_D6_PIN,GET_BIT(Copy_U8_Character,2));
	M_DIO_Void_SetPinValue(LCD_D7_PORT,LCD_D7_PIN,GET_BIT(Copy_U8_Character,3));

	M_DIO_Void_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,HIGH);
	_delay_ms(1);
	M_DIO_Void_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,LOW);
	_delay_ms(5);
}
void LCD_voidWriteData(u8 Copy_U8_Character)
{
	M_DIO_Void_SetPinValue(LCD_RS_PORT,LCD_RS_PIN,HIGH);
	LCD_voidWriteBitsToSend(Copy_U8_Character);

}

void LCD_voidWriteCommand(u8 Copy_U8_Command)
{
	M_DIO_Void_SetPinValue(LCD_RS_PORT,LCD_RS_PIN,LOW);
	LCD_voidWriteBitsToSend(Copy_U8_Command);
}

void LCD_voidWriteString(u8 * Copy_U8_Ptr)
{
	u8 Local_U8_Counter = 0;
	while(Copy_U8_Ptr[Local_U8_Counter] != '\0')
	{
		LCD_voidWriteData(Copy_U8_Ptr[Local_U8_Counter]);
		Local_U8_Counter++;
	}
}

void LCD_voidGoToXY(u8 Copy_U8_Row,u8 Copy_U8_Col)
{
	u8 Local_U8_Arr[4] = {LCD_GOTO_R0_COMMAND , LCD_GOTO_R1_COMMAND ,LCD_GOTO_R2_COMMAND,LCD_GOTO_R3_COMMAND};
	LCD_voidWriteCommand(Local_U8_Arr[Copy_U8_Row] + Copy_U8_Col + LCD_BASE_ADDRESS);
}

void LCD_voidClear(void)
{
	LCD_voidWriteCommand(DISPLAY_CLEAR);
}

void LCD_voidWriteNumber( u32 Copy_S32_Num )
{
	if(Copy_S32_Num < 0)
	{
		Copy_S32_Num = Copy_S32_Num * -1;
		LCD_voidWriteData('-');
	}
	u8 Local_U8_Arr[10] = {0};
	s8 Local_S8_Counter = -1;
	while(Copy_S32_Num != 0)
	{
		Local_S8_Counter++;
		Local_U8_Arr[Local_S8_Counter] = Copy_S32_Num % 10;
		Copy_S32_Num = Copy_S32_Num / 10;
	}
	while(Local_S8_Counter >= 0)
	{
		LCD_voidWriteData( Local_U8_Arr[Local_S8_Counter] + LCD_ASCII_OF_0);
		Local_S8_Counter--;
	}
}


void LCD_voidWriteSpecialCharToCGRAM(u8 * copy_u8data , u8 copy_u8ByteNum )
{
	copy_u8ByteNum &= 0x7; // we only have 8 locations 0-7
	LCD_voidWriteCommand(0x40 | (copy_u8ByteNum << 3)); // Set CGRAM address
	for (int i = 0; i < 8; i++)
	{
		LCD_voidWriteData(copy_u8data[i]); // Write character pattern
	}
}

void LCD_voidDisplaySpecialChar(u8 copy_u8ByteNum )
{
	LCD_voidWriteCommand(0x80); // Move cursor to the beginning of the first line
	LCD_voidWriteData(copy_u8ByteNum);
}



