#ifndef  __BUTTON_H
#define __BUTTON_H

#include "main.h"

#define Btn_Page_Up		GPIO_Pin_0
#define Btn_Prog1			GPIO_Pin_1
#define Btn_Prog2			GPIO_Pin_2		
#define Btn_Prog3			GPIO_Pin_3	
#define Btn_Prog4			GPIO_Pin_4
#define Btn_Prog5			GPIO_Pin_5	
#define Btn_Prog6			GPIO_Pin_6
#define Btn_Page_Down	GPIO_Pin_7


#define Btn_Ch1_1_On GPIO_Pin_8
#define Btn_Ch1_2_On GPIO_Pin_12
#define Btn_Ch2_1_On GPIO_Pin_10
#define Btn_Ch2_2_On GPIO_Pin_14

#define Btn_Ch1_1_Polar GPIO_Pin_9
#define Btn_Ch1_2_Polar GPIO_Pin_13
#define Btn_Ch2_1_Polar GPIO_Pin_11
#define Btn_Ch2_2_Polar GPIO_Pin_15


#define Btn_Calibr GPIO_Pin_11

void button_init(void);
uint8_t IsPushBtn(uint16_t GPIO_PIN);
uint8_t IsPopBtn(uint16_t GPIO_PIN);
uint8_t IsPushBtnI(uint16_t GPIO_PIN);
uint8_t IsPopBtnI(uint16_t GPIO_PIN);


#endif 
