/*
 * ADAS.c
 *
 *  Created on: Mar 18, 2024
 *      Author: Mark
 */


#include "STD.h"
#include "BitMath.h"
#include "ADAS.h"
#include "DIO_Interface.h"
#include "LCD_interface.h"
#include "LED_Interface.h"

#include "util/delay.h"
#include "EXTINT_Interface.h"
#include "GIE_Interface.h"
#include "Buzzer_Interface.h"
#include "ADC_Interface.h"
#include "POT_Interface.h"
#include "Keypad_interface.h"
#include "Timer1_Interface.h"

/**********************************************************/
/****************** Global Variables **********************/
/**********************************************************/
volatile u8 g_secoundCounter =0;
volatile u8 g_WarrningCounter =0;
volatile u8 relay_Flag =0;
volatile u8 Secound_1 =0;
volatile u8 Secound_2 =0;
volatile u8 Minute_1  =0;
volatile u8 Minute_2  =45;
volatile u8 Hour_1    =0;
volatile u8 Hour_2    =0;
CSS_Stats CSSStatus=CSS_OFF;
BA_Stats BAStatus=BA_OFF;
SP_Stats SPStatus=SP_OFF;
DM_Stats DMStatus=DM_OFF;
static volatile GEAR_BOX GearPosition = N;

LCD_Pages Page=LCD_ONE;


u16 CurrentSpeed=1;
u16 PreviousSpeed=0;
u8 FirstTimeFlag=0;
u8 SpeedLimiter=40;
u8 SwitchFlag=0;

volatile u8 InittFlag1=0;
volatile u8 InittFlag2=0;


void A_LCD_void_FirstState(void);
void A_LCD_void_SecondState(void);
void A_LCD_void_ThirdState(void);
void A_LCD_void_ThirdState(void);
void  A_LCD_void_FourthState(void);
void APP_Disply_Watch(void);
void APP_SecoundCounter(void);
/* Initialization function */
void A_CSS_void_Init(void)
{
	/* Global interrupt: Enable */
	M_GIE_Void_GlobalIntEnable();

	/* Enable EXTINT Channel 1: POSITION_PB_INTERRUPT defined as INT1_CHANNEL */
	M_EXTINT_Void_EXTINTInit(POSITION_PB_INTERRUPT);

	/* CallBack Function for EXTINT Channel 1: POSITION_PB_INTERRUPT defined as INT1_CHANNEL
	  A_CSS_Void_GearBox_Handle: function will be invoked in ISR for INT1  */
	M_EXTINT_Void_SetCallBack(POSITION_PB_INTERRUPT,&A_CSS_Void_GearBox_Handle);

	/* LCD Initialize and Display initial state: CCS=OFF, R-N-D=N */
	LCD_voidInit();
	LCD_voidGoToXY(LINE_1,4);
	_delay_ms(20);
	LCD_voidWriteString("  Welcome ");
	_delay_ms(1000);

	/* Buttons Initialize: */

	KPD_voidInit();

	/* Buzzer Initialize: */
	H_Buzzer_Void_BuzzerInit();

	/* LEDs Initialize: */

	H_LED_Void_LedInit(PARKING_LED);

	H_LED_Void_LedInit(ALARM_LED);
	H_LED_Void_LedInit(GRN_LED);
	H_POt_Void_POTInit();

	M_Timer1_CTCMode_Init();

	M_Timer1_Void_SetCallBack(&APP_SecoundCounter);
	/* Relay */
	M_DIO_Void_SetPinDirection(DIO_PORTC,DIO_PIN7,OUTPUT);
}

u8 A_ADAS_Void_KeyPadUpdate(void)
{
	_delay_ms(500);
	u8 Keypad_Update = KPD_NOT_PRESSED;
	do
	{   Keypad_Update = KPD_NOT_PRESSED;
	Keypad_Update = KPD_voidGetPressedKey();
	}while(Keypad_Update == KPD_NOT_PRESSED && g_WarrningCounter < 10);
	if(g_WarrningCounter != 10)
	{
		g_WarrningCounter =0;

		switch(Keypad_Update)
		{
		case '4':
			SwitchFlag=1;
			break;
		case '5':
			SwitchFlag=2;
			break;
		case '6':
			SwitchFlag=3;
			break;
		case '7':
			SwitchFlag=4;
			break;
		case '8':
			SwitchFlag=5;
			break;
		case '9':
			SwitchFlag=6;
			break;
		case '2':
			while (KPD_voidGetPressedKey() == '2')
			{
				H_LED_Void_LedOn(PARKING_LED);
				SwitchFlag=8;
			}
			SwitchFlag=0;
			H_LED_Void_LedOff(PARKING_LED);
			break;
		case '3':
			SwitchFlag=7;
			break;
		default:
			break;

		}
		return SwitchFlag;

	}else
	{
		LCD_voidClear();
		LCD_voidWriteString("WARRING!!!");

		do
		{
		M_DIO_Void_TogPin(DIO_PORTC ,DIO_PIN7);
		_delay_ms(500);
		Keypad_Update = KPD_NOT_PRESSED;
		Keypad_Update = KPD_voidGetPressedKey();
		}while(Keypad_Update == KPD_NOT_PRESSED );

		g_WarrningCounter=0;
		LCD_voidClear();
		LCD_voidWriteString("Welcome");
	}

}

void A_CSS_VoidUpdateTask(void)
{
	if(GearPosition==D)
	{
		if(FirstTimeFlag==0)
		{
			H_POT_Void_POTRead(&CurrentSpeed);
			H_POT_Void_POTRead(&PreviousSpeed);
			FirstTimeFlag=1;
		}
		else
		{
			PreviousSpeed=CurrentSpeed;
			_delay_ms(500);
			H_POT_Void_POTRead(&CurrentSpeed);
		}
		if(CurrentSpeed!=PreviousSpeed&&CSSStatus==CSS_ON)
		{
			CSSStatus=CSS_OFF;
		}
		else if (CurrentSpeed==PreviousSpeed)
		{
			switch(CSSStatus)
			{
			case CSS_OFF:
				CSSStatus=CSS_ON;
				/*fire buzzer*/
				/* Open Buzzer For 10ms, then do no thing */
				H_Buzzer_Void_BuzzerOnce();
				break;
			case CSS_ON:
				CSSStatus=CSS_OFF;
				/*fire buzzer*/
				/* Open Buzzer For 10ms, then do no thing */
				H_Buzzer_Void_BuzzerOnce();
				break;
			default:
				break;
			}
		}
		if(Page==LCD_THREE)
		{
			A_LCD_void_SecondState();
		}
	}
}


void A_BAS_VoidUpdateTask(void)
{
	if(GearPosition==D)
	{
		switch(BAStatus)
		{
		case BA_OFF:
			BAStatus=BA_ON;
			break;
		case BA_ON:
			BAStatus=BA_OFF;
			break;
		default:
			break;
		}
		if(Page==LCD_THREE)
		{
			A_LCD_void_SecondState();
		}
	}
}

void A_SL_VoidUpdateTask(void)
{
	if(GearPosition==D)
	{
		switch(SPStatus)
		{
		case SP_OFF:
			SPStatus=SP_ON;
			break;
		case SP_ON:
			SPStatus=SP_OFF;
			break;
		default:
			break;
		}
		PreviousSpeed=CurrentSpeed;
		H_POT_Void_POTRead(&CurrentSpeed);
		if(SPStatus==SP_ON)
		{
			while(CurrentSpeed>SpeedLimiter)
			{
				/*Relay on OFF*/
				/* flag = 1*/
				relay_Flag = 1;
				PreviousSpeed=CurrentSpeed;
				H_POT_Void_POTRead(&CurrentSpeed);
				if(KPD_voidGetPressedKey()=='7')
				{
					A_SL_VoidIncreaseFunction();
				}

				if(KPD_voidGetPressedKey()=='6')
				{
                    SPStatus=SP_OFF;
					break;
				}
				if(GearPosition==R||GearPosition==N)
				{
					SPStatus=SP_OFF;
					break;
				}
				if(Page==LCD_THREE)
				{
					A_LCD_void_SecondState();
				}

			}
			/* clear flag*/
			relay_Flag =0;

		}
		if(Page==LCD_THREE)
		{
			A_LCD_void_SecondState();
		}
	}
}

void A_SL_VoidIncreaseFunction(void)
{
	SpeedLimiter+=5;
	if(Page==LCD_TWO)
	{
		A_LCD_void_FirstState();
	}

}

void A_SL_VoidDecreaseFunction(void)
{

	SpeedLimiter-=5;
	if(Page==LCD_TWO)
	{
		A_LCD_void_FirstState();
	}
}
void A_LCD_Void_SwitchTask(void)
{
	LCD_voidClear();
	switch(Page)
	{
	case LCD_ONE  : A_LCD_void_FirstState();
					   break;
	case LCD_TWO  : A_LCD_void_SecondState();   break;
	case LCD_THREE : A_LCD_void_ThirdState();   break;
	case LCD_FOUR  : A_LCD_void_FourthState();  break;
	default:                                    break;
	}
	if(Page==LCD_FOUR)
	{

		Page=LCD_ONE;
	}
	else
	{
		Page++;
	}

}
void A_LCD_void_FirstState(void)
{
	/*first line CCS|BA|SP|DM

		 second line   ------------------------
		 */
		LCD_voidGoToXY(LINE_1,4);
		LCD_voidWriteString("CCS|BA|SP|DM");
		_delay_ms(20);
		LCD_voidGoToXY(LINE_2,0);
		LCD_voidWriteString("----------------------");
		_delay_ms(20);
		LCD_voidGoToXY(LINE_3,0);
		_delay_ms(20);
		if(GearPosition==D)
		{
			LCD_voidWriteString("Speed:");
			LCD_voidWriteNumber(CurrentSpeed);
			LCD_voidWriteString("Km/h");
		}
		LCD_voidGoToXY(LINE_3,13);
		_delay_ms(20);
		LCD_voidWriteString("MS:");
		LCD_voidWriteNumber(SpeedLimiter);
		LCD_voidWriteString("Km");
	//	LCD_voidGoToXY(LINE_4,0);
	//	_delay_ms(20);
	//	/* display LCD string KMs counter:*/
	//	LCD_voidWriteNumber(KMs_Counter);
		LCD_voidGoToXY(LINE_4,17);
		_delay_ms(20);
		LCD_voidWriteString("1/4");
}
void A_LCD_void_SecondState(void)
{

	LCD_voidGoToXY(LINE_4,17);
	_delay_ms(20);
	LCD_voidWriteString("2/4");
	LCD_voidGoToXY(LINE_4,10);
	_delay_ms(20);
	LCD_voidWriteString("DM:OFF");
	LCD_voidGoToXY(LINE_1,4);
	_delay_ms(20);
	LCD_voidWriteString("CCS|BA|SP|DM");
	_delay_ms(20);
	LCD_voidGoToXY(LINE_2,4);
	LCD_voidWriteString("---------------------");
	_delay_ms(20);
	/*Display all systems are off*/
	LCD_voidGoToXY(LINE_3,0);
	_delay_ms(20);
	LCD_voidWriteString("CCS:OFF");
	LCD_voidGoToXY(LINE_3,10);
	_delay_ms(20);
	LCD_voidWriteString("BA:OFF");
	LCD_voidGoToXY(LINE_4,0);
	_delay_ms(20);
	LCD_voidWriteString("SP:OFF");
	if(GearPosition==N||GearPosition==R)
	{

	}
	else if(GearPosition==D)
	{
		if(CSSStatus==CSS_OFF)
		{
			/*CCS:ON*/
			LCD_voidGoToXY(LINE_3,0);
			_delay_ms(20);
			LCD_voidWriteString("CCS:OFF");
		}
		else if(CSSStatus==CSS_ON)
		{
			/*CCS:ON*/
			LCD_voidGoToXY(LINE_3,0);
			_delay_ms(20);
			LCD_voidWriteString("CCS:ON ");
		}
		if(BAStatus==BA_OFF)
		{
			/*BA:ON*/
			LCD_voidGoToXY(LINE_3,10);
			_delay_ms(20);
			LCD_voidWriteString("BA:OFF");
		}
		else if(BAStatus==BA_ON)
		{
			/*BA:ON*/
			LCD_voidGoToXY(LINE_3,10);
			_delay_ms(20);
			LCD_voidWriteString("BA:ON ");
		}
		if(SPStatus==SP_ON)
		{
			/*SP:ON*/
			LCD_voidGoToXY(LINE_4,0);
			_delay_ms(20);
			LCD_voidWriteString("SP:ON ");
		}
		if(SPStatus==SP_OFF)
		{
			/*SP:ON*/
			LCD_voidGoToXY(LINE_4,0);
			_delay_ms(20);
			LCD_voidWriteString("SP:OFF");
		}
	}

}
void A_LCD_void_ThirdState(void)
{
	LCD_voidGoToXY(LINE_4,17);
		_delay_ms(20);
		LCD_voidWriteString("3/4");
		LCD_voidGoToXY(LINE_1,4);
		_delay_ms(20);
		LCD_voidWriteString("CCS|BA|SP|DM");
		_delay_ms(20);
		LCD_voidGoToXY(LINE_2,4);
		LCD_voidWriteString("---------------------");
		_delay_ms(20);
		LCD_voidGoToXY(LINE_3,0);
		_delay_ms(20);
		if(GearPosition==D)
		{
			/*Display R,N,D:D*/
			LCD_voidWriteString("R,N,D:D");
		}
		else if(GearPosition==N)
		{
			/*Display R,N,D:N*/
			LCD_voidWriteString("R,N,D:N");
		}
		else if(GearPosition==R)
		{
			/*Display R,N,D:R*/
			LCD_voidWriteString("R,N,D:R");
		}
}
void A_DM_VoidUpdateTask(void)
{
	if(GearPosition==D)
		{
			switch(DMStatus)
			{
			case DM_OFF:
				BAStatus=DM_ON;
				break;
			case DM_ON:
				BAStatus=DM_OFF;
				break;
			default:
				break;
			}
			if(Page==LCD_THREE)
			{
				A_LCD_void_SecondState();
			}
		}
}
void A_CSS_Void_GearBox_Handle(void)
{

	switch (GearPosition)
	{
	case N :
		/* Check Park Button */
		if((KPD_voidGetPressedKey() == '2'))
		{
			GearPosition = D;
			/* Open Buzzer For 10ms, then do no thing */
			H_Buzzer_Void_BuzzerOnce();
			H_LED_Void_LedTog(GRN_LED);


		}
		else
		{
			/* Generate Alarm */
			while((KPD_voidGetPressedKey() == 'A'))
			{
				H_LED_Void_LedOn(ALARM_LED);
			}
			H_LED_Void_LedOff(ALARM_LED);


		}

		break;
	case D:
		/* Check Park Button */
		if((KPD_voidGetPressedKey() == '2'))
		{
			GearPosition = R;
			/* Open Buzzer For 10ms, then do no thing */
			H_Buzzer_Void_BuzzerOnce();
			H_LED_Void_LedTog(GRN_LED);


		}
		else
		{
			/* Generate Alarm */
			while((KPD_voidGetPressedKey() == 'A'))
			{
				H_LED_Void_LedOn(ALARM_LED);
			}
			H_LED_Void_LedOff(ALARM_LED);


		}
//		if(Page==LCD_FOUR)
//		{
//			A_LCD_void_ThirdState();
//		}
		break;
	case R:
		/* Check Park Button */
		if((KPD_voidGetPressedKey() == '2'))
		{
			GearPosition = N;
			/* Open Buzzer For 10ms, then do no thing */
			H_Buzzer_Void_BuzzerOnce();
			H_LED_Void_LedTog(GRN_LED);


		}
		else
		{
			/* Generate Alarm */
			while((KPD_voidGetPressedKey() == 'A'))
			{
				H_LED_Void_LedOn(ALARM_LED);
			}
			H_LED_Void_LedOff(ALARM_LED);


		}
//		if(Page==LCD_FOUR)
//		{
//			A_LCD_void_ThirdState();
//		}
		break;
	default:                                   break;
	}
	if(Page==LCD_FOUR)
	{
		A_LCD_void_ThirdState();

	}


}
void APP_Watch(u8 secound)
{
	Secound_1 = g_secoundCounter;
	if(Secound_1 > 9)
	{
		Secound_1 =0;
		Secound_2++;
		g_secoundCounter=0;
	}
	if(Secound_2 > 5)
	{
		Secound_2 =0;
		Minute_1++;
	}

	if(Minute_1 > 9)
	{
		Minute_1 =0;
		Minute_2++;
	}
	if(Minute_2 > 5)
	{
		Minute_1 =0;
		Hour_1++;
	}
/* handel hours*/
	if(Hour_1 > 9)
	{
		Hour_1 =0;
		Hour_2++;
	}

	if(Hour_2 > 2)
	{
		Secound_1  =0;
		Secound_2  =0;
		Minute_1   =0;
		Minute_2   =0;
		Hour_1     =0;
		Hour_2     =0;
	}

}
void APP_SecoundCounter(void)
{
	g_secoundCounter++;
	g_WarrningCounter++;
	APP_Watch(g_secoundCounter);
	if(relay_Flag == 1)
	{
		M_DIO_Void_TogPin(DIO_PORTC ,DIO_PIN7);
	}else
	{
		M_DIO_Void_SetPinValue(DIO_PORTC ,DIO_PIN7,LOW);
	}
	/* if flag == 1 */
	/*toggle relay
	 *
	 *    */

}
void APP_Disply_Watch(void)
{

	LCD_voidGoToXY(LINE_1,4);
	LCD_voidWriteString("time");
	LCD_voidGoToXY(LINE_2,4);
	LCD_voidWriteString("00:00:00");
	LCD_voidGoToXY(LINE_2,4);
	LCD_voidWriteNumber(Hour_2);
	LCD_voidGoToXY(LINE_2,5);
	LCD_voidWriteNumber(Hour_1);
	LCD_voidGoToXY(LINE_2,6);
	LCD_voidWriteString(":");
	LCD_voidGoToXY(LINE_2,7);
	LCD_voidWriteNumber(Minute_2);
	LCD_voidGoToXY(LINE_2,8);
	LCD_voidWriteNumber(Minute_1);
	LCD_voidGoToXY(LINE_2,9);
	LCD_voidWriteString(":");
	LCD_voidGoToXY(LINE_2,10);
	LCD_voidWriteNumber(Secound_2);
	LCD_voidGoToXY(LINE_2,11);
	LCD_voidWriteNumber(Secound_1);
	_delay_ms(50);
}
void  A_LCD_void_FourthState(void)
{
	APP_Disply_Watch();

}
