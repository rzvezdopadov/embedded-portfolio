#ifndef __INTS_H
#define __INTS_H

#include "main.h"

// INT1 - PG15, INT2 - PG13, INT3 - PG12, INT4 - PG11, 
// INT5 - PG10, INT6 - PG9, INT7 - PG8, INT8 - PG7

void ints_init(void);

uint32_t getINT1(void);
uint32_t getINT2(void);
uint32_t getINT3(void);
uint32_t getINT4(void);
uint32_t getINT5(void);
uint32_t getINT6(void);
uint32_t getINT7(void);
uint32_t getINT8(void);

void setINT1(uint32_t count);
void setINT2(uint32_t count);
void setINT3(uint32_t count);
void setINT4(uint32_t count);
void setINT5(uint32_t count);
void setINT6(uint32_t count);
void setINT7(uint32_t count);
void setINT8(uint32_t count);

void clearAllINT(void);


#endif 



