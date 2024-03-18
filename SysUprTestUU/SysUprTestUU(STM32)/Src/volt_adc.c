#include "volt_adc.h"

// VOLT1 - PF3(IN9),  VOLT2_ADC - PF4(IN14), 
// VOLT3 - PF5(IN15), VOLT4_ADC - PF6(IN4),
// VOLT5 - PF7(IN5),  VOLT6_ADC - PF8(IN6), 
// VOLT7 - PF9(IN7),  VOLT8_ADC - PF10(IN8),

void volt_adc_init(void) {
	GPIOF->MODER |= GPIO_MODER_MODE3_Msk
								 | GPIO_MODER_MODE4_Msk
								  | GPIO_MODER_MODE5_Msk
									 | GPIO_MODER_MODE6_Msk
									  | GPIO_MODER_MODE7_Msk
										 | GPIO_MODER_MODE8_Msk
										  | GPIO_MODER_MODE9_Msk
											 | GPIO_MODER_MODE10_Msk;
	
	#define sampleADC 7

	ADC3->SMPR2 |= (sampleADC<<ADC_SMPR2_SMP4_Pos)
								| (sampleADC<<ADC_SMPR2_SMP5_Pos)
								 | (sampleADC<<ADC_SMPR2_SMP6_Pos)
									| (sampleADC<<ADC_SMPR2_SMP7_Pos)
									 | (sampleADC<<ADC_SMPR2_SMP8_Pos)
										| (sampleADC<<ADC_SMPR2_SMP9_Pos); 
	
	ADC3->SMPR1 |= (sampleADC<<ADC_SMPR1_SMP14_Pos)
							  | (sampleADC<<ADC_SMPR1_SMP15_Pos);
	
	ADC3->SQR3	|= (14 << ADC_SQR3_SQ1_Pos)
								| (15 << ADC_SQR3_SQ2_Pos)
								 | (4 << ADC_SQR3_SQ3_Pos)
									| (5 << ADC_SQR3_SQ4_Pos)
									 | (6 << ADC_SQR3_SQ5_Pos)
									  | (7 << ADC_SQR3_SQ6_Pos);
										
	ADC3->SQR2	|= (8 << ADC_SQR2_SQ7_Pos) 
								|	(9 << ADC_SQR2_SQ8_Pos);

	ADC3->SQR1 |= (7<<ADC_SQR1_L_Pos);
	ADC3->CR1	|= ADC_CR1_SCAN;				
	ADC3->CR2	= ADC_CR2_ADON;

	// DMA2 Stream0, Channel2
	DMA2_Stream0->NDTR = sizeof(t_adcValue)/4; 	// Сколько тетрабайт копировать 
	DMA2_Stream0->PAR  = (uint32_t)&ADC3->DR; 	// Указатель откуда копировать 
	DMA2_Stream0->M0AR = (uint32_t)&adcValue; 	// Указатель куда копировать
	
	DMA2_Stream0->CR   = DMA_SxCR_CHSEL_1
											| DMA_SxCR_PSIZE_1			// Размерность отправителя 32 бита
											 | DMA_SxCR_MSIZE_1			// Размерность приемника 32 бита 
												| DMA_SxCR_MINC 	 		// Разрешить инкрементировать адрес приемника
												 | DMA_SxCR_CIRC 			// Разрешить кольцевой режим
													| DMA_SxCR_EN				// Разрешаем поток этого канала DMA
													 | DMA_SxCR_TCIE;		// Разрешаем прерывание после полного круга передачи

	// Разрешаем прерывания по отработке DMA
	NVIC_SetPriority(DMA2_Stream0_IRQn, 7);
	NVIC_EnableIRQ(DMA2_Stream0_IRQn);
	
	coreFlags.adcConvertStart = flagDisable;
	coreFlags.adcConvertFinal = flagDisable;
}

void volt_adc_start(void) { // Запуск конвертирования АЦП
	if (coreFlags.adcConvertStart == flagDisable) {
		ADC3->CR2	= ADC_CR2_ADON 									// Включаем АЦП
							 | ADC_CR2_SWSTART 							// Запускаем сканирование регулярных каналов АЦП
							  | ADC_CR2_CONT 								// Сканирование каналов друг за другом
								 | ADC_CR2_EOCS								// Разрешаем выставить флаг об окончании, для DMA
									| ADC_CR2_DDS								// Запрос DMA как только сконвертировали один раз
									 | ADC_CR2_DMA;							// Разрешаем проброс DMA
		
		coreFlags.adcConvertStart = flagEnable;
	}
}

void DMA2_Stream0_IRQHandler(void) {	// После того, как записали все каналы АЦП	
	DMA2->LIFCR = DMA_LIFCR_CTCIF0 	// Очищаем флаги DMA
							 | DMA_LIFCR_CDMEIF0
								| DMA_LIFCR_CFEIF0
								 | DMA_LIFCR_CHTIF0
									| DMA_LIFCR_CTEIF0;
	
	ADC3->CR2	= ADC_CR2_ADON;					// Останавливаем конвертацию АЦП, но не выключаем его
	coreFlags.adcConvertTimeOut = 0;	// Идентификатор таймаута		
	
	// Говорим функции обработки данных АЦП, что данные готовы
	coreFlags.adcConvertFinal = flagEnable;
	coreFlags.adcConvertStart = flagDisable;
}

void updateValueWithFiltr(int32_t *adcValueFiltr, uint16_t kFiltr, int32_t adcValue) { // Фильтр значений АЦП
	*adcValueFiltr = (*adcValueFiltr * kFiltr + adcValue) / (kFiltr + 1); 
}

void updateValueWithBiasTitle(int32_t *paramValue, int32_t adcValue, int32_t biasValue, int32_t titlValue, uint8_t flagNeg) { 
	int32_t temp = adcValue + biasValue;	// Суммируем со значением разницы
	
	if ((flagNeg == flagUnsigned) & (temp<0)) {temp = 0;} // Если есть критерий отрицательности, то при уходе в отрицательную область значений ставим 0
	
	int32_t paramValueTitl = (temp * titlValue) / 1000; //	Умножаем на наклон и делим на 1000, точность 0,1%
	
	*paramValue = paramValueTitl; // Вычитание скважности умноженной на коэффициент и делим на 10 
}

void volt_adc_update(void) {	// Преобразования данных АЦП в конечный вид, проверка и выставление флагов 
	if (!coreFlags.adcConvertFinal) return;
	
	#define kFiltr 63
	
////// Преобразуем данные АЦП через фильтр		
	updateValueWithFiltr(&adcValueFiltr.Volt1, kFiltr, adcValue.Volt1);
	updateValueWithFiltr(&adcValueFiltr.Volt2, kFiltr, adcValue.Volt2);
	updateValueWithFiltr(&adcValueFiltr.Volt3, kFiltr, adcValue.Volt3);
	updateValueWithFiltr(&adcValueFiltr.Volt4, kFiltr, adcValue.Volt4);
	updateValueWithFiltr(&adcValueFiltr.Volt5, kFiltr, adcValue.Volt5);
	updateValueWithFiltr(&adcValueFiltr.Volt6, kFiltr, adcValue.Volt6);
	updateValueWithFiltr(&adcValueFiltr.Volt7, kFiltr, adcValue.Volt7);
	updateValueWithFiltr(&adcValueFiltr.Volt8, kFiltr, adcValue.Volt8);

////// Преобразуем данные в зависимости от настроек пользователя	
	updateValueWithBiasTitle(&paramValue.Volt1, adcValueFiltr.Volt1, 
		coreCPUsett.calibrAdcValueBias.Volt1, coreCPUsett.calibrAdcValueTilt.Volt1,  flagUnsigned);
	updateValueWithBiasTitle(&paramValue.Volt2, adcValueFiltr.Volt2, 
		coreCPUsett.calibrAdcValueBias.Volt2, coreCPUsett.calibrAdcValueTilt.Volt2,  flagUnsigned);
	updateValueWithBiasTitle(&paramValue.Volt3, adcValueFiltr.Volt3, 
		coreCPUsett.calibrAdcValueBias.Volt3, coreCPUsett.calibrAdcValueTilt.Volt3,  flagUnsigned);
	updateValueWithBiasTitle(&paramValue.Volt4, adcValueFiltr.Volt4, 
		coreCPUsett.calibrAdcValueBias.Volt4, coreCPUsett.calibrAdcValueTilt.Volt4,  flagUnsigned);
	updateValueWithBiasTitle(&paramValue.Volt5, adcValueFiltr.Volt5, 
		coreCPUsett.calibrAdcValueBias.Volt5, coreCPUsett.calibrAdcValueTilt.Volt5,  flagUnsigned);
	updateValueWithBiasTitle(&paramValue.Volt6, adcValueFiltr.Volt6, 
		coreCPUsett.calibrAdcValueBias.Volt6, coreCPUsett.calibrAdcValueTilt.Volt6,  flagUnsigned);
	updateValueWithBiasTitle(&paramValue.Volt7, adcValueFiltr.Volt7, 
		coreCPUsett.calibrAdcValueBias.Volt7, coreCPUsett.calibrAdcValueTilt.Volt7,  flagUnsigned);
	updateValueWithBiasTitle(&paramValue.Volt8, adcValueFiltr.Volt8, 
		coreCPUsett.calibrAdcValueBias.Volt8, coreCPUsett.calibrAdcValueTilt.Volt8,  flagUnsigned);

	coreFlags.adcConvertFinal = flagDisable;	// Сброс флага
}


