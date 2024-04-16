/*
 * Timer1_Interface.h
 *
 *  Created on: Mar 17, 2024
 *      Author: samy
 */

#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

#include "STD.h"
void M_Timer1_CTCMode_Init(void);
void M_Timer1_Void_SetCallBack(void(*Copy_Ptr)(void));
void M_Timer1_Void_Timer1DeInit(void);
#endif /* TIMER1_INTERFACE_H_ */
