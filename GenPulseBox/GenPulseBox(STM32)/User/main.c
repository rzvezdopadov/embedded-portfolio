#include "stm32f4xx.h"
#include "LCD/LCD.h"
#include "TouchPanel/TouchPanel.h"
#include "delay.h"
#include <stdio.h>
#include "menu.h"
#include "actionMenu.h"
#include "devices.h"
#include "leds.h"
#include "update.h"

int main(void) {
	rcc_init();
	leds_init();
	debug_init();
	setting_init();
	button_init();
	update_init();
	TP_Init();
	LCD_Initializtion();
	LCD_Clear(clBlack);
	GUI_Text(80, 80, "NPC RadarService", clWhite, clBlack);
	GUI_Text(85, 100, "Pulse Generator", clWhite, clBlack);
	char Phrase[200];
	sprintf(Phrase, "FW v.%d", version_fw);
	GUI_Text(90, 120, Phrase, clWhite, clBlack);
	GUI_Text(100, 140, "Loading...", clWhite, clBlack);
	Menu_Init();
	led_blink_on_device();
	uint16_t coordTest0000 = 0x0000;
	uint16_t coordTestFFFF = 0xFFFF;
	
	for (uint16_t i = 0; i < 3; i++) {
		coordTest0000 |= coreCPUsett.screenSample[i].x | coreCPUsett.screenSample[i].y;
		coordTestFFFF &= coreCPUsett.screenSample[i].x & coreCPUsett.screenSample[i].y;
	}
	
	LCD_Clear(clBlack);
		
	if ((coordTest0000 == 0) || (coordTestFFFF == 0xFFFF)) {
		TouchPanel_Calibrate(coreCPUsett.screenSample);
		printf("x0: %d; y0:%d;\nx1:%d; y1:%d;\nx2:%d; y2:%d;\n",
			coreCPUsett.screenSample[0].x, coreCPUsett.screenSample[0].y,
			coreCPUsett.screenSample[1].x, coreCPUsett.screenSample[1].y,
			coreCPUsett.screenSample[2].x, coreCPUsett.screenSample[2].y
		);
		
		coreFlags.settSaveEnable = flagEnable;
	}
	
	TouchPanel_SettCalibrate(coreCPUsett.screenSample);
	getDisplayPoint(&display, Read_Ads7846(), &matrix);
	BaseXY.x = display.x;
	BaseXY.y = display.y;
	
	
	coreFlags.CH1Enable1 = flagDisable;
	coreFlags.CH1Enable2 = flagDisable;
	coreFlags.CH2Enable1 = flagDisable;
	coreFlags.CH2Enable2 = flagDisable;
//	
//	for (uint32_t i=0; i<0xFFFF; i += 0x0713) {	
//		for(uint16_t x=0; x<20; x++) {
//			for(uint16_t y=0; y<20; y++) {
//				LCD_DrawLine(50+x,50+y,x*x,y*y, clGreen);
//				_delay_ms(10);
//			}
//		}
//	}
	
	LCD_Clear(clBlack);
	
	MenuRedraw();


	Timers_Update(&coreCPUsett.sequences[0]);
	
//	Coordinate *coord;
//	uint16_t coordX;
//	uint16_t coordY;
//	
//	while (1) {
//		coord = Read_Ads7846();
//		
//		#define Filtr 300
//		for (uint16_t i = 0; i<Filtr; i++) {
//			coordX = ((coordX * Filtr) + (4095-Read_X()))/(Filtr + 1);
//			coordY = ((coordY * Filtr) + Read_Y())/(Filtr + 1);
//		}
//			
//		printf("x: %d; y: %d;\n", coordX, coordY);
//		_delay_ms(500);
//	}
//	
//	for (uint16_t i=0;i<30;i++) {
//		printf("sequenced %d: \n", i);
//		printfArray((uint8_t *)&coreCPUsett.sequences[i], sizeof(t_sequenced));
//	}

	
	printf("Main cykle start Ok!\n");
	while (1) {		
		getDisplayPoint(&display, Read_Ads7846(), &matrix );
	  TP_DrawPoint(display.x,display.y, Menu.paintColor);
////		printf("x: %d; y: %d; page: %d \n", display.x, display.y, Menu.Prog.page);
////		printf("Base x: %d; y: %d; \n", BaseXY.x, BaseXY.y);
		ActionTouch();
		setting_save();
				
//		for(uint16_t i=0; i<20; i++) {
//			printf("%d ", seqTimer.CH2.pulses[i].CCR1);
//		}
//		printf("\n");
//		
//		for(uint16_t i=0; i<20; i++) {
//			printf("%d ", seqTimer.CH2.pulses[i].CCR2);
//		}
//		
//		printf("\n");
//		_delay_ms(500);
		parseQueryUpdate();
				
		led_control();
			
	}
}
