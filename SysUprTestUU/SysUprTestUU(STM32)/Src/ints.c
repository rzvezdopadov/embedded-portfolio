#include "ints.h"

// INT1 - PG15, INT2 - PG13, INT3 - PG12, INT4 - PG11, 
// INT5 - PG10, INT6 - PG9, INT7 - PG8, INT8 - PG7

void ints_init(void) {
	GPIOG->PUPDR |= GPIO_PUPDR_PUPD15_1
								 | GPIO_PUPDR_PUPD13_1
									| GPIO_PUPDR_PUPD12_1
									 | GPIO_PUPDR_PUPD11_1
										| GPIO_PUPDR_PUPD10_1
										 | GPIO_PUPDR_PUPD9_1
											| GPIO_PUPDR_PUPD8_1
											 | GPIO_PUPDR_PUPD7_1;
	
	EXTI->IMR |= EXTI_IMR_MR15 
							| EXTI_IMR_MR13
								| EXTI_IMR_MR12
									| EXTI_IMR_MR11
										| EXTI_IMR_MR10
											| EXTI_IMR_MR9
												| EXTI_IMR_MR8
													| EXTI_IMR_MR7;					// Разрешаем прерывание
	
	EXTI->RTSR |= EXTI_RTSR_TR15
								| EXTI_RTSR_TR13
									| EXTI_RTSR_TR12
										| EXTI_RTSR_TR11
											| EXTI_RTSR_TR10
												| EXTI_RTSR_TR9
													| EXTI_RTSR_TR8	
														| EXTI_RTSR_TR7;			// Разрешаем ловлю фронтов
	
	EXTI->FTSR |= EXTI_FTSR_TR15
								| EXTI_FTSR_TR13
									| EXTI_FTSR_TR12
										| EXTI_FTSR_TR11
											| EXTI_FTSR_TR10
												| EXTI_FTSR_TR9
													| EXTI_FTSR_TR8
														| EXTI_FTSR_TR7;			// Разрешаем ловлю спадов
														
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI15_PG 
											| SYSCFG_EXTICR4_EXTI13_PG 
												| SYSCFG_EXTICR4_EXTI12_PG; // Запускаем тактирование ветки		
	SYSCFG->EXTICR[2] |= SYSCFG_EXTICR3_EXTI11_PG 
											| SYSCFG_EXTICR3_EXTI10_PG 
												| SYSCFG_EXTICR3_EXTI9_PG
													| SYSCFG_EXTICR3_EXTI8_PG; // Запускаем тактирование ветки
	SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI7_PG; // Запускаем тактирование ветки

	NVIC_SetPriority(EXTI15_10_IRQn, 1);		// Устанавливаем приоритет прерывания
	NVIC_EnableIRQ(EXTI15_10_IRQn);					// Разрешаем прерывание EXT1 в NVIC	
	
	NVIC_SetPriority(EXTI9_5_IRQn, 1);			// Устанавливаем приоритет прерывания
	NVIC_EnableIRQ(EXTI9_5_IRQn);						// Разрешаем прерывание EXT1 в NVIC	

};

uint32_t INT1_Counter = 0;
uint32_t INT2_Counter = 0;
uint32_t INT3_Counter = 0;
uint32_t INT4_Counter = 0;
uint32_t INT5_Counter = 0;
uint32_t INT6_Counter = 0;
uint32_t INT7_Counter = 0;
uint32_t INT8_Counter = 0;

void INT1_Handler(void) { INT1_Counter += 1; }
void INT2_Handler(void) { INT2_Counter += 1; } 
void INT3_Handler(void) { INT3_Counter += 1; } 
void INT4_Handler(void) { INT4_Counter += 1; } 
void INT5_Handler(void) { INT5_Counter += 1; } 
void INT6_Handler(void) { INT6_Counter += 1; } 
void INT7_Handler(void) { INT7_Counter += 1; } 
void INT8_Handler(void) { INT8_Counter += 1; }

void EXTI15_10_IRQHandler(void) {
	uint32_t PR = EXTI->PR;
	
	if (PR & EXTI_PR_PR15) INT1_Handler();
	if (PR & EXTI_PR_PR13) INT2_Handler();
	if (PR & EXTI_PR_PR12) INT3_Handler();
	if (PR & EXTI_PR_PR11) INT4_Handler();
	if (PR & EXTI_PR_PR10) INT5_Handler();

	EXTI->PR |= EXTI_PR_PR15
							| EXTI_PR_PR13
								| EXTI_PR_PR12
									| EXTI_PR_PR11
										| EXTI_PR_PR10; 		// Сброс флага
}

void EXTI9_5_IRQHandler(void) {
	uint32_t PR = EXTI->PR;
	
	if (PR & EXTI_PR_PR9) INT6_Handler();
	if (PR & EXTI_PR_PR8) INT7_Handler();
	if (PR & EXTI_PR_PR7) INT8_Handler();
	
	EXTI->PR |= EXTI_PR_PR9
							| EXTI_PR_PR8
								| EXTI_PR_PR7;			// Сброс флага
}

uint32_t getINT1(void) { return INT1_Counter; }
uint32_t getINT2(void) { return INT2_Counter; }
uint32_t getINT3(void) { return INT3_Counter; }
uint32_t getINT4(void) { return INT4_Counter; }
uint32_t getINT5(void) { return INT5_Counter; }
uint32_t getINT6(void) { return INT6_Counter; }
uint32_t getINT7(void) { return INT7_Counter; }
uint32_t getINT8(void) { return INT8_Counter; }

void setINT1(uint32_t count) { INT1_Counter = count; }
void setINT2(uint32_t count) { INT2_Counter = count; }
void setINT3(uint32_t count) { INT3_Counter = count; }
void setINT4(uint32_t count) { INT4_Counter = count; }
void setINT5(uint32_t count) { INT5_Counter = count; }
void setINT6(uint32_t count) { INT6_Counter = count; }
void setINT7(uint32_t count) { INT7_Counter = count; }
void setINT8(uint32_t count) { INT8_Counter = count; }

void clearAllINT(void) { 
	setINT1(0);
	setINT2(0);
	setINT3(0);
	setINT4(0);
	setINT5(0);
	setINT6(0);
	setINT7(0);
	setINT8(0);
}
