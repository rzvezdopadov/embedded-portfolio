#ifndef  __RAMMAP_H
#define __RAMMAP_H

#include "main.h"
#include "TouchPanel/TouchPanel.h"

/////////////////////////// Фундаментальные настроечные параметры v
#define version_fw	  20221220		// Версия ПО - yyyy.mm.dd
#define serial_number 2022010101	// Серийный номер - yyyy.mm.dd xx (Дата, № устройства)

#pragma pack(1) // Выравнивание 1 байт

typedef struct {
	uint32_t settSaveEnable;
	uint32_t printfEnable;
	uint32_t CH1Enable1;
	uint32_t CH1Enable2;
	uint32_t CH2Enable1;
	uint32_t CH2Enable2;
} t_coreFlags;

typedef struct {
	uint32_t up1;
	uint32_t up2;
	uint32_t down;
	uint32_t count;
} t_pulses_ch;

typedef struct {
	t_pulses_ch pulses[50];
	uint32_t count;
	uint32_t polarity1;
	uint32_t polarity2;
	uint32_t bias;
} t_channel;

typedef struct {
	uint32_t enabled;
	t_channel CH1;
	t_channel CH2;
	uint32_t period;
	char name[20];
} t_sequenced;

typedef struct {
	uint32_t PSC;  // Предделитель таймера
  uint32_t ARR;  // Период 	 	
} t_timer_short;

typedef struct {
	t_timer_short Period;
  uint32_t RCR;  // Количество повторений
  uint32_t CCR1; // Длительность 1 подканала
	uint32_t CCR2; // Длительность 2 подканала
} t_timer;

typedef struct {
	t_timer	pulses[200];
	t_timer_short	bias;
	uint32_t count;
	uint32_t polarity1;
	uint32_t polarity2;
	uint32_t enable;
} t_ch_timer;

typedef struct {
	t_ch_timer CH1;
	t_ch_timer CH2;
	t_timer_short	period;
} t_seq_timer;

#define MaxCountSequenced 30

typedef struct {
	uint8_t addrDevice;
	uint8_t command;
	uint8_t seqPos;
	uint8_t crc;
	t_sequenced sequenced;
} t_FilData;

typedef struct {
	t_sequenced sequences[MaxCountSequenced];
	Coordinate  screenSample[3];
	uint32_t 		sn;							// Серийный номер
	uint32_t  	operatingTime; 	// Время наработки прибора в секундах
	uint32_t		idTime;					// Уникальная метка для памяти
	uint32_t 		codeCRC;				// Контрольная сумма
} t_coreCPUsett;

#define longBuf 300

typedef struct {
// Буферы передачи данных
	t_FilData RX;
	t_FilData TX;
	uint8_t	 *rx_addr;
	uint16_t rx_count;
	uint8_t rx_flag_en;
} t_buf;

typedef struct {
	uint32_t *addrTemp32;
	uint32_t temp32[32];
	uint16_t temp16[32];
	uint8_t  temp8[32];
}	t_test;

// Нумераторы флагов состояния
enum {rwFlagRead, rwFlagWrite};
enum {flagDisable, flagEnable};
enum {flagSigned, flagUnsigned};
enum {flagPulseUp, flagPulseDown};
enum {flagTimerSearchNone, flagTimerSearchWidth, flagTimerSearchDutyCycle};

#pragma pack() 

extern	t_coreCPUsett		 				coreCPUsett;					// Настройки параметров и уровней устройства
extern  t_FilData updateRX;
extern  t_FilData updateTX;
extern	t_coreFlags 						coreFlags; 						// Флаги, для сохранения состояния разных функций и разрешений
extern	t_seq_timer 						seqTimer;
extern 	t_buf 									updateBuf;						// Буферы для передачи данных по UART программе настройки УУ
extern 	t_test									test;									// Массивы для тестов								
#endif
