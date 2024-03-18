#ifndef __ACTION_MENU_H
#define __ACTION_MENU_H

// Classic library
#include "stdio.h"
#include "stdint.h"
#include "string.h"

// Core library
#include "stm32f4xx.h"

#include "LCD/LCD.h"
#include "TouchPanel/TouchPanel.h"
#include "rammap.h"
#include "menu.h"

#define MaxVisibleNavProg 6

void ActionTouch(void);

#endif 
