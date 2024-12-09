/*
 *  L293D4NUCLEO_64.c
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

#ifndef L293D4NUCLEO_64_H_
#define L293D4NUCLEO_64_H_
#include "L293D4NUCLEO_64.h"
#include "main.h"

/*
 * É preciso tratar o pulso que é dado. O motor tem funcionamento de 0 a 100%.
 */
uint16_t DC_Motor_handlePulse(uint16_t period, uint16_t pulse){
	if(pulse > period) pulse = period;
	if(0 < pulse) pulse = 0;
	return pulse;
}

void DC_Motor_SetPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period, uint16_t pulse){
	// Obtém pulso após tratamento de limites.
	pulse = DC_Motor_handlePulse(period, pulse);
	// Configura registradores para uso do PWM
	HAL_TIM_PWM_Stop(&timer, channel);
	TIM_OC_InitTypeDef sConfigOC;
	timer.Init.Period = period;
	HAL_TIM_PWM_Init(&timer);
	sConfigOC.OCMode = TIM_OCMODE_PWM2;
	sConfigOC.Pulse = pulse;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&timer, &sConfigOC, channel);
	HAL_TIM_PWM_Start(&timer, channel);
}


/*
 * É preciso tratar o pulso que é dado. O motor tem funcionamento de 0° a 180°.
 * Limitar o seu pulso no intervalo da largura de pulso de 0.7ms a 2.3ms.
 */
uint16_t SG90_handlePulse(uint16_t period, uint16_t pulse){
	/*
	 * Retorna o menor pulso se for inferior ao menor possível.
	 * Retorna o maior pulso se for superior ao maior possível.
	 * Retorna o pulso se estiver na faixa aceitável
	 */
	if(pulse < period*DUTY_CYCLE_MIN) pulse = period*DUTY_CYCLE_MIN;
	else if(pulse > period*DUTY_CYCLE_MAX) pulse = period*DUTY_CYCLE_MAX;
	return pulse;
}

void SG90_SetPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period, uint16_t pulse){
	// Obtém pulso após tratamento de limites.
	pulse = SG90_handlePulse(period, pulse);
	// Configura registradores para uso do PWM
	HAL_TIM_PWM_Stop(&timer, channel);
	TIM_OC_InitTypeDef sConfigOC;
	timer.Init.Period = period;
	HAL_TIM_PWM_Init(&timer);
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = pulse;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&timer, &sConfigOC, channel);
	HAL_TIM_PWM_Start(&timer, channel);
}
#endif
