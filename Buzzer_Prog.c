/*
 * Buzzer_Prog.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */
#include "Buzzer_Interface.h"

void H_Buzzer_Void_BuzzerInit(void)
{
	M_DIO_Void_SetPinDirection(BUZZER_PORT,BUZZER_PIN,OUTPUT);
}
void H_Buzzer_Void_BuzzerOn(void)
{
	M_DIO_Void_SetPinValue(BUZZER_PORT,BUZZER_PIN,HIGH);
}
void H_Buzzer_Void_BuzzerOff(void)
{
	M_DIO_Void_SetPinValue(BUZZER_PORT,BUZZER_PIN,LOW);

}
void H_Buzzer_Void_BuzzerTog(void)
{
	M_DIO_Void_TogPin(BUZZER_PORT,BUZZER_PIN);
}
void H_Buzzer_Void_BuzzerOnce(void)
{
	M_DIO_Void_SetPinValue(BUZZER_PORT,BUZZER_PIN,HIGH);
	_delay_ms(BUZZER_TIME_ON);
	M_DIO_Void_SetPinValue(BUZZER_PORT,BUZZER_PIN,LOW);
}
void H_Buzzer_Void_BuzzerTwice(void)
{
H_Buzzer_Void_BuzzerOnce();
_delay_ms(BUZZER_TIME_OFF);
H_Buzzer_Void_BuzzerOnce();
}
