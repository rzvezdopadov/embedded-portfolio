#include "main.h"

void debug_info(void);

int main(void) { // Главная функция
	coreFlags.timerGlobalTick = 0;	// 0 сек с момента запуска
// Инициализация	
  rcc_init(); 										// Тактирования
	debug_init();										// Отладки
	setting_init();									// Настроек
	criticalInterrupt_init();				// Критических прерываний
	addr_init();
	leds_debug_init();
	ledsalm_init();
	leds_init();
	sr_init();
	svbp_init();
	volt_init();
  volt_adc_init();
	pulsegen_init();
	ints_init();
	uim_init();
	termo_i2c_init();
	taskManager_init();
		
	printf("Start Main Cycle!\n");
	
	uint16_t svber1 = 1;
	uint16_t svber2 = 5;
	uint16_t svber3 = 9;
	uint16_t svber4 = 13;
	uint16_t svber5 = 17;
	uint16_t svber6 = 21;
	
//	uimOut1_enable;
//	uimOut1_on(10, 10000);
//	
//	uimOut2_enable;
//	uimOut2_on(1, 10000);
	  
	while (1) {
		setting_save();				// Сохранение, если есть флаги
		debug_info(); 				// Отладочная информация
		calcDurationUIM1();
		calcDurationUIM2();
		volt_adc_update();
		termo_i2c_read();
		leds_debug_change();
		
		_delay_ms(40);		
		if (++svber1 > 25) svber1 = 1;
		if (++svber2 > 25) svber2 = 1;
		if (++svber3 > 25) svber3 = 1;
		if (++svber4 > 25) svber4 = 1;
		if (++svber5 > 25) svber5 = 1;
		if (++svber6 > 25) svber6 = 1;
		
		ledalm_all_off();
		ledalm_on(svber1, RGB_Blue);
		ledalm_on(svber2, RGB_Blue | RGB_Red);
		ledalm_on(svber3, RGB_Red);
		ledalm_on(svber4, RGB_Red | RGB_Green);
		ledalm_on(svber5, RGB_Green);
		ledalm_on(svber6, RGB_Green | RGB_Blue);
		ledsalm_send();
	}	
}

void debug_info(void) { // Отладочная информация
	if (!coreFlags.printF) return;
	
//	printf("TermoPCB %d \n", coreCPU.TermoPCB);
//	led_g_change;
	
//	printf("idTime %d \n", coreCPUsett.idTime);
//	
//	printf("serial %d \n", coreCPUsett.serial);
	
//	printf("CFphyAddr: %d; getPhyAddr: %d; MDR_PORTE: %04X;\n", coreFlags.phyAddr, getPhyAddr, MDR_PORTE->RXTX);
	
//	printf("Tick: %d\n", coreFlags.timerGlobalTick);
	
//	printf("flagHWErr: %d\n", coreFlags.flagHWErr);
	
//	printf("%d \n", getPhyAddr);

	
//	getHWError();
//	printf("flagHWErr_Pin: %d, flagHWErr_Pref: %d, flagHWErr_QT: %d, flagHWErr: %d\n", 
//		coreFlags.flagHWErr_Pin, coreFlags.flagHWErr_Pref, 
//			coreFlags.flagHWErr_QT, coreFlags.flagHWErr);
//	printfArray32((uint32_t *)&GPIOG->IDR, 1);
//		printf("Pin: %d, Pref: %d, Tuim: %d, Quim: %d\n", 
//			coreCPUsett.thresholdPin, coreCPUsett.thresholdPref, 
//				coreCPUsett.thresholdTuim, coreCPUsett.thresholdQuim);
//	
//		coreCPU.ControlWord |= flagCW_AlarmUin;
//		printf("TermoPCB: %d \n", coreCPU.TermoPCB);

//	
 //printf("getPhyAddr: %02X \n", getPhyAddr);
	printf("-------------------------------------\n");
//	printf("Volt1: %04d; Volt2: %04d; Volt3: %04d; Volt4: %04d; Volt5: %04d; Volt6: %04d; Volt7: %04d; Volt8: %04d;\n", 
//		paramValue.Volt1, paramValue.Volt2, paramValue.Volt3, paramValue.Volt4,
//		paramValue.Volt5, paramValue.Volt6, paramValue.Volt7, paramValue.Volt8
//	);
	
//	printf("Volt1: %04d; Volt2: %04d; Volt3: %04d; Volt4: %04d; Volt5: %04d; Volt6: %04d; Volt7: %04d; Volt8: %04d;\n", 
//		adcValue.Volt1, adcValue.Volt2, adcValue.Volt3, adcValue.Volt4,
//		adcValue.Volt5, adcValue.Volt6, adcValue.Volt7, adcValue.Volt8
//	);
//	printf("adc_Pin: %d; adcF_Pin: %d; val_Pin: %d;\n", adcValue.Pin, adcValueFiltr.Pin, paramValue.Pin);
//	printf("adc_Pout: %d; adcF_Pout: %d; val_Pout: %d;\n", adcValue.Pout, adcValueFiltr.Pout, paramValue.Pout);
//	printf("adc_Pref: %d; adcF_Pref: %d; val_Pref: %d;\n", adcValue.Pref, adcValueFiltr.Pref, paramValue.Pref);
//	printf("adc_Termo: %d; adcF_Termo: %d; val_Termo: %d;\n", adcValue.Termo, adcValueFiltr.Termo, paramValue.Termo);
//	printf("adc_Uin1: %d; adcF_Uin: %d; val_Uin: %d;\n", adcValue.Uin1, adcValueFiltr.Uin, paramValue.Uin);
//	printf("adc_Uin2: %d;\n", adcValue.Uin2);
////	
//	printf(
//		"UIM Pulse: Duration=%d; Freequency=%d; DutyCyckle=%d; pulsePeriod=%d\n",
//		coreFlags.pulseDuration,
//		coreFlags.pulseFreequency,
//		coreFlags.pulseDutyCyckle,
//		coreFlags.pulsePeriod
//	);
//	t_UIM *uim = getUIM2();
//	
//	printf(
//		"UIM1: Freequency=%d; Duration=%d; Period=%d; DutyCyckle=%d;\n",
//		uim->pulseFreequency,
//		uim->pulseDuration,
//		uim->pulsePeriod,
//		uim->pulseDutyCyckle
//	);
//		coreFlags.pulseDutyCyckle,
//		coreFlags.pulsePeriod
//	);
	
//		printf(
//		"CNT = %d, CCR4 = %d; \n", coreFlags.Count, coreFlags.Siska
//	);
	
	
////	printf("idTime: %d \n", coreCPUsett.idTime);
////	printf("idTime: 0x%04X\n", coreCPU.ControlWord);
//	if (is1532P) {
//		printf("is1532P Yes!\n");
//	} else {
//		printf("is1532P No!\n");
//	}
	coreFlags.printF = flagDisable;
}
