/*
 * main.c
 *
 *  Created on: Jan 3, 2022
 *      Author: Mohy
 */
/*
 * this application is made to work as a stopwatch usinig CTC mode on TIMER0, and toggle a LED on PA0 every one second
 * press on the numbers on the keypad to write the minutes,
 * press '+' to write the seconds,
 * press '=' to start the stopwatch,
 * press 'ON/C' to reset the timer and start entering the values from beginning
 * */


#define F_CPU 8000000UL
#include "../INCLUDE/MCAL/DIO/DIO_interface.h"
#include "../INCLUDE/MCAL/GBI/GBI_interface.h"
#include "../INCLUDE/HAL/LED/LED_interface.h"
#include "../INCLUDE/MCAL/TIMER0/TIMER0_interface.h"
#include "../INCLUDE/HAL/LCD/LCD_interface.h"
#include "../INCLUDE/HAL/KEYPAD/KEYPAD_interface.h"
#include <util/delay.h>

/*call back function for the over flow interrupt*/
void TIM0_OVF_callBackFunc(void);
#define FUNC_FOR_OVF_MODE	0

/*call back function for the compare match interrupt*/
void TIM0_CM_callBackFunc(void);
#define FUNC_FOR_CTC_MODE	1

/*number of over flows needed to count 1 sec*/
#define NO_OF_OVFS	3906
/*number of compare matches needed to count 1 sec*/
#define NO_OF_CMS	5000

u32 STOP_WATCH_TIME=0;

int main(void)
{
	/*if zero we are entering minutes, if one we are entering seconds*/
	u8 flag_for_operand=0;
	u8 minutes=0;
	u8 seconds=0;

	/*enable the global interrupt*/
	GBI_voidEnable();
	/*initialize DIO*/
	MDIO_voidInit();
	/*initialize LCD*/
	HLCD_voidInit();
	/*set call back function for ovf and compare match interrupt*/
	TIMER0_voidSetCallBack(&TIM0_OVF_callBackFunc,FUNC_FOR_OVF_MODE);
	TIMER0_voidSetCallBack(&TIM0_CM_callBackFunc,FUNC_FOR_CTC_MODE);
	/*initialize timer0*/
	TIMER0_voidInit();
	/*clear the LCD*/
	HLCD_voidClearDisplay();
	/*set curser at 0,0 and write mins */
	HLCD_voidGoToPos(0,0);
	HLCD_voidSendString("mins=");
	while(1)
	{
		/*continuesly read the keypad*/
		u8 read_value=KEYPAD_u8_GetPressedKey();
		/*check if there is no key is pressed*/
		if (read_value!=0xFF)
		{
			/*check if minutes are entered and need to enter seconds*/
			if(read_value=='+')
			{
				HLCD_voidGoToPos(1,0);
				HLCD_voidSendString("seconds=");
				flag_for_operand=1;
			}
			/*check if seconds and minutes are entered and need to start stopwatch*/
			else if(read_value=='=')
			{
				STOP_WATCH_TIME=(minutes*60)+seconds;
			}
			/*check if reset timer is needed*/
			else if(read_value=='c')
			{
				HLCD_voidClearDisplay();
				HLCD_voidGoToPos(0,0);
				HLCD_voidSendString("mins=");
				flag_for_operand=0;
				minutes=0;
				seconds=0;
				STOP_WATCH_TIME=0;
			}
			/*check if the minutes is being entered*/
			else if(flag_for_operand==0)
			{
				HLCD_voidGoToPos(0,0);
				HLCD_voidSendString("mins=");
				HLCD_voidSendCharacter(read_value);
				minutes=((minutes)*10)+(read_value-48);
			}
			/*check if the seconds is being entered*/
			else if(flag_for_operand==1)
			{
				HLCD_voidSendCharacter(read_value);
				seconds=((seconds)*10)+(read_value-48);
			}



		}
	}
	return 0;
}

/*call back function for the over flow interrupt*/
void TIM0_OVF_callBackFunc(void)
{

}


/*call back function for the compare match interrupt*/
void TIM0_CM_callBackFunc(void)
{
	static u32 counter=0;
	counter++;

	/*this will be true every one second*/
	if(counter==NO_OF_CMS)
	{
		/*check if the stop watch has finished its count down*/
		if (STOP_WATCH_TIME>0)
		{
			HLCD_voidClearDisplay();
			HLCD_voidSendNumber(STOP_WATCH_TIME/60);
			HLCD_voidSendCharacter(':');
			HLCD_voidSendNumber(STOP_WATCH_TIME%60);
			STOP_WATCH_TIME--;
		}
		/*toggle LED on PA0 every one second*/
		Toggle_Led(DIO_u8_PORTA,DIO_u8_PIN0);
		counter=0;
	}
}



