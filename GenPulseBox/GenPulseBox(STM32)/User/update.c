#include "update.h"
#include "leds.h"

// Перепрошивка и настройка на USART2
// PA3 - RX, PA2 - TX, PA8 - REDE
#define updateBaud 256000 // Битрейт
#define updateBRR ((42000000 + updateBaud / 2) / updateBaud)



void update_init(void) { // Инициализация перепрошивки и настройки контроллера
// Альтернативная функция порта
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// Настройки скоростей и битности
	USART2->BRR = updateBRR;
	// Разрешение интерфейса и прерывания
	USART2->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;
	// Разрешение запросов к DMA
	USART2->CR3 |= USART_CR3_DMAT;

	// Установка приоритета и разрешение прерывания в NVIC
	NVIC_SetPriority(USART2_IRQn, 8);
	NVIC_EnableIRQ(USART2_IRQn);
	
	DMA1_Stream6->PAR  = (uint32_t)&USART2->DR; 	// Указатель куда копировать
	DMA1_Stream6->M0AR = (uint32_t)&updateBuf.TX; // Указатель откуда копировать
	
	NVIC_SetPriority(DMA1_Stream6_IRQn, 6);	// Устанавливаем приоритет прерывания DMA
	NVIC_EnableIRQ(DMA1_Stream6_IRQn);			// Разрешаем прерыванние по DMA
	
	TIM7->PSC  = 168;
	TIM7->CR1  = TIM_CR1_CEN;
	TIM7->CR2	= TIM_CR2_MMS_1;
	TIM7->DIER = TIM_DIER_UIE;
	
	NVIC_SetPriority(TIM7_IRQn, 6);	// Устанавливаем приоритет прерывания
	NVIC_EnableIRQ(TIM7_IRQn);				// Разрешаем прерыванние
		
	TIM6->PSC  = 168;
	TIM6->CR1  = TIM_CR1_CEN;
	TIM6->CR2	= TIM_CR2_MMS_1;
	TIM6->DIER = TIM_DIER_UIE;
	
	NVIC_SetPriority(TIM6_DAC_IRQn, 8);	// Устанавливаем приоритет прерывания
	NVIC_EnableIRQ(TIM6_DAC_IRQn);				// Разрешаем прерыванние
	
	updateBuf.rx_addr = (uint8_t *)&updateBuf.RX;
	updateBuf.rx_count = 0;
	printf("Update Init Ok!\n");
}

void updateSendStrDMA(uint16_t countByte) {
	connectionReDeTx;
	
// DMA1 Stream6, Chanel4, USART2 TX
	DMA1_Stream6->NDTR = countByte;	// Сколько слать
	DMA1_Stream6->CR   = DMA_SxCR_CHSEL_2 |	// 4 канал
												DMA_SxCR_DIR_0 |	// Передача из памяти в периферию
												 DMA_SxCR_MINC | 	// Разрешить инкрементировать адрес приемника	
													DMA_SxCR_TCIE	|	// Разрешаем прерывание по 
													 DMA_SxCR_EN 		// Разрешаем этот поток DMA
	;
}

void DMA1_Stream6_IRQHandler(void) {		// Передача данных USART2 через DMA закончена
	DMA1->HIFCR |= DMA_HIFCR_CTCIF6 | 		// Очищаем флаги DMA
									DMA_HIFCR_CDMEIF6 |
									 DMA_HIFCR_CFEIF6 |
										DMA_HIFCR_CHTIF6 |
										 DMA_HIFCR_CTEIF6;
	
	TIM6->CNT = 65535-1800;			// Устанавливаем параметр от которого считаем
	TIM6->CR1 = TIM_CR1_CEN;		// Разрешаем счет таймера 
	TIM6->DIER = TIM_DIER_UIE; // Разрешаем прерывание таймера 
}

void TIM6_DAC_IRQHandler(void) { // После передачи последнего байта, сбрасываем ReDe
	TIM6->SR  = 0;						// Обнуляем настройки таймера
	TIM6->CR1 = 0;
	TIM6->DIER = 0;
	connectionReDeRx;
}

void USART2_IRQHandler(void) {
	*updateBuf.rx_addr++ = USART2->DR;	// Читаем пришедший байт
		
	if (++updateBuf.rx_count > sizeof(t_FilData)) {
		updateBuf.rx_count = 0;
		updateBuf.rx_addr = (uint8_t *)&updateBuf.RX;
	}	// Проверяем счетчик на превышение размерности данных
	// Запуск таймера отсечки USART2
	TIM7->CNT = 65535-100;			// Устанавливаем параметр от которого считаем
	TIM7->CR1 = TIM_CR1_CEN;		// Разрешаем счет таймера 
	TIM7->DIER = TIM_DIER_UIE; // Разрешаем прерывание таймера 
}

void TIM7_IRQHandler(void) { // Таймер отсечки USART2
	TIM7->SR  = 0;					// Обнуляем настройки таймера
	TIM7->CR1 = 0;
	TIM7->DIER = 0;
	updateBuf.rx_flag_en = flagEnable;
}

uint8_t calcCRC(uint8_t *addrBuf, uint16_t Count) {
	uint8_t crc = 0;
	
	for (uint16_t i=0; i<Count; i++) {
		crc += addrBuf[i]; 
	}
	
	return crc;
}

#define constCmdRead 7
#define constCmdWrite 13

void sendSequencedToPC() {
	updateBuf.TX.addrDevice = updateBuf.RX.addrDevice;
	updateBuf.TX.command = updateBuf.RX.command;
	updateBuf.TX.seqPos = updateBuf.RX.seqPos;
	
	memcpy(&updateBuf.TX.sequenced, &coreCPUsett.sequences[updateBuf.RX.seqPos-1], sizeof(t_sequenced));	
	updateBuf.TX.crc = calcCRC((uint8_t *)&updateBuf.TX, sizeof(t_FilData) - 1);
	updateSendStrDMA(sizeof(t_FilData));
}

void parseQueryUpdate(void) {
	if (updateBuf.rx_flag_en == flagDisable) return;
	
	updateBuf.rx_flag_en = flagDisable;
	uint16_t count = updateBuf.rx_count;	
	updateBuf.rx_count = 0;
	
	updateBuf.rx_addr = (uint8_t *)&updateBuf.RX;
	uint8_t oCRC =  updateBuf.RX.crc;
	updateBuf.RX.crc = 0;
	if (oCRC != calcCRC((uint8_t *)&updateBuf.RX, count)) return;
	if (updateBuf.RX.addrDevice != 0x10) return;
	
	if ((updateBuf.RX.seqPos == 0) || (updateBuf.RX.seqPos > MaxCountSequenced)) return;
	switch (updateBuf.RX.command) {
		case constCmdRead: {
			sendSequencedToPC();
		} break;
		case constCmdWrite: {
			uint8_t *dst = (uint8_t *)&coreCPUsett.sequences[updateBuf.RX.seqPos-1];
			uint8_t *src = (uint8_t *)&updateBuf.RX.sequenced;
			memcpy(dst, src, sizeof(t_sequenced));
			if (updateBuf.RX.seqPos == 29) {
				coreFlags.settSaveEnable = flagEnable;
		
				Menu_Init();
				MenuRedraw();
				Timers_Update(&coreCPUsett.sequences[0]);
			}
				
			updateBuf.TX.addrDevice = updateBuf.RX.addrDevice;
			updateBuf.TX.command = updateBuf.RX.command;
			updateBuf.TX.seqPos = updateBuf.RX.seqPos;
			updateBuf.TX.crc = calcCRC((uint8_t *)&updateBuf.TX, sizeof(t_FilData));
			updateSendStrDMA(4);
		} break;
	}
}
