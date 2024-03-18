#ifndef __SPI_H
#define __SPI_H

#include "main.h"

// SPI1 - Взаимодействие с заказчиком
// PA15 - SS, PB3 - SCK, PB4 - MISO, PB5 - MOSI

// Команды управления
#define cmdRayCtrl 					0x01 // Управление лучом
#define cmdRayCtrlRaw 			0x02	// Управление лучом без коррекции
#define cmdRegCtrlWr 				0x03 // Запись в регистр управления
#define cmdRegCtrlRd 				0x04 // Чтение регистра управления
#define cmdEepromWr 				0x05 // Запись байта в РПЗУ
#define cmdEepromRd 				0x06 // Чтение байта из РПЗУ
#define cmdRegCtrlRdAll 		0x07 // Чтение массива регистров управления
#define cmdRegStateRdAll		0x08 // Чтение регистров состояния
#define cmdEepromArrayWr		0x09 // Запись массива данных в РПЗУ
#define cmdEepromArrayRd		0x0A // Чтение массива данных в РПЗУ
#define cmdGetVersion 			0x0B // Запрос версии ПО
#define cmdGetSerial 				0x0C // Запрос заводского номера
#define cmdTechn 						0x0D // Технологическая

void spi_Init(void);	// Инициализация SPI
void parse_cmd(void);	// Парсинг пришедших данных по SPI
//void updateRayCtrl(void);
void send_cmdRayCtrlGeneral(void);
// Функции обработки команд
void send_cmdRayCtrl(void);
void send_cmdRayCtrlRaw(void);
void send_cmdRegCtrlWr(void);
void send_cmdRegCtrlRd(void);
void send_cmdEepromWr(void);
void send_cmdEepromRd(void);
void send_cmdRegCtrlRdAll(void);
void send_cmdRegStateRdAll(void);
void send_cmdEepromArrayWr(void);
void send_cmdEepromArrayRd(void);
void send_cmdGetVersion(void);
void send_cmdGetSerial(void);
void send_cmdTechn(void);

void spi_Answer(void); // Отправка ответа в SPI



#endif 

