#include "rcc.h"

void rcc_init(void) { // Инициализация тактирования
	_delay_ms(100); // Задержка 2 секунды, для установления питания
	// Включение акселератора памяти Flash(максимальные циклы чтения памяти)
	FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY;
// Изменение веток тактирования на внешний кварц
	RCC->CR = RCC_CR_HSEON; // Переключаем на внешний	 кварц
	while(!(RCC->CR & RCC_CR_HSERDY)){} // Ожидаем, пока не переключится
// Раскачка умножителей PLL
	RCC->PLLCFGR = RCC_PLLCFGR_PLLSRC_HSE
							  | (4 << RCC_PLLCFGR_PLLM_Pos)
								 | (168 << RCC_PLLCFGR_PLLN_Pos)
									| (0 << RCC_PLLCFGR_PLLP_Pos)
									 | (7 << RCC_PLLCFGR_PLLQ_Pos);	// Поднимаем до 168 МГц
	
	RCC->CR |= RCC_CR_PLLON; // Включаем PLL
	while(!(RCC->CR & RCC_CR_PLLRDY)){} 	// Ожидаем, пока не включится
	
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_PPRE2_DIV2; // Включаем делители частоты периферийных шин
	
	RCC->CFGR |= RCC_CFGR_SW_PLL;							
	while(!(RCC->CFGR & RCC_CFGR_SWS_PLL)){}
		
// Запуск тактирования периферии 
	// Порты
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN
								 | RCC_AHB1ENR_GPIOBEN
									| RCC_AHB1ENR_GPIOCEN
									 | RCC_AHB1ENR_GPIODEN
										| RCC_AHB1ENR_GPIOEEN
										 | RCC_AHB1ENR_GPIOFEN
											| RCC_AHB1ENR_GPIOGEN
											 | RCC_AHB1ENR_GPIOHEN
												| RCC_AHB1ENR_GPIOIEN
												 | RCC_AHB1ENR_DMA1EN
													| RCC_AHB1ENR_DMA2EN;
	
	// Периферия
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN							// USART2()
								 | RCC_APB1ENR_USART3EN 						// USART3()
									| RCC_APB1ENR_TIM2EN							// Таймер 2 (Таймер в режиме ШИМ UIM2)
									 | RCC_APB1ENR_TIM3EN							// Таймер 3 (Таймер отсечки по отсылке байта) 485
									  | RCC_APB1ENR_TIM4EN						// Таймер 4 (Таймер отсечки по приему байта) 485
										 | RCC_APB1ENR_TIM5EN						// Таймер 5 (Таймер в режиме ШИМ UIM1)			
											| RCC_APB1ENR_TIM6EN					// Таймер 6 (Таймер отсечки по отсылке байта) PC
											 | RCC_APB1ENR_TIM7EN					// Таймер 7 (Таймер отсечки по приему байта) PC
											  | RCC_APB1ENR_TIM13EN				// Таймер 13 (Таймер в режиме захвата UIM1)
												 | RCC_APB1ENR_TIM14EN			// Таймер 14 (Таймер в режиме захвата UIM2)
													| RCC_APB1ENR_I2C3EN;			// I2C 3 (Цифровой термодатчик)
	
	// Периферия
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN 								// SPI1()
								 | RCC_APB2ENR_USART1EN 						// USART1(Отладка)
								  | RCC_APB2ENR_ADC3EN 							// ADC3(Измерение величин)
									 | RCC_APB2ENR_SYSCFGEN;					// Внешние прерывания
	
}

