/*
 *  HMC5883L_4_NUCLEO_64.c
 *  Copyright (C) 2024
 *  João Vitor de M.G. Rosmaninho <jvrosmaninho@ufmg.br>,
 *  Lucas Soares de Salles <lucas-ss-salles@ufmg.br>,
 *  Stephanie Costa de Avelar <stephanieavelar@ufmg.br>
 *
 *  Version 1.0 - API with the following implemented function:
 *  void L293D_SetPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period, uint16_t pulse);
 *  void SG90_SetPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period, uint16_t pulse);
 *
 *  Based on notes from professor Ricardo O. Duarte <ricardoduarte@ufmg.br> for embedded systems programming course.
 *
 *
 *  Created on: 18 de nov de 2024
 *  Institution: UFMG
 *  This API contain functions to provide use of some hardware resources
 *  from Motor shield 293D driver available at:
 *  https://www.makerhero.com/produto/motor-shield-l293d-driver-ponte-h-para-arduino/
 */

#ifndef HMC5883L_4_NUCLEO_64_H_
#define HMC5883L_4_NUCLEO_64_H_

#include "HMC5883L_4_NUCLEO_64.h"
#include "main.h"

/*
 * Função que recebe de um buffer 8 amostras, e aplica um filtro nas mesmas. Obtendo a média das amostras.
 */
float HMC5883L_FilterAxisData(uint8_t *buffer)
{
	float value;
	for (int i = 1; i < 8; i++)
	{
		if (abs(buffer[i] - buffer[i - 1]) < 10)
		{
			buffer[i] = buffer[i - 1];
		}
		value += buffer[i];
	}
	value += buffer[0];
	value = value / 8;
	return value;
}

/*
Inicia HMC5883L com as configurações padrões.
*/
void HMC5883L_Init(I2C_HandleTypeDef huart)
{
	HAL_I2C_Mem_Write(&huart, HMC5883L_ADDRESS, 0x00, 1, HMC5883L_Enable_A, 1, 100);
	HAL_I2C_Mem_Write(&huart, HMC5883L_ADDRESS, 0x01, 1, HMC5883L_Enable_B, 1, 100);
	HAL_I2C_Mem_Write(&huart, HMC5883L_ADDRESS, 0x02, 1, HMC5883L_MR, 1, 100);
}

#endif
