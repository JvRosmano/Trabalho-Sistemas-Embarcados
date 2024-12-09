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

int8_t HMC5883L_Init(HMC5883LScale_t scale)
	{
	int8_t state;
	i2c_writeByte(HMC5883L_ADDRESS, COMPASS_MODE_REGISTER, 0x00);

	if(state==-1){return -1;}

	i2c_writeByte(HMC5883L_ADDRESS, 0x00, 0xD0);

	if(state==-1){return -1;}

	switch(scale)
	    {
		case HMC5883L_RANGE_0_88GA:
			m_Scale = 0.073f;
		    break;

		case HMC5883L_RANGE_1_3GA:
			m_Scale = 0.92f;
		    break;

		case HMC5883L_RANGE_1_9GA:
			m_Scale = 1.2f;
		    break;

		case HMC5883L_RANGE_2_5GA:
			m_Scale = 1.52f;
		    break;

		case HMC5883L_RANGE_4GA:
			m_Scale = 2.27f;
		    break;

		case HMC5883L_RANGE_4_7GA:
			m_Scale = 2.56f;
		    break;

		case HMC5883L_RANGE_5_7GA:
			m_Scale = 3.03f;
		    break;

		case HMC5883L_RANGE_8_1GA:
			m_Scale = 4.35f;
		    break;

		default:
		    break;
	    }

	state = i2c_writeByte(HMC5883L_ADDRESS, COMPASS_CONFIG_REGISTER_B, scale);
	if(state==-1){return -1;}
	return 0;
}

int8_t update_HMC5883L(void)
	{

	int8_t state;
	state=i2c_ReadMulti(HMC5883L_ADDRESS, 0x03, 6, (char *)gaus_data);
	if(state==-1){return -1;}
	return 0;
}

float getGausX(void)
	{
	uint16_t data=gaus_data[0]<<8|gaus_data[1];
	float g=data*m_Scale;
	return g;
}

float getGausY(void)
	{
	uint16_t data=gaus_data[4]<<8|gaus_data[5];
	float g=data*m_Scale;
	return g;
}
*/

void HMC5883L_Init(I2C_HandleTypeDef huart){
	 uint8_t RegSettingA = HMC5883l_Enable_A;
	 uint8_t RegSettingB = HMC5883l_Enable_B;
	 uint8_t RegSettingMR = HMC5883l_MR;
	 HAL_I2C_Mem_Write(&huart, HMC5883L_ADDRESS, 0x00 , 1, &RegSettingA , 1, 100);
	 HAL_I2C_Mem_Write(&huart, HMC5883L_ADDRESS, 0x01 , 1, &RegSettingB , 1, 100);
	 HAL_I2C_Mem_Write(&huart, HMC5883L_ADDRESS, 0x02 , 1, &RegSettingMR , 1, 100);
}
#endif
