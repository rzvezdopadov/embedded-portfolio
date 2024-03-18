#include "pulsegen.h"

// UIM1 - PA0, UIM2 - PA15
// UIM1_EN - PF13, UIM2_EN - PF14

void pulsegen_init(void) {
	GPIOF->OSPEEDR |= GPIO_OSPEEDR_OSPEED13_Msk
										| GPIO_OSPEEDR_OSPEED14_Msk;
	
	GPIOF->MODER	 |= GPIO_MODER_MODE13_0
											| GPIO_MODER_MODE14_0;
	
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED0_Msk
										| GPIO_OSPEEDR_OSPEED15_Msk;
	
	GPIOA->MODER	 |= GPIO_MODER_MODE0_1
											| GPIO_MODER_MODE15_1;
	
	GPIOA->PUPDR	 |= GPIO_PUPDR_PUPD0_1
											| GPIO_PUPDR_PUPD15_1;
	
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL0_1;
	GPIOA->AFR[1] |= GPIO_AFRH_AFSEL15_0;
	
	uimOut1_disable;
	uimOut1_off();
	uimOut2_disable;
	uimOut2_off();
}

void uim_off(TIM_TypeDef *TIM) {
	TIM->CCER  = 0;
	TIM->CCMR1 = 0;
	TIM->CR1 	 = 0;
	TIM->PSC 	 = 0;
	TIM->ARR   = 0;
	TIM->CCR1  = 0;
	TIM->CNT 	 = 0;
}

void uim_on(TIM_TypeDef *TIM, uint32_t *duration, uint32_t *period) {
	#define paramOverflow 10000000
	if (*duration > paramOverflow) *duration = paramOverflow;
	
	if (*period > paramOverflow) *period = paramOverflow;

	if (
		(*duration == 0) 
		|| (*period == 0) 
			|| (*duration == *period)
	) return;
	
	uint32_t durationNew = *duration;
	uint32_t periodNew = *period;
	
	if (*duration > *period) {
		durationNew = *period;
		periodNew = *duration;
	}
	
	TIM->PSC = 0;
	TIM->ARR  =  (periodNew * 84) / 10;
	TIM->CCR1 =  (durationNew * 84) / 10;
	TIM->CR1 = TIM_CR1_ARPE;
	TIM->EGR |= TIM_EGR_UG;
	TIM->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
	TIM->CCMR1 |= TIM_CCMR1_OC1PE;
	TIM->CCER = TIM_CCER_CC1E;
	TIM->CR1 |= TIM_CR1_CEN;
}

void uimOut1_off(void) {
	uim_off(TIM5);
}

void uimOut1_on(uint32_t duration, uint32_t period) {
	uim_on(TIM5, &duration, &period);
}

void uimOut2_off(void) {
	uim_off(TIM2);
}

void uimOut2_on(uint32_t duration, uint32_t period) {
	uim_on(TIM2, &duration, &period);
}
