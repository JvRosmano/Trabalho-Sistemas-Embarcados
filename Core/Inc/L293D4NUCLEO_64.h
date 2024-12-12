/*
 *  L293D4NUCLEO_64.h
 *  Copyright (C) 2024
 *  João Vitor de M.G. Rosmaninho <jvrosmaninho@ufmg.br>,
 *  Lucas Soares de Salles <lucas-ss-salles@ufmg.br>,
 *  Stephanie Costa de Avelar <stephanieavelar@ufmg.br>
 *
 *  Version 1.1 - API with the following implemented function:
 *  void L293D_SetPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period, uint16_t pulse);
 *  void SG90_SetPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period, uint16_t pulse);
 *  uint16_t SG90_handlePulse(uint16_t, uint16_t);
 *  uint16_t DC_Motor_handlePulse(uint16_t, uint16_t);
 *  uint16_t SG90_angle2Pulse(float angle, uint16_t period);
 *  uint16_t SG90_handleAngle(float angle);
 *  float L293D_rad2Degree(float angleRad);
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

#define DUTY_CYCLE_MIN 0.035
#define DUTY_CYCLE_MAX 0.115
#ifndef L293D4NUCLEO_64_H_
#define L293D4NUCLEO_64_H_
#include "stdint.h"
#include "main.h"

/*
 * Functions to control the SG90 servo motor and the DC Motor
 * In both functions in the future will be needed to convert values
 */
void DC_Motor_SetPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period, uint16_t pulse);
void SG90_SetPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period, uint16_t pulse);
/*
 * É preciso tratar o pulso que é dado. O motor tem funcionamento de 0° a 180°.
 * Limitar o seu pulso no intervalo da largura de pulso de 0.7ms a 2.3ms.
 */
uint16_t SG90_handlePulse(uint16_t, uint16_t);
/*
 * É preciso tratar o pulso que é dado. O motor tem funcionamento de 0 a 100%.
 */
uint16_t DC_Motor_handlePulse(uint16_t, uint16_t);
/*
Função que receberá um ângulo e retornará o valor de pulso que o leme deve se movimentar para atender o ângulo.
*/
uint16_t SG90_angle2Pulse(float angle, uint16_t period);
/*
Função que irá tratar o ângulo recebibo para as faixas de 0 a 180°.
*/
uint16_t SG90_handleAngle(float angle);
/*
Converter graus para radianos.
*/
float L293D_rad2Degree(float angleRad);
#endif
