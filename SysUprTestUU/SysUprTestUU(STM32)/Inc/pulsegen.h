#ifndef __PULSEGEN_H
#define __PULSEGEN_H

#include "main.h"

void pulsegen_init(void);
void uimOut1_off(void);
void uimOut1_on(uint32_t duration, uint32_t period);

#define uimOut1_enable 	GPIOF->BSRR = GPIO_BSRR_BS13;
#define uimOut1_disable	GPIOF->BSRR = GPIO_BSRR_BR13;

void uimOut2_off(void);
void uimOut2_on(uint32_t duration, uint32_t period);

#define uimOut2_enable 	GPIOF->BSRR = GPIO_BSRR_BS14;
#define uimOut2_disable	GPIOF->BSRR = GPIO_BSRR_BR14;

#endif 
