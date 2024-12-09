/*
 *  HMC5883L_4_NUCLEO_64.h
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


#define HMC5883L_ADDRESS (0x1E << 1)
// CONTROL REG A
#define HMC5883l_Enable_A (0x78)
// CONTROL REG B
#define HMC5883l_Enable_B (0xA0)
// MODE REGISTER
#define HMC5883l_MR (0x00)
// HMC5883l - MSB / LSB ADDRESSES
#define HMC5883l_ADD_DATAX_MSB (0x03)
#define HMC5883l_ADD_DATAX_LSB (0x04)
#define HMC5883l_ADD_DATAZ_MSB (0x05)
#define HMC5883l_ADD_DATAZ_LSB (0x06)
#define HMC5883l_ADD_DATAY_MSB (0x07)
#define HMC5883l_ADD_DATAY_LSB (0x08)
// SUM (MSB + LSB) DEFINE
#define HMC5883l_ADD_DATAX_MSB_MULTI (HMC5883l_ADD_DATAX_MSB | 0x80)
#define HMC5883l_ADD_DATAY_MSB_MULTI (HMC5883l_ADD_DATAY_MSB | 0x80)
#define HMC5883l_ADD_DATAZ_MSB_MULTI (HMC5883l_ADD_DATAZ_MSB | 0x80)
#ifndef HMC5883L_4_NUCLEO_64_H_
#define HMC5883L_4_NUCLEO_64_H_
#include "stdint.h"
#include "main.h"

/*
 * Functions to control the SG90 servo motor and the DC Motor
 * In both functions in the future will be needed to convert values
 */


/*
#define COMPASS_CONFIG_REGISTER_B 0x01
#define COMPASS_MODE_REGISTER     0x02
#define HMC5883L_ADDRESS  0x1E

typedef enum{
	HMC5883L_RANGE_0_88GA	=0x00,
	HMC5883L_RANGE_1_3GA	=0x20,
	HMC5883L_RANGE_1_9GA	=0x40,
	HMC5883L_RANGE_2_5GA    =0x60,
	HMC5883L_RANGE_4GA      =0x80,
	HMC5883L_RANGE_4_7GA    =0xA0,
	HMC5883L_RANGE_5_7GA    =0xC0,
	HMC5883L_RANGE_8_1GA    =0xE0
} HMC5883LScale_t;

int8_t update_HMC5883L(void);

*/

void HMC5883L_Init(I2C_HandleTypeDef huart);

#endif
