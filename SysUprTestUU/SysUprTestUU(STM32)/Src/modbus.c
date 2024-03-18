#include "modbus.h"
 
///// Функции расчета контрольных сумм Modbus
#define modbusPolynom 0xA001
// Проверяет контрольные суммы, возвращает 1, если суммы верны
uint8_t modbusTestCRC(uint8_t *addr, uint16_t sizeArray) {
	uint16_t mbCRC = modbusCalcCRCwithTable(addr, sizeArray-2);				// Вызываем расчет контрольной суммы данных из массива
	uint16_t mbCRCrecive = (addr[sizeArray-1]<<8)+addr[sizeArray-2];	// Копируем контрольную сумму из имеющегося массива
	if (mbCRCrecive == mbCRC) {																				// Сравниваем контрольные суммы
		return 1;
	}
	return 0;
}

// Добавляет контрольную сумму, в хвост массива
void modbusAddCRC(uint8_t *addr, uint16_t sizeArray) {
	uint16_t mbCRC = modbusCalcCRCwithTable(addr, sizeArray); 			 // Вызываем расчет контрольной суммы данных из массива
	addr[sizeArray] 	= mbCRC; 																			 // Добавляем контрольную сумму в конец массива(младший байт)
	addr[sizeArray+1] = mbCRC>>8;																		 // (старший байт)
	//printf("size: %04X\n", mbCRC);
}

// Расчет контрольной суммы обычным методом
uint16_t modbusCalcCRC(uint8_t *addr, uint16_t sizeArray) {
	uint16_t mbCRC = 0xFFFF;																				// Записываем начальное значение массива
	
	for (uint16_t i=0;i<sizeArray;i++) {														// Цикл обработки данных побайтно
		mbCRC ^= addr[i];																							// XOR текущего значения и входного байта
		for(uint8_t j=0;j<8;j++) {																		// Цикл обработки данных побитно
			if ((mbCRC & 1) != 0) {																			// Если правый бит не = 1
				mbCRC >>= 1;																							// Сдвиг вправо
				mbCRC ^= modbusPolynom; 																	// XOR текущего значения с полиномом
			} else {
				mbCRC >>= 1;																							// Сдвиг вправо
			}
		} 
	}
	return mbCRC;
}

// Расчет контрольной суммы табличным методом(в 7 раз быстрее, обычного метода)
uint16_t modbusCalcCRCwithTable(uint8_t *addr, uint16_t sizeArray) {
	uint8_t uchCRCHi = 0xFF;  																		// Записываем начальное значение массива
  uint8_t uchCRCLo = 0xFF; 
	uint16_t uIndex; 																								// Значение счетчика
	
	for (uint16_t i=0;i<sizeArray;i++) {														// Цикл обработки данных побайтно
		uIndex = uchCRCHi ^ *addr++;																	
    uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex];
    uchCRCLo = auchCRCLo[uIndex];
	}
	return (uchCRCLo << 8 | uchCRCHi);
}












