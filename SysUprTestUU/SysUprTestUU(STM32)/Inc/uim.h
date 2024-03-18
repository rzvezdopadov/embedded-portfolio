#ifndef __UIM_H
#define __UIM_H

#include "main.h"

typedef struct {	// Флаги состояний
	uint32_t flagDurationUpdate;
	uint32_t pulseFreequencyTemp;		// Временная частота(для счетчика) УИМ
	uint32_t pulseFreequency;				// Финальная частота УИМ
	uint32_t pulseDurationTemp;			// Длительность импульса УИМ
	uint32_t pulseDurationX;				// Длительность импульса УИМ умноженная на n(используется при фильтрации)
	uint32_t pulseDuration;					// Длительность импульса УИМ
	uint32_t pulseDutyCyckle;				// Скважность импульса УИМ
	uint32_t pulsePeriod;						// Период импульса УИМ
	uint32_t pulseUpTimeValue;			// Регистр наличия импульсов УИМ(0 - отсутствуют)
} t_UIM;

void uim_init(void);
void calcDurationUIM1(void);
void updateUIM1Freequency(void);
t_UIM *getUIM1(void);
void calcDurationUIM2(void);
void updateUIM2Freequency(void);
t_UIM *getUIM2(void);


#endif 
