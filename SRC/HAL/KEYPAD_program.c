/*
 * KEYPAD_program.c
 *
 *  Created on: Jan 9, 2022
 *      Author: Mohy
 */

#include "../../INCLUDE/MCAL/DIO/DIO_interface.h"
#include "../../INCLUDE/MCAL/DIO/DIO_private.h"
#include "../../INCLUDE/MCAL/DIO/DIO_configuratios.h"

#include "../../INCLUDE/HAL/KEYPAD/KEYPAD_interface.h"
#include "../../INCLUDE/HAL/KEYPAD/KEYPAD_configuration.h"

#include "../../INCLUDE/LIB/bit_math.h"

#include <util/delay.h>

/************************************************************************************
* Service Name: KEYPAD_u8_GetPressedKey
* Parameters (in): None
* Return value: None
* Description:	function to check which key is pressed on the keypad
*
* Note: all rows should be output pins and initialized with ones
************************************************************************************/
u8 KEYPAD_u8_GetPressedKey(void)
{
	u8 local_key_ID[ROWS_NO][COLS_NO] = KEYPAD_ARRAY;
	u8 key_ID=KEYPAD_NOTPRESSED_VALUE;
	u8 key_Value=0;
	u8 key_flag=KEYPAD_NOTPRESSED_VALUE;

	for(u8 i=0;i<ROWS_NO;i++)
	{
		MDIO_voidSetPinValue(KEYPAD_PORT,KEYPAD_ROWS_ARRAY[i],DIO_u8_LOW);
		for(u8 j=0;j<COLS_NO;j++)
		{
			key_Value=MDIO_u8GetPinValue(KEYPAD_PORT,KEYPAD_COLS_ARRAY[j]);
			if(key_Value==DIO_u8_LOW)
			{
				/*solving the bouncing effect if the key_value still low, the key is stabilized*/
				_delay_ms(20);
				key_Value=MDIO_u8GetPinValue(KEYPAD_PORT,KEYPAD_COLS_ARRAY[j]);
				if(key_Value==DIO_u8_LOW)
				{
					key_flag=KEYPAD_PRESSED_VALUE;

					/*waiting until the key is released*/
					while(key_Value==DIO_u8_LOW)
					{
						key_Value=MDIO_u8GetPinValue(KEYPAD_PORT,KEYPAD_COLS_ARRAY[j]);
					}

					key_ID=local_key_ID[i][j];
					break;
				}

			}
		}
		MDIO_voidSetPinValue(KEYPAD_PORT,KEYPAD_ROWS_ARRAY[i],DIO_u8_HIGH);
		if(key_flag==KEYPAD_PRESSED_VALUE)
		{
			break;
		}
	}


	return key_ID;
}

