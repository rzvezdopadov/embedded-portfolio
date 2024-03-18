#include "devices.h"

void devices_init(void) {
	printf("Devices Init Start...\n");
	printf("Devices Init Ok!\n");
}

uint32_t addPscArrHS(t_timer_short *timer, uint32_t duration) {
	timer->ARR = 1;
	if (duration == 0) {
		timer->PSC = 0;
		timer->ARR = 1;
	} else if (duration < 3500) {
		timer->PSC = 0;
		timer->ARR = 168 * duration / 10;
	} else if (duration < 35000) {
		timer->PSC = 9;
		timer->ARR = 168 * duration / 100;
	} else if (duration < 350000) {
		timer->PSC = 99;
		timer->ARR = 168 * duration / 1000; 
	} else if (duration < 3500000) {
		timer->PSC = 999 ;
		timer->ARR = 168 * duration / 10000; 
	} else {
		timer->PSC = 9999 ;
		timer->ARR = 168 * duration / 100000; 
	}
	
	return timer->PSC;
}

uint32_t addPscArrLS(t_timer_short *timer, uint32_t duration) {
	if (duration < 700) {
		timer->PSC = 0;
		timer->ARR = 84 * duration;
	} else if (duration < 7000) {
		timer->PSC = 0;
		timer->ARR = 84 * duration / 10;
	} else if (duration < 70000) {
		timer->PSC = 9;
		timer->ARR = 84 * duration / 100;
	} else if (duration < 700000) {
		timer->PSC = 99;
		timer->ARR = 84 * duration / 1000; 
	} else if (duration < 7000000) {
		timer->PSC = 999 ;
		timer->ARR = 84 * duration / 10000; 
	} else {
		timer->PSC = 9999 ;
		timer->ARR = 84 * duration / 100000; 
	}
	
	return timer->PSC;
}

void CalcParamCH(t_ch_timer *timer_ch, t_channel *seq_ch) {
	uint32_t allCountPulse = 0;
	
	for (uint16_t i=0; i<seq_ch->count; i++) {
		for (uint16_t j=0; j<seq_ch->pulses[i].count; j++) {
			timer_ch->pulses[allCountPulse].Period.ARR = (seq_ch->pulses[i].down * 84) / 10 ;
			timer_ch->pulses[allCountPulse].CCR1 = (seq_ch->pulses[i].up1 * 84) / 10;
			timer_ch->pulses[allCountPulse].CCR2 = (seq_ch->pulses[i].up2 * 84) / 10;
			timer_ch->pulses[allCountPulse].RCR	= 0;
			
			allCountPulse++;
		}
	}
	
	timer_ch->count = allCountPulse;
	
	for (int16_t i=0;i<2;i++) {
		timer_ch->pulses[allCountPulse+i].Period.PSC = 0;
		timer_ch->pulses[allCountPulse+i].Period.ARR = 1;
		timer_ch->pulses[allCountPulse+i].CCR1 = 0;
		timer_ch->pulses[allCountPulse+i].CCR2 = 0;
		timer_ch->pulses[allCountPulse+i].RCR	= 0;
	}
	
	timer_ch->polarity1 = seq_ch->polarity1;
	timer_ch->polarity2 = seq_ch->polarity2;
	
	addPscArrHS(&timer_ch->bias, seq_ch->bias);
	
//	uint32_t biasCH = (168 * seq_ch->bias) / 10;
//	if (!(biasCH > 0)) biasCH = 1;
//	timer_ch->bias.ARR = biasCH;
}

void Timers_Update(t_sequenced *sec) {	
// Настройка 1 канала
	CalcParamCH(&seqTimer.CH1, &sec->CH1);

// Настройка 2 канала	
	CalcParamCH(&seqTimer.CH2, &sec->CH2);
	
// Период	
	addPscArrLS(&seqTimer.period, sec->period);
	
	timer_init();
}
