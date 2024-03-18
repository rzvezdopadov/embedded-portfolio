#include "flash.h"

void flash_unlock(void) {																		// Разблокировка Flash памяти для записи
	while ((FLASH->SR & FLASH_SR_BSY) != 0);	
	
	// Проверяем память на предмет занятости
	if ((FLASH->CR & FLASH_CR_LOCK) != 0){									// Если она заблокирована
		FLASH->KEYR = 0x45670123;															// Пишем первый ключ разблокировки
		FLASH->KEYR = 0xCDEF89AB; 														// Пишем второй ключ разблокировки
	}
}

void flash_erase_sector(uint8_t sectNum) {									// Очистка сектора памяти
	USART2->CR1 &= ~USART_CR1_RE;
	__disable_irq();
	flash_unlock();																// Разблокировка памяти

	FLASH->CR |= FLASH_CR_SER;
	FLASH->CR &= ~(FLASH_CR_SNB_0 | FLASH_CR_SNB_1 | FLASH_CR_SNB_2 | FLASH_CR_SNB_3);  // Записываем номер сектора, который будем стирать
	FLASH->CR |= (uint32_t)(sectNum<<3U);  								// Записываем номер сектора, который будем стирать
	FLASH->CR |= FLASH_CR_STRT;																// Запускаем старт стирания сектора

	while ((FLASH->SR & FLASH_SR_BSY) != 0); 									// Проверяем память на предмет занятости
		
	if ((FLASH->SR & FLASH_SR_EOP) != 0) { 										// Если произошла ошибка, скидываем флаг
			FLASH->SR = FLASH_SR_EOP; 
	}
	FLASH->CR = FLASH_CR_LOCK; 															// Блокируем память для записи
	
	__enable_irq();
	USART2->CR1 |= USART_CR1_RE;
}

void flash_write(uint32_t addr, uint8_t *data, uint16_t size) {
	flash_unlock();

	for (uint16_t i=0;i<size;i++) {
		while ((FLASH->SR & FLASH_SR_BSY) != 0){};							// Проверяем память на предмет занятости

		FLASH->CR |= FLASH_CR_PG;																// Устанавливаем флаг записи памяти
		*(__IO uint8_t*)(addr+i) = data[i]; 										// Записываем байт

		while ((FLASH->SR & FLASH_SR_BSY) != 0); 								// Проверяем память на предмет занятости

		if ((FLASH->SR & FLASH_SR_EOP) != 0) {									// Если произошла ошибка, скидываем флаг
				FLASH->SR = FLASH_SR_EOP;
		}
		
		FLASH->CR &= ~FLASH_CR_PG; 															// Сбрасываем флаг записи памяти
	}
	
	FLASH->CR |= FLASH_CR_LOCK; 															// Блокируем память от записи
}






