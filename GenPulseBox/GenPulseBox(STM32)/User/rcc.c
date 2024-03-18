#include "rcc.h"

void rcc_init(void) { // Инициализация тактирования
	_delay_ms(100); // Задержка 2 секунды, для установления питания
	// Включение акселератора памяти Flash(максимальные циклы чтения памяти)
	FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY;
//// Изменение веток тактирования на внешний кварц
//	RCC->CR = RCC_CR_HSEON; // Переключаем на внешний	 кварц
//	while(!(RCC->CR & RCC_CR_HSERDY)){} // Ожидаем, пока не переключится
//// Раскачка умножителей PLL
//	RCC->PLLCFGR = RCC_PLLCFGR_PLLSRC_HSE |
//								(4 << RCC_PLLCFGR_PLLM_Pos) | 
//									(168 << RCC_PLLCFGR_PLLN_Pos) |
//										(0 << RCC_PLLCFGR_PLLP_Pos)	|
//											(7 << RCC_PLLCFGR_PLLQ_Pos)
//	;	// Поднимаем до 168 МГц
//		RCC->CR |= RCC_CR_PLLON; // Включаем PLL
//	while(!(RCC->CR & RCC_CR_PLLRDY)){} // Ожидаем, пока не включится
//	
//	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_PPRE2_DIV2; // Включаем делители частоты периферийных шин
//	
//	RCC->CFGR |= RCC_CFGR_SW_PLL;							
//	while(!(RCC->CFGR & RCC_CFGR_SWS_PLL)){}
		
// Запуск тактирования периферии 
	// Порты
	RCC->AHB1ENR |= 
					RCC_AHB1ENR_GPIOAEN |
					 RCC_AHB1ENR_GPIOBEN |
					  RCC_AHB1ENR_GPIOCEN |
					   RCC_AHB1ENR_GPIODEN |
					    RCC_AHB1ENR_GPIOEEN |
					     RCC_AHB1ENR_GPIOFEN |
								RCC_AHB1ENR_GPIOGEN |
								 RCC_AHB1ENR_GPIOHEN |
									RCC_AHB1ENR_GPIOIEN |
									 RCC_AHB1ENR_DMA1EN |
										RCC_AHB1ENR_DMA2EN
	;
	
	// Периферия частота таймеров 84MHz
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN |				// USART2(Перепрограммирование устройства)
										 RCC_APB1ENR_TIM2EN | 				// Таймер 2
											RCC_APB1ENR_TIM3EN |				// Таймер 3
											 RCC_APB1ENR_TIM4EN |				// Таймер 4
												RCC_APB1ENR_TIM5EN | 			// Таймер 5
												 RCC_APB1ENR_TIM6EN | 		// Таймер 6
													RCC_APB1ENR_TIM7EN | 		// Таймер 7
													 RCC_APB1ENR_TIM12EN |	// Таймер 12
														RCC_APB1ENR_TIM13EN	|	// Таймер 13
														 RCC_APB1ENR_TIM14EN	// Таймер 14
	;
	
	// Периферия частота таймеров 168MHz
	RCC->APB2ENR |= 
	RCC_APB2ENR_SPI1EN | 						//
									 RCC_APB2ENR_USART1EN | 				//
									  RCC_APB2ENR_ADC1EN | 					//
										 RCC_APB2ENR_SYSCFGEN | 			//
											RCC_APB2ENR_TIM1EN |				// Таймер 1
											 RCC_APB2ENR_TIM8EN |				// Таймер 8
												RCC_APB2ENR_TIM9EN |			// Таймер 9
												 RCC_APB2ENR_TIM10EN |		// Таймер 10
													RCC_APB2ENR_TIM11EN			// Таймер 11
	;
}
