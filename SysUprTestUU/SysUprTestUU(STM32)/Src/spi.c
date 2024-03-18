#include "spi.h"

// SPI1 - AF5
// MOSI - PB5, MISO - PB4,
// CLK  - PB3, SS   - PA4,

#define dataRegSPI SPI1->DR

void spi_Init(void) {  //  SPI
	// Альтернативная функция порта
	GPIOA->AFR[0] |= (5<<GPIO_AFRL_AFSEL4_Pos);
	GPIOA->MODER |= GPIO_MODER_MODE4_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED4_Msk;
	
	GPIOB->AFR[0] |= (5<<GPIO_AFRL_AFSEL3_Pos) | (5<<GPIO_AFRL_AFSEL4_Pos) | (5<<GPIO_AFRL_AFSEL5_Pos);
	GPIOB->MODER |= GPIO_MODER_MODE3_1 | GPIO_MODER_MODE4_1 | GPIO_MODER_MODE5_1;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED3_Msk | GPIO_OSPEEDR_OSPEED4_Msk | GPIO_OSPEEDR_OSPEED5_Msk;
	
	// Настройки скоростей и битности
	SPI1->CR1 = SPI_CR1_LSBFIRST // первым шлется младший бит
								// | (3<<SPI_CR1_BR_Pos) // Делитель для SPI
								| SPI_CR1_SPE // разрешить SPI 
	;
	// Прерывания
	SPI1->CR2 = SPI_CR2_RXNEIE;
	// Установка приоритета и разрешение прерывания в NVIC
	NVIC_SetPriority(SPI1_IRQn, 0);
	NVIC_EnableIRQ(SPI1_IRQn);
		
	printf("SPI Init Ok!\n");
}
		
void SPI1_IRQHandler(void) {
		bufSPI.rx[bufSPI.rx_count] = dataRegSPI;	// Читаем значение
		dataRegSPI = bufSPI.tx[bufSPI.rx_count];	// Записываем новое значение		
		bufSPI.rx_count++;
}
