#ifndef  __FLASH_H
#define __FLASH_H

#include "main.h"
												
void flash_erase_sector(uint8_t sectNum);												// Очистка сектора памяти
void flash_write(uint32_t addr, uint8_t *data, uint16_t size);	// Запись данных


#endif 



