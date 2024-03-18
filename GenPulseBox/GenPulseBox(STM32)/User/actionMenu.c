#include "actionMenu.h"
#include "button.h"

Coordinate BaseXY;

void Menu_Timer_Update(void) {
	Timers_Update(&coreCPUsett.sequences[Menu.NavProg.activeProg]);
}

void MenuParamInc(uint32_t *Param, uint32_t maxParam) {
	uint16_t page = *Param;
	
	page++;
	
	if (page > maxParam - 1) {
		page = 0;
	}
	*Param = page;
	
	MenuRedraw();	
}

void MenuParamDec(uint32_t *Param, uint32_t maxParam) {
	uint16_t page = *Param;
	
	page--;
	
	if (page > maxParam) {
		page = maxParam - 1;
	}
	
	*Param = page;
	
	MenuRedraw();	
}

void MenuProgPageUp(void) {
	uint16_t page = Menu.NavProg.page;
	
	page--;
	
	if (page > (Menu.NavProg.maxCountProgs - 1) / MaxVisibleNavProg) {
		page = (Menu.NavProg.maxCountProgs - 1) / MaxVisibleNavProg;
	}
	
	Menu.NavProg.page = page;
	
	MenuRedraw();
}

void MenuProgPageDown(void) {
	uint16_t page = Menu.NavProg.page;
	
	page++;
	
	if (page > (Menu.NavProg.maxCountProgs - 1) / MaxVisibleNavProg) {
		page = 0;
	}
	Menu.NavProg.page = page;
	
	MenuRedraw();
}

void MenuPageLeft(void) {
	uint16_t page = Menu.NavPage.page;
	
	page--;
	
	if (page > MENU_PAGEMAX - 1) {
		page = MENU_PAGEMAX - 1;
	}
	
	Menu.NavPage.page = page;
	MenuRedraw();	
}

void MenuPageRight(void) {
	uint16_t page = Menu.NavPage.page;
	
	page++;
	
	if (page > (MENU_PAGEMAX - 1)) {
		page = MENU_PAGE1;
	}
	Menu.NavPage.page = page;
	
	MenuRedraw();	
}

void MenuSwitchByte(uint32_t *SwitchByte) {
	*SwitchByte = *SwitchByte ? flagDisable : flagEnable;
	
	Menu_Timer_Update();
	MenuRedraw();
}

uint8_t IsPushCoordinate(uint16_t Left, uint16_t Top, uint16_t Width, uint16_t Height) {
	getDisplayPoint(&display, Read_Ads7846(), &matrix );
	
	uint16_t x = display.x;
	uint16_t y = display.y;
	
	return ((x >= Left) && (x <= Left + Width) && (y >= Top) && (y <= Top + Height));
}

uint8_t IsPopCoordinate(uint16_t Left, uint16_t Top, uint16_t Width, uint16_t Height) {
	if (IsPushCoordinate(Left, Top, Width, Height)) {
		uint16_t contrCount = 0;
		
		while(1) {
			_delay_ms(20);
			contrCount++;
			
			if (IsPushCoordinate(Left, Top, Width, Height)) { 
				contrCount = 0; 
			}
			if (contrCount > 10) { 
				return 1; 
			}
		}
	}
	
	return 0;
}

void MenuProgPageProg(uint8_t index) {
	uint16_t prog = Menu.NavProg.page * 6 + index;
	
	if (prog < Menu.NavProg.maxCountProgs) {
		Menu.NavProg.activeProg = prog;
	}
	
	Menu.NavProg.activePulseCH1 = 0;
	Menu.NavProg.activePulseCH2 = 0;	
	
	Menu_Timer_Update();
	
	MenuRedraw();
}

void MenuAddNewPulse(t_channel *ch, uint32_t *activePulseCH) {
	for (uint16_t i = ch->count; i > *activePulseCH; i--) {
		ch->pulses[i].up1	= ch->pulses[i-1].up1;
		ch->pulses[i].up2	= ch->pulses[i-1].up2;
		ch->pulses[i].down	= ch->pulses[i-1].down;
		ch->pulses[i].count	= ch->pulses[i-1].count;
	}
		
	ch->count += 1;
	*activePulseCH += 1;
	
	Menu_Timer_Update();
}

void MenuDelCurPulse(t_channel *ch, uint32_t *activePulseCH) {
	if (ch->count < 2) return;
	
	for (uint16_t i = *activePulseCH; i < ch->count; i++) {
		ch->pulses[i].up1	= ch->pulses[i+1].up1;
		ch->pulses[i].up2	= ch->pulses[i+1].up2;
		ch->pulses[i].down	= ch->pulses[i+1].down;
		ch->pulses[i].count	= ch->pulses[i+1].count;
	}
		
	ch->count -= 1;
	if (*activePulseCH > 0) { 
		*activePulseCH -= 1;
	} else {
		*activePulseCH = 0;
	} 

	Menu_Timer_Update();
}

void ActionBtn(void) {
	if (IsPopBtn(Btn_Page_Up)) {
		MenuProgPageUp();
	} else if (IsPopBtn(Btn_Page_Down)) {
		MenuProgPageDown();
	} else if (IsPopBtn(Btn_Prog1)) {
		MenuProgPageProg(0);
	} else if (IsPopBtn(Btn_Prog2)) {
		MenuProgPageProg(1);
	} else if (IsPopBtn(Btn_Prog3)) {
		MenuProgPageProg(2);
	} else if (IsPopBtn(Btn_Prog4)) {
		MenuProgPageProg(3);
	} else if (IsPopBtn(Btn_Prog5)) {
		MenuProgPageProg(4);
	} else if (IsPopBtn(Btn_Prog6)) {
		MenuProgPageProg(5);
	} else if (IsPopBtn(Btn_Ch1_1_Polar)) {
		MenuSwitchByte(&coreCPUsett.sequences[Menu.NavProg.activeProg].CH1.polarity1);
	} else if (IsPopBtn(Btn_Ch2_1_Polar)) {
		MenuSwitchByte(&coreCPUsett.sequences[Menu.NavProg.activeProg].CH2.polarity1);
	} else if (IsPopBtn(Btn_Ch1_2_Polar)) {
		MenuSwitchByte(&coreCPUsett.sequences[Menu.NavProg.activeProg].CH1.polarity2);
	}  else if (IsPopBtn(Btn_Ch2_2_Polar)) {
		MenuSwitchByte(&coreCPUsett.sequences[Menu.NavProg.activeProg].CH2.polarity2);
	} else if (IsPopBtn(Btn_Ch1_1_On)) {
		MenuSwitchByte(&coreFlags.CH1Enable1);
	} else if (IsPopBtn(Btn_Ch2_1_On)) {
		MenuSwitchByte(&coreFlags.CH2Enable1);
	} else if (IsPopBtn(Btn_Ch1_2_On)) {
		MenuSwitchByte(&coreFlags.CH1Enable2);
	} else if (IsPopBtn(Btn_Ch2_2_On)) {
		MenuSwitchByte(&coreFlags.CH2Enable2);
	} else if (IsPopBtnI(Btn_Calibr)) {
		TouchPanel_Calibrate(coreCPUsett.screenSample);
		coreFlags.settSaveEnable = flagEnable;
		MenuRedraw();
	}
}

void ActionTouchPage1(void) {
	ActionBtn();
	
	if (
		IsPopCoordinate(btnNavLeft + 5, 0, btnNavWidht, btnNavHeight)
	) { // Btn Page Up
		MenuProgPageUp();
	}

	for (uint16_t i=0; i<6; i++) {
		if (IsPopCoordinate(btnNavLeft, btnNavTop + 2 + i * (btnNavHeight + btnNavMargin), btnNavWidht, btnNavHeight)) { // Btn Navi 1
			MenuProgPageProg(i);
		}
	}
	
	if (IsPopCoordinate(btnNavLeft + 5, 215, btnNavWidht, btnNavHeight)
	) { // Btn Page Down
		MenuProgPageDown();
	}
	
	if (IsPopCoordinate(0 + 51, 21, 60, 20)) { // Btn Durat CH1
		if (Menu.NavPage.page == MENU_PAGE1) {
			Menu.Modal.Value = &coreCPUsett.sequences[Menu.NavProg.activeProg].CH1.pulses[Menu.NavProg.activePulseCH1].up1;
		} else {
			Menu.Modal.Value = &coreCPUsett.sequences[Menu.NavProg.activeProg].CH1.pulses[Menu.NavProg.activePulseCH1].up2;
		}
		
		Menu.Modal.Type = TYPE_TIME;
		Menu.Modal.minValue = 0;
		Menu.Modal.maxValue = 10000000;
		Menu.Modal.Enable = flagEnable;
		MenuRedraw();
		_delay_ms(2000);
	}
	
	if (IsPopCoordinate(0 + 51, 21 + 21 + 0, 60, 20)) { // Btn Durat CH2
		if (Menu.NavPage.page == MENU_PAGE1) {
			Menu.Modal.Value = &coreCPUsett.sequences[Menu.NavProg.activeProg].CH2.pulses[Menu.NavProg.activePulseCH2].up1;
		} else {
			Menu.Modal.Value = &coreCPUsett.sequences[Menu.NavProg.activeProg].CH2.pulses[Menu.NavProg.activePulseCH2].up2;
		}
		
		Menu.Modal.Type = TYPE_TIME;
		Menu.Modal.minValue = 0;
		Menu.Modal.maxValue = 10000000;
		Menu.Modal.Enable = flagEnable;
		MenuRedraw();
		_delay_ms(2000);
	}
	
	if (IsPopCoordinate(0 + 51 + 61, 21, 60, 20)) { // Btn Period CH1
		Menu.Modal.Value = &coreCPUsett.sequences[Menu.NavProg.activeProg].CH1.pulses[Menu.NavProg.activePulseCH1].down;
		Menu.Modal.Type = TYPE_TIME;
		Menu.Modal.minValue = 0;
		Menu.Modal.maxValue = 10000000;
		Menu.Modal.Enable = flagEnable;
		MenuRedraw();
		_delay_ms(2000);
	}
	
	if (IsPopCoordinate(0 + 51 + 61, 21 + 21 + 0, 60, 20)) { // Btn Period CH2
		Menu.Modal.Value = &coreCPUsett.sequences[Menu.NavProg.activeProg].CH2.pulses[Menu.NavProg.activePulseCH2].down;
		Menu.Modal.Type = TYPE_TIME;
		Menu.Modal.minValue = 0;
		Menu.Modal.maxValue = 10000000;
		Menu.Modal.Enable = flagEnable;
		MenuRedraw();
		_delay_ms(2000);
	}
	
	if (IsPopCoordinate(0 + 51 + 61 + 61, 21, 60, 20)) { // Btn Amount CH1
		Menu.Modal.Value = &coreCPUsett.sequences[Menu.NavProg.activeProg].CH1.pulses[Menu.NavProg.activePulseCH1].count;
		Menu.Modal.Type = TYPE_COUNT;
		Menu.Modal.minValue = 0;
		Menu.Modal.maxValue = 10000000;
		Menu.Modal.Enable = flagEnable;
		MenuRedraw();
		_delay_ms(2000);
	}
	
	if (IsPopCoordinate(0 + 51 + 61 + 61, 21 + 21 + 0, 60, 20)) { // Btn Amount CH2
		Menu.Modal.Value = &coreCPUsett.sequences[Menu.NavProg.activeProg].CH2.pulses[Menu.NavProg.activePulseCH2].count;
		Menu.Modal.Type = TYPE_COUNT;
		Menu.Modal.minValue = 0;
		Menu.Modal.maxValue = 10000000;
		Menu.Modal.Enable = flagEnable;
		MenuRedraw();
		_delay_ms(2000);
	}

	if (IsPopCoordinate(0 + 51, TableAPOOTop + 21, 60, 20)) { // Btn Bias CH1
		Menu.Modal.Value = &coreCPUsett.sequences[Menu.NavProg.activeProg].CH1.bias;
		Menu.Modal.Type = TYPE_TIME;
		Menu.Modal.minValue = 0;
		Menu.Modal.maxValue = 10000000;
		Menu.Modal.Enable = flagEnable;
		MenuRedraw();
		_delay_ms(2000);
	}
	
	if (IsPopCoordinate(0 + 51, TableAPOOTop + 21 + 21, 60, 20)) { // Btn Bias CH2
		Menu.Modal.Value = &coreCPUsett.sequences[Menu.NavProg.activeProg].CH2.bias;
		Menu.Modal.Type = TYPE_TIME;
		Menu.Modal.minValue = 0;
		Menu.Modal.maxValue = 10000000;
		Menu.Modal.Enable = flagEnable;
		MenuRedraw();
		_delay_ms(2000);
	}
		
	if (IsPopCoordinate(91, 190, 60, btnNavPageHeight)) { // Btn Period All
		Menu.Modal.Value = &coreCPUsett.sequences[Menu.NavProg.activeProg].period;
		Menu.Modal.Type = TYPE_TIME;
		Menu.Modal.minValue = 1;
		Menu.Modal.maxValue = 10000000;
		Menu.Modal.Enable = flagEnable;
		MenuRedraw();
		_delay_ms(2000);
	}
	
	if (IsPopCoordinate(0 + 51 + 61, TableAPOOTop + 21, 60, 20)) { // Btn Polarity CH1
		if (Menu.NavPage.page == MENU_PAGE1) {
			MenuSwitchByte(&coreCPUsett.sequences[Menu.NavProg.activeProg].CH1.polarity1);
		} else {
			MenuSwitchByte(&coreCPUsett.sequences[Menu.NavProg.activeProg].CH1.polarity2);
		}
	}
	
	if (IsPopCoordinate(0 + 51 + 61, TableAPOOTop + 21 + 21, 60, 20)) { // Btn Polarity CH2
		if (Menu.NavPage.page == MENU_PAGE1) {
			MenuSwitchByte(&coreCPUsett.sequences[Menu.NavProg.activeProg].CH2.polarity1);
		} else {
			MenuSwitchByte(&coreCPUsett.sequences[Menu.NavProg.activeProg].CH2.polarity2);
		}
	}
	
	if (IsPopCoordinate(0 + 51 + 61 + 61, TableAPOOTop + 21, 60, 20)) { // Btn On/Off CH1
		if (Menu.NavPage.page == MENU_PAGE1) {
			MenuSwitchByte(&coreFlags.CH1Enable1);
		} else {
			MenuSwitchByte(&coreFlags.CH1Enable2);
		}
	}
	
	if (IsPopCoordinate(0 + 51 + 61 + 61, TableAPOOTop + 21 + 21, 60, 20)) { // Btn On/Off CH2
		if (Menu.NavPage.page == MENU_PAGE1) {
			MenuSwitchByte(&coreFlags.CH2Enable1);
		} else {
			MenuSwitchByte(&coreFlags.CH2Enable2);
		}
	}
	
	if (IsPopCoordinate(btnNavPageLeft + 51, TablePulseCheckTop + 0, 20, 20)) { // Btn "<" CH1
		MenuParamDec(&Menu.NavProg.activePulseCH1, coreCPUsett.sequences[Menu.NavProg.activeProg].CH1.count);
	}
	
	if (IsPopCoordinate(btnNavPageLeft + 51 + 20 + 100, TablePulseCheckTop, 20, btnNavPageHeight)) { // Btn ">" CH1
		MenuParamInc(&Menu.NavProg.activePulseCH1, coreCPUsett.sequences[Menu.NavProg.activeProg].CH1.count);
	}
	
	if (IsPopCoordinate(btnNavPageLeft + 51, TablePulseCheckTop + 21 + 0, 20, 20)) { // Btn "<" CH2
		MenuParamDec(&Menu.NavProg.activePulseCH2, coreCPUsett.sequences[Menu.NavProg.activeProg].CH2.count);
	}
	
	if (IsPopCoordinate(btnNavPageLeft + 51 + 20 + 100, TablePulseCheckTop + 21, 20, btnNavPageHeight)) { // Btn ">" CH2
		MenuParamInc(&Menu.NavProg.activePulseCH2, coreCPUsett.sequences[Menu.NavProg.activeProg].CH2.count);
	}
	
	if (IsPopCoordinate(btnNavPageLeft + 51 + 20 + 100 + 20 + 1, TablePulseCheckTop, 20, btnNavPageHeight)) { // Btn "A" CH1
		MenuAddNewPulse(&coreCPUsett.sequences[Menu.NavProg.activeProg].CH1, &Menu.NavProg.activePulseCH1);
		MenuRedraw();
	}
	
	if (IsPopCoordinate(btnNavPageLeft + 51 + 20 + 100 + 20 + 21 + 1, TablePulseCheckTop, 20, btnNavPageHeight)) { // Btn "D" CH1
		MenuDelCurPulse(&coreCPUsett.sequences[Menu.NavProg.activeProg].CH1, &Menu.NavProg.activePulseCH1);
		MenuRedraw();
	}
	
	if (IsPopCoordinate(btnNavPageLeft + 51 + 20 + 100 + 20 + 1, TablePulseCheckTop + 21, 20, btnNavPageHeight)) { // Btn "A" CH2
		MenuAddNewPulse(&coreCPUsett.sequences[Menu.NavProg.activeProg].CH2, &Menu.NavProg.activePulseCH2);
		MenuRedraw();
	}
	
	if (IsPopCoordinate(btnNavPageLeft + 51 + 20 + 100 + 20 + 21 + 1, TablePulseCheckTop + 21, 20, btnNavPageHeight)) { // Btn "D" CH2
		MenuDelCurPulse(&coreCPUsett.sequences[Menu.NavProg.activeProg].CH2, &Menu.NavProg.activePulseCH2);
		MenuRedraw();
	}
}

void ActionTouchPagePaint(void) {
	if (IsPopCoordinate(btnPaintPageColorLeft-40, btnNavPageTop, 40, btnNavPageHeight)) { //
		LCD_Clear(clBlack);
		MenuRedraw();
	}

	if (IsPopCoordinate(btnPaintPageColorLeft + 20 * 0, btnNavPageTop, 20, btnNavPageHeight)) { //
		Menu.paintColor = clRed; 
	} 
	
	if (IsPopCoordinate(btnPaintPageColorLeft + 20 * 1, btnNavPageTop, 20, btnNavPageHeight)) { //
		Menu.paintColor = clOrange; 
	} 
	
	if (IsPopCoordinate(btnPaintPageColorLeft + 20 * 2, btnNavPageTop, 20, btnNavPageHeight)) { //
		Menu.paintColor = clYellow; 
	} 
	
	if (IsPopCoordinate(btnPaintPageColorLeft + 20 * 3, btnNavPageTop, 20, btnNavPageHeight)) { //
		Menu.paintColor = clGreen; 
	} 
	
	if (IsPopCoordinate(btnPaintPageColorLeft + 20 * 4, btnNavPageTop, 20, btnNavPageHeight)) { //
		Menu.paintColor = clBlue; 
	} 
	
	if (IsPopCoordinate(btnPaintPageColorLeft + 20 * 5, btnNavPageTop, 20, btnNavPageHeight)) { //
		Menu.paintColor = clMagenta; 
	} 
	
	if (IsPopCoordinate(btnPaintPageColorLeft + 20 * 6, btnNavPageTop, 20, btnNavPageHeight)) { //
		Menu.paintColor = clCyan; 
	} 
	
	if (IsPopCoordinate(btnPaintPageColorLeft + 20 * 7, btnNavPageTop, 20, btnNavPageHeight)) { //
		Menu.paintColor = clWhite; 
	}
	
	if (IsPopCoordinate(btnPaintPageColorLeft + 20 * 8, btnNavPageTop, 20, btnNavPageHeight)) { //
		Menu.paintColor = clBlack; 
	}
}

void incValueModal(uint32_t incValue) {
	int64_t Value = *Menu.Modal.Value;
	
	Value += incValue;
	
	if (Value > Menu.Modal.maxValue) { Value = Menu.Modal.maxValue; }
	
	*Menu.Modal.Value = Value;
	
	PulseChangeDrawModalValue();
}

void decValueModal(uint32_t decValue) {
	int64_t Value = *Menu.Modal.Value;
	
	Value -= decValue;
	
	if (Value < Menu.Modal.minValue) { Value = Menu.Modal.minValue; }
	
	*Menu.Modal.Value = Value;
	
	PulseChangeDrawModalValue();
}

void ActionTouchModal(void) {
	if (IsPopCoordinate(260, 30, 30, 30)) {
		Menu.Modal.Enable = flagDisable;
		LCD_Clear(clBlack);
		MenuRedraw();
		Menu_Timer_Update();
	}
	
	if (IsPopCoordinate(btnIncDecModalLeft + 36 * 0, 119, 35, 30)) {
		incValueModal(1);
	}
	
	if (IsPopCoordinate(btnIncDecModalLeft + 36 * 0, 171, 35, 30)) {
		decValueModal(1);
	}
	
	if (IsPopCoordinate(btnIncDecModalLeft + 36 * 1, 119, 35, 30)) {
		incValueModal(10);
	}
	
	if (IsPopCoordinate(btnIncDecModalLeft + 36 * 1, 171, 35, 30)) {
		decValueModal(10);
	}
	
	if (IsPopCoordinate(btnIncDecModalLeft + 36 * 2, 119, 35, 30)) {
		incValueModal(100);
	}
	
	if (IsPopCoordinate(btnIncDecModalLeft + 36 * 2, 171, 35, 30)) {
		decValueModal(100);
	}
	
	if (Menu.Modal.Type == TYPE_TIME) {
		if (IsPopCoordinate(btnIncDecModalLeft + 36 * 3, 119, 35, 30)) {
			incValueModal(1000);
		}
		
		if (IsPopCoordinate(btnIncDecModalLeft + 36 * 3, 171, 35, 30)) {
			decValueModal(1000);
		}
		
		if (IsPopCoordinate(btnIncDecModalLeft + 36 * 4, 119, 35, 30)) {
			incValueModal(10000);
		}
		
		if (IsPopCoordinate(btnIncDecModalLeft + 36 * 4, 171, 35, 30)) {
			decValueModal(10000);
		}
		
		if (IsPopCoordinate(btnIncDecModalLeft + 36 * 5, 119, 35, 30)) {
			incValueModal(100000);
		}
		
		if (IsPopCoordinate(btnIncDecModalLeft + 36 * 5, 171, 35, 30)) {
			decValueModal(100000);
		}
		
		if (IsPopCoordinate(btnIncDecModalLeft + 36 * 6, 119, 35, 30)) {
			incValueModal(1000000);
		}

		if (IsPopCoordinate(btnIncDecModalLeft + 36 * 6, 171, 35, 30)) {
			decValueModal(1000000);
		}
	}
}

void bckspsSymbol(void) {
	char *p = &coreCPUsett.sequences[Menu.NavProg.activeProg].name[1];
	int16_t length = strlen(p)-1;
	
	if (length < 0) return;
	
	p[length] = 0x00;
}

void otherSymbol(char *str) {
	char *p = &coreCPUsett.sequences[Menu.NavProg.activeProg].name[1];
	
	if (strlen(p) > 9) return;
	
	sprintf(p, "%s%s", p, str);
} 

void DeleteProg(void) {
	uint16_t countProg = 0;
	
	for (uint16_t i=0; i<MaxCountSequenced; i++) {
		if (coreCPUsett.sequences[i].enabled == flagDisable) break;
		
		countProg++;
	}
	
	if (countProg < 2) return;
	
	for (uint16_t i = Menu.NavProg.activeProg; i < countProg; i++) {
		uint8_t *dst = (uint8_t *)&coreCPUsett.sequences[i];
		uint8_t *src = (uint8_t *)&coreCPUsett.sequences[i+1];
		memcpy(dst, src, sizeof(t_sequenced));
	}
		
	if (Menu.NavProg.activeProg > 0) { 
		Menu.NavProg.activeProg--;
	} else {
		Menu.NavProg.activeProg = 0;
	} 
	
	Menu.NavProg.maxCountProgs--;
	
	Menu_Timer_Update();
}

void AddNewProg(void) {
	uint16_t countProg = 0;
	
	for (uint16_t i=0; i<MaxCountSequenced; i++) {
		if (coreCPUsett.sequences[i].enabled == flagDisable) break;
		
		countProg++;
	}
	
	if (countProg > MaxCountSequenced - 1) return;
	
	for (uint16_t i = countProg; i > Menu.NavProg.activeProg; i--) {
		uint8_t *dst = (uint8_t *)&coreCPUsett.sequences[i];
		uint8_t *src = (uint8_t *)&coreCPUsett.sequences[i-1];
		memcpy(dst, src, sizeof(t_sequenced));
	}
		
	if (Menu.NavProg.activeProg > MaxCountSequenced) { 
		Menu.NavProg.activeProg = MaxCountSequenced;
	} else {
		Menu.NavProg.activeProg++;
	}
	
	Menu.NavProg.maxCountProgs++;

	sprintf(&coreCPUsett.sequences[Menu.NavProg.activeProg].name[1], "%s", "New Prog");
	
	Menu_Timer_Update();	
}

void ActionTouchPageChangeProg(void) {
	char str[10];
	
	if (IsPopCoordinate(220, 0, 100, 20)) { // Delete prog.
		DeleteProg();
		MenuRedraw();
	}
	
	if (IsPopCoordinate(0, 25, 110, 20)) { // Add new prog.
		AddNewProg();
		MenuRedraw();
	}

	str[0] = 0x20;
	str[1] = 0x00;
	for (uint16_t y = 0; y < 7; y++) {
		for (uint16_t x = 0; x < 14; x++) {
			if (str[0] < 0x7F) { 
				if (IsPopCoordinate(15 + 21 * x, 53 + 21 * y, 20, 20)) { // Symbol
					otherSymbol(str);
					MenuRedraw();
				}
			}
			
			str[0]++;
		}
	}
	
	if (IsPopCoordinate(15 + 21 * 11, 53 + 21 * 6, 62, 20)) { // Bcsp.
		bckspsSymbol();
		MenuRedraw();
	}
	
	if (IsPopCoordinate(160, 220, 60, 20)) { // Save
		coreFlags.settSaveEnable = flagEnable;	
		SaveYesDraw();
		_delay_ms(4000);
		LCD_Clear(clBlack);
		MenuRedraw();
	}
}

void ActionTouch(void) {
	if (!Menu.Modal.Enable) {
		switch(Menu.NavPage.page) {
			case MENU_PAGE1:
			case MENU_PAGE2:
				ActionTouchPage1();
			break;
			case MENU_PAGE3:
				ActionTouchPagePaint();
			break;
			case MENU_PAGE_CALIBR:
				if (IsPopCoordinate(50, 50, 220, 100)) {
					TouchPanel_Calibrate(coreCPUsett.screenSample);
					coreFlags.settSaveEnable = flagEnable;
					MenuRedraw();
				}
			break;
			case MENU_PAGE_PROG:
				ActionTouchPageChangeProg();
			break;	
			default:
			break;
		}
	} else {
		ActionTouchModal();
	}
	
	if (IsPopCoordinate(btnNavPageLeft, btnNavPageTop, 20, btnNavPageHeight)) { // Btn Menu Left
		LCD_Clear(clBlack);
		MenuPageLeft();
	}
	
	if (IsPopCoordinate(btnNavPageLeft + 20 + 60, btnNavPageTop, 20, btnNavPageHeight)) { // Btn Menu Right
		LCD_Clear(clBlack);
		MenuPageRight();
	}
}
