/*
 * KEYPAD_interface.h
 *
 *  Created on: Jan 9, 2022
 *      Author: Mohy
 */

#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_


/************************************************************************************
* Service Name: KEYPAD_u8_GetPressedKey
* Parameters (in): None
* Return value: None
* Description:	function to check which key is pressed on the keypad
*
* Note: all rows should be output pins and initialized with ones
************************************************************************************/
u8 KEYPAD_u8_GetPressedKey(void);

/*those values are written in  this file instead of the private one
 *  to let the HCAL_voidCalculate function use them*/
#define KEYPAD_NOTPRESSED_VALUE		0xFF
#define KEYPAD_PRESSED_VALUE		0x00

#endif /* INCLUDE_HAL_KEYPAD_INTERFACE_H_ */
