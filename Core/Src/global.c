/*
 * global.c
 *
 *  Created on: Nov 5, 2022
 *      Author: PC
 */

#include"global.h"

uint16_t button[BUTTON_COUNT] = {A1_Pin, A2_Pin, A3_Pin, A0_Pin};
GPIO_TypeDef * button_gpio[BUTTON_COUNT] = {A1_GPIO_Port, A2_GPIO_Port, A3_GPIO_Port, A0_GPIO_Port};
//NOTE: DIFFERENT PINS HAVE DIFFERENT GPIO CONFIG, SO TO BE SURE, WE WILL SET GPIO FOR ALL BUTTONS

uint16_t led[6] = {D2_Pin, D3_Pin, D5_Pin, D4_Pin, D6_Pin, D7_Pin};
GPIO_TypeDef * led_gpio[6] = {D2_GPIO_Port, D3_GPIO_Port, D5_GPIO_Port, D4_GPIO_Port, D6_GPIO_Port, D7_GPIO_Port};
//NOTE: LEDS

int TimeOutForKeyPress[BUTTON_COUNT] = {100}; //SET TIMED OUT FOR LONG PRESSED
int button_flag[BUTTON_COUNT] = {0}; //INIT BUTTON_FLAG TO 0
int button_long_flag[BUTTON_COUNT] = {0};

/*
 * CONFIG TIMER PINS
 */

int timer_counter[TIMER_COUNT] = {0};
int timer_flag[TIMER_COUNT] = {0};
int timer_delay[TIMER_COUNT] = {100, 25, 700, 100};

/*
 * CONFIG UART
 */

