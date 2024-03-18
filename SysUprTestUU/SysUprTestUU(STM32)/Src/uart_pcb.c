#include "uart_pcb.h"

// Отладка на USART6
// PB1 - RX, PB0 - TX
#define baud 921600 // Битрейт отладки
#define baudBRR ((84000000 + baud / 2) / baud)

void uart_pcb_init(void) { // Инициализация отладки
	// Альтернативная функция порта
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL0_0 | GPIO_AFRL_AFSEL0_1 | GPIO_AFRL_AFSEL0_2;
	GPIOB->MODER |= GPIO_MODER_MODE0_1;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED0_Msk;
	
	// Настройки скоростей и битности
	USART1->BRR = baudBRR;
	// Разрешение интерфейса и прерывания
	USART1->CR1 |= USART_CR1_UE | USART_CR1_TE;
}

void USART6_IRQHandler(void) {
	
}







