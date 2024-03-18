#include "rammap.h"
t_coreCPUsett		 				coreCPUsett;					// Настройки параметров и уровней устройства
t_coreFlags 						coreFlags; 						// Флаги, для сохранения состояния разных функций и разрешений
t_seq_timer							seqTimer;							// Управление последовательностями таймеров
t_buf 									updateBuf;						// Буферы для передачи данных по UART программе настройки УУ
t_test									test;									// Массивы для тестов		
