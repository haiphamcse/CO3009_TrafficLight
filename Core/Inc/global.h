/*
 * global.h
 *
 *  Created on: Nov 4, 2022
 *      Author: PC
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_
#include "main.h"
/*
 * INIT PARAMETERS FOR SYSTEM
 */
#define TIMER_COUNT 2
#define BUTTON_COUNT 3
#define duration_LONGPRESS 300 //LONG_PRESS TIMED OUT

/*
 * CONFIG BUTTON PINS
 */

#define NORMAL_STATE SET
#define PRESSED_STATE RESET

extern uint16_t button[BUTTON_COUNT];
extern GPIO_TypeDef * button_gpio[BUTTON_COUNT];
//NOTE: DIFFERENT PINS HAVE DIFFERENT GPIO CONFIG, SO TO BE SURE, WE WILL SET GPIO FOR ALL BUTTONS
extern int TimeOutForKeyPress[BUTTON_COUNT]; //SET TIMED OUT FOR LONG PRESSED
extern int button_flag[BUTTON_COUNT]; //INIT BUTTON_FLAG TO 0
extern int button_long_flag[BUTTON_COUNT];

/*
 * CONFIG TIMER PINS
 */

extern int timer_counter[TIMER_COUNT];
extern int timer_flag[TIMER_COUNT];
extern int timer_delay[TIMER_COUNT];

/*
 * CONFIG LED PINS
 */

extern uint16_t led[4];
extern GPIO_TypeDef * led_gpio[4];

/*
 * CONFIG UART
 */
extern UART_HandleTypeDef huart2;
extern uint8_t temp;

#endif /* INC_GLOBAL_H_ */
