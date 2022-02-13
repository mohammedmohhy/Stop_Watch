/*
 * LED_interface.h
 *
 *  Created on: Jan 22, 2022
 *      Author: Mohy
 */

#ifndef INCLUDE_HAL_LED_INTERFACE_H_
#define INCLUDE_HAL_LED_INTERFACE_H_

/******************************************************************************
 * Function: Toggle_Led
 * I/P parms: takes Port_number(0->3), Pin_number(0->8)
 * return: None
 * DESC: this function toggle the pin on the port specified in arguments
 * *******************************************************************************/
void Toggle_Led(u8 Copy_PortNumber,u8 Copy_PinNumber);

#endif /* INCLUDE_HAL_LED_INTERFACE_H_ */
