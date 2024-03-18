#ifndef __VOLT_H
#define __VOLT_H

#include "main.h"

// Enable
// VOLT1_EN - PH5, VOLT2_EN - PH4, VOLT3_EN - PA1, VOLT4_EN - PC3
// VOLT5_EN - PC2, VOLT6_EN - PC1, VOLT7_EN - PC0, VOLT8_EN - PF2

#define volt1_en_off GPIOH->BSRR = GPIO_BSRR_BS5;
#define volt1_en_on	 GPIOH->BSRR = GPIO_BSRR_BR5;

#define volt2_en_off GPIOH->BSRR = GPIO_BSRR_BS4;
#define volt2_en_on	 GPIOH->BSRR = GPIO_BSRR_BR4;

#define volt3_en_off GPIOA->BSRR = GPIO_BSRR_BS1;
#define volt3_en_on	 GPIOA->BSRR = GPIO_BSRR_BR1;

#define volt4_en_off GPIOC->BSRR = GPIO_BSRR_BS3;
#define volt4_en_on	 GPIOC->BSRR = GPIO_BSRR_BR3;

#define volt5_en_off GPIOC->BSRR = GPIO_BSRR_BS2;
#define volt5_en_on	 GPIOC->BSRR = GPIO_BSRR_BR2;

#define volt6_en_off GPIOC->BSRR = GPIO_BSRR_BS1;
#define volt6_en_on	 GPIOC->BSRR = GPIO_BSRR_BR1;

#define volt7_en_off GPIOC->BSRR = GPIO_BSRR_BS0;
#define volt7_en_on	 GPIOC->BSRR = GPIO_BSRR_BR0;

#define volt8_en_off GPIOF->BSRR = GPIO_BSRR_BS2;
#define volt8_en_on	 GPIOF->BSRR = GPIO_BSRR_BR2;

// Shift register
// DS_MISO - PE2, DS_MOSI - PE3, SHCP_CLK - PE4
// STCP_CS1 - PE5, STCP_CS2 - PE6

#define	ds_mosi_Enable  GPIOE->BSRR = GPIO_BSRR_BS3
#define	ds_mosi_Disable GPIOE->BSRR = GPIO_BSRR_BR3

#define	shcp_clk_Enable  GPIOE->BSRR = GPIO_BSRR_BS4
#define	shcp_clk_Disable GPIOE->BSRR = GPIO_BSRR_BR4

#define	stcp_cs1_Enable  GPIOE->BSRR = GPIO_BSRR_BS5
#define	stcp_cs1_Disable GPIOE->BSRR = GPIO_BSRR_BR5

#define	stcp_cs2_Enable  GPIOE->BSRR = GPIO_BSRR_BS6
#define	stcp_cs2_Disable GPIOE->BSRR = GPIO_BSRR_BR6

void volt_init(void);
void volt1LevelSend(uint16_t volt);
void volt2LevelSend(uint16_t volt);
void volt3LevelSend(uint16_t volt);
void volt4LevelSend(uint16_t volt);
void volt5LevelSend(uint16_t volt);
void volt6LevelSend(uint16_t volt);
void volt7LevelSend(uint16_t volt);
void volt8LevelSend(uint16_t volt);

#endif 
