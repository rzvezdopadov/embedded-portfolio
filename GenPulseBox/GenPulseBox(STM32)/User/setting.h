#ifndef  __SETTING_H
#define __SETTING_H

#include "main.h"
												
#define baseAddrSetting 			0x080E0000												// Адрес начала 11 сектора памяти Flash
#define baseSectorSetting 		11																// 11 Сектор

//#define	baseSizeSectorSetting 5120														// Размер сектора в байтах
#define	baseSizeSectorSetting 131072														// Размер сектора в байтах

void setting_init(void); 																				// Инициализация заводских настроек
void setting_null(void); 																				// Сброс к настройкам "по умолчанию"
void setting_load(void); 																				// Загрузка настроек
void setting_save(void); 																				// Сохранение настроек
void setting_update_struct(void);																// Обновление структур из основных регистров настройки в регистры выдачи данных

#endif 



