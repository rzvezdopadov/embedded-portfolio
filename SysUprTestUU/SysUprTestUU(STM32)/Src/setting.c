#include "setting.h"

void clearRAM(uint8_t *addr, uint32_t size) {
	for (uint32_t i=0;i<size;i++) {
		addr[i] = 0;
	}
}

void setting_init(void) { // Инициализация заводских настроек
	printf("Sett Init Start...\n");
	
// Очищаем всю ОЗУ v
	clearRAM((uint8_t *)&coreCPUsett, sizeof(coreCPUsett));
	clearRAM((uint8_t *)&coreCPU, sizeof(coreCPU));
	clearRAM((uint8_t *)&coreFlags, sizeof(coreFlags));
	clearRAM((uint8_t *)&bufSPI, sizeof(bufSPI));
	clearRAM((uint8_t *)&bufUART, sizeof(bufUART));
	clearRAM((uint8_t *)&buf485, sizeof(buf485));
	clearRAM((uint8_t *)&adcValue, sizeof(adcValue));
	clearRAM((uint8_t *)&adcValueFiltr, sizeof(adcValueFiltr));
	clearRAM((uint8_t *)&paramValue, sizeof(paramValue));
	
// Очищаем всю ОЗУ ^	
		
	setting_load(); // Загружаем данные настроек
	
	if (coreCPUsett.codeCRC != Const_codeCRC) {	// Проверяем наличие контрольного слова
		setting_null();											// Если слова нет, сбрасываем в настройки по умолчанию
	}
		
	printf("Sett Init Ok!\n");
}

void setting_null(void) {
//// Настройки по умолчанию
	coreCPUsett.calibrAdcValueBias.Volt1 		= Const_calibrBiasVolt;		// 0:3		bytes // Входная мощность (Разница)
	coreCPUsett.calibrAdcValueBias.Volt2 		= Const_calibrBiasVolt;
	coreCPUsett.calibrAdcValueBias.Volt3 		= Const_calibrBiasVolt;
	coreCPUsett.calibrAdcValueBias.Volt4 		= Const_calibrBiasVolt;
	coreCPUsett.calibrAdcValueBias.Volt5 		= Const_calibrBiasVolt;
	coreCPUsett.calibrAdcValueBias.Volt6 		= Const_calibrBiasVolt;
	coreCPUsett.calibrAdcValueBias.Volt7 		= Const_calibrBiasVolt;
	coreCPUsett.calibrAdcValueBias.Volt8 		= Const_calibrBiasVolt;
	
	coreCPUsett.calibrAdcValueTilt.Volt1		= Const_calibrTiltVolt;
	coreCPUsett.calibrAdcValueTilt.Volt2		= Const_calibrTiltVolt;
	coreCPUsett.calibrAdcValueTilt.Volt3		= Const_calibrTiltVolt;
	coreCPUsett.calibrAdcValueTilt.Volt4		= Const_calibrTiltVolt;
	coreCPUsett.calibrAdcValueTilt.Volt5		= Const_calibrTiltVolt;
	coreCPUsett.calibrAdcValueTilt.Volt6		= Const_calibrTiltVolt;
	coreCPUsett.calibrAdcValueTilt.Volt7		= Const_calibrTiltVolt;
	coreCPUsett.calibrAdcValueTilt.Volt8		= Const_calibrTiltVolt;
	
	coreCPUsett.serial 										= Const_serial;						// 72:75	bytes // Серийный номер
	coreCPUsett.opTime										= Const_opTime; 					// 76:79	bytes // Время наработки прибора в секундах
	coreCPUsett.idTime 										= 0;											// 80:83	bytes // Уникальная метка для памяти
	coreCPUsett.codeCRC 									= Const_codeCRC;					// 84:85	bytes // Проверка корректности записи
		
	printf("Sett Null Ok!\n");
	
// Очищаем сектор памяти настроек
	flash_erase_sector(baseSectorSetting);
// Сохраняем настройки в память
	coreFlags.settSaveEnable = flagEnable;
	setting_save();
}

void setting_load(void) { // Загрузка настроек из памяти
	// Настройки устройства занимают 11 сектор памяти Flash, алгоритм ищет в памяти самую последнюю запись
	// исходя из параметра метки времени idTime, которая инкрементируется в таймере SysTick, выравнивание данных по coreCPUsett
	
	uint16_t bias = (uint16_t)((uint8_t *)(&coreCPUsett.idTime) - (uint8_t *)(&coreCPUsett));	// Размер смещения до idTime
	uint16_t position = 0;																																		// Для поиска позиции записи
	uint32_t *idTimeTemp = (uint32_t *)(baseAddrSetting+bias);
	if (*idTimeTemp != 0xFFFFFFFF) {																													// Если начало сектора не свободно
		for (uint16_t i=1;i<(baseSizeSectorSetting/sizeof(coreCPUsett)-1);i++) {								// Цикл поиска самой старшей записи в памяти по idTime
			uint32_t *idTime = (uint32_t *)(baseAddrSetting+bias+sizeof(coreCPUsett)*i);
			//printf("Search i = %d; Addr = 0x%08X idTime = %d \n", i, (uint32_t)idTime, (uint32_t)*idTime);
			if ((*idTime != 0xFFFFFFFF) & (*idTime > *idTimeTemp)) {
				position = i;
				idTimeTemp = idTime;
			}
		}	
	}
	
	// printf("Search setting position = %d;\n", position);
	uint8_t *p = (uint8_t *)(baseAddrSetting+sizeof(coreCPUsett)*position);
	uint8_t *q = (uint8_t *)&coreCPUsett;
	
	for (uint16_t i=0;i<sizeof(coreCPUsett);i++) {	// Копируем данные из Flash в RAM
		q[i] = p[i];
	}
		
	printf("Sett Load Ok!\n");
}

void setting_save(void) { // Сохранение настройки в память
	// На 11 секторе памяти ищутся свободные ячейки по критерию метки времени idTime = 0xFFFFFFFF, 
	// после нахождения записываются данные , в размере выравнивания по coreCPUsett, 
	// если вся память чистая, данные пишутся в начало сектора,
	// если весь сектор уже исписан, он чистится и данные записываются вначало
	if (coreFlags.settSaveEnable) {
		//__disable_irq();
		uint16_t bias = (uint16_t)((uint8_t *)(&coreCPUsett.idTime) - (uint8_t *)(&coreCPUsett)); 								// Размер смещения до idTime
		int16_t position = 0;																																											// Для поиска позиции записи
		uint32_t *idTimeTemp = (uint32_t *)(baseAddrSetting+bias); 																								// Получаем метку времени вначале сектора
		if (*idTimeTemp != 0xFFFFFFFF) {																																					// Если начало сектора не свободно
			for (uint16_t i=1;i<(baseSizeSectorSetting/sizeof(coreCPUsett))-1;i++) { 																	// Цикл поиска свободного места в секторе
				uint32_t *idTime = (uint32_t *)(baseAddrSetting+bias+sizeof(coreCPUsett)*i);													// Читаем метку времени
				//printf("Search i = %d; Addr = 0x%08X; idTime = %d \n", i, (uint32_t)idTime, (uint32_t)*idTime);
				if ((uint32_t)*idTime == 0xFFFFFFFF) {																																// Если часть памяти свободна
					position = i;																																												// Присваиваем найденную позицию
					idTimeTemp = idTime; 																																								// Присваиваем метку времени
					break;																																															// Выходим из цикла
				}
			}
					
			if (position == (baseSizeSectorSetting/sizeof(coreCPUsett)-2)) {																				// Если конец сектора 
				//printf("Flash erase sector Start!\n");
				flash_erase_sector(baseSectorSetting); 																																// Очищаем сектор
				//printf("Flash erase sector Ok!\n");
				position = 0;																																													// Устанавливаем позицию начала сектора
			}
		}
		
		// printf("Position: %d; Fucking addr: 0x%08X; Bias=0x%X \n", position, baseAddrSetting+bias*position,bias);
		flash_write(baseAddrSetting+sizeof(coreCPUsett)*position, (uint8_t *)&coreCPUsett, sizeof(coreCPUsett));	// Записываем данные во Flash
		
		//__enable_irq();
		printf("Sett Save pos: '%d', id: '%d' - Ok!\n", position, coreCPUsett.idTime);
		coreFlags.settSaveEnable = flagDisable;																																		// Сбрасываем флаг записи
	}
}

