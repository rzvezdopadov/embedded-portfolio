#ifndef __SR_H
#define __SR_H

#include "main.h"

///////////////////////////////////////////////////////////////////////
// SR0  - PB9, 	SR1  - PB8,  SR2  - PB6, SR3  - PD7,

#define sr0_IsHigh	(GPIOB->IDR & GPIO_IDR_ID9)
#define sr0_IsLow 	(!(GPIOB->IDR & GPIO_IDR_ID9))

#define sr1_IsHigh	(GPIOB->IDR & GPIO_IDR_ID8)
#define sr1_IsLow 	(!(GPIOB->IDR & GPIO_IDR_ID8))

#define sr2_IsHigh	(GPIOB->IDR & GPIO_IDR_ID6)
#define sr2_IsLow 	(!(GPIOB->IDR & GPIO_IDR_ID6))

#define sr3_IsHigh	(GPIOD->IDR & GPIO_IDR_ID7)
#define sr3_IsLow 	(!(GPIOD->IDR & GPIO_IDR_ID7))

///////////////////////////////////////////////////////////////////////
// SR4  - PD6, 	SR5  - PD3,  SR6  - PD2, SR7  - PC12,

#define sr4_IsHigh	(GPIOD->IDR & GPIO_IDR_ID6)
#define sr4_IsLow 	(!(GPIOD->IDR & GPIO_IDR_ID6))

#define sr5_IsHigh	(GPIOD->IDR & GPIO_IDR_ID3)
#define sr5_IsLow 	(!(GPIOD->IDR & GPIO_IDR_ID3))

#define sr6_IsHigh	(GPIOD->IDR & GPIO_IDR_ID2)
#define sr6_IsLow 	(!(GPIOD->IDR & GPIO_IDR_ID2))

#define sr7_IsHigh	(GPIOC->IDR & GPIO_IDR_ID12)
#define sr7_IsLow 	(!(GPIOC->IDR & GPIO_IDR_ID12))

///////////////////////////////////////////////////////////////////////
// SR8  - PC11, SR9  - PC10, SR10 - PI3, SR11 - PC9,

#define sr8_IsHigh	(GPIOC->IDR & GPIO_IDR_ID11)
#define sr8_IsLow 	(!(GPIOC->IDR & GPIO_IDR_ID11))

#define sr9_IsHigh	(GPIOC->IDR & GPIO_IDR_ID10)
#define sr9_IsLow 	(!(GPIOC->IDR & GPIO_IDR_ID10))

#define sr10_IsHigh	(GPIOI->IDR & GPIO_IDR_ID3)
#define sr10_IsLow 	(!(GPIOI->IDR & GPIO_IDR_ID3))

#define sr11_IsHigh	(GPIOC->IDR & GPIO_IDR_ID9)
#define sr11_IsLow 	(!(GPIOC->IDR & GPIO_IDR_ID9))

///////////////////////////////////////////////////////////////////////
// SR12 - PC8,  SR13 - PC7,	 SR14 - PC6, SR15 - PG6,

#define sr12_IsHigh	(GPIOC->IDR & GPIO_IDR_ID8)
#define sr12_IsLow 	(!(GPIOC->IDR & GPIO_IDR_ID8))

#define sr13_IsHigh	(GPIOC->IDR & GPIO_IDR_ID7)
#define sr13_IsLow 	(!(GPIOC->IDR & GPIO_IDR_ID7))

#define sr14_IsHigh	(GPIOC->IDR & GPIO_IDR_ID6)
#define sr14_IsLow 	(!(GPIOC->IDR & GPIO_IDR_ID6))

#define sr15_IsHigh	(GPIOG->IDR & GPIO_IDR_ID6)
#define sr15_IsLow 	(!(GPIOG->IDR & GPIO_IDR_ID6))

///////////////////////////////////////////////////////////////////////
// SR16 - PG4,  SR17 - PG3,  SR18 - PG2, SR19 - PD13,

#define sr16_IsHigh	(GPIOG->IDR & GPIO_IDR_ID4)
#define sr16_IsLow 	(!(GPIOG->IDR & GPIO_IDR_ID4))

#define sr17_IsHigh	(GPIOG->IDR & GPIO_IDR_ID3)
#define sr17_IsLow 	(!(GPIOG->IDR & GPIO_IDR_ID3))

#define sr18_IsHigh	(GPIOG->IDR & GPIO_IDR_ID2)
#define sr18_IsLow 	(!(GPIOG->IDR & GPIO_IDR_ID2))

#define sr19_IsHigh	(GPIOD->IDR & GPIO_IDR_ID13)
#define sr19_IsLow 	(!(GPIOD->IDR & GPIO_IDR_ID13))

///////////////////////////////////////////////////////////////////////
// SR20 - PD12, SR21 - PD11, SR22 - PH6, SR23 - PF15,

#define sr20_IsHigh	(GPIOD->IDR & GPIO_IDR_ID12)
#define sr20_IsLow 	(!(GPIOD->IDR & GPIO_IDR_ID12))

#define sr21_IsHigh	(GPIOD->IDR & GPIO_IDR_ID11)
#define sr21_IsLow 	(!(GPIOD->IDR & GPIO_IDR_ID11))

#define sr22_IsHigh	(GPIOH->IDR & GPIO_IDR_ID6)
#define sr22_IsLow 	(!(GPIOH->IDR & GPIO_IDR_ID6))

#define sr23_IsHigh	(GPIOF->IDR & GPIO_IDR_ID15)
#define sr23_IsLow 	(!(GPIOF->IDR & GPIO_IDR_ID15))

void sr_init(void);
uint32_t getSR(void);

#endif 


