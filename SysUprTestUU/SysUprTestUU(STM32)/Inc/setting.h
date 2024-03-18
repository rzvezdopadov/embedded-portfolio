#ifndef __SETTING_H
#define __SETTING_H

#include "main.h"
												
#define baseAddrSetting 			0x080E0000												// Адрес начала 11 сектора памяти Flash
#define baseSectorSetting 		11																// 11 Сектор
#define	baseSizeSectorSetting 131072														// Размер сектора в байтах

#define maxResourceInHour			10000				// Максимальный ресурс прибора в часах
#define maxResourceInSec			(maxResourceInHour * 3600) // Максимальный ресурс прибора в секундах

// Настройки по умолчанию
#define Const_calibrBiasVolt		0					// 0:3		bytes // Разница 
	
#define Const_calibrTiltVolt		1000			// 20:23	bytes // Умножение

#define Const_serial						123456		// 72:75	bytes // Серийный номер
#define Const_opTime 						0					// 76:79	bytes // Время наработки прибора в секундах
#define Const_codeCRC						0x55AA		// 76:77	bytes // Проверка корректности записи
#define Const_fwVersion					20230403	// Версия прошивки формат YYYYMMDD (Год, Месяц, День выпуска)

void setting_init(void); 																				// Инициализация заводских настроек
void setting_null(void); 																				// Сброс к настройкам "по умолчанию"
void setting_load(void); 																				// Загрузка настроек
void setting_save(void); 																				// Сохранение настроек

#endif 



