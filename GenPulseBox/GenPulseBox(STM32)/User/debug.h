#ifndef  __DEBUG_H
#define __DEBUG_H

#include "main.h"
#include "stm32f4xx.h"

// Отладка на USART1
// PA10 - RX, PA9 - TX

void debug_init(void); 															// Инициализация тактирования
void debugSendStr(uint8_t *addr);										// Отправка строки
void printfArray(uint8_t *addr, uint16_t count);		// Вывод данных в шестнадцатеричной форме
void printfArray32(uint32_t *addr, uint16_t count);


#endif 


