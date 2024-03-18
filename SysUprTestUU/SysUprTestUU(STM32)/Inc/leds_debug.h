#ifndef __LEDS_DEBUG_H
#define __LEDS_DEBUG_H

#include "main.h"
// Светодиод отладочный
// PH2 - LED G, PH3 - LED B, PI8 - LED R

#define led_debug_r_off 	GPIOH->BSRR = GPIO_BSRR_BS2;
#define led_debug_r_on	GPIOH->BSRR = GPIO_BSRR_BR2;
#define led_debug_r_change	if (GPIOH->ODR & GPIO_ODR_OD2) { led_debug_r_on } else { led_debug_r_off }

#define led_debug_g_off 	GPIOH->BSRR = GPIO_BSRR_BS3;
#define led_debug_g_on	GPIOH->BSRR = GPIO_BSRR_BR3;
#define led_debug_g_change	if (GPIOH->ODR & GPIO_ODR_OD3) { led_debug_g_on } else { led_debug_g_off }

#define led_debug_b_off 	GPIOI->BSRR = GPIO_BSRR_BS8;
#define led_debug_b_on	GPIOI->BSRR = GPIO_BSRR_BR8;
#define led_debug_b_change	if (GPIOI->ODR & GPIO_ODR_OD8) { led_debug_b_on } else { led_debug_b_off }

void leds_debug_init(void); // Инициализация светодиодов
void leds_debug_off(void);		// Отключение всех светодиодов
void leds_debug_change(void); // Переключение светодиодов
void changePos(void);

#endif
