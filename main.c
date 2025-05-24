/*
 * main.c
 *
 *  Created on: Nov 23, 2023
 *      Author: Yasmin
 */

#define F_CPU   16000000UL
#include <util/delay.h>
#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "TIMER_Interface.h"
#include "GIE_Interface.h"
#include "GLCD_Interface.h"
#include "GLCD_Config.h"

u8 count = 0;	//Variable to Count When OverFlow Occurs
u8 flag = 0;
u32 T1;		//Variable to Save Counts for First Rising Edge
u32 T2;		//Variable to Save Counts for Falling Edge
u32 T3;		//Variable to Save Counts for Second Rising Edge

void Vid_Drawer(void);
void Vid_TIMER1_COUNT(void);

int main(void)
{
	u8 Frequency_ARR[] ="Frequency = ";
	u8 KHZ[] ="KHZ";
	u8 DutyCycle_ARR[] = "Duty Cycle = ";
	u8 Percent[] ="%";
	u8 TimePerid_ARR[] = "Time Period = ";
	u8 ms[] ="ms";
	u8 Welcome[] = "Welcome...";

	/*Set OC2 as Output*/
	DIO_VidSetPinDirection(DIO_PORTD,7,PIN_OUTPUT);
	/*Set ICP1 as Input*/
	DIO_VidSetPinDirection(DIO_PORTD,6,PIN_INPUT);

	/*Set Data Pins Direction*/
	DIO_VidSetPortDirection(GLCD_DATA_PORT,PORT_OUTPUT);
	/*Set Control Pins Direction*/
	DIO_VidSetPinDirection(GLCD_CONTROL_PORT,GLCD_RS_PIN,PIN_OUTPUT);
	DIO_VidSetPinDirection(GLCD_CONTROL_PORT,GLCD_RW_PIN,PIN_OUTPUT);
	DIO_VidSetPinDirection(GLCD_CONTROL_PORT,GLCD_E_PIN,PIN_OUTPUT);
	DIO_VidSetPinDirection(GLCD_CONTROL_PORT,GLCD_C1_PIN,PIN_OUTPUT);
	DIO_VidSetPinDirection(GLCD_CONTROL_PORT,GLCD_C2_PIN,PIN_OUTPUT);
	DIO_VidSetPinDirection(GLCD_CONTROL_PORT,GLCD_RST_PIN,PIN_OUTPUT);

	//GLCD Initialization
	GLCD_VidInit();
	//Clear GLCD
	GLCD_VidClear();

	/*ICU Select Raising Edge & Enable Interrupt*/
	TIMER1_VidICUEnable(TIMER1_ICU_RAISING_EDGE);

	/*Timer1 Initialization Normal Mode - No Prescaler*/
	TIMER1_VidInit();
    //Timer1 Call Back Function for ICU
	CallBack_TIMER1_ICU(Vid_Drawer);
	//Timer1 Call Back Function for Over Flow
	CallBack_TIMER1_OVER_FLOW(Vid_TIMER1_COUNT);

	/*Timer2 CTC Value*/
	TIMER2_VidSetCTCValue(150);
	/*Timer2 Initialization Fast PWM Mode Non Inverting - Prescaler 256*/
	TIMER2_VidInit();

	/*GLobal Interrupt Enable*/
	GIE_VidEnable();

	f32 Frequency;
	f32 DutyCycle;
	f32 TimePeriod;

	//Select Position
	GLCD_VidSetPosition(0,0);
	GLCD_VidSendString(Welcome);
	_delay_ms(1000);
	//Clear GLCD
	GLCD_VidClear();

	while(1)
	{
		if(flag == 3)
		{
			Frequency = (1000/(((T3*1.0)/16)-((T1*1.0)/16))); //Calculate Frequency in KHz
			DutyCycle = (((T2-T1)*100.0)/(T3-T1));          //Calculate Duty Cycle
			TimePeriod = (1/Frequency);
			GLCD_VidSetPosition(0,0);                       //Select Page 0 Column 0
			GLCD_VidSendString(Frequency_ARR);
			GLCD_VidSendNumber(Frequency);                  //Display Frequency
			GLCD_VidSendString(KHZ);
			GLCD_VidSetPosition(2,0);                       //Select Page 1 Column 0
			GLCD_VidSendString(DutyCycle_ARR);
			GLCD_VidSendNumber(DutyCycle);                  //Display Duty Cycle
			GLCD_VidSendString(Percent);
			GLCD_VidSetPosition(4,0);                       //Select Page 2 Column 0
			GLCD_VidSendString(TimePerid_ARR);
			GLCD_VidSendNumber(TimePeriod);                 //Display Time Period in ms
			GLCD_VidSendString(ms);

			//Draw PWM
			GLCD_VidDrawPWM(6,Frequency,DutyCycle);

			flag = 4;
		}
	}
	return 0;
}

void Vid_Drawer(void)
{
	if(flag == 0)
	{
		T1 = TIMER1_u16_READ_COUNT() + (count*65536);                      //Store Counts For The Raising Edge
		TIMER1_VidICUEnable(TIMER1_ICU_FALLING_EDGE);   //Wait For Falling Edge
		flag = 1;
	}
	else if(flag == 1)
	{
		T2 = TIMER1_u16_READ_COUNT() + (count*65536);                      //Store Counts For The Falling Edge
		TIMER1_VidICUEnable(TIMER1_ICU_RAISING_EDGE);   //Wait For Raising Edge
		flag = 2;
	}
	else if(flag == 2)
	{
		T3 = TIMER1_u16_READ_COUNT() + (count*65536);   //Store Counts For The Raising Edge
		flag = 3;
	}

}

void Vid_TIMER1_COUNT(void)
{
	count++;   //Increment Counter When OverFlow Occurs
}

