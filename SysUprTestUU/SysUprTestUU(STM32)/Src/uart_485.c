#include "uart_485.h"

//  Пердача данных в устройство по USART2(AF7) - RS485
// PA8 - EN, PA2 - TX, PA3 - RX 

#define baud 921600 // Битрейт отладки
#define baudBRR ((84000000 + baud / 2) / baud)

void uart_485_init(void) { // Инициализация отладки
	// Альтернативная функция порта
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL2_0 | GPIO_AFRL_AFSEL2_1 | GPIO_AFRL_AFSEL2_2
									| GPIO_AFRL_AFSEL3_0 | GPIO_AFRL_AFSEL3_1 | GPIO_AFRL_AFSEL3_2;
	GPIOA->MODER |= GPIO_MODER_MODE2_1 | GPIO_MODER_MODE3_1;
	GPIOA->MODER |= GPIO_MODER_MODE8_0;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED2_Msk |  GPIO_OSPEEDR_OSPEED3_Msk |  GPIO_OSPEEDR_OSPEED8_Msk;

	// Настройки скоростей и битности
	USART2->BRR = baudBRR;
	// Разрешение интерфейса и прерывания
	USART2->CR1 |= USART_CR1_UE | USART_CR1_TE;
	
//////////////	
	DMA1_Stream5->PAR  = (uint32_t)&USART2->DR; 	// Указатель куда копировать
	DMA1_Stream5->M0AR = (uint32_t)&buf485.tx; // Указатель откуда копировать
	
	NVIC_SetPriority(DMA1_Stream6_IRQn, 6);	// Устанавливаем приоритет прерывания DMA
	NVIC_EnableIRQ(DMA1_Stream6_IRQn);			// Разрешаем прерыванние по DMA
	
	TIM3->PSC  = 168;
	TIM3->CR1  = TIM_CR1_CEN;
	TIM3->CR2	= TIM_CR2_MMS_1;
	TIM3->DIER = TIM_DIER_UIE;
	
	TIM4->PSC  = 168;
	TIM4->CR1  = TIM_CR1_CEN;
	TIM4->CR2	= TIM_CR2_MMS_1;
	TIM4->DIER = TIM_DIER_UIE;
	
	NVIC_SetPriority(TIM3_IRQn, 6);					// Устанавливаем приоритет прерывания
	NVIC_EnableIRQ(TIM3_IRQn);							// Разрешаем прерыванние
	
	NVIC_SetPriority(TIM4_IRQn, 8);			// Устанавливаем приоритет прерывания
	NVIC_EnableIRQ(TIM4_IRQn);					// Разрешаем прерыванние
	
	buf485.rx_addr  = (uint8_t *)&buf485.rx;
	buf485.rx_count = 0;
	uart485ReDeRx;
}

// DMA1 Stream 6 Channel 4
void uart485SendStrDMA(uint16_t countByte) {
	uart485ReDeTx;
	
	DMA1_Stream6->NDTR = countByte;	// Сколько слать
	DMA1_Stream6->CR   = DMA_SxCR_CHSEL_2		// 4 канал
											| DMA_SxCR_DIR_0		// Передача из памяти в периферию
											 | DMA_SxCR_MINC 		// Разрешить инкрементировать адрес приемника	
												| DMA_SxCR_TCIE		// Разрешаем прерывание по 
												 | DMA_SxCR_EN 		// Разрешаем этот поток DMA
	;
}

void DMA1_Stream6_IRQHandler(void) {			// Передача данных USART2 через DMA закончена
	DMA1->HIFCR |= DMA_HIFCR_CTCIF6 				// Очищаем флаги DMA
							  | DMA_HIFCR_CDMEIF6
								 | DMA_HIFCR_CFEIF6
									| DMA_HIFCR_CHTIF6
									 | DMA_HIFCR_CTEIF6;
	
	TIM3->CNT = 65535-10800;								// Устанавливаем параметр от которого считаем
	TIM3->CR1 = TIM_CR1_CEN;								// Разрешаем счет таймера 
	TIM3->DIER = TIM_DIER_UIE; 							// Разрешаем прерывание таймера 
}

void TIM3_IRQHandler(void) { // После передачи последнего байта, сбрасываем ReDe
	TIM3->SR  = 0;						// Обнуляем настройки таймера
	TIM3->CR1 = 0;
	TIM3->DIER = 0;
	uart485ReDeRx;
}

void USART2_IRQHandler(void) {
	*buf485.rx_addr++ = USART2->DR;	// Читаем пришедший байт
	
	if (++buf485.rx_count > sizeof(buf485.rx)) {
		buf485.rx_count = 0;
		buf485.rx_addr = (uint8_t *)&buf485.rx;
	}	// Проверяем счетчик на превышение размерности данных
	// Запуск таймера отсечки USART3
	TIM4->CNT = 65535-58800;								// Устанавливаем параметр от которого считаем
	TIM4->CR1 = TIM_CR1_CEN;								// Разрешаем счет таймера 
	TIM4->DIER = TIM_DIER_UIE; 							// Разрешаем прерывание таймера 
}

void TIM4_IRQHandler(void) { 							// Таймер отсечки USART3
	TIM4->SR  = 0;													// Обнуляем настройки таймера
	TIM4->CR1 = 0;
	TIM4->DIER = 0;
	coreFlags.enable485 = flagEnable;		// Поднимаем флаг обработки посылки
}





