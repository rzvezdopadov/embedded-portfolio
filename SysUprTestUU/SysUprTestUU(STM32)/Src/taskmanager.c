#include "taskmanager.h"

// Критические прерывания

void taskManager_init(void) {	
	// Прерывание раз в секунду	
  SysTick->LOAD  = (F_CPU/100) + 43;						// Значение до которого считать	
  NVIC_SetPriority(SysTick_IRQn, 3);						// Устанавливаем приоритет прерывания в NVIC
	NVIC_EnableIRQ(SysTick_IRQn); 								// Разрешаем прерывание в NVIC
  SysTick->VAL   = 0UL;													// Значение от которого считать
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |	// Разрешаем от какой ветки тактируется
                   SysTick_CTRL_TICKINT_Msk   |	// Разрешаем прерывание
                   SysTick_CTRL_ENABLE_Msk;			// Разрешаем таймер
}

void SysTick_Handler(void) {										// Прерывание 100 раз в секунду
	if (coreFlags.sysTickTemp++ > 98) {											// Один раз в секунду
		coreCPUsett.idTime++; 											// Уникальная метка времени для памяти
		coreCPUsett.opTime++;												// Наработка
		coreFlags.timerGlobalTick++;								// Глобальная переменная для старта некоторой логики, тикает раз в секунду
		
		if (!(coreCPUsett.idTime % 180)) {coreFlags.settSaveEnable = flagEnable;} // Если 3 минуты прошли, сохраняем
		
		if (!(coreCPUsett.idTime % 1)) {
			coreFlags.printF = flagEnable; 							// Флаг вывода данных отладки
			coreFlags.flagGetTermoSensor = flagEnable;	// Флаг чтения термодатчика
		}
		
		updateUIM1Freequency();
		updateUIM2Freequency();
		
		changePos();
		
		coreFlags.sysTickTemp = 0; // Обнуляем регистр
	}
		
	volt_adc_start();
}


