/*
 ===================================================================================================
 Module      : LCD
 File Name   : LCD_interface.h
 Author      : Mohamed Samy
  ===================================================================================================
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#include "STD.h"
void LCD_voidInit(void);

void LCD_voidWriteData(u8 copy_u8data);

void LCD_voidWriteCommand(u8 copy_u8Command);




void LCD_voidWriteString(u8 * copy_str);

void LCD_voidGoToXY(u8 copy_u8Row,u8 copy_u8Col);

void LCD_voidClear(void);

void LCD_voidWriteNumber( u32 Copy_u8num );


void LCD_voidWriteSpecialCharToCGRAM(u8 * copy_u8data , u8 copy_u8ByteNum );

void LCD_voidDisplaySpecialChar(u8 copy_u8ByteNum ) ;




#define LINE_1					0
#define LINE_2					1
#define LINE_3					2
#define LINE_4					3
#endif
