#ifndef __MENU_H
#define __MENU_H

// Classic library
#include "stdio.h"
#include "stdint.h"
#include "string.h"

// Core library
#include "stm32f4xx.h"

#include "LCD/LCD.h"
#include "TouchPanel/TouchPanel.h"
#include "rammap.h"

#define MaxVisibleNavProg 6

#define btnNavTop 		35
#define btnNavLeft  	240
#define btnNavWidht  	80
#define btnNavHeight  20
#define btnNavMargin  10

#define btnNavPageTop 	 220
#define btnNavPageLeft 	 0
#define btnNavPageHeight 20

#define TableAPOOTop 70

#define btnPaintPageColorLeft 140

#define TablePulseCheckTop 140

#define btnIncDecModalLeft 35
#define btnIncDecModalTop 125

typedef struct {
	uint16_t page;
	uint16_t maxCountProgs;
	uint16_t progsId[MaxVisibleNavProg];
	uint16_t activeProg;
	uint32_t activePulseCH1;
	uint32_t activePulseCH2;
} t_NavProg;

typedef struct {
	uint16_t page;
} t_NavPage;

typedef struct {
	uint8_t Enable;
	uint8_t Type;
	uint32_t *Value;
	uint32_t minValue;
	uint32_t maxValue;
} t_Modal;

typedef struct {
	t_NavPage NavPage;
	t_NavProg NavProg;
	uint16_t paintColor;
	t_Modal Modal;
} t_Menu;

enum { MENU_PAGE1, MENU_PAGE2, MENU_PAGE3, MENU_PAGE_CALIBR, MENU_PAGE_PROG, MENU_PAGEMAX };
enum { TYPE_TIME, TYPE_COUNT };

void Menu_Init(void);
void MenuRedraw(void);
void CircleDraw(uint16_t LeftCenter, uint16_t TopCenter, uint16_t Radius, uint16_t color);
void ModalDraw(uint16_t Left, uint16_t Top, uint16_t Width, uint16_t Height, uint16_t color);
void PulseChangeDrawModalValue(void);
void SaveYesDraw(void);

extern	t_Menu Menu;
extern	Coordinate BaseXY;

#endif 
