#include "debug.h"

// Отладка на USART1
// PB7 - RX, PA9 - TX
#define debugBaud 921600 // Битрейт отладки
#define debugBRR ((84000000 + debugBaud / 2) / debugBaud)

void debug_init(void) { // Инициализация отладки
	// Альтернативная функция порта
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL7_0 | GPIO_AFRL_AFSEL7_1 | GPIO_AFRL_AFSEL7_2;
	GPIOB->MODER |= GPIO_MODER_MODE7_1;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED7_Msk;
	
	GPIOA->AFR[1] |= GPIO_AFRH_AFSEL9_0 | GPIO_AFRH_AFSEL9_1 | GPIO_AFRH_AFSEL9_2;
	GPIOA->MODER |= GPIO_MODER_MODE9_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED9_Msk;
	
	// Настройки скоростей и битности
	USART1->BRR = debugBRR;
	// Разрешение интерфейса и прерывания
	USART1->CR1 |= USART_CR1_UE | USART_CR1_TE;
	
	printf("Debug Init Ok!\n");
}

int fputc(int ch, FILE *f) {
	debugSendStr((uint8_t *)&ch);
	return ch;
}

void debugSendStr(uint8_t *addr) {					// Функция передачи данных побайтно до символа 0x00
	while (*addr) {
		while(!(USART1->SR & USART_SR_TXE)) {}	// Ожидаем сброса флага окончания передачи данных
		USART1->DR = *addr++;										// Отправляем очередной байт
	}
}

void printfArray(uint8_t *addr, uint16_t count) {	// Функция вывода данных в HEX форме
	printf("-------------------------------\n");
	
	for (uint16_t i=0;i<count;i++) {
		if (!(i%16) & (i != 0)) printf("\n");
		printf("%02X ", addr[i]);
	}
	
	printf("\n");
}

void printfArray32(uint32_t *addr, uint16_t count) {	// Функция вывода данных в HEX форме 32 битных чисел
	printf("-------------------------------\n");
	
	for (uint16_t i=0;i<count;i++) {
		if (!(i%4) & (i != 0)) printf("\n");
		printf("%08X ", addr[i]);
	}
	
	printf("\n");
}


void USART1_IRQHandler(void) {
}







