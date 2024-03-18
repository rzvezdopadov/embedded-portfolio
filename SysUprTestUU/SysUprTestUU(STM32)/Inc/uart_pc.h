#ifndef __UART_PC_H
#define __UART_PC_H

#include "main.h"

// Пердача данных в комп по USART3(AF7) - RS485
// PB10 - TX, PB11 - RX, PB12 - EN

#define uartPcReDeTx GPIOB->BSRR = GPIO_BSRR_BS12 	// Передача данных
#define uartPcReDeRx GPIOB->BSRR = GPIO_BSRR_BR12 	// Прием данных

void uart_pc_init(void); 														// Инициализация тактирования
void uartPCSendStrDMA(uint16_t countByte);					// Отправка данный суйка

#endif 


