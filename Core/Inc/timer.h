/*
 * timer.h
 *
 *  Created on: Sep 24, 2022
 *      Author: PC
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "global.h"
#include "main.h"
#include "button.h"
#include "scheduler.h"

void timerRun();
void setAllTimer(int duration);
void setTimer(int duration, int index);

#endif /* INC_TIMER_H_ */
