#include "volt.h"

// VOLT1_EN - PH5, VOLT2_EN - PH4, VOLT3_EN - PA1, VOLT4_EN - PC3
// VOLT5_EN - PC2, VOLT6_EN - PC1, VOLT7_EN - PC0, VOLT8_EN - PF2

// DS_MISO - PE2, DS_MOSI - PE3, SHCP_CLK - PE4
// STCP_CS1 - PE5, STCP_CS2 - PE6

void volt_init(void) {
	GPIOA->MODER	 |= GPIO_MODER_MODE1_0;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED1_Msk;

	GPIOC->MODER	 |= GPIO_MODER_MODE3_0
										| GPIO_MODER_MODE2_0
											| GPIO_MODER_MODE1_0
												| GPIO_MODER_MODE0_0;
	GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED3_Msk
										| GPIO_OSPEEDR_OSPEED2_Msk
											| GPIO_OSPEEDR_OSPEED1_Msk
												| GPIO_OSPEEDR_OSPEED0_Msk;

	GPIOF->MODER	 |= GPIO_MODER_MODE2_0;
	GPIOF->OSPEEDR |= GPIO_OSPEEDR_OSPEED2_Msk;

	GPIOH->MODER	 |= GPIO_MODER_MODE5_0
										| GPIO_MODER_MODE4_0;
	GPIOH->OSPEEDR |= GPIO_OSPEEDR_OSPEED5_Msk 
										| GPIO_OSPEEDR_OSPEED4_Msk;

	GPIOE->MODER	 |= GPIO_MODER_MODE3_0
										| GPIO_MODER_MODE4_0 
											| GPIO_MODER_MODE5_0 
												| GPIO_MODER_MODE6_0;
	GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED3_Msk 
										| GPIO_OSPEEDR_OSPEED4_Msk
											| GPIO_OSPEEDR_OSPEED5_Msk
												| GPIO_OSPEEDR_OSPEED6_Msk;

	volt1LevelSend(0);
	volt2LevelSend(0);
	volt3LevelSend(0);
	volt4LevelSend(0);
	volt5LevelSend(0);
	volt6LevelSend(0);
	volt7LevelSend(0);
	volt8LevelSend(0);
}


#define voltSr_tick 1

void voltSrSend(uint16_t value, uint8_t bitCount) {
	_delay_tick(voltSr_tick);
	
	for (uint8_t i=0; i<bitCount; i++) {
		if (value & (1<<((bitCount - 1)-i))) {	
			ds_mosi_Enable;
		} else {
			ds_mosi_Disable;
		}
		
		shcp_clk_Enable;
		_delay_tick(voltSr_tick);
		
		shcp_clk_Disable;
		_delay_tick(voltSr_tick);
	}
}

uint8_t normilizeVolt(uint16_t volt) {
	if (volt > 1800) volt = 1800;
	
	uint8_t value = ((volt * 100) / 706) & 0xFF;
	
	return value;	
}

void volt1LevelSend(uint16_t volt) {
	uint8_t value = normilizeVolt(volt);
	
	stcp_cs1_Enable;
	voltSrSend(0x0000 + value, 10);
	stcp_cs1_Disable;
}

void volt2LevelSend(uint16_t volt) {
	uint8_t value = normilizeVolt(volt);
	
	stcp_cs1_Enable;
	voltSrSend(0x0100 + value, 10);
	stcp_cs1_Disable;
}

void volt3LevelSend(uint16_t volt) {
	uint8_t value = normilizeVolt(volt);
	
	stcp_cs1_Enable;
	voltSrSend(0x0200 + value, 10);
	stcp_cs1_Disable;
}

void volt4LevelSend(uint16_t volt) {
	uint8_t value = normilizeVolt(volt);
	
	stcp_cs1_Enable;
	voltSrSend(0x0300 + value, 10);
	stcp_cs1_Disable;
}

void volt5LevelSend(uint16_t volt) {
	uint8_t value = normilizeVolt(volt);
	
	stcp_cs2_Enable;
	voltSrSend(0x0000 + value, 10);
	stcp_cs2_Disable;
}

void volt6LevelSend(uint16_t volt) {
	uint8_t value = normilizeVolt(volt);
	
	stcp_cs2_Enable;
	voltSrSend(0x0100 + value, 10);
	stcp_cs2_Disable;
}

void volt7LevelSend(uint16_t volt) {
	uint8_t value = normilizeVolt(volt);
	
	stcp_cs2_Enable;
	voltSrSend(0x0200 + value, 10);
	stcp_cs2_Disable;
}

void volt8LevelSend(uint16_t volt) {
	uint8_t value = normilizeVolt(volt);
	
	stcp_cs2_Enable;
	voltSrSend(0x0300 + value, 10);
	stcp_cs2_Disable;
}



