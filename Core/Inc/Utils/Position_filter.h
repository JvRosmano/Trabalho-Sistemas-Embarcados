/*
 *  Position_Filter.h
 *
 *  João Vitor de M.G. Rosmaninho <jvrosmaninho@ufmg.br>,
 *  Lucas Soares de Salles <lucas-ss-salles@ufmg.br>,
 *  Stephanie Costa de Avelar <stephanieavelar@ufmg.br>
 *
 *
 *  Version 1.0 - API with the following implemented functions:
 *  void DataFilterService_InitBuffer(buffer_t* buffer);
 *  float DataFilterService_MovingAverage(buffer_t* buffer, float newValue);
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

#ifndef __DATA_FILTER_SERVICE_H
#define __DATA_FILTER_SERVICE_H

#include <stdint.h>
#include <memory.h>

#define MAX_BUFFER_SIZE 10

typedef struct {
	float data[MAX_BUFFER_SIZE];
	float sum;
	size_t size;
	size_t position;
} buffer_t;

void DataFilterService_InitBuffer(buffer_t* buffer);

/**
 * @brief Calculates moving average from buffer
 *
 * @param buffer buffer_t pointer to data to be filtered
 * @param newValue float value to be inserted in the buffer
 * @return float value representing the moving average from buffer
 */
float DataFilterService_MovingAverage(buffer_t* buffer, float newValue);

#endif /* __DATA_FILTER_SERVICE_H */
