#include "leds.h"

// PH2 - LED G, PH3 - LED B, PI8 - LED R

void leds_debug_init(void) { // Инициализация светодиодов
	GPIOH->MODER |= GPIO_MODER_MODE2_0 | GPIO_MODER_MODE3_0;
	GPIOH->OSPEEDR |= GPIO_OSPEEDR_OSPEED2_Msk | GPIO_OSPEEDR_OSPEED3_Msk;
	
	GPIOI->MODER |= GPIO_MODER_MODE8_0;
	GPIOI->OSPEEDR |= GPIO_OSPEEDR_OSPEED8_Msk;
	
	leds_debug_off();
} 

void leds_debug_off(void) {
	led_debug_r_off
	led_debug_g_off
	led_debug_b_off;
}

uint32_t led_change_pos = 0;
uint32_t led_change_old = 1;

#define led_long 1

void changePos(void) {
	if (led_change_pos++ > led_long*6) led_change_pos = 0;
}

void leds_debug_change(void) {
	if (led_change_pos != led_change_old) {
		switch(led_change_pos) {
			case 0:
				leds_debug_off();
				led_debug_r_on
			break;
			case led_long:
				leds_debug_off();
				led_debug_g_on
			break;
			case led_long*2:
				leds_debug_off();
				led_debug_b_on
			break;
			case led_long*3:
				leds_debug_off();
				led_debug_r_on
				led_debug_g_on
			break;
			case led_long*4:
				leds_debug_off();
				led_debug_g_on
				led_debug_b_on
			break;
			case led_long*5:
				leds_debug_off();
				led_debug_b_on
				led_debug_r_on
			break;
		}
		
		led_change_old = led_change_pos;
	}
}
