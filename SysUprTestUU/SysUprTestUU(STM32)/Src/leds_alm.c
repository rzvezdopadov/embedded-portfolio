#include "leds_alm.h"

// STCP - PI2, SHCP - PI1, DS - PI0 
typedef struct {
	uint8_t In[25];
	uint8_t Out[25];
} t_almLeds;

t_almLeds Leds;

void ledsalm_init(void) {
	GPIOI->MODER	|= GPIO_MODER_MODE2_0
									| GPIO_MODER_MODE1_0
										| GPIO_MODER_MODE0_0
	;
	
	GPIOI->OSPEEDR |= GPIO_OSPEEDR_OSPEED2_Msk
										| GPIO_OSPEEDR_OSPEED1_Msk
											| GPIO_OSPEEDR_OSPEED0_Msk
	;
	
	
	for (uint8_t i=0; i<25; i++) {
		Leds.In[i] 	= 0;
		Leds.Out[i] = 0;
	}
	
	ledalm_all_off();
	ledsalm_send();
}

void ledalm_on(uint8_t ledpos, enum RGB color) {
	if (color & RGB_Red) 	 Leds.In[ledpos-1] |= RGB_Red;
	if (color & RGB_Green) Leds.In[ledpos-1] |= RGB_Green;
	if (color & RGB_Blue)	 Leds.In[ledpos-1] |= RGB_Blue;
}

void ledalm_off(uint8_t ledpos, enum RGB color) {
	if (color & RGB_Red) 	 Leds.In[ledpos-1] &= ~RGB_Red;
	if (color & RGB_Green) Leds.In[ledpos-1] &= ~RGB_Green;
	if (color & RGB_Blue)  Leds.In[ledpos-1] &= ~RGB_Blue;
}

void ledalm_all_off(void) {
	for (uint8_t i=0; i<25; i++) {
		Leds.In[i] 	= 0;
		Leds.Out[i] = 0;
	}
}

void ledalm_transposition(void) {
	for (uint8_t i=0; i<25; i++) {
		Leds.Out[i] = Leds.In[i];
	}
	
	Leds.Out[8] = 0;
	if (Leds.In[8] & RGB_Red) 	Leds.Out[8] |= RGB_Blue;
	if (Leds.In[8] & RGB_Green) Leds.Out[8] |= RGB_Red;
	if (Leds.In[8] & RGB_Blue) 	Leds.Out[8] |= RGB_Green;
	
	Leds.Out[9] = 0;
	if (Leds.In[9] & RGB_Red) 	Leds.Out[9] |= RGB_Blue;
	if (Leds.In[9] & RGB_Green) Leds.Out[9] |= RGB_Green;
	if (Leds.In[9] & RGB_Blue) 	Leds.Out[9] |= RGB_Red;

	Leds.Out[10] = 0;
	if (Leds.In[10] & RGB_Red) 	 Leds.Out[10] |= RGB_Red;
	if (Leds.In[10] & RGB_Green) Leds.Out[10] |= RGB_Blue;
	if (Leds.In[10] & RGB_Blue)	 Leds.Out[10] |= RGB_Green;
	
	Leds.Out[15] = 0;
	if (Leds.In[15] & RGB_Red) 	 Leds.Out[15] |= RGB_Blue;
	if (Leds.In[15] & RGB_Green) Leds.Out[15] |= RGB_Green;
	if (Leds.In[15] & RGB_Blue)  Leds.Out[15] |= RGB_Red;
	
	Leds.Out[19] = 0;
	if (Leds.In[19] & RGB_Red) 	 Leds.Out[19] |= RGB_Blue;
	if (Leds.In[19] & RGB_Green) Leds.Out[19] |= RGB_Green;
	if (Leds.In[19] & RGB_Blue)  Leds.Out[19] |= RGB_Red;
	
	Leds.Out[20] = 0;
	if (Leds.In[20] & RGB_Red) 	 Leds.Out[20] |= RGB_Blue;
	if (Leds.In[20] & RGB_Green) Leds.Out[20] |= RGB_Green;
	if (Leds.In[20] & RGB_Blue)  Leds.Out[20] |= RGB_Red;
}

#define ledsalm_tick 1

void ledsalm_send(void) {
	ledalm_transposition();
	
	ledsalm_stcp_enable;
	_delay_tick(ledsalm_tick);
	
	for (uint8_t i=0; i<25; i++) {
		for (uint8_t j=0; j<3; j++) {
			if (Leds.Out[24-i] & (1<<j)) {	
				ledsalm_ds_enable;
			} else {
				ledsalm_ds_disable;
			}
			
			ledsalm_shcp_enable;
			_delay_tick(ledsalm_tick);
			
			ledsalm_shcp_disable;
			_delay_tick(ledsalm_tick);
		}
	}
	
	ledsalm_stcp_disable;
}
