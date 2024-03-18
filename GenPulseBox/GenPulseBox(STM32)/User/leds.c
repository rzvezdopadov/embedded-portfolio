#include "leds.h"

// PI8 - Debug R, PH2 - Debug B, PH3 - Debug G
// PI0 - PWR R, PI1 - PWR B, PI2 - PWR G,
// PH4 - CH1(1) R, PH6 - CH1(1) B, PH5 - CH1(1) G,
// PH10 - CH1(2) R, PH11 - CH1(2) B, PH12 - CH1(2) G,
// PH7 - CH2(1) R, PH8 - CH2(1) B, PH9 - CH2(1) G,
// PH13 - CH2(2) R, PH15 - CH2(2) B, PH14 - CH2(2) G,

void leds_init(void) { // Инициализация светодиодов
	GPIO_InitTypeDef GPIO_InitStructure; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | 
																	GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | 
																		GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
																			GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | 
																				GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOH, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_8;
	GPIO_Init(GPIOI, &GPIO_InitStructure);
	
	led_off();
} 

void led_off(void) {
	led_debug_r_off;
	led_debug_g_off;
	led_debug_b_off;
	led_pwr_r_off;
	led_pwr_g_off;
	led_pwr_b_off;
	led_ch11_r_off;
	led_ch11_g_off;
	led_ch11_b_off;
	led_ch21_r_off;
	led_ch21_g_off;
	led_ch21_b_off;
	led_ch12_r_off;
	led_ch12_g_off;
	led_ch12_b_off;
	led_ch22_r_off;
	led_ch22_g_off;
	led_ch22_b_off;
}



void led_control(void) {
	if (!strcmp(&coreCPUsett.sequences[Menu.NavProg.activeProg].name[1], "elka")) {
		led_blink();
		return;
	}
	
	led_pwr_r_change;
	led_pwr_g_on;
	led_pwr_b_on;
	
	if (coreFlags.CH1Enable1 == flagEnable) {
		led_ch11_r_off;
		if (seqTimer.CH1.polarity1) {
			led_ch11_g_off;
			led_ch11_b_on;
		} else {
			led_ch11_b_off;
			led_ch11_g_on;
		}
	} else {
		led_ch11_r_on;
		led_ch11_g_off;
		led_ch11_b_off;
	}
	
	if (coreFlags.CH2Enable1 == flagEnable) {
		led_ch21_r_off;
		if (seqTimer.CH2.polarity1) {
			led_ch21_g_off;
			led_ch21_b_on;
		} else {
			led_ch21_b_off;
			led_ch21_g_on;
		}
	} else {
		led_ch21_r_on;
		led_ch21_g_off;
		led_ch21_b_off;
	}
	
	if (coreFlags.CH1Enable2 == flagEnable) {
		led_ch12_r_off;
		if (seqTimer.CH1.polarity2) {
			led_ch12_g_off;
			led_ch12_b_on;
		} else {
			led_ch12_b_off;
			led_ch12_g_on;
		}
	} else {
		led_ch12_r_on;
		led_ch12_g_off;
		led_ch12_b_off;
	}
	
	if (coreFlags.CH2Enable2 == flagEnable) {
		led_ch22_r_off;
		if (seqTimer.CH2.polarity2) {
			led_ch22_g_off;
			led_ch22_b_on;
		} else {
			led_ch22_b_off;
			led_ch22_g_on;
		}
	} else {
		led_ch22_r_on;
		led_ch22_g_off;
		led_ch22_b_off;
	}
}


#define led_blink_wait 30

void led_blink_on_device(void) {
	for (uint16_t i=0;i<2;i++) {
		led_ch11_r_change;
		_delay_ms(led_blink_wait);
		led_ch21_r_change;
		_delay_ms(led_blink_wait);
		led_ch12_r_change;
		_delay_ms(led_blink_wait);
		led_ch22_r_change;
		_delay_ms(led_blink_wait);
		led_pwr_r_change;
		_delay_ms(led_blink_wait);
		led_ch11_r_change;
		_delay_ms(led_blink_wait);
		led_ch21_r_change;
		_delay_ms(led_blink_wait);
		led_ch12_r_change;
		_delay_ms(led_blink_wait);
		led_ch22_r_change;
		_delay_ms(led_blink_wait);
		led_pwr_r_change;
		_delay_ms(led_blink_wait);
		
		led_ch11_g_change;
		_delay_ms(led_blink_wait);
		led_ch21_g_change;
		_delay_ms(led_blink_wait);
		led_ch12_g_change;
		_delay_ms(led_blink_wait);
		led_ch22_g_change;
		_delay_ms(led_blink_wait);
		led_pwr_g_change;
		_delay_ms(led_blink_wait);
		led_ch11_g_change;
		_delay_ms(led_blink_wait);
		led_ch21_g_change;
		_delay_ms(led_blink_wait);
		led_ch12_g_change;
		_delay_ms(led_blink_wait);
		led_ch22_g_change;
		_delay_ms(led_blink_wait);
		led_pwr_g_change;
		_delay_ms(led_blink_wait);
		
		led_ch11_b_change;
		_delay_ms(led_blink_wait);
		led_ch21_b_change;
		_delay_ms(led_blink_wait);
		led_ch12_b_change;
		_delay_ms(led_blink_wait);
		led_ch22_b_change;
		_delay_ms(led_blink_wait);
		led_pwr_b_change;
		_delay_ms(led_blink_wait);
		led_ch11_b_change;
		_delay_ms(led_blink_wait);
		led_ch21_b_change;
		_delay_ms(led_blink_wait);
		led_ch12_b_change;
		_delay_ms(led_blink_wait);
		led_ch22_b_change;
		_delay_ms(led_blink_wait);
		led_pwr_b_change;
		_delay_ms(led_blink_wait);
	}
	
	led_off();
}



