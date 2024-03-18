#ifndef __LEDS_ALM_H
#define __LEDS_ALM_H

#include "main.h"

// STCP - PI2, SHCP - PI1, DS - PI0 

#define ledsalm_shcp_disable GPIOI->BSRR = GPIO_BSRR_BR1;
#define ledsalm_shcp_enable	 GPIOI->BSRR = GPIO_BSRR_BS1;

#define ledsalm_stcp_disable GPIOI->BSRR = GPIO_BSRR_BR2;
#define ledsalm_stcp_enable	 GPIOI->BSRR = GPIO_BSRR_BS2;

#define ledsalm_ds_disable GPIOI->BSRR = GPIO_BSRR_BS0;
#define ledsalm_ds_enable	 GPIOI->BSRR = GPIO_BSRR_BR0;

enum RGB {
	RGB_Red 	= 1,
	RGB_Green = 2,
	RGB_Blue  = 4
};

void ledsalm_init(void);
void ledsalm_send(void);
void ledalm_on(uint8_t ledpos, enum RGB color);
void ledalm_off(uint8_t ledpos, enum RGB color);
void ledalm_all_off(void);

#endif 
