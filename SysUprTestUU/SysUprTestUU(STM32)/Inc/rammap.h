#ifndef __RAMMAP_H
#define __RAMMAP_H

#include "main.h"

#pragma pack(1) // Выравнивание 1 байт

typedef struct {
	int32_t Volt1;
	int32_t Volt2;
	int32_t Volt3;
	int32_t Volt4;
	int32_t Volt5;
	int32_t Volt6;
	int32_t Volt7;
	int32_t Volt8;
} t_adcValue;	

#pragma pack() 

#pragma pack(1) // Выравнивание 1 байт

typedef struct {	//	Настройки
	t_adcValue calibrAdcValueBias;	// 0:19		bytes // Разница измеряемых величин
	t_adcValue calibrAdcValueTilt;	// 20:39	bytes // Наклон измеряемых величин
	uint32_t serial;								// 72:75	bytes // Серийный номер
	uint32_t opTime; 								// 76:79	bytes // Время наработки прибора в секундах
	uint32_t idTime;								// 80:83	bytes // Уникальная метка для памяти
	uint32_t codeCRC;								// 84:85	bytes // Проверка корректности записи
} t_coreCPUsett;

#pragma pack() 

typedef struct {	// Флаги состояний
	uint32_t timerGlobalTick;				// Глобальная переменная для старта некоторой логики, возникает раз в секунду
	uint16_t settSaveEnable;				// Флаг разрешения записи настроек
	uint16_t enabledModeUpdate;			// Разрешение изменения режима
	uint16_t flagSpec;							// Специальный флаг для передачи в ПО ПК
	
	uint8_t  printF;								// Флаг для вывода данных в консоль в основном цикле
	uint8_t  adcConvertFinal;				// Флаг, что АЦП отдало параметры и можно расчет вести
	uint8_t	 enableProtocol;				// Нужно ли обслуживать протокол
	uint8_t	 enableUartPC;					// Нужно ли обслуживать протокол
	uint8_t	 enable485;
	uint8_t  enableProtoModeUpdate;	// Пришел запрос по обновлению режима устройства
	
	uint16_t sysTickTemp;						// Счетчик для sysTick Timer
	
	uint16_t adcConvertStart;
	
	uint16_t adcConvertTimeOut;
	
	uint8_t flagGetTermoSensor;			// Флаг чтения термодатчика
	
	uint8_t flagAddr;
	
} t_coreFlags;

typedef struct {									//	Динамические данные ядра
	int16_t TermoPCB;								// Температура датчика на плате
} t_coreCPU;

// Нумераторы флагов состояния
enum {flagNoAlarm, flagAlarm};
enum {flagRead,  	 flaghWrite};
enum {flagDisable, flagEnable};
enum {flagSigned,  flagUnsigned};
enum {flagPulseUp, flagPulseDown};
enum {flagTimerSearchNone, flagTimerSearchWidth, flagTimerSearchDutyCycle};

#define longBufferUart 256

typedef struct {
// Буферы передачи данных
	uint8_t  rx[longBufferUart];
	uint16_t rx_count;
	uint8_t  *rx_addr;
	uint8_t  tx[longBufferUart];
	uint16_t tx_count;
	uint8_t  *tx_addr;
} t_buf;

typedef struct {
	uint32_t value32;
	uint16_t value16;
	uint8_t  value8;
} t_test;

extern	t_coreCPUsett		coreCPUsett;		// Настройки параметров и уровней устройства
extern	t_adcValue 			adcValue;				// Значение с АЦП
extern	t_adcValue 			adcValueFiltr;	// Значение с АЦП после фильтра
extern	t_adcValue 			paramValue;			// Текущее значение
extern 	t_buf 					bufSPI;					// Буфер передачи данных SPI
extern	t_buf 					bufUART;				// Буфер для подключения к ебаному компу
extern	t_buf 					buf485;					// Буфер для подключения к мане небесной
extern	t_buf 					bufPC;					// Буфер для подключения к мане небесной 1
extern	t_coreFlags 		coreFlags; 			// Флаги, для сохранения состояния разных функций и разрешений
extern	t_coreCPU				coreCPU;				// Динамические данные ядра 
extern  t_test					test;						// Переменные для тестов

#endif


