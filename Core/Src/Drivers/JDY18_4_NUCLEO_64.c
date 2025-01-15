/*
 *  JDY18_4_NUCLEO_64.c
 *
 *  João Vitor de M.G. Rosmaninho <jvrosmaninho@ufmg.br>,
 *  Lucas Soares de Salles <lucas-ss-salles@ufmg.br>,
 *  Stephanie Costa de Avelar <stephanieavelar@ufmg.br>
 *
 *
 *  Version 1.0 - API with the following implemented functions:
 *  void JDY18Driver_Init(JDY18_HandleTypeDef* handler);
 *  void JDY18Driver_SendData(UART_HandleTypeDef* huart, char *data);
 *  void JDY18Driver_SetName(UART_HandleTypeDef* huart, char *name);
 *  void JDY18Driver_SetBaudRate(UART_HandleTypeDef* huart, BaudRate_t baudRate);
 *  void JDY18Driver_SetRole(UART_HandleTypeDef* huart, RoleParam_t role);
 *  void JDY18Driver_SetParity(UART_HandleTypeDef* huart, ParityParam_t parity);
 *  void JDY18Driver_SetStopBit(UART_HandleTypeDef* huart, uint8_t stopBit);
 *  void JDY18Driver_InquireDevices(UART_HandleTypeDef* huart);
 *  void JDY18Driver_GetScannedDevices(scan_t* scan);
 *  void JDY18Driver_LoadDeviceInfo(char* start, char* end, device_t* device);
 *  void JDY18Driver_ParseScanResponse(char* scanResponse, scan_t* scan);
 *  void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
 *
 *  File provided by professor Ricardo O. Duarte <ricardoduarte@ufmg.br> for embedded systems programming course.
 *	Copyrighted to students:
 *	Pierre Victor
 *  Mariana Leite
 *   *
 *  Created on: 18 de dez de 2024
 *  Institution: UFMG
 *  This API contains functions to provide the use of some hardware resources
 *  from the JDY18 module available at:
 *  https://www.makerhero.com/produto/modulo-bluetooth-ble-v4-2-jdy-18/
 */

#include "Drivers/JDY18_4_NUCLEO_64.h"

char *atInstructions[] = {
	"AT+NAME",
	"AT+BAUD",
	"AT+ROLE",
	"AT+PARITY",
	"AT+USTP",
	"AT+INQ"};

uint8_t uartBuffer[MAX_SIZE_UART_BUFFER];

scan_t gScan;

void JDY18Driver_Init(JDY18_HandleTypeDef *handler)
{
	JDY18Driver_SetPerm(handler->huart);
	JDY18Driver_SetName(handler->huart, handler->name);
	JDY18Driver_SetRole(handler->huart, handler->role);
	JDY18Driver_SetBaudRate(handler->huart, handler->baudRate);
	JDY18Driver_SetParity(handler->huart, handler->parity);
	JDY18Driver_SetStopBit(handler->huart, handler->stopBit);

	HAL_Delay(200);

	gScan.size = 0;
	memset(uartBuffer, 0, sizeof(uartBuffer));

	__HAL_UART_ENABLE_IT(handler->huart, UART_IT_IDLE);
	HAL_UART_Receive_DMA(handler->huart, uartBuffer, sizeof(uartBuffer));
}

void JDY18Driver_SendData(UART_HandleTypeDef *huart, char *data)
{
	char package[MAX_SIZE_DATA + 4];
	memset(package, 0, MAX_SIZE_DATA + 4);
	sprintf(package, "%s\r\n", data);
	HAL_UART_Transmit(huart, (uint8_t *)package, strlen(package), HAL_MAX_DELAY);
}

void JDY18Driver_SetPerm(UART_HandleTypeDef *huart)
{
	char *instruction = "AT+PERM";
	char data[MAX_SIZE_DATA];
	memset(data, 0, MAX_SIZE_DATA);
	sprintf(data, "%s%s", instruction, "11111");
	JDY18Driver_SendData(huart, data);
}

void JDY18Driver_SetName(UART_HandleTypeDef *huart, char *name)
{
	char *instruction = atInstructions[SET_NAME];
	char data[MAX_SIZE_DATA];
	memset(data, 0, MAX_SIZE_DATA);
	sprintf(data, "%s%s", instruction, name);
	JDY18Driver_SendData(huart, data);
}

void JDY18Driver_SetBaudRate(UART_HandleTypeDef *huart, BaudRate_t baudRate)
{
	char *instruction = atInstructions[SET_BAUD_RATE];
	char data[MAX_SIZE_DATA];
	memset(data, 0, MAX_SIZE_DATA);
	sprintf(data, "%s%d", instruction, baudRate);
	JDY18Driver_SendData(huart, data);
}

void JDY18Driver_SetRole(UART_HandleTypeDef *huart, RoleParam_t role)
{
	char *instruction = atInstructions[SET_ROLE];
	char data[MAX_SIZE_DATA];
	memset(data, 0, MAX_SIZE_DATA);
	sprintf(data, "%s%d", instruction, role);
	JDY18Driver_SendData(huart, data);
}

void JDY18Driver_SetParity(UART_HandleTypeDef *huart, ParityParam_t parity)
{
	char *instruction = atInstructions[SET_PARITY];
	char data[MAX_SIZE_DATA];
	memset(data, 0, MAX_SIZE_DATA);
	sprintf(data, "%s%d", instruction, parity);
	JDY18Driver_SendData(huart, data);
}

void JDY18Driver_SetStopBit(UART_HandleTypeDef *huart, uint8_t stopBit)
{
	char *instruction = atInstructions[SET_STOP_BIT];
	char data[MAX_SIZE_DATA];
	memset(data, 0, MAX_SIZE_DATA);
	sprintf(data, "%s%d", instruction, stopBit);
	JDY18Driver_SendData(huart, data);
}
//
void JDY18Driver_InquireDevices(UART_HandleTypeDef *huart)
{
	char *instruction = atInstructions[MASTER_SCAN_SLAVE];
	char data[MAX_SIZE_DATA];
	memset(data, 0, MAX_SIZE_DATA);
	sprintf(data, "%s", instruction);
	JDY18Driver_SendData(huart, data);
}

void JDY18Driver_GetScannedDevices(scan_t *scan)
{
	*scan = gScan;
}

void JDY18Driver_LoadDeviceInfo(char *start, char *end, device_t *device)
{
	size_t size = end - start;
	char temp[size];
	memcpy(temp, start, size);

	char *macAddressPointer = temp + 7;
	char *rssiPointer = macAddressPointer + MAC_ADDRESS_SIZE + 1;
	char *namePointer = strstr(rssiPointer, ",") + 1;

	size_t rssiSize = namePointer - rssiPointer - 1;
	char rssiStr[rssiSize];
	memcpy(rssiStr, rssiPointer, rssiSize);

	memcpy(device->mac, macAddressPointer, MAC_ADDRESS_SIZE);
	memcpy(device->name, namePointer, MAX_DEVICE_NAME_SIZE);
	device->rssi = atoi(rssiStr);
}

void JDY18Driver_ParseScanResponse(char *scanResponse, scan_t *scan)
{
	char *start, *end;
	scan->size = 0;

	if ((start = strstr(scanResponse, INIT_MODULE_RESPONSE_SCAN)))
	{
		while ((end = strstr(start + 1, INIT_MODULE_RESPONSE_SCAN)))
		{
			JDY18Driver_LoadDeviceInfo(start, end, &scan->devices[scan->size]);
			start = end;
			scan->size++;
		}
		if ((end = strstr(start + 1, END_RESPONSE_SCAN)))
		{
			JDY18Driver_LoadDeviceInfo(start, end, &scan->devices[scan->size]);
			scan->size++;
		}
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
	{
		__HAL_UART_CLEAR_IDLEFLAG(huart);

		if (strstr((char *)uartBuffer, END_RESPONSE_SCAN))
		{
			HAL_UART_DMAStop(huart);

			JDY18Driver_ParseScanResponse((char *)uartBuffer, &gScan);

			memset(uartBuffer, 0, sizeof(uartBuffer));
			HAL_UART_Receive_DMA(huart, uartBuffer, sizeof(uartBuffer));
		}
	}
}
