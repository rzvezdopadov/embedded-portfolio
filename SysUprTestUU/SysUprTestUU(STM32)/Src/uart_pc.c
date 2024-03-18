#include "uart_pc.h"

// Пердача данных в комп по USART3(AF7) - RS485
// PB10 - TX, PB11 - RX, PB12 - EN

#define baud 921600 // Битрейт отладки
#define baudBRR ((84000000 + baud / 2) / baud)

void uart_pc_init(void) { // Инициализация отладки
	// Альтернативная функция порта
	GPIOB->AFR[1] |= GPIO_AFRH_AFSEL10_0 | GPIO_AFRH_AFSEL10_1 | GPIO_AFRH_AFSEL10_2
									| GPIO_AFRH_AFSEL11_0 | GPIO_AFRH_AFSEL11_1 | GPIO_AFRH_AFSEL11_2;
	GPIOB->MODER |= GPIO_MODER_MODE10_1 | GPIO_MODER_MODE11_1;
	GPIOB->MODER |= GPIO_MODER_MODE12_0;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED10_Msk | GPIO_OSPEEDR_OSPEED11_Msk | GPIO_OSPEEDR_OSPEED12_Msk;
		
	// Настройки скоростей и битности
	USART3->BRR = baudBRR;
	// Разрешение интерфейса и прерывания
	USART3->CR1 |= USART_CR1_UE | USART_CR1_TE;
	
	DMA1_Stream3->PAR  = (uint32_t)&USART3->DR; 	// Указатель куда копировать
	DMA1_Stream3->M0AR = (uint32_t)&bufPC.tx; // Указатель откуда копировать
	
	NVIC_SetPriority(DMA1_Stream3_IRQn, 6);	// Устанавливаем приоритет прерывания DMA
	NVIC_EnableIRQ(DMA1_Stream3_IRQn);			// Разрешаем прерыванние по DMA
	
	TIM7->PSC  = 168;
	TIM7->CR1  = TIM_CR1_CEN;
	TIM7->CR2	= TIM_CR2_MMS_1;
	TIM7->DIER = TIM_DIER_UIE;
	
	TIM6->PSC  = 168;
	TIM6->CR1  = TIM_CR1_CEN;
	TIM6->CR2	= TIM_CR2_MMS_1;
	TIM6->DIER = TIM_DIER_UIE;
	
	NVIC_SetPriority(TIM7_IRQn, 6);					// Устанавливаем приоритет прерывания
	NVIC_EnableIRQ(TIM7_IRQn);							// Разрешаем прерыванние
	
	NVIC_SetPriority(TIM6_DAC_IRQn, 8);			// Устанавливаем приоритет прерывания
	NVIC_EnableIRQ(TIM6_DAC_IRQn);					// Разрешаем прерыванние
	
	bufPC.rx_addr  = (uint8_t *)&bufPC.rx;
	bufPC.rx_count = 0;
	uartPcReDeRx;
}

// DMA1 Stream 3 Channel 4
void uartPCSendStrDMA(uint16_t countByte) {
	uartPcReDeTx;
	
	DMA1_Stream3->NDTR = countByte;	// Сколько слать
	DMA1_Stream3->CR   = DMA_SxCR_CHSEL_2		// 4 канал
											| DMA_SxCR_DIR_0		// Передача из памяти в периферию
											 | DMA_SxCR_MINC 		// Разрешить инкрементировать адрес приемника	
												| DMA_SxCR_TCIE		// Разрешаем прерывание по 
												 | DMA_SxCR_EN 		// Разрешаем этот поток DMA
	;
}

void DMA1_Stream3_IRQHandler(void) {			// Передача данных USART3 через DMA закончена
	DMA1->LIFCR |= DMA_LIFCR_CTCIF3 				// Очищаем флаги DMA
							  | DMA_LIFCR_CDMEIF3
								 | DMA_LIFCR_CFEIF3
									| DMA_LIFCR_CHTIF3
									 | DMA_LIFCR_CTEIF3;
	
	TIM6->CNT = 65535-10800;								// Устанавливаем параметр от которого считаем
	TIM6->CR1 = TIM_CR1_CEN;								// Разрешаем счет таймера 
	TIM6->DIER = TIM_DIER_UIE; 							// Разрешаем прерывание таймера 
}

void TIM6_DAC_IRQHandler(void) { // После передачи последнего байта, сбрасываем ReDe
	TIM6->SR  = 0;						// Обнуляем настройки таймера
	TIM6->CR1 = 0;
	TIM6->DIER = 0;
	uartPcReDeRx;
}

void USART3_IRQHandler(void) {
	*bufUART.rx_addr++ = USART3->DR;	// Читаем пришедший байт
	
	if (++bufPC.rx_count > sizeof(bufPC.rx)) {
		bufPC.rx_count = 0;
		bufPC.rx_addr = (uint8_t *)&bufPC.rx;
	}	// Проверяем счетчик на превышение размерности данных
	// Запуск таймера отсечки USART3
	TIM7->CNT = 65535-58800;								// Устанавливаем параметр от которого считаем
	TIM7->CR1 = TIM_CR1_CEN;								// Разрешаем счет таймера 
	TIM7->DIER = TIM_DIER_UIE; 							// Разрешаем прерывание таймера 
}

void TIM7_IRQHandler(void) { 							// Таймер отсечки USART3
	TIM7->SR  = 0;													// Обнуляем настройки таймера
	TIM7->CR1 = 0;
	TIM7->DIER = 0;
	coreFlags.enableUartPC = flagEnable;		// Поднимаем флаг обработки посылки
}





