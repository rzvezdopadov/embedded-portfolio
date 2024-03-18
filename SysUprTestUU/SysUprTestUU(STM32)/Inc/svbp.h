#ifndef __SVBP_H
#define __SVBP_H

#include "main.h"

// SVBP1  - PC13, SVBP2  - PC14

#define svbp1_IsHigh	(GPIOC->IDR & GPIO_IDR_ID13)
#define svbp1_IsLow 	(!(GPIOC->IDR & GPIO_IDR_ID13))

#define svbp2_IsHigh	(GPIOC->IDR & GPIO_IDR_ID14)
#define svbp2_IsLow 	(!(GPIOC->IDR & GPIO_IDR_ID14))

void svbp_init(void);
uint16_t getSVBP(void);
uint16_t getSVBP1(void);
uint16_t getSVBP2(void);

#endif
