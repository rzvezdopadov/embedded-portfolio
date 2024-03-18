#ifndef __MAIN_H
#define __MAIN_H

#define F_CPU 168000000
//#define F_CPU 8000000

// Classic library
#include "stdio.h"
#include "stdint.h"
#include "string.h"

// Core library
#include "stm32f4xx.h"

// User library
#include "delay.h"
#include "rammap.h"
#include "flash.h"
#include "rcc.h"
#include "debug.h"
#include "setting.h"
#include "button.h"
#include "timer.h"
#include "criticalinterrupt.h"
#include "taskmanager.h"
#include "devices.h"
#include "update.h"
#include "blink.h"

#endif 
