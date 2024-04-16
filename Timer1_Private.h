/*
 * Timer1_Private.h
 *
 *  Created on: Mar 17, 2024
 *      Author: samy
 */

#ifndef TIMER1_PRIVATE_H_
#define TIMER1_PRIVATE_H_

#define TCCR1A_REG    *(volatile u8*)0x4F
#define TCCR1B_REG    *(volatile u8*)0x4E
#define OCR1A_REG     *(volatile u16*)0x4A
#define ICR1_REG      *(volatile u16*)0x46
#define TCNT1_REG     *(volatile u16*)0x4C
#define TIMSK_REG     *(volatile u8*)0x59
/*   TCCR1A BITS   */
#define COM1A1_BIT                 7
#define COM1A0_BIT                 6
#define FOC1A_BIT				   3
#define WGM11_BIT                  1
#define WGM10_BIT                  0

/*   TCCR1B BITS   */
#define WGM13_BIT                  4
#define WGM12_BIT                  3
#define CS12_BIT                   2
#define CS11_BIT                   1
#define CS10_BIT                   0

#define OCIE1A_BIT				   4
#endif /* TIMER1_PRIVATE_H_ */
