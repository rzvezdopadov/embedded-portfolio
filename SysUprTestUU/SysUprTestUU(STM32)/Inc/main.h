#ifndef __MAIN_H
#define __MAIN_H

#define F_CPU 168000000
//#define F_CPU 8000000

// Classic library
#include "stdio.h"
#include "stdint.h"
#include "string.h"

// Core library
#include "stm32f407xx.h"
#include "stm32f4xx.h"

// User library
#include "delay.h"
#include "rammap.h"
#include "flash.h"
#include "rcc.h"
#include "debug.h"
#include "setting.h"
#include "criticalinterrupt.h"
#include "addr.h"
#include "ints.h"
#include "leds.h"
#include "leds_debug.h"
#include "leds_alm.h"
#include "sr.h"
#include "svbp.h"
#include "termo_i2c.h"
#include "uim.h"
#include "volt.h"
#include "volt_adc.h"
#include "pulsegen.h"
#include "modbus.h"
#include "uart_485.h"
#include "uart_pc.h"
#include "uart_pcb.h"
#include "spi.h"
#include "taskmanager.h"

#endif 











