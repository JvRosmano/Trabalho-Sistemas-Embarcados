/*
 *  HMC5883L_4_NUCLEO_64.c
 *  Copyright (C) 2024
 *  João Vitor de M.G. Rosmaninho <jvrosmaninho@ufmg.br>,
 *  Lucas Soares de Salles <lucas-ss-salles@ufmg.br>,
 *  Stephanie Costa de Avelar <stephanieavelar@ufmg.br>
 *
 *  Version 1.0 - API with the following implemented function:
 *  HMC5883L_Init(I2C_HandleTypeDef huart);
 *  HMC5883L_GetPosition(I2C_HandleTypeDef huart, Position *position);
 *  HMC5883L_Read(I2C_HandleTypeDef huart, uint8_t *buffer_x, uint8_t *buffer_y);
 *  HMC5883L_FilterData(uint8_t *buffer);
 *  HMC5883L_GetMeanData(uint8_t *buffer);
 *	HMC5883_HandleAngle(float angle);
 *  Based on notes from professor Ricardo O. Duarte <ricardoduarte@ufmg.br> for embedded systems programming course.
 *
 *
 *  Created on: 6 de dez de 2024
 *  Institution: UFMG
 *  This API contain functions to provide use of some hardware resources from HMC5883L:
 *  https://www.makerhero.com/produto/modulo-bussola-eletronica-hmc5883l
 */

#ifndef HMC5883L_4_NUCLEO_64_H_
#define HMC5883L_4_NUCLEO_64_H_

#include "HMC5883L_4_NUCLEO_64.h"

void HMC5883L_Init(I2C_HandleTypeDef huart)
{
	uint8_t data = (COMPASS_SAMPLE8 | COMPASS_RATE15 | COMPASS_MEASURE_NORMAL);
	uint8_t ScaleMode = COMPASS_SCALE_130;
	uint8_t Measure = COMPASS_CONTINUOUS;
	HAL_I2C_Mem_Write(&huart, HMC5883L_ADDRESS, COMPASS_CONFIG_REGISTER_A, 1, &data, 1, 100);
	HAL_I2C_Mem_Write(&huart, HMC5883L_ADDRESS, COMPASS_CONFIG_REGISTER_B, 1, &ScaleMode, 1, 100);
	HAL_I2C_Mem_Write(&huart, HMC5883L_ADDRESS, COMPASS_MODE_REGISTER, 1, &Measure, 1, 100);
}

int16_t HMC5883L_GetMeanData(int16_t *buffer)
{
	int16_t mean = 0;
	for (int i = 0; i < 8; i++)
	{
		mean += buffer[i];
	}
	return (mean / 8);
}

int16_t HMC5883L_FilterData(int16_t *buffer)
{
	uint8_t min = 200;
	for (int i = 1; i < 8; i++)
	{
		if ((abs(buffer[i] - buffer[i - 1])) > min)
		{
			buffer[i] = buffer[i - 1];
		}
	}
	return HMC5883L_GetMeanData(buffer);
}

void HMC5883L_Read(I2C_HandleTypeDef huart, int16_t *buffer_t_x, int16_t *buffer_t_y)
{
	uint8_t buffer[6];
	for (int i = 0; i < 8; i++)
	{
		HAL_I2C_Mem_Read(&huart, HMC5883L_ADDRESS, Data_Output_X_MSB, I2C_MEMADD_SIZE_8BIT, (uint8_t *)&buffer, 6, 100);
		buffer_t_x[i] = ((buffer[0] << 8) | buffer[1]);
		HAL_I2C_Mem_Read(&huart, HMC5883L_ADDRESS, Data_Output_Y_MSB, I2C_MEMADD_SIZE_8BIT, (uint8_t *)&buffer, 6, 100);
		buffer_t_y[i] = ((buffer[0] << 8) | buffer[1]);
	}
}

void HMC5883L_GetPosition(I2C_HandleTypeDef huart, Position *position)
{
	int16_t buffer_x[8];
	int16_t buffer_y[8];
	HMC5883L_Read(huart, &position->x, &position->y);
	position->x = HMC5883L_FilterData(buffer_x);
	position->y = HMC5883L_FilterData(buffer_y);
	position->angle = L293D_rad2Degree((float)atan2(position->y, position->x));
}
/*
 * Trata ângulo para estar entre -180° e 180°.
 */
float HMC5883_HandleAngle(float angle)
{
	// Converte radianos para graus.
	angle = L293D_rad2Degree(angle);
	// Adequar nos limites
	if (angle > 180)
		angle = 180;
	if (angle < -180)
		angle = -180;
	return angle;
}

#endif
