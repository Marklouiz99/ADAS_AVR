/*
 ===================================================================================================
 Module      : DIO
 File Name   : DIO_Interface.h
 Author      : Mohamed Samy
 ===================================================================================================
 */

#ifndef DIO_DIO_INTERFACE_H_
#define DIO_DIO_INTERFACE_H_



#include "BitMath.h"
#include "STD.h"



#define INPUT               0
#define OUTPUT              1
#define LOW                 0
#define HIGH                1

#define DIO_PIN0            0
#define DIO_PIN1            1
#define DIO_PIN2            2
#define DIO_PIN3            3
#define DIO_PIN4            4
#define DIO_PIN5            5
#define DIO_PIN6            6
#define DIO_PIN7            7

#define DIO_PORTA           1
#define DIO_PORTB           2
#define DIO_PORTC           3
#define DIO_PORTD           4

void M_DIO_Void_SetPinDirection(u8,u8,u8);
void M_DIO_Void_SetPinValue(u8,u8,u8);
void M_DIO_Void_TogPin(u8,u8);
u8   M_DIO_U8_GetPinValue(u8,u8);

#endif /* DIO_DIO_INTERFACE_H_ */
