#ifndef __UART_485_H
#define __UART_485_H

#include "main.h"

//  Пердача данных в устройство по USART2(AF7) - RS485
// PA8 - EN, PA2 - TX, PA3 - RX

#define uart485ReDeTx GPIOA->BSRR = GPIO_BSRR_BS8 	// Передача данных
#define uart485ReDeRx GPIOA->BSRR = GPIO_BSRR_BR8 	// Прием данных

void uart_485_init(void); 															// Инициализация тактирования

#endif 


