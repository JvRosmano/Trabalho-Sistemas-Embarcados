/*
 *  Position_Filter.c
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

#include <Utils/Position_filter.h>

void DataFilterService_InitBuffer(buffer_t* buffer)
{
	buffer->size = 0;
	buffer->sum = 0;
	buffer->position = 0;
}

float DataFilterService_MovingAverage(buffer_t* buffer, float newValue) {
	if (buffer->size <= MAX_BUFFER_SIZE) buffer->size++;
  buffer->sum += newValue - buffer->data[buffer->position];
  buffer->data[buffer->position] = newValue;
  buffer->position = (buffer->position + 1) % MAX_BUFFER_SIZE;
  return (float)buffer->sum / buffer->size;
}
