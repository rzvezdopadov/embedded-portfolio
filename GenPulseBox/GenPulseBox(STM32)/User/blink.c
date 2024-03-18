#include "leds.h"

#define blink_time 50;
uint32_t blink_programm = 0;
uint32_t blink_phase = 0;
uint32_t blink_delay = blink_time;

void blink_programm0(void) {
	switch (blink_phase) {
		case 0:	led_off(); break;
		case 1:	led_ch11_r_change; break;
		case 2:	led_ch21_r_change; break;
		case 3:	led_ch12_r_change; break;
		case 4:	led_ch22_r_change; break;
		case 5:	led_pwr_r_change; break;
		case 6:	led_ch11_r_change; break;
		case 7:	led_ch21_r_change; break;
		case 8:	led_ch12_r_change; break;
		case 9:	led_ch22_r_change; break;
		case 10:	led_pwr_r_change; break;
		case 11:	led_ch11_g_change; break;
		case 12:	led_ch21_g_change; break;
		case 13:	led_ch12_g_change; break;
		case 14:	led_ch22_g_change; break;
		case 15:	led_pwr_g_change; break;
		case 16:	led_ch11_g_change; break;
		case 17:	led_ch21_g_change; break;
		case 18:	led_ch12_g_change; break;
		case 19:	led_ch22_g_change; break;
		case 20:	led_pwr_g_change; break;
		case 21:	led_ch11_b_change; break;
		case 22:	led_ch21_b_change; break;
		case 23:	led_ch12_b_change; break;
		case 24:	led_ch22_b_change; break;
		case 25:	led_pwr_b_change; break;
		case 26:	led_ch11_b_change; break;
		case 27:	led_ch21_b_change; break;
		case 28:	led_ch12_b_change; break;
		case 29:	led_ch22_b_change; break;
		case 30:	led_pwr_b_change; break;
	}
	
	if (blink_phase++ > 29) blink_phase = 0;  
}

void blink_programm1(void) {
	switch (blink_phase) {
		case 0:	led_off(); break;
		case 1:	led_ch11_r_change; break;
		case 2:	led_ch21_g_change; break;
		case 3:	led_ch12_b_change; break;
		case 4:	led_ch22_r_change; break;
		case 5:	led_pwr_g_change; break;
		case 6:	led_ch11_b_change; break;
		case 7:	led_ch21_r_change; break;
		case 8:	led_ch12_g_change; break;
		case 9:	led_ch22_b_change; break;
		case 10:	led_pwr_r_change; break;
		case 11:	led_ch11_g_change; break;
		case 12:	led_ch21_b_change; break;
		case 13:	led_ch12_r_change; break;
		case 14:	led_ch22_g_change; break;
		case 15:	led_pwr_b_change; break;
		case 16:	led_ch11_r_change; break;
		case 17:	led_ch21_g_change; break;
		case 18:	led_ch12_b_change; break;
		case 19:	led_ch22_r_change; break;
		case 20:	led_pwr_g_change; break;
		case 21:	led_ch11_b_change; break;
		case 22:	led_ch21_r_change; break;
		case 23:	led_ch12_g_change; break;
		case 24:	led_ch22_b_change; break;
		case 25:	led_pwr_r_change; break;
		case 26:	led_ch11_g_change; break;
		case 27:	led_ch21_b_change; break;
		case 28:	led_ch12_r_change; break;
		case 29:	led_ch22_g_change; break;
		case 30:	led_pwr_b_change; break;
	}
	
	if (blink_phase++ > 30) blink_phase = 0; 
}

void blink_programm2(void) {
	switch (blink_phase) {
		case 0:	led_off(); break;
		case 1:	led_ch11_r_change; break;
		case 2:	led_pwr_r_change; break;
		case 3:	led_ch21_r_change; break;
		case 4:	led_ch22_r_change; break;
		case 5:	led_ch12_r_change; break;
		case 6:	led_ch11_g_change; break;
		case 7:	led_pwr_g_change; break;
		case 8:	led_ch21_g_change; break;
		case 9:	led_ch22_g_change; break;
		case 10:	led_ch12_g_change; break;
		case 11:	led_ch11_b_change; break;
		case 12:	led_pwr_b_change; break;
		case 13:	led_ch21_b_change; break;
		case 14:	led_ch22_b_change; break;
		case 15:	led_ch12_b_change; break;
		case 16:	led_ch11_r_change; break;
		case 17:	led_pwr_r_change; break;
		case 18:	led_ch21_r_change; break;
		case 19:	led_ch22_r_change; break;
		case 20:	led_ch12_r_change; break;
		case 21:	led_ch11_g_change; break;
		case 22:	led_pwr_g_change; break;
		case 23:	led_ch21_g_change; break;
		case 24:	led_ch22_g_change; break;
		case 25:	led_ch12_g_change; break;
		case 26:	led_ch11_b_change; break;
		case 27:	led_pwr_b_change; break;
		case 28:	led_ch21_b_change; break;
		case 29:	led_ch22_b_change; break;
		case 30:	led_ch12_b_change; break;
	}
	
	if (blink_phase++ > 30) blink_phase = 0; 
}

//void blink_programm3(void) {
//	switch (blink_phase) {
//		case 0:	led_off(); break;
//		case 1:
//			led_off();
//			led_ch11_r_change; 
//			led_ch21_r_change; 
//			led_ch12_r_change; 
//			led_ch22_r_change;
//			led_pwr_r_change;		
//		break;
//		case 2:
//			led_off();
//			led_ch11_g_change; 
//			led_ch21_g_change; 
//			led_ch12_g_change; 
//			led_ch22_g_change;
//			led_pwr_g_change;
//			led_ch11_b_change; 
//			led_ch21_b_change; 
//			led_ch12_b_change; 
//			led_ch22_b_change;
//			led_pwr_b_change;
//		break;
//		case 3:
//			led_off();
//			led_ch11_g_change; 
//			led_ch21_g_change; 
//			led_ch12_g_change; 
//			led_ch22_g_change;
//			led_pwr_g_change;	
//		break;
//		case 4:
//			led_off();
//			led_ch11_r_change; 
//			led_ch21_r_change; 
//			led_ch12_r_change; 
//			led_ch22_r_change;
//			led_pwr_r_change;
//			led_ch11_b_change; 
//			led_ch21_b_change; 
//			led_ch12_b_change; 
//			led_ch22_b_change;
//			led_pwr_b_change;		
//		break;
//		case 5:
//			led_off();
//			led_ch11_b_change; 
//			led_ch21_b_change; 
//			led_ch12_b_change; 
//			led_ch22_b_change;
//			led_pwr_b_change;	
//		break;
//		case 6:
//			led_off();
//			led_ch11_r_change; 
//			led_ch21_r_change; 
//			led_ch12_r_change; 
//			led_ch22_r_change;
//			led_pwr_r_change;
//			led_ch11_g_change; 
//			led_ch21_g_change; 
//			led_ch12_g_change; 
//			led_ch22_g_change;
//			led_pwr_g_change;		
//		break;
//	}
//	
//	if (blink_phase++ > 6) blink_phase = 0; 
//}

void led_blink(void) { // Мигание светодиодов
	blink_delay--;
	if (blink_delay) return;
	blink_delay = blink_time;

	switch (coreCPUsett.sequences[Menu.NavProg.activeProg].period % 3) {
		case 0:	blink_programm0(); break;
		case 1:	blink_programm1(); break;
		case 2: blink_programm2(); break;
//		case 3: blink_programm3(); break;
		default: blink_programm0(); break;
	}	
}
