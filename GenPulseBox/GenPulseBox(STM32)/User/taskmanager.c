#include "taskmanager.h"

// Критические прерывания

void taskManager_init(void) {
	printf("Task Manager Init Start...\n");
	// Прерывание раз в секунду	
  SysTick->LOAD  = 84000000/10+218;							// Значение до которого считать	
  NVIC_SetPriority (SysTick_IRQn, 3);						// Устанавливаем приоритет прерывания в NVIC
	NVIC_EnableIRQ(SysTick_IRQn); 								// Разрешаем прерывание в NVIC
  SysTick->VAL   = 0UL;													// Значение от которого считать
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |	// Разрешаем от какой ветки тактируется
                   SysTick_CTRL_TICKINT_Msk   |	// Разрешаем прерывание
                   SysTick_CTRL_ENABLE_Msk;			// Разрешаем таймер
	printf("Task Manager Init Ok!\n");
}

uint8_t sysTickTemp = 0;

void SysTick_Handler(void) {
	if (sysTickTemp++ > 18) {
		coreCPUsett.operatingTime++; 							// Наработка в сек
		coreCPUsett.idTime++; 										// Уникальная метка времени для памяти
		coreFlags.printfEnable++;									// Вывод данных в главном цикле(Main) раз в секунду
		
//		if (!(coreCPUsett.idTime % 60)) {coreFlags.settSaveEnable = flagEnable;} // Если минута прошла, сохраняем

		sysTickTemp = 0;
	}
}
