#include "uim.h"

// UIM1_IN - PG0, PA6
// UIM2_IN - PG1, PA7

void uim_init(void) {
	EXTI->IMR |= EXTI_IMR_MR0 | EXTI_IMR_MR1;						// Разрешаем прерывание
	EXTI->FTSR |= EXTI_FTSR_TR0 | EXTI_FTSR_TR1;				// Разрешаем ловлю спадов
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PG | SYSCFG_EXTICR1_EXTI1_PG; // Запускаем тактирование ветки
	
	NVIC_SetPriority(EXTI0_IRQn, 1);	// Устанавливаем приоритет прерывания
	NVIC_EnableIRQ(EXTI0_IRQn);					// Разрешаем прерывание EXT1 в NVIC
	
	NVIC_SetPriority(EXTI1_IRQn, 1);	// Устанавливаем приоритет прерывания
	NVIC_EnableIRQ(EXTI1_IRQn);					// Разрешаем прерывание EXT1 в NVIC
	
	GPIOA->AFR[0] |=  GPIO_AFRL_AFSEL6_3 | GPIO_AFRL_AFSEL6_0
									 | GPIO_AFRL_AFSEL7_3 | GPIO_AFRL_AFSEL7_0;
	GPIOA->MODER |= GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED6_Msk | GPIO_OSPEEDR_OSPEED7_Msk;
	
	TIM13->CNT = 0;
	TIM13->CCR1 = 0;
	TIM13->PSC = 9;
	TIM13->CCMR1 |= TIM_CCMR1_CC1S_0;
	TIM13->CCER |= TIM_CCER_CC1E;
	TIM13->DIER |= TIM_DIER_CC1IE;
	TIM13->CR1 |= TIM_CR1_CEN;
	
	NVIC_SetPriority(TIM8_UP_TIM13_IRQn, 6);
	NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);
		
	TIM14->CNT = 0;
	TIM14->CCR1 = 0;
	TIM14->PSC = 9;
	TIM14->CCMR1 |= TIM_CCMR1_CC1S_0;
	TIM14->CCER |= TIM_CCER_CC1E;
	TIM14->DIER |= TIM_DIER_CC1IE;
	TIM14->CR1 |= TIM_CR1_CEN;
	
	NVIC_SetPriority(TIM8_TRG_COM_TIM14_IRQn, 6);
	NVIC_EnableIRQ(TIM8_TRG_COM_TIM14_IRQn);
}

#define pulseDurationFiltr 4
#define pulseDurationDivide 127

void calcDuration(t_UIM *UIM) {
	if (UIM->pulseFreequency) {
		uint32_t pulseDuration = pulseDurationDivide * UIM->pulseDurationTemp;
		UIM->pulseDurationX = ((UIM->pulseDurationX * pulseDurationFiltr) + pulseDuration) / (pulseDurationFiltr + 1);
		UIM->pulseDuration = UIM->pulseDurationX * 10 / (pulseDurationDivide * 84);
		UIM->pulseDutyCyckle = 1000000 / (UIM->pulseFreequency * UIM->pulseDuration);
		UIM->pulsePeriod = 1000000 / UIM->pulseFreequency;
	}
}

void clearUIMParam(t_UIM *UIM) {
	UIM->pulseDurationX = 0;
	UIM->pulseDuration = 0;
	UIM->pulseDutyCyckle = 0;
	UIM->pulsePeriod = 0;
}

////////////////////////////////// UIM1
t_UIM UIM1;

void EXTI0_IRQHandler(void) {
	if (UIM1.pulseFreequency) {
		UIM1.pulseDurationTemp = TIM13->CNT;
		UIM1.flagDurationUpdate = 1;
	};
	
	EXTI->PR |= EXTI_PR_PR0;
}

void TIM8_UP_TIM13_IRQHandler(void) {
	TIM13->CNT = 0;
	
	UIM1.pulseFreequencyTemp++;
	
	if (UIM1.pulseFreequency) {
		uint32_t pulseDutyCyckle = TIM13->CCR1;
	}
}

void calcDurationUIM1(void) {
	if (UIM1.flagDurationUpdate) {
		calcDuration(&UIM1);
		UIM1.flagDurationUpdate = 0;
	} 
	
	if (!UIM1.pulseFreequency) {
		clearUIMParam(&UIM1);
	}
}

void updateUIM1Freequency(void) {
	UIM1.pulseFreequency = UIM1.pulseFreequencyTemp;
	UIM1.pulseFreequencyTemp = 0;
}

t_UIM *getUIM1(void) { return &UIM1; }

////////////////////////////////// UIM2
t_UIM UIM2;

void EXTI1_IRQHandler(void) {
	if (UIM2.pulseFreequency) {
		UIM2.pulseDurationTemp = TIM14->CNT;
		UIM2.flagDurationUpdate = 1;
	};

	EXTI->PR |= EXTI_PR_PR1; 		// Сброс флага
}

void TIM8_TRG_COM_TIM14_IRQHandler(void) { 
	TIM14->CNT = 0;
	
	UIM2.pulseFreequencyTemp++;
	
	if (UIM2.pulseFreequency) {
		uint32_t pulseDutyCyckle = TIM14->CCR1;
	}
}

void calcDurationUIM2(void) {
	if (UIM2.flagDurationUpdate) {
		calcDuration(&UIM2);
		UIM2.flagDurationUpdate = 1;
	}
	
	if (!UIM2.pulseFreequency) {
		clearUIMParam(&UIM2);
	}
}

void updateUIM2Freequency(void) {
	UIM2.pulseFreequency = UIM2.pulseFreequencyTemp;
	UIM2.pulseFreequencyTemp = 0;
}

t_UIM *getUIM2(void) { return &UIM2; }



