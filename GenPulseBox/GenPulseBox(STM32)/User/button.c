#include "button.h"
#include "leds.h"

void button_init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = 
		GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3 | 
			GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 |
				GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |
					GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOI, &GPIO_InitStructure);
}

uint8_t IsPushBtn(uint16_t GPIO_PIN) {
	if ((GPIOF->IDR & GPIO_PIN) & GPIO_PIN){
		return 0;
	}
	
	return 1;
}

uint8_t IsPopBtn(uint16_t GPIO_PIN) {
	if (IsPushBtn(GPIO_PIN)) {
		uint16_t contrCount = 0;
		
		while(1) {
			_delay_ms(20);
			contrCount++;
			
			if (IsPushBtn(GPIO_PIN)) { 
				contrCount = 0; 
			}
			if (contrCount > 10) { 
				return 1; 
			}
		}
	}
	
	return 0;
}

uint8_t IsPushBtnI(uint16_t GPIO_PIN) {
	if ((GPIOI->IDR & GPIO_PIN) & GPIO_PIN){
		return 0;
	}
	
	return 1;
}

uint8_t IsPopBtnI(uint16_t GPIO_PIN) {
	if (IsPushBtnI(GPIO_PIN)) {
		uint16_t contrCount = 0;
		
		while(1) {
			_delay_ms(20);
			contrCount++;
			
			if (IsPushBtnI(GPIO_PIN)) { 
				contrCount = 0; 
			}
			if (contrCount > 10) { 
				return 1; 
			}
		}
	}
	
	return 0;
}


