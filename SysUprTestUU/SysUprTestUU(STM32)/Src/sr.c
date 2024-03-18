#include "sr.h"

// SR0  - PB9, 	SR1  - PB8,  SR2  - PB6, SR3  - PD7,
// SR4  - PD6, 	SR5  - PD3,  SR6  - PD2, SR7  - PC12,
// SR8  - PC11, SR9  - PC10, SR10 - PI3, SR11 - PC9,
// SR12 - PC8,  SR13 - PC7,	 SR14 - PC6, SR15 - PG6,
// SR16 - PG4,  SR17 - PG3,  SR18 - PG2, SR19 - PD13,
// SR20 - PD12, SR21 - PD11, SR22 - PH6, SR23 - PF15,

void sr_init(void) {
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED9_Msk
										| GPIO_OSPEEDR_OSPEED8_Msk
											| GPIO_OSPEEDR_OSPEED6_Msk;
	
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD9_1
										| GPIO_PUPDR_PUPD8_1
											| GPIO_PUPDR_PUPD6_1;
	
	GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED12_Msk 
										| GPIO_OSPEEDR_OSPEED11_Msk 
											| GPIO_OSPEEDR_OSPEED10_Msk 
												| GPIO_OSPEEDR_OSPEED9_Msk
													| GPIO_OSPEEDR_OSPEED8_Msk 
														| GPIO_OSPEEDR_OSPEED7_Msk  
															| GPIO_OSPEEDR_OSPEED6_Msk;
	GPIOC->PUPDR |= GPIO_PUPDR_PUPD12_1 
									| GPIO_PUPDR_PUPD11_1 
										| GPIO_PUPDR_PUPD10_1 
											| GPIO_PUPDR_PUPD9_1
												| GPIO_PUPDR_PUPD8_1 
													| GPIO_PUPDR_PUPD7_1  
														| GPIO_PUPDR_PUPD6_1;
	
	GPIOD->OSPEEDR |= GPIO_OSPEEDR_OSPEED7_Msk
										| GPIO_OSPEEDR_OSPEED6_Msk
											| GPIO_OSPEEDR_OSPEED3_Msk
												| GPIO_OSPEEDR_OSPEED2_Msk 
													| GPIO_OSPEEDR_OSPEED13_Msk
														| GPIO_OSPEEDR_OSPEED12_Msk
															| GPIO_OSPEEDR_OSPEED11_Msk;
	GPIOD->PUPDR |= GPIO_PUPDR_PUPD7_1
										| GPIO_PUPDR_PUPD6_1
											| GPIO_PUPDR_PUPD3_1
												| GPIO_PUPDR_PUPD2_1 
													| GPIO_PUPDR_PUPD13_1
														| GPIO_PUPDR_PUPD12_1
															| GPIO_PUPDR_PUPD11_1;
															
	GPIOF->OSPEEDR |= GPIO_OSPEEDR_OSPEED15_Msk;
	GPIOF->PUPDR |= GPIO_PUPDR_PUPD15_1;
	
	GPIOG->OSPEEDR |= GPIO_OSPEEDR_OSPEED6_Msk 
										| GPIO_OSPEEDR_OSPEED4_Msk
											| GPIO_OSPEEDR_OSPEED3_Msk
												| GPIO_OSPEEDR_OSPEED2_Msk;
	GPIOG->PUPDR |= GPIO_PUPDR_PUPD6_1 
										| GPIO_PUPDR_PUPD4_1
											| GPIO_PUPDR_PUPD3_1
												| GPIO_PUPDR_PUPD2_1;
												
	GPIOH->OSPEEDR |= GPIO_OSPEEDR_OSPEED6_Msk;
	GPIOH->PUPDR |= GPIO_PUPDR_PUPD6_1;
	
	GPIOI->OSPEEDR |= GPIO_OSPEEDR_OSPEED3_Msk;
	GPIOI->PUPDR |= GPIO_PUPDR_PUPD3_1;
}

uint32_t getSR(void) {
	uint32_t sr = 0;
	
	if (sr0_IsHigh)  sr |= 0x00000001;
	if (sr1_IsHigh)  sr |= 0x00000002;
	if (sr2_IsHigh)  sr |= 0x00000004;
	if (sr3_IsHigh)  sr |= 0x00000008;
	if (sr4_IsHigh)  sr |= 0x00000010;
	if (sr5_IsHigh)  sr |= 0x00000020;
	if (sr6_IsHigh)  sr |= 0x00000040;
	if (sr7_IsHigh)  sr |= 0x00000080;
	if (sr8_IsHigh)  sr |= 0x00000100;
	if (sr9_IsHigh)  sr |= 0x00000200;
	if (sr10_IsHigh) sr |= 0x00000400;
	if (sr11_IsHigh) sr |= 0x00000800;
	if (sr12_IsHigh) sr |= 0x00001000;
	if (sr13_IsHigh) sr |= 0x00002000;
	if (sr14_IsHigh) sr |= 0x00004000;
	if (sr15_IsHigh) sr |= 0x00008000;
	if (sr16_IsHigh) sr |= 0x00010000;
	if (sr17_IsHigh) sr |= 0x00020000;
	if (sr18_IsHigh) sr |= 0x00040000;
	if (sr19_IsHigh) sr |= 0x00080000;
	if (sr20_IsHigh) sr |= 0x00100000;
	if (sr21_IsHigh) sr |= 0x00200000;
	if (sr22_IsHigh) sr |= 0x00400000;
	if (sr23_IsHigh) sr |= 0x00800000;
	
	return sr;
}

