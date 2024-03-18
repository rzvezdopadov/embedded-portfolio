#ifndef __ADDR_H
#define __ADDR_H

#include "main.h"

// ADDR1 - PI7, ADDR2 - PI6, ADDR3 - PI5,
// ADDR4 - PI4, ADDR5 - PE1, ADDR6 - PE0

#define addr1_off GPIOI->BSRR = GPIO_BSRR_BS7;
#define addr1_on	GPIOI->BSRR = GPIO_BSRR_BR7;

#define addr2_off GPIOI->BSRR = GPIO_BSRR_BS6;
#define addr2_on	GPIOI->BSRR = GPIO_BSRR_BR6;

#define addr3_off GPIOI->BSRR = GPIO_BSRR_BS5;
#define addr3_on	GPIOI->BSRR = GPIO_BSRR_BR5;

#define addr4_off GPIOI->BSRR = GPIO_BSRR_BS4;
#define addr4_on	GPIOI->BSRR = GPIO_BSRR_BR4;

#define addr5_off GPIOE->BSRR = GPIO_BSRR_BS1;
#define addr5_on	GPIOE->BSRR = GPIO_BSRR_BR1;

#define addr6_off GPIOE->BSRR = GPIO_BSRR_BS0;
#define addr6_on	GPIOE->BSRR = GPIO_BSRR_BR0;

void addr_init(void);
void setAddr(uint16_t addr);


#endif 
