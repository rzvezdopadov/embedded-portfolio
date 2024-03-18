#ifndef  __UPDATE_H
#define __UPDATE_H

#include "main.h"
// PA3 - RX, PA2 - TX, PA8 - REDE

#define connectionReDeTx GPIO_SetBits(GPIOA, GPIO_Pin_8); 	// Передача данных
#define connectionReDeRx GPIO_ResetBits(GPIOA, GPIO_Pin_8); 	// Прием данных

void update_init(void); // Инициализация обновления системы через USART2
void updateSendStr(uint8_t *addr);
void updateSendStrDMA(uint16_t countByte);
void updateCommandParse(void);
uint8_t modbusTestCRC(uint8_t *addr, uint16_t sizeArray);
void modbusAddCRC(uint8_t *addr, uint16_t sizeArray);
uint16_t modbusCalcCRC(uint8_t *addr, uint16_t sizeArray);
void updateFilDataTx(void);
void parseQueryUpdate(void);

#endif 


