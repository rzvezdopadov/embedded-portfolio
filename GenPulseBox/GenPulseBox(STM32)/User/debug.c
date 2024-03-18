#include "debug.h"

// Отладка на USART1
// PA10 - RX, PA9 - TX
#define debugBaud 921600 // Битрейт отладки
#define debugBRR ((84000000 + debugBaud / 2) / debugBaud)

void debug_init(void) { // Инициализация отладки
	// Альтернативная функция порта
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);

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
	uint16_t i=0;
	
	for (; i<count; i++) {
		if (!(i%16) & (i != 0)) printf("\n");
		printf("%02X ", addr[i]);
	}
	printf("\n--------------------------\n");
}

void printfArray32(uint32_t *addr, uint16_t count) {	// Функция вывода данных в HEX форме 32 битных чисел
	uint16_t i=0;
	
	for (; i<count; i++) {
		if (!(i%4) & (i != 0)) printf("\n");
		printf("%08X ", addr[i]);
	}
	printf("\n-------------------------------\n");
}


void USART1_IRQHandler(void) {
}







