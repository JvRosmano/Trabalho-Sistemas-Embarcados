/*
 *  Position.h
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

#ifndef __LOCATION_SERVICE_H
#define __LOCATION_SERVICE_H

#define MASTER_BLE_NAME "MASTERBOAT"
#define SLAVE_BEACON_NAME_B1 "PSE2022_B1"
#define SLAVE_BEACON_NAME_B2 "PSE2022_B2"
#define SLAVE_BEACON_NAME_B3 "PSE2022_B3"
#define PRECISION_BLE_METERS 0.5

#define MEASURED_POWER -82

#include "stm32f4xx.h"

typedef struct {
	float latitude;
	float longitude;
} location_t;

/**
 * @brief Initialize location service.
 *
 * @param huart UART_HandleTypeDef pointer to serial handler structure.
 * @param htim TIM_HandleTypeDef pointer to timer handler structure.
 */
void LocationService_Init(UART_HandleTypeDef* huart, TIM_HandleTypeDef* htim);

/**
 * @brief Calculate the distance between the beacon and the master.
 *
 * @param rssi RSSI of the beacon.
 * @return float Distance between the beacon and the master.
 */
float LocationService_CalculateDistance(int rssi);

/**
 * @brief Calculates and updates the system location.
 *
 */
void LocationService_UpdateLocation();

/**
 * @brief Get the Location of the boat.
 *
 * @return location_t with latitude and longitude in Universal Transversa de Mercator.
 */
location_t LocationService_GetLocation();

/**
 * @brief Get the angle between the arrival and the boat.
 *
 * @return float Calculated angle.
 */
float LocationService_GetArrivalAngle();

/**
 * @brief Inform if the boat is in the destiny.
 * The precision is PRECISION_BLE_METERS, you can define in this file.
 *
 * @return	true if the boat is in the destiny, false otherwise.
 */
uint8_t LocationService_IsInDestiny();

#endif /* __LOCATION_SERVICE_H */
