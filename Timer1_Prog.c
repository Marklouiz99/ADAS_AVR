/*
 * Timer1_Prog.c
 *
 *  Created on: Mar 17, 2024
 *      Author: samy
 */
#include "Timer1_Interface.h"
#include "Timer1_Config.h"
#include "Timer1_Private.h"
#include <avr/interrupt.h>

/*--------------------------------------------------------------------------------------------*/
/*   GLOBAL VARIABLES   */
/*--------------------------------------------------------------------------------------------*/
void(*Timer_CallBack)(void);


void M_Timer1_Void_SetCallBack(void(*Copy_Ptr)(void))
{
	Timer_CallBack = Copy_Ptr;
}


void M_Timer1_CTCMode_Init(void)
{
	/*
	 *Timer/Counter1 Set Normal port operation OC1A/OC1B disconnected.
	 *Compare Output Mode for Compare unit A  (COM1A1 =0 COM1A0=0)
	 *Compare Output Mode for Compare unit B  (COM1B1 =0 COM1B0=0)
	 *FOC1A = 1: Force Output Compare for Compare unit A --> because non-PWM mode
	 *Waveform Generation Mode (select mode 4 CTC MODE)
				WGM13 = 0
				WGM12 = 1
				WGM11 = 0
				WGM10 = 0
	 *
	 *Select clk/1024 (From prescaler) - clk = 16Mhz
	 * timer frequency  = clk / 1024 = 16000000 / 1024 = 15625
	 * TCNT1 =0
	 * OCR1A = top --> (15625 to generate interrupt each 1 sec)
	 * Output Compare A Match Interrupt Enable
	 * 		OCIE1A =1
	 */
	TCNT1_REG  = 0;
	OCR1A_REG  = 15625;
	TIMSK_REG |= (1<<OCIE1A_BIT);

	TCCR1A_REG |= (1<<FOC1A_BIT);
	TCCR1B_REG |= (1<<WGM12_BIT) |(1<<CS12_BIT) |(1<<CS10_BIT);
}

void M_Timer1_Void_Timer1DeInit(void)
{
	TCNT1_REG =0;
	TIMSK_REG &=~(1<<OCIE1A_BIT);
	OCR1A_REG =0;
}
void __vector_7 (void) __attribute__ ((signal,used, externally_visible)) ;
void __vector_7 (void)
{
	Timer_CallBack();
}
/*
ISR(TIMER1_COMPA_vect)
{
	Timer_CallBack();
}*/
