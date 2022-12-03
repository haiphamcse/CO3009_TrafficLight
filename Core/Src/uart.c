/*
 * uart.c
 *
 *  Created on: Dec 3, 2022
 *      Author: PC
 */

#include "uart.h"

uint8_t temp = 0;
#define MAX_BUFFER_SIZE 30
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart)
{
	if(huart->Instance == USART2)
	{
		if(temp == 33){index_buffer = 0;}
		buffer[index_buffer++] = temp;
		if(index_buffer == MAX_BUFFER_SIZE) index_buffer = 0;
		buffer_flag = 1;
		HAL_UART_Transmit(&huart2, &temp, 1, 50);
		HAL_UART_Receive_IT(&huart2, &temp, 1);
	}
}
