/*
 * LED_program.c
 *
 *  Created on: Jan 22, 2022
 *      Author: Mohy
 */
#include "../../INCLUDE/LIB/std_types.h"
#include "../../INCLUDE/HAL/LED/LED_interface.h"
#include "../../INCLUDE/MCAL/DIO/DIO_interface.h"



/******************************************************************************
 * Function: Toggle_Led
 * I/P parms: takes Port_number(0->3), Pin_number(0->8)
 * return: None
 * DESC: this function toggle the pin on the port specified in arguments
 * *******************************************************************************/
void Toggle_Led(u8 Copy_PortNumber,u8 Copy_PinNumber)
{
	static u8 value = 0;
	value^=1;
	MDIO_voidSetPinValue(Copy_PortNumber,Copy_PinNumber,value);
}
