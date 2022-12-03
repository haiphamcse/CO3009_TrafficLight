/*
 * fsm.c
 *
 *  Created on: Dec 1, 2022
 *      Author: PC
 */


#include "fsm.h"

//CONFIG
int auto_status = 0;
int auto_status_1 = 0;

int clock_counter = 3;
int clock_counter_1 = 5;

int manual_status = 0;

int MAX_RED = 5;
int MAX_YELLOW = 2;
int MAX_GREEN = 3;

int BUFFER_RED = 5;
int BUFFER_YELLOW = 2;
int BUFFER_GREEN = 3;

char str[50];
/*
 * TIMER[0]: MAIN TRAFFIC COUNTER
 * TIMER[1]: BLINKING COUNTER
 *
 * led[0] = D2, led[1] = D3, led[2] = D5, led[3] = D4
 * led[0] = 1, led[1] = 0: YELLOW LINE 1
 * led[0] = 0, led[1] = 1:
 * led[0] = 0, led[1] = 0:
 * led[0] = 1, led[1] = 1:
 */

void buffer_print()
{
	if(manual_status == 1){
		HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "!BUFFER_RED=%d#\r\n", BUFFER_RED), 1000);
	}
	else if(manual_status == 2){
		HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "!BUFFER_YELLOW=%d#\r\n", BUFFER_YELLOW), 1000);
	}
	else if(manual_status == 3){
		HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "!BUFFER_GREEN=%d#\r\n", BUFFER_GREEN), 1000);
	}
}

void clear_led()
{
	for(int i = 0; i < 4; i++){
		HAL_GPIO_WritePin(led_gpio[i], led[i], 0);
	}
}

void blink_red(){
	if(timer_flag[1] == 1)
	{
		//TOGGLE RED
		HAL_GPIO_TogglePin(led_gpio[0], led[0]);
		HAL_GPIO_TogglePin(led_gpio[3], led[3]);
		setTimer(timer_delay[1], 1);
	}
};
void blink_yellow(){
	if(timer_flag[1] == 1)
	{
		//TOGGLE YELLOW
		HAL_GPIO_TogglePin(led_gpio[0], led[0]);
		HAL_GPIO_TogglePin(led_gpio[1], led[1]);
		HAL_GPIO_TogglePin(led_gpio[2], led[2]);
		HAL_GPIO_TogglePin(led_gpio[3], led[3]);
		setTimer(timer_delay[1], 1);
	}
};
void blink_green(){
	if(timer_flag[1] == 1)
	{
		//TOGGLE GREEN
		HAL_GPIO_TogglePin(led_gpio[2], led[2]);
		HAL_GPIO_TogglePin(led_gpio[1], led[1]);
		setTimer(timer_delay[1], 1);
	}
};

//INDEX = 1 FOR LINE 1, = 2 FOR LINE 2
void auto_red(int index){
	if(index == 1){
		HAL_GPIO_WritePin(led_gpio[0], led[0], 1);
		HAL_GPIO_WritePin(led_gpio[1], led[1], 0);
	}
	else if(index == 2){
		HAL_GPIO_WritePin(led_gpio[2], led[2], 0);
		HAL_GPIO_WritePin(led_gpio[3], led[3], 1);
	}
	else{}
};
void auto_yellow(int index){
	if(index == 1){
		HAL_GPIO_WritePin(led_gpio[0], led[0], 1);
		HAL_GPIO_WritePin(led_gpio[1], led[1], 1);
	}
	else if(index == 2){
		HAL_GPIO_WritePin(led_gpio[2], led[2], 1);
		HAL_GPIO_WritePin(led_gpio[3], led[3], 1);
	}
	else{}
};
void auto_green(int index){
	if(index == 1){
		HAL_GPIO_WritePin(led_gpio[0], led[0], 0);
		HAL_GPIO_WritePin(led_gpio[1], led[1], 1);
	}
	else if(index == 2){
		HAL_GPIO_WritePin(led_gpio[2], led[2], 1);
		HAL_GPIO_WritePin(led_gpio[3], led[3], 0);
	}
	else{}
};

void fsm_clock_counter()
{
	if(timer_flag[0] == 1 && (manual_status == 0))
	{
		HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "!7SEG_LINE1=%d#", clock_counter), 1000);
		HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "!7SEG_LINE2=%d#\r\n", clock_counter_1), 1000);
		clock_counter--;
		clock_counter_1--;
		setTimer(timer_delay[0], 0);

	}
}

//LINE 1
void fsm_auto_traffic(){
	switch(auto_status){
	case 0:
		//GREEN
		//ADD FUNCTION TO DISPLAY GREEN LINE 1
		auto_green(1);
				  if(clock_counter == 0)
				  {
					  clock_counter = MAX_YELLOW;
					  auto_status = 1;
				  }
		break;
	case 1:
		//YELLOW
		//ADD FUNCTION TO DISPLAY YELLOW LINE 1
		auto_yellow(1);
				  if(clock_counter == 0)
				  {
					  clock_counter = MAX_RED;
					  auto_status = 2;
				  }


		break;
	case 2:
		//RED
		//ADD FUNCTION TO DISPLAY RED LINE 1
		auto_red(1);
				  if(clock_counter == 0)
				  {
					  clock_counter = MAX_GREEN;
					  auto_status = 0;
				  }
		break;
	}
}

//LINE 2
void fsm_auto_traffic_1(){
	switch(auto_status_1){
	case 0:
		//RED
		//ADD FUNCTION TO DISPLAY RED LINE 2
		auto_red(2);
				  if(clock_counter_1 == 0)
				  {
					  clock_counter_1 = MAX_GREEN;
					  auto_status_1 = 2;
				  }
		break;
	case 1:
		//YELLOW
		//ADD FUNCTION TO DISPLAY YELLOW LINE 2
		auto_yellow(2);
				  if(clock_counter_1 == 0)
				  {
					  clock_counter_1 = MAX_RED;
					  auto_status_1 = 0;
				  }

		break;
	case 2:
		//GREEN
		//ADD FUNCTION TO DISPLAY GREEN LINE 2
		auto_green(2);
				  if(clock_counter_1 == 0)
				  {
					  clock_counter_1 = MAX_YELLOW;
					  auto_status_1 = 1;
				  }
		break;
	}
}

//FULL FSM
void fsm_traffic(){
	switch(manual_status)
	{
	case 0:
		fsm_auto_traffic();
		fsm_auto_traffic_1();
		if(isButtonPressed(0) == 1){
			manual_status = 1;
			clear_led();
		}
		break;
	case 1:
		blink_red();
		if(isButtonPressed(0) == 1){
			manual_status = 2;
			clear_led();
		}
		if(isButtonPressed(1) == 1){
			BUFFER_RED++;
			if(BUFFER_RED == 10){BUFFER_RED = 0;}
		}
		if(isButtonPressed(2) == 1){
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "!UPDATE_RED_ACK#\r\n"), 1000);
			MAX_RED = BUFFER_RED;
		}
		break;
	case 2:
		blink_yellow();
		if(isButtonPressed(0) == 1){
			manual_status = 3;
			clear_led();
		}
		if(isButtonPressed(1) == 1){
			BUFFER_YELLOW++;
			if(BUFFER_YELLOW == 10){BUFFER_YELLOW = 0;}
		}
		if(isButtonPressed(2) == 1){
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "!UPDATE_YELLOW_ACK#\r\n"), 1000);
			MAX_YELLOW = BUFFER_YELLOW;
		}
		break;
	case 3:
		blink_green();
		if(isButtonPressed(0) == 1){
			manual_status = 0;
			//CHECK CONDITIONS HERE
			if(MAX_RED != MAX_GREEN + MAX_YELLOW)
			{
				HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "!UPDATE_DENIED#\r\n"), 1000);
				MAX_RED = 5;
				MAX_YELLOW = 2;
				MAX_GREEN = 3;
			}
			else{
				HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "!UPDATE_GRANTED#\r\n"), 1000);
			}
			//RESET TRAFFIC
			auto_status = 0;
			auto_status_1 = 0;
			clock_counter = MAX_GREEN;
			clock_counter_1 = MAX_RED;
			setTimer(timer_delay[0], 0);
		}
		if(isButtonPressed(1) == 1){
			BUFFER_GREEN++;
			if(BUFFER_GREEN == 10){BUFFER_GREEN = 0;}
		}
		if(isButtonPressed(2) == 1){
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "!UPDATE_GREEN_ACK#\r\n"), 1000);
			MAX_GREEN = BUFFER_GREEN;
		}
		break;
	}
}
