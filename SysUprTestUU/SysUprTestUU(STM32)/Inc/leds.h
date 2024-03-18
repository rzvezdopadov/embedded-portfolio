#ifndef __LEDS_H
#define __LEDS_H

#include "main.h"

// PC15 - LED1, PI9 - LED2, PI10 - LED3
// PI11 - LED4, PF0 - LED5, PF1  - LED6

#define led1_IsHigh	(GPIOC->IDR & GPIO_IDR_ID15)
#define led1_IsLow 	(!(GPIOC->IDR & GPIO_IDR_ID15))

#define led2_IsHigh	(GPIOI->IDR & GPIO_IDR_ID9)
#define led2_IsLow 	(!(GPIOI->IDR & GPIO_IDR_ID9))

#define led3_IsHigh	(GPIOI->IDR & GPIO_IDR_ID10)
#define led3_IsLow 	(!(GPIOI->IDR & GPIO_IDR_ID10))

#define led4_IsHigh	(GPIOI->IDR & GPIO_IDR_ID11)
#define led4_IsLow 	(!(GPIOI->IDR & GPIO_IDR_ID11))

#define led5_IsHigh	(GPIOF->IDR & GPIO_IDR_ID0)
#define led5_IsLow 	(!(GPIOF->IDR & GPIO_IDR_ID0))

#define led6_IsHigh	(GPIOF->IDR & GPIO_IDR_ID1)
#define led6_IsLow 	(!(GPIOF->IDR & GPIO_IDR_ID1))

void leds_init(void); // Инициализация светодиодов
uint16_t getLeds(void);
uint16_t getLed1(void);
uint16_t getLed2(void);
uint16_t getLed3(void);
uint16_t getLed4(void);
uint16_t getLed5(void);
uint16_t getLed6(void);

#endif
