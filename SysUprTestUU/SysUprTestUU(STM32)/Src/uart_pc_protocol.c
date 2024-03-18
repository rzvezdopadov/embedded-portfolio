#include "uart_pc_protocol.h"

void bufPCCopyAddrCommand(void) {
	for (uint16_t i=0; i<3; i++) { bufPC.tx[i] = bufPC.rx[i]; }
	bufPC.tx_count = 3;
}

void bufPCAddByte(uint8_t value) {
	bufPC.tx[bufPC.tx_count] = value;
	bufPC.tx_count += 1;
}

void bufPCAddWord(uint16_t value) {
	bufPC.tx[bufPC.tx_count] 	 = (value >> 8) & 0xFF;
	bufPC.tx[bufPC.tx_count+1] = value & 0xFF;
	bufPC.tx_count += 2;
}

void bufPCAddDWord(uint32_t value) {
	bufPC.tx[bufPC.tx_count] 	 = (value >> 24) & 0xFF;
	bufPC.tx[bufPC.tx_count+1] = (value >> 16) & 0xFF;
	bufPC.tx[bufPC.tx_count+2] = (value >> 8) & 0xFF;
	bufPC.tx[bufPC.tx_count+3] = value & 0xFF;
	bufPC.tx_count += 4;
}

uint32_t getDWordFromArr(uint8_t *arr) {
	uint32_t value = 0;
	
	value |=  *(arr + 3) << 24;
	value |=  *(arr + 2) << 16;
	value |=  *(arr + 1) << 8;
	value |=  *(arr);

	return value;
}

uint16_t getWordFromArr(uint8_t *arr) {
	uint32_t value = 0;
	
	value |=  *(arr + 1) << 8;
	value |=  *(arr);

	return value;
}

void uartPCSendStr() {
	modbusAddCRC(bufPC.tx, bufPC.tx_count);
	uartPCSendStrDMA(bufPC.tx_count + 2);
}

void uart_pc_parse(void) {
	if (!coreFlags.enableUartPC) return;
	
	if ((bufPC.rx[0] == CMD_ADDR_PCB) & modbusTestCRC(bufPC.rx, bufPC.rx_count)) {
		bufPCCopyAddrCommand();
		
		uint16_t command = (bufPC.rx[1] << 8) | bufPC.rx[2];
				
		switch (command) {
			///////////////////////////////////////////////////////			
			case CMD_GET_TRM_PCB: {
				bufPCAddWord(coreCPU.TermoPCB);
				uartPCSendStr();
			} break;
			///////////////////////////////////////////////////////	
			case CMD_USART_PCB_CONF: {
				
			} break;
			case CMD_USART_PCB_SEND: {
				
			} break;
			///////////////////////////////////////////////////////
			case CMD_RS485_PCB_CONF: {
				
			} break;
			case CMD_RS485_PCB_SEND: {
				
			} break;
			///////////////////////////////////////////////////////
			case CMD_SPI_PCB_CONF: {
				
			} break;
			case CMD_SPI_PCB_SEND: {
				
			} break;
			///////////////////////////////////////////////////////		
			case CMD_UIM_OUT1_ON: {
				uimOut1_on(getDWordFromArr(&bufPC.rx[3]), getDWordFromArr(&bufPC.rx[7]));
				uartPCSendStr();
			} break;
			case CMD_UIM_OUT1_OFF: {
				uimOut1_off();
				uartPCSendStr();
			} break;
			case CMD_UIM_OUT1_EN: {
				uimOut1_enable;
				uartPCSendStr();
			} break;
			case CMD_UIM_OUT1_DIS: {
				uimOut1_disable;
				uartPCSendStr();
			} break;
			case CMD_UIM_OUT2_ON: {
				uimOut2_on(getDWordFromArr(&bufPC.rx[3]), getDWordFromArr(&bufPC.rx[7]));
				uartPCSendStr();
			} break;
			case CMD_UIM_OUT2_OFF: {
				uimOut2_off();
				uartPCSendStr();
			} break;
			case CMD_UIM_OUT2_EN: {
				uimOut2_enable;
				uartPCSendStr();
			} break;
			case CMD_UIM_OUT2_DIS: {
				uimOut2_disable;
				uartPCSendStr();
			} break;
			///////////////////////////////////////////////////////		
			case CMD_ADDR_SET: {
				setAddr(getWordFromArr(&bufPC.rx[3]));
				uartPCSendStr();
			} break;
			///////////////////////////////////////////////////////	
			case CMD_UIM_IN1_GET_PARAM: {
				t_UIM *uim1 = getUIM1();
				bufPCAddDWord(uim1->pulseFreequency);
				bufPCAddDWord(uim1->pulseDuration);
				bufPCAddDWord(uim1->pulsePeriod);
				bufPCAddDWord(uim1->pulseDutyCyckle);
				uartPCSendStr();
			} break;
			case CMD_UIM_IN2_GET_PARAM: {
				t_UIM *uim2 = getUIM2();
				bufPCAddDWord(uim2->pulseFreequency);
				bufPCAddDWord(uim2->pulseDuration);
				bufPCAddDWord(uim2->pulsePeriod);
				bufPCAddDWord(uim2->pulseDutyCyckle);
				uartPCSendStr();
			} break;
			///////////////////////////////////////////////////////
			case CMD_VOLT1_SET_PARAM: {
				volt1LevelSend(getWordFromArr(&bufPC.rx[3]));
				uartPCSendStr();
			} break;
			case CMD_VOLT2_SET_PARAM: {
				volt2LevelSend(getWordFromArr(&bufPC.rx[3]));
				uartPCSendStr();
			} break;
			case CMD_VOLT3_SET_PARAM: {
				volt3LevelSend(getWordFromArr(&bufPC.rx[3]));
				uartPCSendStr();
			} break;
			case CMD_VOLT4_SET_PARAM: {
				volt4LevelSend(getWordFromArr(&bufPC.rx[3]));
				uartPCSendStr();
			} break;
			case CMD_VOLT5_SET_PARAM: {
				volt5LevelSend(getWordFromArr(&bufPC.rx[3]));
				uartPCSendStr();
			} break;		
			case CMD_VOLT6_SET_PARAM: {
				volt6LevelSend(getWordFromArr(&bufPC.rx[3]));
				uartPCSendStr();
			} break;
			case CMD_VOLT7_SET_PARAM: {
				volt7LevelSend(getWordFromArr(&bufPC.rx[3]));
				uartPCSendStr();
			} break;
			case CMD_VOLT8_SET_PARAM: {
				volt8LevelSend(getWordFromArr(&bufPC.rx[3]));
				uartPCSendStr();
			} break;
			
			case CMD_VOLT1_ON: {
				volt1_en_on;
				uartPCSendStr();
			} break;
			case CMD_VOLT2_ON: {
				volt2_en_on;
				uartPCSendStr();
			} break;
			case CMD_VOLT3_ON: {
				volt3_en_on;
				uartPCSendStr();
			} break;		
			case CMD_VOLT4_ON: {
				volt4_en_on;
				uartPCSendStr();
			} break;
			case CMD_VOLT5_ON: {
				volt5_en_on;
				uartPCSendStr();
			} break;
			case CMD_VOLT6_ON: {
				volt6_en_on;
				uartPCSendStr();
			} break;
			case CMD_VOLT7_ON: {
				volt7_en_on;
				uartPCSendStr();
			} break;		
			case CMD_VOLT8_ON: {
				volt8_en_on;
				uartPCSendStr();
			} break;
			
			case CMD_VOLT1_OFF: {
				volt1_en_off;
				uartPCSendStr();
			} break;
			case CMD_VOLT2_OFF: {
				volt2_en_off;
				uartPCSendStr();
			} break;
			case CMD_VOLT3_OFF: {
				volt3_en_off;
				uartPCSendStr();
			} break;		
			case CMD_VOLT4_OFF: {
				volt4_en_off;
				uartPCSendStr();
			} break;
			case CMD_VOLT5_OFF: {
				volt5_en_off;
				uartPCSendStr();
			} break;
			case CMD_VOLT6_OFF: {
				volt6_en_off;
				uartPCSendStr();
			} break;
			case CMD_VOLT7_OFF: {
				volt7_en_off;
				uartPCSendStr();
			} break;		
			case CMD_VOLT8_OFF: {
				volt8_en_off;
				uartPCSendStr();
			} break;
			///////////////////////////////////////////////////////		
			case CMD_INT_ALL_CLEAR: {
				clearAllINT();
				uartPCSendStr();
			} break;
			
			case CMD_INT1_CLEAR: {
				setINT1(0);
				uartPCSendStr();
			} break;
			case CMD_INT2_CLEAR: {
				setINT2(0);
				uartPCSendStr();
			} break;
			case CMD_INT3_CLEAR: {
				setINT3(0);
				uartPCSendStr();
			} break;		
			case CMD_INT4_CLEAR: {
				setINT4(0);
				uartPCSendStr();
			} break;
			case CMD_INT5_CLEAR: {
				setINT5(0);
				uartPCSendStr();
			} break;
			case CMD_INT6_CLEAR: {
				setINT6(0);
				uartPCSendStr();
			} break;
			case CMD_INT7_CLEAR: {
				setINT7(0);
				uartPCSendStr();
			} break;		
			case CMD_INT8_CLEAR: {
				setINT8(0);
				uartPCSendStr();
			} break;
			
			case CMD_INT1_SET: {
				setINT1(getDWordFromArr(&bufPC.rx[3]));
				uartPCSendStr();
			} break;
			case CMD_INT2_SET: {
				setINT2(getDWordFromArr(&bufPC.rx[3]));
				uartPCSendStr();
			} break;
			case CMD_INT3_SET: {
				setINT3(getDWordFromArr(&bufPC.rx[3]));
				uartPCSendStr();
			} break;		
			case CMD_INT4_SET: {
				setINT4(getDWordFromArr(&bufPC.rx[3]));
				uartPCSendStr();
			} break;
			case CMD_INT5_SET: {
				setINT5(getDWordFromArr(&bufPC.rx[3]));
				uartPCSendStr();
			} break;
			case CMD_INT6_SET: {
				setINT6(getDWordFromArr(&bufPC.rx[3]));
				uartPCSendStr();
			} break;
			case CMD_INT7_SET: {
				setINT7(getDWordFromArr(&bufPC.rx[3]));
				uartPCSendStr();
			} break;		
			case CMD_INT8_SET: {
				setINT8(getDWordFromArr(&bufPC.rx[3]));
				uartPCSendStr();
			} break;
			///////////////////////////////////////////////////////		
			case CMD_VOLT1_GET_PARAM: {
				bufPCAddDWord(paramValue.Volt1);
				uartPCSendStr();
			} break;
			case CMD_VOLT2_GET_PARAM: {
				bufPCAddDWord(paramValue.Volt2);
				uartPCSendStr();
			} break;
			case CMD_VOLT3_GET_PARAM: {
				bufPCAddDWord(paramValue.Volt3);
				uartPCSendStr();
			} break;		
			case CMD_VOLT4_GET_PARAM: {
				bufPCAddDWord(paramValue.Volt4);
				uartPCSendStr();
			} break;
			case CMD_VOLT5_GET_PARAM: {
				bufPCAddDWord(paramValue.Volt5);
				uartPCSendStr();
			} break;
			case CMD_VOLT6_GET_PARAM: {
				bufPCAddDWord(paramValue.Volt6);
				uartPCSendStr();
			} break;
			case CMD_VOLT7_GET_PARAM: {
				bufPCAddDWord(paramValue.Volt7);
				uartPCSendStr();
			} break;		
			case CMD_VOLT8_GET_PARAM: {
				bufPCAddDWord(paramValue.Volt8);
				uartPCSendStr();
			} break;
			///////////////////////////////////////////////////////		
			case CMD_SR_GET_PARAM: {
				bufPCAddDWord(getSR());
				uartPCSendStr();
			} break;
			///////////////////////////////////////////////////////	
			case CMD_LED_GET_PARAM: {
				bufPCAddWord(getLeds());
				uartPCSendStr();
			} break;
			case CMD_LED1_GET_PARAM: {
				bufPCAddWord(getLed1());
				uartPCSendStr();
			} break;
			case CMD_LED2_GET_PARAM: {
				bufPCAddWord(getLed2());
				uartPCSendStr();
			} break;
			case CMD_LED3_GET_PARAM: {
				bufPCAddWord(getLed3());
				uartPCSendStr();
			} break;		
			case CMD_LED4_GET_PARAM: {
				bufPCAddWord(getLed4());
				uartPCSendStr();
			} break;
			case CMD_LED5_GET_PARAM: {
				bufPCAddWord(getLed5());
				uartPCSendStr();
			} break;
			case CMD_LED6_GET_PARAM: {
				bufPCAddWord(getLed6());
				uartPCSendStr();
			} break;
			///////////////////////////////////////////////////////		
			default: {
				
			} break;
		}
	}

	coreFlags.enableUartPC = 0;
}



