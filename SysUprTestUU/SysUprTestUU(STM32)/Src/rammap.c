#include "rammap.h"
// Структуры
t_coreCPUsett		coreCPUsett;		// Настройки параметров и уровней устройства
t_adcValue 			adcValue;				// Значение с АЦП 
t_adcValue 			adcValueFiltr;	// Значение с АЦП после фильтра
t_adcValue 			paramValue;			// Текущее значение
t_buf 					bufSPI;					// Буфер передачи данных SPI
t_buf 					bufUART;				// Буфер для подключения к ебаному компу
t_buf 					buf485;					// Буфер для подключения к мане небесной
t_buf 					bufPC;					// Буфер для подключения к мане небесной 1
t_coreCPU				coreCPU;				// Динамические данные ядра 
t_coreFlags 		coreFlags; 			// Флаги, для сохранения состояния разных функций и разрешений
t_test					test;						// Переменные для тестов


