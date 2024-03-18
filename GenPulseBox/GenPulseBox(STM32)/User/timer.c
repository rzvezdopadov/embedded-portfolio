#include "timer.h"
#include "leds.h"

void timer_init(void) { // Инициализация таймеров
	printf("Timers Init Start...\n");
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	
	DMA1_Stream1->CR = 0;
	DMA1_Stream0->CR = 0;

//////////////////////////////// Синхронизация
// PB6 - TIM4_CH1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6 , GPIO_AF_TIM4);
	
// Таймер по периоду		
	TIM4->PSC = seqTimer.period.PSC;
	TIM4->ARR = seqTimer.period.ARR;
	TIM4->DIER |= TIM_DIER_UIE;
	TIM4->CR2 |= TIM_CR2_MMS_1;
	TIM4->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
	TIM4->CCER |= TIM_CCER_CC1E;
	TIM4->CCR1 = seqTimer.period.ARR >> 1;
	TIM4->CR1 |= TIM_CR1_ARPE;
	TIM4->CR1 |= TIM_CR1_CEN;
	
	NVIC_SetPriority(TIM4_IRQn, 5);
	NVIC_EnableIRQ(TIM4_IRQn);
	
///////////////////////////////// 1 канал
// PA15 - TIM2_CH1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource15 , GPIO_AF_TIM2);
// PB3 - TIM2_CH2	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3 , GPIO_AF_TIM2);

// Запуск таймера по таймауту канала 1 
	TIM1->PSC = seqTimer.CH1.bias.PSC;
	TIM1->ARR = seqTimer.CH1.bias.ARR;
	TIM1->SMCR |= TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1 | TIM_SMCR_TS_1  | TIM_SMCR_TS_0;
	TIM1->DIER |= TIM_DIER_UIE;
	TIM1->CR2 |= TIM_CR2_MMS_1;
	TIM1->CR1 |= TIM_CR1_ARPE | TIM_CR1_OPM;
	
	NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 5);
	NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
	
// DMA1 Stream 1, Channel 3
	DMA1_Stream1->CR   = 0;
	DMA1_Stream1->CR   = (DMA_SxCR_CHSEL_1 | DMA_SxCR_CHSEL_0) |						// 3 Канал
												DMA_SxCR_PL |						// Очень высокий приоритет
												 DMA_SxCR_PSIZE_1 |					// Размерность отправителя 64 бита 16 * 4
													DMA_SxCR_MSIZE_1 |				// Размерность приемника 64 бита  16 * 4
													 DMA_SxCR_DIR_0 |				// Передача из памяти в периферию
														DMA_SxCR_MINC	 			// Разрешить инкрементировать адрес передатчика
	;
	DMA1_Stream1->NDTR = seqTimer.CH1.count * 5 + 10; // Сколько тетрабайт копировать
	DMA1_Stream1->M0AR = (uint32_t)&seqTimer.CH1; // Указатель откуда копировать
	DMA1_Stream1->PAR  = (uint32_t)&TIM2->DMAR; 			// Указатель куда копировать
	DMA1_Stream1->CR   |= DMA_SxCR_EN | DMA_SxCR_TCIE; 				// Разрешаем поток этого канала DMA	
	NVIC_SetPriority(DMA1_Stream1_IRQn, 1);
	NVIC_EnableIRQ(DMA1_Stream1_IRQn);
	
// Запуск таймера по длительности канал 1
	TIM2->PSC = 0;
	TIM2->ARR = 168;
	TIM2->CCR1 = 84;
	TIM2->CCR2 = 84;
	TIM2->CR1 &= ~(TIM_CR1_DIR | TIM_CR1_CMS);
	TIM2->CR1 |= TIM_CR1_ARPE;
	if (coreFlags.CH1Enable1 == flagEnable) {
		TIM2->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
	} else {
		TIM2->CCMR1 &= ~(TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1);
	}
	if (coreFlags.CH1Enable2 == flagEnable) {
		TIM2->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1;
	} else {
		TIM2->CCMR1 &= ~(TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1);
	}
	
	TIM2->CCMR1 |= TIM_CCMR1_OC1PE | TIM_CCMR1_OC2PE;
	TIM2->DIER |= TIM_DIER_UDE;
	TIM2->DCR |= (TIM_DCR_DBA_3 | TIM_DCR_DBA_1) | (TIM_DCR_DBL_2);
	TIM2->BDTR |= TIM_BDTR_MOE;
	uint32_t polarityCH1_1 = seqTimer.CH1.polarity1 ? TIM_CCER_CC1P : 0;
	uint32_t polarityCH1_2 = seqTimer.CH1.polarity2 ? TIM_CCER_CC2P : 0;
	TIM2->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E | polarityCH1_1 | polarityCH1_2;
	TIM2->SMCR |= TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1;

///////////////////////////////// 2 канал	
// PA0 - TIM5_CH1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0 , GPIO_AF_TIM5);
// PA1 - TIM5_CH2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1 , GPIO_AF_TIM5);
	
// Запуск таймера по таймауту канала 2
	TIM8->PSC = seqTimer.CH2.bias.PSC;
	TIM8->ARR = seqTimer.CH2.bias.ARR;
	TIM8->SMCR |= TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1 | TIM_SMCR_TS_1;
	TIM8->DIER |= TIM_DIER_UIE;
	TIM8->CR2 |= TIM_CR2_MMS_1;
	TIM8->CR1 |= TIM_CR1_ARPE | TIM_CR1_OPM;
	
	NVIC_SetPriority(TIM8_UP_TIM13_IRQn, 5);
	NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);

// DMA1 Stream 0, Channel 6
	DMA1_Stream0->CR   = 0;
	DMA1_Stream0->CR   = (DMA_SxCR_CHSEL_2 | DMA_SxCR_CHSEL_1) |						// 6 Канал
												DMA_SxCR_PL |						// Очень высокий приоритет
												 DMA_SxCR_PSIZE_1 |					// Размерность отправителя 64 бита 16 * 4
													DMA_SxCR_MSIZE_1 |				// Размерность приемника 64 бита  16 * 4
													 DMA_SxCR_DIR_0 |				// Передача из памяти в периферию
														DMA_SxCR_MINC	 			// Разрешить инкрементировать адрес передатчика
	;
	DMA1_Stream0->NDTR = seqTimer.CH2.count * 5 + 10;//	// Сколько тетрабайт копировать
	
	DMA1_Stream0->M0AR = (uint32_t)&seqTimer.CH2; // Указатель откуда копировать
	DMA1_Stream0->PAR  = (uint32_t)&TIM5->DMAR; 			// Указатель куда копировать
	DMA1_Stream0->CR   |= DMA_SxCR_EN | DMA_SxCR_TCIE; 				// Разрешаем поток этого канала DMA	
	NVIC_SetPriority(DMA1_Stream0_IRQn, 1);
	NVIC_EnableIRQ(DMA1_Stream0_IRQn);
	
// Запуск таймера по длительности канал 2
	TIM5->PSC = 0;
	TIM5->ARR = 168;
	TIM5->CCR1 = 84;
	TIM5->CCR2 = 84;
	TIM5->CR1 &= ~(TIM_CR1_DIR | TIM_CR1_CMS);
	TIM5->CR1 |= TIM_CR1_ARPE;
	if (coreFlags.CH2Enable1 == flagEnable) {
		TIM5->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
	} else {
		TIM5->CCMR1 &= ~(TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1);
	}
	if (coreFlags.CH2Enable2 == flagEnable) {
		TIM5->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1;
	} else {
		TIM5->CCMR1 &= ~(TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1);
	}
	TIM5->CCMR1 |= TIM_CCMR1_OC1PE | TIM_CCMR1_OC2PE;
	TIM5->DIER |= TIM_DIER_UDE;
	TIM5->DCR |= (TIM_DCR_DBA_3 | TIM_DCR_DBA_1) | (TIM_DCR_DBL_2);
	TIM5->BDTR |= TIM_BDTR_MOE;
	uint32_t polarityCH2_1 = seqTimer.CH2.polarity1 ? TIM_CCER_CC1P : 0;
	uint32_t polarityCH2_2 = seqTimer.CH2.polarity2 ? TIM_CCER_CC2P : 0;
	TIM5->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E | polarityCH2_1 | polarityCH2_2;
	TIM5->SMCR |= TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1 | TIM_SMCR_TS_1 | TIM_SMCR_TS_0;

	printf("Timers Init Ok!\n");
}

void TIM4_IRQHandler(void) {
	TIM4->SR = 0;
	led_debug_g_change;
}

void TIM1_UP_TIM10_IRQHandler(void) {
	TIM1->SR = 0;
}

void TIM8_UP_TIM13_IRQHandler(void) {
	TIM8->SR = 0;
}

// DMA2 Stream 1, Channel 3 // TIM2
void DMA1_Stream1_IRQHandler(void) {
	TIM2->CR1 &= ~TIM_CR1_CEN;
	DMA1->LIFCR	|= DMA_LIFCR_CDMEIF1 | DMA_LIFCR_CFEIF1 | DMA_LIFCR_CHTIF1 | DMA_LIFCR_CTCIF1 | DMA_LIFCR_CTEIF1;
	DMA1_Stream1->CR |= DMA_SxCR_EN; 				// Разрешаем поток этого канала DMA
}

// DMA2 Stream 0, Channel 6 // TIM5
void DMA1_Stream0_IRQHandler(void) {
	TIM5->CR1 &= ~TIM_CR1_CEN;
	DMA1->LIFCR	|= DMA_LIFCR_CDMEIF0 | DMA_LIFCR_CFEIF0 | DMA_LIFCR_CHTIF0 | DMA_LIFCR_CTCIF0 | DMA_LIFCR_CTEIF0;
	DMA1_Stream0->CR |= DMA_SxCR_EN; 				// Разрешаем поток этого канала DMA
}
