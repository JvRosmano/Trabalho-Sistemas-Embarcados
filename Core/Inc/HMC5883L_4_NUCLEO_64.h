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

typedef struct
{
  float x;
  float y;
  float angle;
} Ponto;

#define HMC5883L_ADDRESS (0x1E)
// CONTROL REG A
#define HMC5883L_Enable_A (0x70)
// CONTROL REG B
#define HMC5883L_Enable_B (0xA0)
// MODE REGISTER
#define HMC5883L_MR (0x00)
#ifndef HMC5883L_4_NUCLEO_64_H_
#define HMC5883L_4_NUCLEO_64_H_
#include "stdint.h"
#include "main.h"

void HMC5883L_Init(I2C_HandleTypeDef huart);

float HMC5883L_FilterAxisData(uint8_t *buffer);

#endif
