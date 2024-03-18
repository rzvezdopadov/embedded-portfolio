#include "setting.h"

void clearRAM(uint8_t *addr, uint32_t size) {
	for (uint32_t i=0;i<size;i++) {
		addr[i] = 0;
	}
}

void setting_init(void) { // Инициализация заводских настроек
	printf("Setting Init Start...\n");
	setting_load(); // Загружаем данные настроек
	
	if (coreCPUsett.codeCRC != 0x55AA) {	// Проверяем наличие контрольного слова
		setting_null();											// Если слова нет, сбрасываем в настройки по умолчанию
	}
	
	printf("Setting Init Ok!\n");
}

void setting_null(void) {
// Настройки по умолчанию
// Очищаем всю ОЗУ v
	clearRAM((uint8_t *)&coreCPUsett, sizeof(coreCPUsett));
	clearRAM((uint8_t *)&coreFlags, sizeof(coreFlags));
// Очищаем всю ОЗУ ^
	
// 1 программа
	for (uint16_t i=0; i<14; i++) {
		coreCPUsett.sequences[i].enabled = flagEnable;
		
		strcpy((char *)coreCPUsett.sequences[i].name, "GU-01(");
		sprintf((char *)coreCPUsett.sequences[i].name, "%s%d)", coreCPUsett.sequences[i].name, i);
		
		coreCPUsett.sequences[i].CH1.pulses[0].count = i + 1;
		coreCPUsett.sequences[i].CH1.pulses[0].up1 = 10 * (i+1);
		coreCPUsett.sequences[i].CH1.pulses[0].up2 = 15 * (i+1);
		coreCPUsett.sequences[i].CH1.pulses[0].down = 30 * (i+1);
		coreCPUsett.sequences[i].CH1.count = 1;
		coreCPUsett.sequences[i].CH1.bias = 0;
		coreCPUsett.sequences[i].CH1.polarity1 = 0;
		coreCPUsett.sequences[i].CH1.polarity2 = 0;
		
		coreCPUsett.sequences[i].CH2.pulses[0].count = 1;
		coreCPUsett.sequences[i].CH2.pulses[0].up1 = 20 * (i+1);
		coreCPUsett.sequences[i].CH2.pulses[0].up2 = 25 * (i+1);
		coreCPUsett.sequences[i].CH2.pulses[0].down = 40 * (i+1);
		coreCPUsett.sequences[i].CH2.count = 1;
		coreCPUsett.sequences[i].CH2.bias = 0;
		coreCPUsett.sequences[i].CH2.polarity1 = 0;
		coreCPUsett.sequences[i].CH2.polarity2 = 0;
				
		coreCPUsett.sequences[i].period = 10000;
	}
	
	coreCPUsett.sequences[14].enabled = flagEnable;
	strcpy((char *)coreCPUsett.sequences[14].name, "Fuck Me!");
	sprintf((char *)coreCPUsett.sequences[14].name, "%s", coreCPUsett.sequences[14].name);
	coreCPUsett.sequences[14].CH1.pulses[0].count = 1;
	coreCPUsett.sequences[14].CH1.pulses[0].up1 = 10;
	coreCPUsett.sequences[14].CH1.pulses[0].down = 30;
	coreCPUsett.sequences[14].CH1.pulses[1].count = 2;
	coreCPUsett.sequences[14].CH1.pulses[1].up1 = 20;
	coreCPUsett.sequences[14].CH1.pulses[1].down = 60;
	coreCPUsett.sequences[14].CH1.count = 2;
	coreCPUsett.sequences[14].CH1.bias = 0;
	coreCPUsett.sequences[14].CH1.polarity1 = 0;
	coreCPUsett.sequences[14].CH1.polarity2 = 0;
	
	coreCPUsett.sequences[14].CH2.pulses[0].count = 1;
	coreCPUsett.sequences[14].CH2.pulses[0].up1 = 20;
	coreCPUsett.sequences[14].CH2.pulses[0].down = 50;
	coreCPUsett.sequences[14].CH2.pulses[1].count = 2;
	coreCPUsett.sequences[14].CH2.pulses[1].up1 = 10;
	coreCPUsett.sequences[14].CH2.pulses[1].down = 50;
	coreCPUsett.sequences[14].CH2.pulses[2].count = 3;
	coreCPUsett.sequences[14].CH2.pulses[2].up1 = 30;
	coreCPUsett.sequences[14].CH2.pulses[2].down = 50;
	coreCPUsett.sequences[14].CH2.count = 3;
	coreCPUsett.sequences[14].CH2.bias = 0;
	coreCPUsett.sequences[14].CH2.polarity1 = 0;
	coreCPUsett.sequences[14].CH2.polarity2 = 0;
	
	coreCPUsett.sequences[14].period = 10000;
	
// Заводские номера и версии ПО и прибора, контрольное число
	coreCPUsett.sn				= serial_number;
	coreCPUsett.codeCRC		= 0x55AA;

	coreCPUsett.operatingTime = 0;												// Время наработки
	coreCPUsett.idTime = 0;															// Метка времени
		
	printf("Sett Null Ok!\n");
	coreFlags.settSaveEnable = flagEnable;
// Сохраняем настройки в память
	setting_save();
}

void setting_load(void) { // Загрузка настроек из памяти
	// Настройки устройства занимают 11 сектор памяти Flash, алгоритм ищет в памяти самую последнюю запись
	// исходя из параметра метки времени idTime, которая инкрементируется в таймере SysTick, выравнивание данных по coreCPUsett
	
	printf("sett_load: %d \n", baseSizeSectorSetting);
	
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
	
	printf("Search setting position = %d;\n", position);
	uint8_t *p = (uint8_t *)(baseAddrSetting+sizeof(coreCPUsett)*position);
	uint8_t *q = (uint8_t *)&coreCPUsett;
	
	for (uint32_t i=0;i<sizeof(coreCPUsett);i++) {	// Копируем данные из Flash в RAM
		q[i] = p[i];
	}
		
	setting_update_struct();	// Обновление данных для структур передачи данных, после загрузки данных
	printf("Sett Load Ok!\n");
}

void setting_save(void) { // Сохранение настройки в память
	if (coreFlags.settSaveEnable) {
		coreFlags.settSaveEnable = flagDisable; 
		// На 11 секторе памяти ищутся свободные ячейки по критерию метки времени idTime = 0xFFFFFFFF, 
		// после нахождения записываются данные , в размере выравнивания по coreCPUsett, 
		// если вся память чистая, данные пишутся в начало сектора,
		// если весь сектор уже исписан, он чистится и данные записываются вначало

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
		// setting_update_struct();																																									// Обновляем структуры для передачи данных
		//__enable_irq();
		printf("Sett Save pos: '%d', id: '%d' - Ok!\n", position, coreCPUsett.idTime);
	}
}

void setting_update_struct(void) { // Обновление структур для передачи данных

}
