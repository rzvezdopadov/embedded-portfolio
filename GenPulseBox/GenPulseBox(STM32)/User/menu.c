#include "menu.h"

t_Menu Menu;

void Menu_Init(void) { // Инициализация меню
// Стэйт
	Menu.NavPage.page = 0;
	Menu.NavProg.activeProg = 0;
	Menu.NavProg.maxCountProgs = 0;
	Menu.NavProg.page = 0;
	Menu.paintColor = clBlack;
	
	for (uint16_t i=0; i<MaxCountSequenced; i++) {
		if (coreCPUsett.sequences[i].enabled) {
			Menu.NavProg.maxCountProgs++;
		} else {
			break;
		}
	}
	
	printf("Menu Init Ok!\n");
}

void RectDraw(uint16_t Left, uint16_t Top, uint16_t Width, uint16_t Height, uint16_t color) {
	for (uint16_t i = Top; i<Top + Height; i++) {
		for (uint16_t j=Left; j<Left + Width; j++) {
				LCD_SetPoint(j, i, color);
		}
	}
}

void ModalDraw(uint16_t Left, uint16_t Top, uint16_t Width, uint16_t Height, uint16_t color) {
	RectDraw(Left, Top, Width, Height, clBlue);
	RectDraw(Left+2, Top+24, Width-4, Height-26, clGrey);
	RectDraw(Width+8, Top+2, 20, 20, clRed);
	GUI_Text(Width+14, Top+4, "X", clWhite, clRed);
}
	
void CircleDraw(uint16_t LeftCenter, uint16_t TopCenter, uint16_t Radius, uint16_t color) {
	for (uint16_t i = LeftCenter - Radius; i < LeftCenter + Radius; i++) {
		for (uint16_t j = TopCenter - Radius; j < TopCenter + Radius; j++) {
			if (Radius == Radius) {
				LCD_SetPoint(i, j, color);
			}
		}
	}
}

void RightButtonDraw(void) {
	RectDraw(btnNavLeft, 0, btnNavWidht, btnNavHeight + 5, clYellow);
	GUI_Text(btnNavLeft + 12, 2 + 2, "Page Up" , clBlack, clYellow);

	uint16_t VisibleNavProg =  MaxVisibleNavProg;
	
	if ((Menu.NavProg.page + 1) * MaxVisibleNavProg > Menu.NavProg.maxCountProgs) {
		VisibleNavProg =  MaxVisibleNavProg - ((Menu.NavProg.page + 1) * MaxVisibleNavProg - Menu.NavProg.maxCountProgs);
	} 
	
	for (uint16_t i=0; i<MaxVisibleNavProg; i++) {
		RectDraw(btnNavLeft, btnNavTop + i * (btnNavHeight + btnNavMargin), btnNavWidht, btnNavHeight, clBlack);
	}
	
	for (uint16_t i=0; i<VisibleNavProg; i++) {
		if (Menu.NavProg.activeProg == Menu.NavProg.page * MaxVisibleNavProg + i) {
			RectDraw(btnNavLeft, btnNavTop + i * (btnNavHeight + btnNavMargin), btnNavWidht, btnNavHeight, clMagenta);
			GUI_Text(btnNavLeft, btnNavTop + 2 + i * (btnNavHeight + btnNavMargin), &coreCPUsett.sequences[Menu.NavProg.page * MaxVisibleNavProg + i].name[1], clBlack, clMagenta);
		} else {
			RectDraw(btnNavLeft, btnNavTop + i * (btnNavHeight + btnNavMargin), btnNavWidht, btnNavHeight, clCyan);
			GUI_Text(btnNavLeft, btnNavTop + 2 + i * (btnNavHeight + btnNavMargin), &coreCPUsett.sequences[Menu.NavProg.page * MaxVisibleNavProg + i].name[1], clBlack, clCyan);
		}
	}
	
	RectDraw(btnNavLeft, 215, btnNavWidht, btnNavHeight + 5, clYellow);
	GUI_Text(btnNavLeft + 5, 217 + 2, "Page Down" , clBlack, clYellow);
}

void NaviPageButtonDraw(void) {
	char str[10];	
	
	RectDraw(btnNavPageLeft, btnNavPageTop, 20, btnNavPageHeight, clYellow);
	GUI_Text(btnNavPageLeft + 5, btnNavPageTop + 2, "<" , clBlack, clYellow);
	
	RectDraw(btnNavPageLeft + 20, btnNavPageTop, 60, btnNavPageHeight, clCyan);
	sprintf(str, "Menu %d", Menu.NavPage.page + 1);
	GUI_Text(btnNavPageLeft + 5 + 20, btnNavPageTop + 2, str, clBlack, clCyan);
	
	RectDraw(btnNavPageLeft + 20 + 60, btnNavPageTop, 20, btnNavPageHeight, clYellow);
	GUI_Text(btnNavPageLeft + 5 + 20 + 60, btnNavPageTop + 2, ">" , clBlack, clYellow);
}

void convertTimeParamDraw(char *str, uint32_t time) {
	uint32_t timeDouble;
	uint32_t timeDoubleDiv;	
		
	if (time < 10000) {
		timeDouble = time / 10;
		timeDoubleDiv = time % 10;
		sprintf(str, "%d.%dus", timeDouble, timeDoubleDiv);
	} else {
		timeDouble = time / 10000;
		timeDoubleDiv = (time / 1000) % 10;
		sprintf(str, "%d.%dms", timeDouble, timeDoubleDiv);
	}
}

void convertOnOffParamDraw(char *str, uint32_t onOff) {
	if (onOff == 1) {
		sprintf(str, "On");
	} else {
		sprintf(str, "Off");
	}
}

void convertReverseParamDraw(char *str, uint32_t reverse) {
	if (reverse == 1) {
		sprintf(str, "Reverse");
	} else {
		sprintf(str, "Straig.");
	}
}

void convertPulseCountParamDraw(char *str, uint32_t countPulse, uint32_t maxCountPulse) {
	sprintf(str, "Pulse %d/%d", countPulse, maxCountPulse);
}

void TableDPBDraw(void) {
	char str[10];
	
	RectDraw(0, 0, 50, 20, clGreen);
	GUI_Text(0 + 2, 0 + 2, "", clBlack, clGreen);
	
	RectDraw(0, 21, 50, 20, clYellow);
	Menu.NavPage.page == MENU_PAGE1 ? sprintf(str, "CH1(1)") : sprintf(str, "CH1(2)");
	GUI_Text(0 + 2, 21 + 2, str, clBlack, clYellow);
	
	RectDraw(0, 21 + 21 + 0, 50, 20, clOrange);
	Menu.NavPage.page == MENU_PAGE1 ? sprintf(str, "CH2(1)") : sprintf(str, "CH2(2)");
	GUI_Text(0 + 2, 21 + 21 + 2, str, clBlack, clOrange);
	
/////////////////
	RectDraw(0 + 51, 0, 60, 20, clGreen);
	GUI_Text(0 + 51 + 4, 0 + 2, "Durat." , clBlack, clGreen);

	RectDraw(0 + 51, 21, 60, 20, clYellow);
	if (Menu.NavPage.page == MENU_PAGE1) {
		convertTimeParamDraw(str, coreCPUsett.sequences[Menu.NavProg.activeProg].CH1.pulses[Menu.NavProg.activePulseCH1].up1);
	} else {
		convertTimeParamDraw(str, coreCPUsett.sequences[Menu.NavProg.activeProg].CH1.pulses[Menu.NavProg.activePulseCH1].up2);
	}
	GUI_Text(0 + 51 + 2, 21 + 2, str, clBlack, clYellow);
	
	RectDraw(0 + 51, 21 + 21 + 0, 60, 20, clOrange);
	if (Menu.NavPage.page == MENU_PAGE1) {
		convertTimeParamDraw(str, coreCPUsett.sequences[Menu.NavProg.activeProg].CH2.pulses[Menu.NavProg.activePulseCH2].up1);
	} else {
		convertTimeParamDraw(str, coreCPUsett.sequences[Menu.NavProg.activeProg].CH2.pulses[Menu.NavProg.activePulseCH2].up2);
	}
	GUI_Text(0 + 51 + 2, 21 + 21 + 2, str, clBlack, clOrange);

/////////////////
	RectDraw(0 + 51 + 61, 0, 60, 20, clGreen);
	GUI_Text(0 + 51 + 61 + 6, 0 + 2, "Period", clBlack, clGreen);
	
	RectDraw(0 + 51 + 61, 21, 60, 20, clYellow);
	convertTimeParamDraw(str, coreCPUsett.sequences[Menu.NavProg.activeProg].CH1.pulses[Menu.NavProg.activePulseCH1].down);
	GUI_Text(0 + 51 + 61 + 2, 21 + 2, str, clBlack, clYellow);
		
	RectDraw(0 + 51 + 61, 21 + 21 + 0, 60, 20, clOrange);
	convertTimeParamDraw(str, coreCPUsett.sequences[Menu.NavProg.activeProg].CH2.pulses[Menu.NavProg.activePulseCH2].down);
	GUI_Text(0 + 51 + 61 + 2, 21 + 21 + 2, str, clBlack, clOrange);
	
/////////////////	
	RectDraw(0 + 51 + 61 + 61, 0, 60, 20, clGreen);
	GUI_Text(0 + 51 + 61 + 61 + 5, 0 + 2, "Amount", clBlack, clGreen);
	
	RectDraw(0 + 51 + 61 + 61, 21, 60, 20, clYellow);
	sprintf(str, "%d", coreCPUsett.sequences[Menu.NavProg.activeProg].CH1.pulses[Menu.NavProg.activePulseCH1].count);
	GUI_Text(0 + 51 + 61 + 61 + 20, 21 + 2, str, clBlack, clYellow);
		
	RectDraw(0 + 51 + 61 + 61, 21 + 21 + 0, 60, 20, clOrange);
	sprintf(str, "%d", coreCPUsett.sequences[Menu.NavProg.activeProg].CH2.pulses[Menu.NavProg.activePulseCH2].count);
	GUI_Text(0 + 51 + 61 + 61 + 20, 21 + 21 + 2, str, clBlack, clOrange);
}

void TableAPOODraw(void) {
	char str[10];
	uint16_t color;
	
	RectDraw(0, TableAPOOTop + 0, 50, 20, clGreen);
	GUI_Text(0 + 2, TableAPOOTop + 0 + 2, "", clBlack, clGreen);
	
	RectDraw(0, TableAPOOTop + 21, 50, 20, clYellow);
	if (Menu.NavPage.page == MENU_PAGE1) {
		GUI_Text(0 + 2, TableAPOOTop + 21 + 2, "CH1(1)", clBlack, clYellow);
	} else {
		GUI_Text(0 + 2, TableAPOOTop + 21 + 2, "CH1(2)", clBlack, clYellow);
	}
		
	RectDraw(0, TableAPOOTop + 21 + 21 + 0, 50, 20, clOrange);
	if (Menu.NavPage.page == MENU_PAGE1) {
		GUI_Text(0 + 2, TableAPOOTop + 21 + 21 + 2, "CH2(1)", clBlack, clOrange);
	} else {
		GUI_Text(0 + 2, TableAPOOTop + 21 + 21 + 2, "CH2(2)", clBlack, clOrange);
	}
		
/////////////////
	RectDraw(0 + 51, TableAPOOTop + 0, 60, 20, clGreen);
	GUI_Text(0 + 51 + 16, TableAPOOTop + 0 + 2, "Bias" , clBlack, clGreen);

	RectDraw(0 + 51, TableAPOOTop + 21, 60, 20, clYellow);
	convertTimeParamDraw(str, coreCPUsett.sequences[Menu.NavProg.activeProg].CH1.bias);
	GUI_Text(0 + 51 + 2, TableAPOOTop + 21 + 2, str, clBlack, clYellow);
	
	RectDraw(0 + 51, TableAPOOTop + 21 + 21 + 0, 60, 20, clOrange);
	convertTimeParamDraw(str, coreCPUsett.sequences[Menu.NavProg.activeProg].CH2.bias);
	GUI_Text(0 + 51 + 2, TableAPOOTop + 21 + 21 + 2, str, clBlack, clOrange);

///////////////////
	RectDraw(0 + 51 + 61, TableAPOOTop + 0, 60, 20, clGreen);
	GUI_Text(0 + 51 + 61 + 5, TableAPOOTop + 0 + 2, "Polar.", clBlack, clGreen);
	
	RectDraw(0 + 51 + 61, TableAPOOTop + 21, 60, 20, clYellow);
	if (Menu.NavPage.page == MENU_PAGE1) {
		convertReverseParamDraw(str, coreCPUsett.sequences[Menu.NavProg.activeProg].CH1.polarity1);
	} else {
		convertReverseParamDraw(str, coreCPUsett.sequences[Menu.NavProg.activeProg].CH1.polarity2);
	}
		
	GUI_Text(0 + 51 + 61 + 2, TableAPOOTop + 21 + 2, str, clBlack, clYellow);
		
	RectDraw(0 + 51 + 61, TableAPOOTop + 21 + 21, 60, 20, clOrange);
	if (Menu.NavPage.page == MENU_PAGE1) {
		convertReverseParamDraw(str, coreCPUsett.sequences[Menu.NavProg.activeProg].CH2.polarity1);
	} else {
		convertReverseParamDraw(str, coreCPUsett.sequences[Menu.NavProg.activeProg].CH2.polarity2);
	}
	GUI_Text(0 + 51 + 61 + 2, TableAPOOTop + 21 + 21 + 2, str, clBlack, clOrange);

///////////////////	
	RectDraw(0 + 51 + 61 + 61, TableAPOOTop + 0, 60, 20, clGreen);
	GUI_Text(0 + 51 + 61 + 61 + 5, TableAPOOTop + 0 + 2, "On/Off", clBlack, clGreen);
	
	if (Menu.NavPage.page == MENU_PAGE1) {
		convertOnOffParamDraw(str, coreFlags.CH1Enable1);
		color = coreFlags.CH1Enable1 == flagEnable ? clGreen : clRed;
	} else {
		convertOnOffParamDraw(str, coreFlags.CH1Enable2);
		color = coreFlags.CH1Enable2 == flagEnable ? clGreen : clRed;
	}
	RectDraw(0 + 51 + 61 + 61, TableAPOOTop + 21, 60, 20, color);
	GUI_Text(0 + 51 + 61 + 61 + 18, TableAPOOTop + 21 + 2, str, clBlack, color);

	if (Menu.NavPage.page == MENU_PAGE1) {
		convertOnOffParamDraw(str, coreFlags.CH2Enable1);
		color = coreFlags.CH2Enable1 == flagEnable ? clGreen : clRed;
	} else {
		convertOnOffParamDraw(str, coreFlags.CH2Enable2);
		color = coreFlags.CH2Enable2 == flagEnable ? clGreen : clRed;
	}
		
	RectDraw(0 + 51 + 61 + 61, TableAPOOTop + 21 + 21, 60, 20, color);
	GUI_Text(0 + 51 + 61 + 61 + 18, TableAPOOTop + 21 + 21 + 2, str, clBlack, color);
}

void TablePulseCheckDraw(void) {
	char str[10];
	
	RectDraw(0, TablePulseCheckTop, 50, 20, clYellow);
	GUI_Text(0 + 13, TablePulseCheckTop + 2, "CH1", clBlack, clYellow);
	
	RectDraw(0, TablePulseCheckTop + 21 + 0, 50, 20, clOrange);
	GUI_Text(0 + 13, TablePulseCheckTop + 21 + 2, "CH2", clBlack, clOrange);

///////////////////
	RectDraw(btnNavPageLeft + 51, TablePulseCheckTop + 0, 20, 20, clYellow);
	GUI_Text(btnNavPageLeft + 51 + 5, TablePulseCheckTop + 2, "<" , clBlack, clYellow);
	
	RectDraw(btnNavPageLeft + 51 + 20, TablePulseCheckTop, 100, btnNavPageHeight, clCyan);
		convertPulseCountParamDraw(str, Menu.NavProg.activePulseCH1 + 1, coreCPUsett.sequences[Menu.NavProg.activeProg].CH1.count);
	GUI_Text(btnNavPageLeft + 51 + 5 + 20, TablePulseCheckTop + 2, str, clBlack, clCyan);
	
	RectDraw(btnNavPageLeft + 51 + 20 + 100, TablePulseCheckTop, 20, btnNavPageHeight, clYellow);
	GUI_Text(btnNavPageLeft + 51 + 5 + 20 + 100, TablePulseCheckTop + 2, ">" , clBlack, clYellow);
	
	RectDraw(btnNavPageLeft + 51 + 20 + 100 + 20 + 1, TablePulseCheckTop, 20, btnNavPageHeight, clGreen);
	GUI_Text(btnNavPageLeft + 51 + 5 + 20 + 100 + 20 + 1, TablePulseCheckTop + 2, "A" , clBlack, clGreen);
	
	RectDraw(btnNavPageLeft + 51 + 20 + 100 + 20 + 21 + 1, TablePulseCheckTop, 20, btnNavPageHeight, clRed);
	GUI_Text(btnNavPageLeft + 51 + 5 + 20 + 100 + 20 + 21 + 1, TablePulseCheckTop + 2, "D" , clBlack, clRed);
///////////////////
	RectDraw(btnNavPageLeft + 51, TablePulseCheckTop + 21 + 0, 20, 20, clOrange);
	GUI_Text(btnNavPageLeft + 51 + 5, TablePulseCheckTop + 21 + 2, "<" , clBlack, clOrange);
	
	RectDraw(btnNavPageLeft + 51 + 20, TablePulseCheckTop + 21, 100, btnNavPageHeight, clCyan);
	convertPulseCountParamDraw(str, Menu.NavProg.activePulseCH2 + 1, coreCPUsett.sequences[Menu.NavProg.activeProg].CH2.count);
	GUI_Text(btnNavPageLeft + 51 + 5 + 20, TablePulseCheckTop + 21 + 2, str, clBlack, clCyan);
	
	RectDraw(btnNavPageLeft + 51 + 20 + 100, TablePulseCheckTop + 21, 20, btnNavPageHeight, clOrange);
	GUI_Text(btnNavPageLeft + 51 + 5 + 20 + 100, TablePulseCheckTop + 21 + 2, ">" , clBlack, clOrange);
	
	RectDraw(btnNavPageLeft + 51 + 20 + 100 + 20 + 1, TablePulseCheckTop + 21, 20, btnNavPageHeight, clGreen);
	GUI_Text(btnNavPageLeft + 51 + 5 + 20 + 100 + 20 + 1, TablePulseCheckTop + 21 + 2, "A" , clBlack, clGreen);
	
	RectDraw(btnNavPageLeft + 51 + 20 + 100 + 20 + 21 + 1, TablePulseCheckTop + 21, 20, btnNavPageHeight, clRed);
	GUI_Text(btnNavPageLeft + 51 + 5 + 20 + 100 + 20 + 21 + 1, TablePulseCheckTop + 21 + 2, "D" , clBlack, clRed);
}

void TablePeriodDraw(void) {
	char str[10];
	
	RectDraw(0, 190, 90, btnNavPageHeight, clGreen);
	GUI_Text(4, 190 + 2, "Period All" , clBlack, clGreen);
	
	RectDraw(91, 190, 70, btnNavPageHeight, clYellow);
	convertTimeParamDraw(str, coreCPUsett.sequences[Menu.NavProg.activeProg].period);
	GUI_Text(91 + 4, 190 + 2, str, clBlack, clYellow);
}

void PaintPage(void) {
	RectDraw(btnPaintPageColorLeft - 40, btnNavPageTop, 40, btnNavPageHeight, clWhite);
	GUI_Text(btnPaintPageColorLeft - 40, btnNavPageTop+2, "Clear", clBlack, clWhite);
	RectDraw(btnPaintPageColorLeft + 20 * 0, btnNavPageTop, 20, btnNavPageHeight, clRed);
	RectDraw(btnPaintPageColorLeft + 20 * 1, btnNavPageTop, 20, btnNavPageHeight, clOrange);
	RectDraw(btnPaintPageColorLeft + 20 * 2, btnNavPageTop, 20, btnNavPageHeight, clYellow);
	RectDraw(btnPaintPageColorLeft + 20 * 3, btnNavPageTop, 20, btnNavPageHeight, clGreen);
	RectDraw(btnPaintPageColorLeft + 20 * 4, btnNavPageTop, 20, btnNavPageHeight, clBlue);
	RectDraw(btnPaintPageColorLeft + 20 * 5, btnNavPageTop, 20, btnNavPageHeight, clMagenta);
	RectDraw(btnPaintPageColorLeft + 20 * 6, btnNavPageTop, 20, btnNavPageHeight, clCyan);
	RectDraw(btnPaintPageColorLeft + 20 * 7, btnNavPageTop, 20, btnNavPageHeight, clWhite);
	RectDraw(btnPaintPageColorLeft + 20 * 8, btnNavPageTop, 20, btnNavPageHeight, clBlack);
}

void PulseChangeDrawModalValue(void) {
	char str[10];
	RectDraw(128, 78, 74, 24, clBlack);
	RectDraw(130, 80, 70, 20, clWhite);
	if (Menu.Modal.Type == TYPE_TIME) {
		convertTimeParamDraw(str, *Menu.Modal.Value);
	} else {
		sprintf(str, "%d", *Menu.Modal.Value);
	}
	GUI_Text(130 + 2, 80, str, clBlack, clWhite);
}

void PulseChangeDrawModal(void) { 
	NaviPageButtonDraw();
	ModalDraw(30, 30, 260, 180, clBlack);
	PulseChangeDrawModalValue();
		
	RectDraw(btnIncDecModalLeft + 36 * 0, btnIncDecModalTop, 35, 30, clOrange);
	GUI_Text(btnIncDecModalLeft + 36 * 0 + 13, btnIncDecModalTop + 12, "^", clBlack, clOrange);
	RectDraw(btnIncDecModalLeft + 36 * 0, btnIncDecModalTop + 31, 35, 20, clOrange);
	if (Menu.Modal.Type == TYPE_TIME) { 
		GUI_Text(btnIncDecModalLeft + 36 * 0 + 5, btnIncDecModalTop + 31 + 2, "0.1", clBlack, clOrange);
	} else {
		GUI_Text(btnIncDecModalLeft + 36 * 0 + 13, btnIncDecModalTop + 31 + 2, "1", clBlack, clOrange);
	}
	RectDraw(btnIncDecModalLeft + 36 * 0, btnIncDecModalTop + 52, 35, 30, clOrange);
	GUI_Text(btnIncDecModalLeft + 36 * 0 + 13,  btnIncDecModalTop + 52 + 6, "v", clBlack, clOrange);
	
	RectDraw(btnIncDecModalLeft + 36 * 1, btnIncDecModalTop, 35, 30, clYellow);
	GUI_Text(btnIncDecModalLeft + 36 * 1 + 13, btnIncDecModalTop + 12, "^", clBlack, clYellow);
	RectDraw(btnIncDecModalLeft + 36 * 1, btnIncDecModalTop + 31, 35, 20, clYellow);
	if (Menu.Modal.Type == TYPE_TIME) { 
		GUI_Text(btnIncDecModalLeft + 36 * 1 + 13, btnIncDecModalTop + 31 + 2, "1", clBlack, clYellow);
	} else {
		GUI_Text(btnIncDecModalLeft + 36 * 1 + 8, btnIncDecModalTop + 31 + 2, "10", clBlack, clYellow);
	}
	RectDraw(btnIncDecModalLeft + 36 * 1,  btnIncDecModalTop + 52, 35, 30, clYellow);
	GUI_Text(btnIncDecModalLeft + 36 * 1 + 13,  btnIncDecModalTop + 52 + 6, "v", clBlack, clYellow);
		
	RectDraw(btnIncDecModalLeft + 36 * 2, btnIncDecModalTop, 35, 30, clOrange);
	GUI_Text(btnIncDecModalLeft + 36 * 2 + 13, btnIncDecModalTop + 12, "^", clBlack, clOrange);
	RectDraw(btnIncDecModalLeft + 36 * 2, btnIncDecModalTop + 31, 35, 20, clOrange);
	if (Menu.Modal.Type == TYPE_TIME) { 
		GUI_Text(btnIncDecModalLeft + 36 * 2 + 8, btnIncDecModalTop + 31 + 2, "10", clBlack, clOrange);
	} else {
		GUI_Text(btnIncDecModalLeft + 36 * 2 + 4, btnIncDecModalTop + 31 + 2, "100", clBlack, clOrange);
	}
	RectDraw(btnIncDecModalLeft + 36 * 2,  btnIncDecModalTop + 52, 35, 30, clOrange);
	GUI_Text(btnIncDecModalLeft + 36 * 2 + 13,  btnIncDecModalTop + 52 + 6, "v", clBlack, clOrange);
	
	if (Menu.Modal.Type == TYPE_TIME) {
		RectDraw(btnIncDecModalLeft + 36 * 3, btnIncDecModalTop, 35, 30, clYellow);
		GUI_Text(btnIncDecModalLeft + 36 * 3 + 13, btnIncDecModalTop + 12, "^", clBlack, clYellow);
		RectDraw(btnIncDecModalLeft + 36 * 3, btnIncDecModalTop + 31, 35, 20, clYellow);
		GUI_Text(btnIncDecModalLeft + 36 * 3 + 4, btnIncDecModalTop + 31 + 2, "100", clBlack, clYellow);
		RectDraw(btnIncDecModalLeft + 36 * 3,  btnIncDecModalTop + 52, 35, 30, clYellow);
		GUI_Text(btnIncDecModalLeft + 36 * 3 + 13,  btnIncDecModalTop + 52 + 6, "v", clBlack, clYellow);
		
		RectDraw(btnIncDecModalLeft + 36 * 4, btnIncDecModalTop, 35, 30, clOrange);
		GUI_Text(btnIncDecModalLeft + 36 * 4 + 13, btnIncDecModalTop + 12, "^", clBlack, clOrange);
		RectDraw(btnIncDecModalLeft + 36 * 4, btnIncDecModalTop + 31, 35, 20, clOrange);
		GUI_Text(btnIncDecModalLeft + 36 * 4 + 13, btnIncDecModalTop + 31 + 2, "1", clBlack, clOrange);
		RectDraw(btnIncDecModalLeft + 36 * 4,  btnIncDecModalTop + 52, 35, 30, clOrange);
		GUI_Text(btnIncDecModalLeft + 36 * 4 + 13,  btnIncDecModalTop + 52 + 6, "v", clBlack, clOrange);
		
		RectDraw(btnIncDecModalLeft + 36 * 5, btnIncDecModalTop, 35, 30, clYellow);
		GUI_Text(btnIncDecModalLeft + 36 * 5 + 13, btnIncDecModalTop + 12, "^", clBlack, clYellow);
		RectDraw(btnIncDecModalLeft + 36 * 5, btnIncDecModalTop + 31, 35, 20, clYellow);
		GUI_Text(btnIncDecModalLeft + 36 * 5 + 8, btnIncDecModalTop + 31 + 2, "10", clBlack, clYellow);
		RectDraw(btnIncDecModalLeft + 36 * 5,  btnIncDecModalTop + 52, 35, 30, clYellow);
		GUI_Text(btnIncDecModalLeft + 36 * 5 + 13,  btnIncDecModalTop + 52 + 6, "v", clBlack, clYellow);
		
		RectDraw(btnIncDecModalLeft + 36 * 6, btnIncDecModalTop, 35, 30, clOrange);
		GUI_Text(btnIncDecModalLeft + 36 * 6 + 13, btnIncDecModalTop + 12, "^", clBlack, clOrange);
		RectDraw(btnIncDecModalLeft + 36 * 6, btnIncDecModalTop + 31, 35, 20, clOrange);
		GUI_Text(btnIncDecModalLeft + 36 * 6 + 4, btnIncDecModalTop + 31 + 2, "100", clBlack, clOrange);
		RectDraw(btnIncDecModalLeft + 36 * 6,  btnIncDecModalTop + 52, 35, 30, clOrange);
		GUI_Text(btnIncDecModalLeft + 36 * 6 + 13,  btnIncDecModalTop + 52 + 6, "v", clBlack, clOrange);
	}
	
	if (Menu.Modal.Type == TYPE_TIME) {
		RectDraw(btnIncDecModalLeft + 36 * 0, btnIncDecModalTop - 20, 35 * 4 + 3, 20, clGreen);
		GUI_Text(btnIncDecModalLeft + 36 * 2 - 10, btnIncDecModalTop - 17, "us", clBlack, clGreen);
		
		RectDraw(btnIncDecModalLeft + 36 * 4, btnIncDecModalTop - 20, 35 * 3 + 2, 20, clGreen);
		GUI_Text(btnIncDecModalLeft + 36 * 5 + 10, btnIncDecModalTop - 17, "ms", clBlack, clGreen);
	}
}

void PageProgDraw(void) {
	char str[10];
	RectDraw(0, 0, 100, 20, clGreen);
	GUI_Text(0 + 2, 0 + 2, "Name prog.:", clBlack, clGreen);
		
	RectDraw(101, 0, 100, 20, clGreen);
	GUI_Text(101 + 2, 0 + 2, &coreCPUsett.sequences[Menu.NavProg.activeProg].name[1], clBlack, clGreen);
	
	RectDraw(220, 0, 100, 20, clRed);
	GUI_Text(220 + 2, 0 + 2, "Delete prog.", clBlack, clRed);
	
	RectDraw(0, 25, 110, 20, clGreen);
	GUI_Text(0 + 2, 25 + 2, "Add new prog.", clBlack, clGreen);
	
	str[0] = 0x20;
	str[1] = 0x00;
	for (uint16_t y = 0; y < 7; y++) {
		for (uint16_t x = 0; x < 14; x++) {
			if (str[0] < 0x7F) { 
				RectDraw(15 + 21 * x, 53 + 21 * y, 20, 20, clYellow);
				GUI_Text(15 + 6 + 21 * x, 53 + 21 * y + 1, str , clBlack, clYellow);
				str[0]++;
			}
		}
	}
	
	RectDraw(15 + 21 * 11, 53 + 21 * 6, 62, 20, clOrange);
	GUI_Text(15 + 10 + 21 * 11, 53 + 21 * 6 + 1, "Bcsp." , clBlack, clOrange);
	
	RectDraw(160, 220, 60, 20, clWhite);
	GUI_Text(160 + 12, 220 + 2, "Save" , clBlack, clWhite);
}

void SaveYesDraw(void) {
	LCD_Clear(clBlack);
	RectDraw(50, 70, 220, 110, clGreen);
	GUI_Text(60, 120, "Settings have been saved!", clBlack, clGreen);
}
	
void MenuRedraw(void) {
	switch(Menu.NavPage.page) {
		case MENU_PAGE1:
		case MENU_PAGE2:
			TableDPBDraw();
			TableAPOODraw();
			TablePulseCheckDraw();
			RightButtonDraw();
			TablePeriodDraw();
		break;
		case MENU_PAGE3:
			PaintPage();
		break;
		case MENU_PAGE_CALIBR:	
			RectDraw(50, 50, 220, 100, clWhite);
			GUI_Text(100, 90, "Calibrate Touch?", clBlack, clWhite);
		break;
		case MENU_PAGE_PROG:
			PageProgDraw();
		break;
		default:
		break;
	}
	
	NaviPageButtonDraw();
	
	if (Menu.Modal.Enable) PulseChangeDrawModal();
}

