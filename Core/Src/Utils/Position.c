/*
 *  Position.c
 *
 *  João Vitor de M.G. Rosmaninho <jvrosmaninho@ufmg.br>,
 *  Lucas Soares de Salles <lucas-ss-salles@ufmg.br>,
 *  Stephanie Costa de Avelar <stephanieavelar@ufmg.br>
 *
 *
 *  Version 1.0 - API with the following implemented functions:
 *  void LocationService_Init(UART_HandleTypeDef *huart, TIM_HandleTypeDef* htim);
 *  float LocationService_CalculateDistance(int rssi);
 *	location_t LocationService_GetLocation();
 *	uint8_t LocationService_IsInDestiny();
 *	float LocationService_GetArrivalAngle();
 *
 *  File provided by professor Ricardo O. Duarte <ricardoduarte@ufmg.br> for embedded systems programming course.
 *	Copyrighted to students:
 *	Pierre Victor
 *  Mariana Leite
 *   *
 *  Created on: 18 de dez de 2024
 *  Institution: UFMG
 *  This API contains functions to use of some hardware resources
 *  from the JDY18 module.
 */

#include <Drivers/JDY18_4_NUCLEO_64.h>
#include <math.h>
#include <Utils/Position.h>
#include <Utils/Position_filter.h>

JDY18_HandleTypeDef bleHandler;

buffer_t b1Buffer;
buffer_t b2Buffer;
buffer_t b3Buffer;

/*
(lat, long)
Beacon (B1)  (-19.866581, -43.964787) > (7802949.9627924375, 608384.2009718714)
Chegada (B2) (-19.866733, -43.964666) > (7802933.062793205, 608396.7671230149)
Saida (B3)   (-19.866425, -43.964556) > (7802967.079134472, 608408.4941720127)
*/
location_t slaveBeaconLocationB1 = { 7802949.9627924375, 608384.2009718714 };
location_t slaveBeaconLocationB2 = { 7802933.062793205, 608396.7671230149 };
location_t slaveBeaconLocationB3 = { 7802967.079134472, 608408.4941720127 };
location_t masterLocation = { 0, 0 };

float trilaterationCalcCPartial = 0;
float trilaterationCalcFPartial = 0;

void LocationService_Init(UART_HandleTypeDef *huart)
{
	bleHandler.huart = huart;
	bleHandler.name = MASTER_BLE_NAME;
	bleHandler.baudRate = BAUD_230400;
	bleHandler.role = MASTER;
	bleHandler.parity = NO_PARITY;
	bleHandler.stopBit = 0;
	JDY18Driver_Init(&bleHandler);

	DataFilterService_InitBuffer(&b1Buffer);
	DataFilterService_InitBuffer(&b2Buffer);
	DataFilterService_InitBuffer(&b3Buffer);

	trilaterationCalcCPartial = - pow(slaveBeaconLocationB1.longitude, 2) + pow(slaveBeaconLocationB2.longitude, 2) - pow(slaveBeaconLocationB1.latitude, 2) + pow(slaveBeaconLocationB2.latitude, 2);
	trilaterationCalcFPartial = - pow(slaveBeaconLocationB2.longitude, 2) + pow(slaveBeaconLocationB3.longitude, 2) - pow(slaveBeaconLocationB2.latitude, 2) + pow(slaveBeaconLocationB3.latitude, 2);

	JDY18Driver_InquireDevices(bleHandler.huart);
}

float LocationService_CalculateDistance(int rssi)
{
	return pow(10, ((MEASURED_POWER - rssi) / 20));
}

void LocationService_UpdateLocation()
{
	scan_t scannedDevices;
	float b1Distance = -1, b2Distance = -1, b3Distance = -1;

	JDY18Driver_GetScannedDevices(&scannedDevices);

	for(size_t i = 0; i < scannedDevices.size; i++) {
		char* deviceName = scannedDevices.devices[i].name;
		int rssi = scannedDevices.devices[i].rssi;

		if(strstr(deviceName, SLAVE_BEACON_NAME_B1) != NULL) {
			b1Distance = DataFilterService_MovingAverage(&b1Buffer, LocationService_CalculateDistance(rssi));
		} else if(strstr(deviceName, SLAVE_BEACON_NAME_B2) != NULL) {
			b2Distance = DataFilterService_MovingAverage(&b2Buffer, LocationService_CalculateDistance(rssi));
		} else if(strstr(deviceName, SLAVE_BEACON_NAME_B3) != NULL) {
			b3Distance = DataFilterService_MovingAverage(&b3Buffer, LocationService_CalculateDistance(rssi));
		}
	}

	if (b1Distance != -1 && b2Distance != -1 && b3Distance != -1) {
		float trilaterationCalcA = -2*slaveBeaconLocationB1.longitude + 2*slaveBeaconLocationB2.longitude;
		float trilaterationCalcB = -2*slaveBeaconLocationB1.latitude + 2*slaveBeaconLocationB2.latitude;
		float trilaterationCalcC = pow(b1Distance, 2) - pow(b2Distance, 2) + trilaterationCalcCPartial;
		float trilaterationCalcD = -2*slaveBeaconLocationB2.longitude + 2*slaveBeaconLocationB3.longitude;
		float trilaterationCalcE = -2*slaveBeaconLocationB2.latitude + 2*slaveBeaconLocationB3.latitude;
		float trilaterationCalcF = pow(b2Distance, 2) - pow(b3Distance, 2) + trilaterationCalcFPartial;

		masterLocation.longitude = (trilaterationCalcC*trilaterationCalcE - trilaterationCalcF*trilaterationCalcB)/(trilaterationCalcE*trilaterationCalcA - trilaterationCalcB*trilaterationCalcD);
		masterLocation.latitude= (trilaterationCalcC*trilaterationCalcD - trilaterationCalcA*trilaterationCalcF)/(trilaterationCalcB*trilaterationCalcD - trilaterationCalcA*trilaterationCalcE);
	}

	JDY18Driver_InquireDevices(bleHandler.huart);
}

location_t LocationService_GetLocation()
{
	return masterLocation;
}

float LocationService_GetArrivalAngle()
{
	return atan((masterLocation.longitude - slaveBeaconLocationB2.longitude) / (masterLocation.latitude - slaveBeaconLocationB2.latitude)) * 180 / 3.14159265359 + 180;
}

uint8_t LocationService_IsInDestiny()
{
	return ((masterLocation.longitude - slaveBeaconLocationB2.longitude) < PRECISION_BLE_METERS) && ((masterLocation.latitude - slaveBeaconLocationB2.latitude) < PRECISION_BLE_METERS) ? 1 : 0;
}
