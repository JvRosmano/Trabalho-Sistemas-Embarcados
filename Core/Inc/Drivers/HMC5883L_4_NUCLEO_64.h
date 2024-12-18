/*
 *  HMC5883L_4_NUCLEO_64.h
 *  Copyright (C) 2024
 *  João Vitor de M.G. Rosmaninho <jvrosmaninho@ufmg.br>,
 *  Lucas Soares de Salles <lucas-ss-salles@ufmg.br>,
 *  Stephanie Costa de Avelar <stephanieavelar@ufmg.br>
 *
 *  Version 1.0 - API with the following implemented function:
 *  void HMC5883L_Init(I2C_HandleTypeDef huart);
 *  int16_t meanData(int16_t* buffer);
 *  int16_t FilterData(int16_t* buffer);
 *  void CompassReadAxis (I2C_HandleTypeDef huart, int16_t* buffer_t_x, int16_t* buffer_t_y);
 *  float VectorToAngle (int16_t* PosX, int16_t* PosY);
 *  void getDirectionBoat (I2C_HandleTypeDef huart, int16_t* PosX, int16_t* PosY, float* AngleXY);
 *
 *  Based on notes from professor Ricardo O. Duarte <ricardoduarte@ufmg.br> for embedded systems programming course.
 *
 *
 *  Created on: 6 de dez de 2024
 *  Institution: UFMG
 *  This API contain functions to provide use of some hardware resources from HMC5883L:
 *  https://www.makerhero.com/produto/modulo-bussola-eletronica-hmc5883l
 */

#define HMC5883L_ADDRESS (0x3D)

#define COMPASS_CONFIG_REGISTER_A 0x00
#define COMPASS_CONFIG_REGISTER_B 0x01
#define COMPASS_MODE_REGISTER     0x02
#define COMPASS_DATA_REGISTER     0x03

#define Data_Output_X_MSB 0x03
#define Data_Output_X_LSB 0x04
#define Data_Output_Z_MSB 0x05
#define Data_Output_Z_LSB 0x06
#define Data_Output_Y_MSB 0x07
#define Data_Output_Y_LSB 0x08

#define COMPASS_SAMPLE1 0x00
#define COMPASS_SAMPLE8 0x60

#define COMPASS_RATE15   0x10 // 15Hz (Default)

#define COMPASS_MEASURE_NORMAL   0x00 // Normal measurement configuration (Default)

#define COMPASS_SCALE_88  0x00
#define COMPASS_SCALE_130  0x20 //1.3 Ga (Default)

#define COMPASS_CONTINUOUS 0x00  //Continuous-Measurement Mode.

#ifndef HMC5883L_4_NUCLEO_64_H_
#define HMC5883L_4_NUCLEO_64_H_
#include "stdint.h"
#include "main.h"

typedef struct {
	int16_t x;
	int16_t y;
	float angle;
} Position;

void HMC5883L_Init(I2C_HandleTypeDef huart);

void getDirectionBoat (I2C_HandleTypeDef huart, int16_t* PosX, int16_t* PosY, float* AngleXY);

void CompassReadAxis (I2C_HandleTypeDef huart, uint8_t* buffer_x, uint8_t* buffer_y, float scale);

int16_t FilterData(uint8_t* buffer);

int16_t meanData(uint8_t* buffer);

float VectorToAngle (int16_t* PosX, int16_t* PosY);

#endif
