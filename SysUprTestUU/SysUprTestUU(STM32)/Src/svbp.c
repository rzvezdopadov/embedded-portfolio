#include "svbp.h"

// SVBP1  - PC13, SVBP2  - PC14

void svbp_init(void) {
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED13_Msk
										| GPIO_OSPEEDR_OSPEED14_Msk;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD13_1
										| GPIO_PUPDR_PUPD14_1;
}

uint16_t getSVBP(void) { 
	uint8_t svbp = 0;
	
	if (svbp1_IsHigh) svbp |= 0x01;
	if (svbp2_IsHigh) svbp |= 0x02;
	
	return svbp;
}

uint16_t getSVBP1(void) { 
	uint8_t svbp = 0;
	
	if (svbp1_IsHigh) svbp |= 0x01;
	
	return svbp;
}

uint16_t getSVBP2(void) { 
	uint8_t svbp = 0;
	
	if (svbp2_IsHigh) svbp |= 0x01;
	
	return svbp;
}
