/*
 ===================================================================================================
 Module      : DIO
 File Name   : DIO_PROG.c
 Author      : Mohamed Samy
 Description : Source file for the AVR DIO driver
 ===================================================================================================
 */

#include "DIO_Interface.h"
#include "DIO_Private.h"
#include "STD.h"
#include "BitMath.h"

void M_DIO_Void_SetPinDirection(u8 Copy_U8_Port, u8 Copy_U8_Pin, u8 Copy_U8_State)
{
	switch(Copy_U8_State)
	{
	case INPUT :
		switch(Copy_U8_Port)
		{
		case DIO_PORTA: CLR_BIT(DDRA_REG,Copy_U8_Pin); break;
		case DIO_PORTB: CLR_BIT(DDRB_REG,Copy_U8_Pin); break;
		case DIO_PORTC: CLR_BIT(DDRC_REG,Copy_U8_Pin); break;
		case DIO_PORTD: CLR_BIT(DDRD_REG,Copy_U8_Pin); break;
		default:                                       break;
		}
		break;
	case OUTPUT:
		switch(Copy_U8_Port)
		{
		case DIO_PORTA: SET_BIT(DDRA_REG,Copy_U8_Pin); break;
		case DIO_PORTB: SET_BIT(DDRB_REG,Copy_U8_Pin); break;
		case DIO_PORTC: SET_BIT(DDRC_REG,Copy_U8_Pin); break;
		case DIO_PORTD: SET_BIT(DDRD_REG,Copy_U8_Pin); break;
		default:                                       break;
		}
		break;
	}
}

void M_DIO_Void_SetPinValue(u8 Copy_U8_Port, u8 Copy_U8_Pin, u8 Copy_U8_State)
{
	switch(Copy_U8_State)
	{
	case LOW :
		switch(Copy_U8_Port)
		{
		case DIO_PORTA: CLR_BIT(PORTA_REG,Copy_U8_Pin); break;
		case DIO_PORTB: CLR_BIT(PORTB_REG,Copy_U8_Pin); break;
		case DIO_PORTC: CLR_BIT(PORTC_REG,Copy_U8_Pin); break;
		case DIO_PORTD: CLR_BIT(PORTD_REG,Copy_U8_Pin); break;
		default:                                        break;
		}
		break;
		case HIGH:
			switch(Copy_U8_Port)
			{
			case DIO_PORTA: SET_BIT(PORTA_REG,Copy_U8_Pin); break;
			case DIO_PORTB: SET_BIT(PORTB_REG,Copy_U8_Pin); break;
			case DIO_PORTC: SET_BIT(PORTC_REG,Copy_U8_Pin); break;
			case DIO_PORTD: SET_BIT(PORTD_REG,Copy_U8_Pin); break;
			default:                                        break;
			}
			break;
	}
}
void M_DIO_Void_TogPin(u8 Copy_U8_Port,u8 Copy_U8_Pin)
{
	switch(Copy_U8_Port)
	{
	case DIO_PORTA: TOG_BIT(PORTA_REG,Copy_U8_Pin); break;
	case DIO_PORTB: TOG_BIT(PORTB_REG,Copy_U8_Pin); break;
	case DIO_PORTC: TOG_BIT(PORTC_REG,Copy_U8_Pin); break;
	case DIO_PORTD: TOG_BIT(PORTD_REG,Copy_U8_Pin); break;
	default:                                        break;
	}
}
u8   M_DIO_U8_GetPinValue(u8 Copy_U8_Port, u8 Copy_U8_Pin)
{
	u8 Local_U8_Reading = 0;
	switch(Copy_U8_Port)
	{
	case DIO_PORTA: Local_U8_Reading = GET_BIT(PINA_REG,Copy_U8_Pin); break;
	case DIO_PORTB: Local_U8_Reading = GET_BIT(PINB_REG,Copy_U8_Pin); break;
	case DIO_PORTC: Local_U8_Reading = GET_BIT(PINC_REG,Copy_U8_Pin); break;
	case DIO_PORTD: Local_U8_Reading = GET_BIT(PIND_REG,Copy_U8_Pin); break;
	default:                                                          break;
	}
	return Local_U8_Reading;
}
