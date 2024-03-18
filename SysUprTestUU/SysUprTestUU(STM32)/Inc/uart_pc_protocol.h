#ifndef __UART_PC_PROTOCOL_H
#define __UART_PC_PROTOCOL_H

#include "main.h"

///////////////////////////////////////////////////////
#define CMD_ADDR_PCB 						0x20

///////////////////////////////////////////////////////
#define CMD_GET_TRM_PCB 				0x0001
///////////////////////////////////////////////////////
#define CMD_USART_PCB_CONF 			0x0100
#define CMD_USART_PCB_SEND 			0x0101
///////////////////////////////////////////////////////
#define CMD_RS485_PCB_CONF 			0x0200
#define CMD_RS485_PCB_SEND 			0x0201
///////////////////////////////////////////////////////
#define CMD_SPI_PCB_CONF 				0x0300
#define CMD_SPI_PCB_SEND 				0x0301
///////////////////////////////////////////////////////
#define CMD_UIM_OUT1_ON 				0x0400
#define CMD_UIM_OUT1_OFF 				0x0401
#define CMD_UIM_OUT1_EN 				0x0402
#define CMD_UIM_OUT1_DIS 				0x0403
#define CMD_UIM_OUT2_ON 				0x0404
#define CMD_UIM_OUT2_OFF 				0x0405
#define CMD_UIM_OUT2_EN 				0x0406
#define CMD_UIM_OUT2_DIS 				0x0407
///////////////////////////////////////////////////////
#define CMD_ADDR_SET 						0x0500
///////////////////////////////////////////////////////
#define CMD_UIM_IN1_GET_PARAM		0x0600
#define CMD_UIM_IN2_GET_PARAM		0x0601
///////////////////////////////////////////////////////
#define CMD_VOLT1_SET_PARAM			0x0701
#define CMD_VOLT2_SET_PARAM			0x0702
#define CMD_VOLT3_SET_PARAM			0x0703
#define CMD_VOLT4_SET_PARAM			0x0704
#define CMD_VOLT5_SET_PARAM			0x0705
#define CMD_VOLT6_SET_PARAM			0x0706
#define CMD_VOLT7_SET_PARAM			0x0707
#define CMD_VOLT8_SET_PARAM			0x0708

#define CMD_VOLT1_ON						0x0711
#define CMD_VOLT2_ON						0x0712
#define CMD_VOLT3_ON						0x0713
#define CMD_VOLT4_ON						0x0714
#define CMD_VOLT5_ON						0x0715
#define CMD_VOLT6_ON						0x0716
#define CMD_VOLT7_ON						0x0717
#define CMD_VOLT8_ON						0x0718

#define CMD_VOLT1_OFF						0x0721
#define CMD_VOLT2_OFF						0x0722
#define CMD_VOLT3_OFF						0x0723
#define CMD_VOLT4_OFF						0x0724
#define CMD_VOLT5_OFF						0x0725
#define CMD_VOLT6_OFF						0x0726
#define CMD_VOLT7_OFF						0x0727
#define CMD_VOLT8_OFF						0x0728
///////////////////////////////////////////////////////
#define CMD_INT_ALL_CLEAR				0x0800

#define CMD_INT1_CLEAR					0x0801
#define CMD_INT2_CLEAR					0x0802
#define CMD_INT3_CLEAR					0x0803
#define CMD_INT4_CLEAR					0x0804
#define CMD_INT5_CLEAR					0x0805
#define CMD_INT6_CLEAR					0x0806
#define CMD_INT7_CLEAR					0x0807
#define CMD_INT8_CLEAR					0x0808

#define CMD_INT1_SET						0x0811
#define CMD_INT2_SET						0x0812
#define CMD_INT3_SET						0x0813
#define CMD_INT4_SET						0x0814
#define CMD_INT5_SET						0x0815
#define CMD_INT6_SET						0x0816
#define CMD_INT7_SET						0x0817
#define CMD_INT8_SET						0x0818
///////////////////////////////////////////////////////
#define CMD_VOLT1_GET_PARAM			0x0901
#define CMD_VOLT2_GET_PARAM			0x0902
#define CMD_VOLT3_GET_PARAM			0x0903
#define CMD_VOLT4_GET_PARAM			0x0904
#define CMD_VOLT5_GET_PARAM			0x0905
#define CMD_VOLT6_GET_PARAM			0x0906
#define CMD_VOLT7_GET_PARAM			0x0907
#define CMD_VOLT8_GET_PARAM			0x0908
///////////////////////////////////////////////////////
#define CMD_SR_GET_PARAM				0x0A01
///////////////////////////////////////////////////////
#define CMD_LED_GET_PARAM				0x0B00
#define CMD_LED1_GET_PARAM			0x0B01
#define CMD_LED2_GET_PARAM			0x0B02
#define CMD_LED3_GET_PARAM			0x0B03
#define CMD_LED4_GET_PARAM			0x0B04
#define CMD_LED5_GET_PARAM			0x0B05
#define CMD_LED6_GET_PARAM			0x0B06
///////////////////////////////////////////////////////

#endif 
