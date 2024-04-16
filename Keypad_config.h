/*
 ===================================================================================================
 Module      : KEYPAD
 File Name   : Keypad_config.h
 Author      : Mohamed Samy
  ===================================================================================================
 */
#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_


#define KEYPAD_R0_PORT            DIO_PORTC
#define KEYPAD_R0_PIN             DIO_PIN5
#define KEYPAD_R1_PORT            DIO_PORTC
#define KEYPAD_R1_PIN             DIO_PIN4
#define KEYPAD_R2_PORT            DIO_PORTC
#define KEYPAD_R2_PIN             DIO_PIN3
#define KEYPAD_R3_PORT            DIO_PORTC
#define KEYPAD_R3_PIN             DIO_PIN2

#define KEYPAD_C0_PORT            DIO_PORTD
#define KEYPAD_C0_PIN             DIO_PIN7
#define KEYPAD_C1_PORT            DIO_PORTD
#define KEYPAD_C1_PIN             DIO_PIN6
#define KEYPAD_C2_PORT            DIO_PORTD
#define KEYPAD_C2_PIN             DIO_PIN5
#define KEYPAD_C3_PORT            DIO_PORTD
#define KEYPAD_C3_PIN             DIO_PIN3
/*
 * SELECT KEYPAD_DEBOUNCING_TIME IN MILLI SECOND
 */
#define KEYPAD_DEBOUNCING_TIME          120
#endif
