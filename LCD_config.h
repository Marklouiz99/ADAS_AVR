/*
 ===================================================================================================
 Module      : LCD
 File Name   : LCD_config.h
 Author      : Mohamed Samy
  ===================================================================================================
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_


#define LCD_D0_PORT         DIO_PORTA
#define LCD_D0_PIN          DIO_PIN0
#define LCD_D1_PORT         DIO_PORTA
#define LCD_D1_PIN          DIO_PIN1
#define LCD_D2_PORT         DIO_PORTA
#define LCD_D2_PIN          DIO_PIN2
#define LCD_D3_PORT         DIO_PORTA
#define LCD_D3_PIN          DIO_PIN3

#define LCD_D4_PORT         DIO_PORTB
#define LCD_D4_PIN          DIO_PIN0
#define LCD_D5_PORT         DIO_PORTB
#define LCD_D5_PIN          DIO_PIN1
#define LCD_D6_PORT         DIO_PORTB
#define LCD_D6_PIN          DIO_PIN2
#define LCD_D7_PORT         DIO_PORTB
#define LCD_D7_PIN          DIO_PIN4

#define LCD_RS_PORT         DIO_PORTA
#define LCD_RS_PIN          DIO_PIN3
#define LCD_EN_PORT         DIO_PORTA
#define LCD_EN_PIN          DIO_PIN2
/*
 * LCD_MODE OPTIONS : [ LCD_8_BIT_MODE , LCD_4_BIT_MODE ]
 */
#define LCD_MODE            LCD_4_BIT_MODE

#endif
