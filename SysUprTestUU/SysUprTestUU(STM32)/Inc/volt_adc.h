#ifndef __VOLT_ADC_H
#define __VOLT_ADC_H

#include "main.h"

// VOLT1 - PF3(IN9),  VOLT2_ADC - PF4(IN14), 
// VOLT3 - PF5(IN15), VOLT4_ADC - PF6(IN4),
// VOLT5 - PF7(IN5),  VOLT6_ADC - PF8(IN6), 
// VOLT7 - PF9(IN7),  VOLT8_ADC - PF10(IN8),

void volt_adc_init(void);
void volt_adc_update(void);
void volt_adc_start(void);

#endif 
