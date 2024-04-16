/*
 ===================================================================================================
 Module      : LED
 File Name   : LED_PInterface.h
 Author      : Mohamed Samy
 ===================================================================================================
 */


#ifndef LED_LED_INTERFACE_H_
#define LED_LED_INTERFACE_H_
#include "LED_Config.h"
#include "DIO_Interface.h"
#include "STD.h"
#include <util/delay.h>

#define BLU_LED        1
#define GRN_LED        2
#define RED_LED         3
#define YELLOW_LED      4
void H_LED_Void_LedInit(u8);
void H_LED_Void_LedOn(u8);
void H_LED_Void_LedOff(u8);
void H_LED_Void_LedTog(u8);

#endif /* LED_LED_INTERFACE_H_ */
