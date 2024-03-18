#include "leds.h"

// PC15 - LED1, PI9 - LED2, PI10 - LED3
// PI11 - LED4, PF0 - LED5, PF1  - LED6

void leds_init(void) { // Инициализация светодиодов
	GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED15_Msk;
	GPIOC->PUPDR |= GPIO_PUPDR_PUPD15_1;
	
	GPIOI->OSPEEDR |= GPIO_OSPEEDR_OSPEED9_Msk 
									 | GPIO_OSPEEDR_OSPEED10_Msk
										| GPIO_OSPEEDR_OSPEED11_Msk;
	GPIOI->PUPDR |= GPIO_PUPDR_PUPD9_1 
								 | GPIO_PUPDR_PUPD10_1 
									| GPIO_PUPDR_PUPD11_1;
	
	GPIOF->OSPEEDR |= GPIO_OSPEEDR_OSPEED0_Msk 
									 | GPIO_OSPEEDR_OSPEED1_Msk;
	GPIOF->PUPDR |= GPIO_PUPDR_PUPD0_1
								 | GPIO_PUPDR_PUPD1_1;	
}

uint16_t getLeds(void) {
	uint8_t led = 0;
	
	if (led1_IsHigh) led |= 0x01;
	if (led2_IsHigh) led |= 0x02;
	if (led3_IsHigh) led |= 0x04;
	if (led4_IsHigh) led |= 0x08;
	if (led5_IsHigh) led |= 0x10;
	if (led6_IsHigh) led |= 0x20;
	
	return led;
}

uint16_t getLed1(void) {
	uint8_t led = 0;
	
	if (led1_IsHigh) led |= 0x01;
	
	return led;
}

uint16_t getLed2(void) {
	uint8_t led = 0;
	
	if (led2_IsHigh) led |= 0x01;
	
	return led;
}

uint16_t getLed3(void) {
	uint8_t led = 0;
	
	if (led3_IsHigh) led |= 0x01;
	
	return led;
}

uint16_t getLed4(void) {
	uint8_t led = 0;
	
	if (led4_IsHigh) led |= 0x01;
	
	return led;
}

uint16_t getLed5(void) {
	uint8_t led = 0;
	
	if (led5_IsHigh) led |= 0x01;
	
	return led;
}

uint16_t getLed6(void) {
	uint8_t led = 0;
	
	if (led6_IsHigh) led |= 0x01;
	
	return led;
}
