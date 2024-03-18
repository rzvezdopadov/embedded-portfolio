#include "termo_i2c.h"

// I2C3(AF4) - PH7(SCL) - PH8(SDA) 

void termo_i2c_init(void) {									// Инициализация I2C
// Альтернативная функция порта
	GPIOH->AFR[0] |= GPIO_AFRL_AFSEL7_2;
	GPIOH->AFR[1] |= GPIO_AFRH_AFSEL8_2;
	GPIOH->MODER |= GPIO_MODER_MODE7_1 | GPIO_MODER_MODE8_1;
	GPIOH->OTYPER |= GPIO_OTYPER_OT7 | GPIO_OTYPER_OT8;
	GPIOH->PUPDR |= GPIO_PUPDR_PUPD7_0 | GPIO_PUPDR_PUPD8_0;
	GPIOH->OSPEEDR |= GPIO_OSPEEDR_OSPEED7_Msk | GPIO_OSPEEDR_OSPEED8_Msk;
	
	I2C3->CR1 |= I2C_CR1_SWRST;
	I2C3->CR1 &= ~I2C_CR1_SWRST;
	
	I2C3->CR2 = 0x002A; // 0x002A
	I2C3->OAR1 = 0x4000; // 0x4000
	I2C3->CCR = 0x00D2; // 0x00D2
	I2C3->TRISE = 0x002B; // 0x002B
	I2C3->CR1 = I2C_CR1_PE;
	
	printf("Termo I2C Init Ok!\n");
}

void i2c_clear_sr(void) {
	(void)I2C3->SR1;
	(void)I2C3->SR2;
}

#define wait_i2c_init delay = 30000; 
#define wait_i2c if (delay-- == 0) return;

void termo_i2c_read(void) {
	if (!coreFlags.flagGetTermoSensor) return;
	
	uint32_t delay;
	
	I2C3->CR1 &= ~I2C_CR1_POS;
	I2C3->CR1 |= I2C_CR1_ACK;
	I2C3->CR1 |= I2C_CR1_START;
	wait_i2c_init
	while(!(I2C3->SR1 & I2C_SR1_SB)) {
		wait_i2c
	}
	i2c_clear_sr();
	
	#define Addr_T 0
	
	I2C3->DR = LM75_WRITE_ADDR + Addr_T;
	wait_i2c_init
	while(!(I2C3->SR1 & I2C_SR1_ADDR)) {
		wait_i2c
	} 
	i2c_clear_sr();
	
	I2C3->DR = LM75_ADDR_TERMO;
	wait_i2c_init
	while(!(I2C3->SR1 & I2C_SR1_TXE)) {
		wait_i2c
	};
	i2c_clear_sr();
	
	I2C3->CR1 |= I2C_CR1_START;
	wait_i2c_init
	while(!(I2C3->SR1 & I2C_SR1_SB)) {
		wait_i2c
	}
	i2c_clear_sr();
	
	I2C3->DR = LM75_READ_ADDR + Addr_T;
	wait_i2c_init
	while(!(I2C3->SR1 & I2C_SR1_ADDR)) {
		wait_i2c
	}
	i2c_clear_sr();
	
	wait_i2c_init
	while(!(I2C3->SR1 & I2C_SR1_RXNE)) {
		wait_i2c
	}
	uint8_t HighTemperature = I2C3->DR;
	
	I2C3->CR1 &= ~I2C_CR1_ACK;
	I2C3->CR1 |= I2C_CR1_STOP;
	wait_i2c_init
	while(!(I2C3->SR1 & I2C_SR1_RXNE)) {
		wait_i2c
	}
	uint8_t LowTemperature = I2C3->DR;

// v For Tests
//  #define temp 0x300 // 20.0
//	#define temp 0xA0 // 20.0
//	#define temp 0x649 // -54.8
//	HighTemperature = (temp >> 3) & 0xFF;
//	LowTemperature = (temp << 5) & 0xFF;
// ^ For Tests

	uint16_t TemperatureHex = ((HighTemperature << 8) | LowTemperature) >> 5;

	int16_t Temperature = (TemperatureHex * 5 / 4);
	
	if (HighTemperature & 0x80) { // Если отрицательная
			Temperature = ((0x7FF - TemperatureHex + 1) * -5 / 4) ;
	}
	
	coreCPU.TermoPCB = Temperature;

//	printf("TermoPCB: %d \n", coreCPU.TermoPCB);
	
	coreFlags.flagGetTermoSensor = flagDisable;
}
