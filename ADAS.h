/*
 * ADAS.h
 *
 *  Created on: Mar 18, 2024
 *      Author: Mark
 */

#ifndef ADAS_H_
#define ADAS_H_

#include "STD.h"
#include "BitMath.h"

//#define N_POSITION	0x20
//#define D_POSITION	0x30
//#define R_POSITION	0x40
typedef enum{
	CSS_OFF,
	CSS_ON
}CSS_Stats;


typedef enum{
	BA_OFF,
	BA_ON
}BA_Stats;

typedef enum{
	DM_OFF,
	DM_ON
}DM_Stats;

typedef enum{
	SP_OFF,
	SP_ON
}SP_Stats;

typedef enum{
	N,
	R,
	D
}GEAR_BOX;

typedef enum{
	LCD_ONE,
	LCD_TWO,
	LCD_THREE,
	LCD_FOUR
}LCD_Pages;



#define PARKING_LED 	RED_LED
#define ALARM_LED	    YELLOW_LED


//#define PARKING_PB   	PB2
//#define CSS_PB 			PB3
//#define POSITION_PB 	PB4

#define POSITION_PB_INTERRUPT	INT1_CHANNEL
void A_CSS_void_Init(void);
u8 A_ADAS_Void_KeyPadUpdate(void);
void A_CSS_VoidUpdateTask(void);
void A_BAS_VoidUpdateTask(void);
void A_SL_VoidUpdateTask(void);
void A_SL_VoidIncreaseFunction(void);
void A_SL_VoidDecreaseFunction(void);
void A_DM_VoidUpdateTask(void);
void A_LCD_Void_SwitchTask(void);
void A_CSS_Void_GearBox_Handle(void);
void APP_Watch(u8 secound);
#endif /* ADAS_H_ */
