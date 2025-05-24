/*
 * TIMER_Interface.h
 *
 *  Created on: Nov 18, 2023
 *      Author: Yasmin
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#define TIMER1_ICU_RAISING_EDGE   0
#define TIMER1_ICU_FALLING_EDGE   1


//Timer0 Initialization
void TIMER0_VidInit(void);
//Timer0 Set Preload
void TIMER0_VidSetPreload(u8 Copy_u8Preload);
//Timer0 Set CTC Value
void TIMER0_VidSetCTCValue(u8 Copy_u8CTCValue);
//Call Back Function for Timer0 CTC ISR
void CallBack_TIMER0_CTC(void(*ptr)(void));
//Call Back Function for Timer0 Over Flow ISR
void CallBack_TIMER0_OVER_FLOW(void(*ptr)(void));

//Timer1 Initialization
void TIMER1_VidInit(void);
//Timer1 Set Preload
void TIMER1_VidSetPreload(u16 Copy_u16Preload);
//Timer1 Set CTC Value
void TIMER1_VidSetCTCValue(u16 Copy_u16CTCValue);
//Timer1 Set Top Value
void TIMER1_VidSetTopValue(u16 Copy_u16TopValue);
//Timer1 Select Sense Edge & Enable ICU Interrupt
void TIMER1_VidICUEnable(u8 Copy_u8Edge);
//Function For Returning Register ICR1
u16 TIMER1_u16_READ_COUNT(void);
//Call Back Function for Timer1 ICU ISR
void CallBack_TIMER1_ICU(void(*ptr)(void));
//Call Back Function for Timer1 CTC Channel A ISR
void CallBack_TIMER1_CTC_Channel_A(void(*ptr)(void));
//Call Back Function for Timer1 CTC Channel B ISR
void CallBack_TIMER1_CTC_Channel_B(void(*ptr)(void));
//Call Back Function for Timer1 OverFlow ISR
void CallBack_TIMER1_OVER_FLOW(void(*ptr)(void));

//Timer2 Initialization
void TIMER2_VidInit(void);
//Timer2 Set Preload
void TIMER2_VidSetPreload(u8 Copy_u8Preload);
//Timer2 Set CTC Value
void TIMER2_VidSetCTCValue(u8 Copy_u8CTCValue);
//Call Back Function for Timer2 CTC
void CallBack_TIMER2_CTC(void(*ptr)(void));
//Call Back Function for Timer2 Over Flow ISR
void CallBack_TIMER2_OVER_FLOW(void(*ptr)(void));

#endif /* TIMER_INTERFACE_H_ */
