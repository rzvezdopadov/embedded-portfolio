#include "addr.h"

// ADDR1 - PI7, ADDR2 - PI6, ADDR3 - PI5,
// ADDR4 - PI4, ADDR5 - PE1, ADDR6 - PE0

void addr_init(void) {
	GPIOI->MODER	 |= GPIO_MODER_MODE7_0
										| GPIO_MODER_MODE6_0
											| GPIO_MODER_MODE5_0
												| GPIO_MODER_MODE4_0
	;
	
	GPIOI->OSPEEDR |= GPIO_OSPEEDR_OSPEED7_Msk
											| GPIO_OSPEEDR_OSPEED6_Msk
												| GPIO_OSPEEDR_OSPEED5_Msk
													| GPIO_OSPEEDR_OSPEED4_Msk
	;
	
	GPIOE->MODER	 |= GPIO_MODER_MODE1_0
										| GPIO_MODER_MODE0_0
	;
	
	GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED1_Msk
											| GPIO_OSPEEDR_OSPEED0_Msk
	;
}

void setAddr(uint16_t addr) {
	if (addr & 0x01) addr1_on else addr1_off
	if (addr & 0x02) addr2_on else addr2_off
	if (addr & 0x04) addr3_on else addr3_off
	if (addr & 0x08) addr4_on else addr4_off
	if (addr & 0x10) addr5_on else addr5_off
	if (addr & 0x20) addr6_on else addr6_off
}

