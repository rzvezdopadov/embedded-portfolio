#ifndef  __TERMO_I2C_H
#define __TERMO_I2C_H

#include "main.h"

#define LM75_WRITE_ADDR 0x90
#define LM75_ADDR_TERMO 0x00
#define LM75_READ_ADDR 0x91

void termo_i2c_init(void);
void termo_i2c_read(void);

#endif 


