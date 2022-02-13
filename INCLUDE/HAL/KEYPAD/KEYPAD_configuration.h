/*
 * KEYPAD_configuration.h
 *
 *  Created on: Jan 9, 2022
 *      Author: Mohy
 */

#ifndef KEYPAD_CONFIGURATION_H_
#define KEYPAD_CONFIGURATION_H_

#define KEYPAD_PORT			DIO_u8_PORTB
#define ROWS_NO				4
#define COLS_NO				4

#define KEYPAD_ROW1_PIN		DIO_u8_PIN0
#define KEYPAD_ROW2_PIN		DIO_u8_PIN1
#define KEYPAD_ROW3_PIN		DIO_u8_PIN2
#define KEYPAD_ROW4_PIN		DIO_u8_PIN3

#define KEYPAD_COL1_PIN		DIO_u8_PIN4
#define KEYPAD_COL2_PIN		DIO_u8_PIN5
#define KEYPAD_COL3_PIN		DIO_u8_PIN6
#define KEYPAD_COL4_PIN		DIO_u8_PIN7

/*those array that are used in the loops inside the GetPressedKey function*/
u8 KEYPAD_ROWS_ARRAY[ROWS_NO]={KEYPAD_ROW1_PIN,KEYPAD_ROW2_PIN,KEYPAD_ROW3_PIN,KEYPAD_ROW4_PIN};
u8 KEYPAD_COLS_ARRAY[COLS_NO]={KEYPAD_COL1_PIN,KEYPAD_COL2_PIN,KEYPAD_COL3_PIN,KEYPAD_COL4_PIN};


#define KEYPAD_ARRAY {{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'c','0','=','+'}}

#endif /* INCLUDE_HAL_KEYPAD_CONFIGURATION_H_ */
