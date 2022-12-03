/*
 * scheduler.h
 *
 *  Created on: Nov 9, 2022
 *      Author: PC
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>

#define MAX_TASK 5

typedef struct{
	//Delay, Period, Function, ID
	int Delay;
	int Period;
	void (*Function)();
	int RunMe;
	int ID;
}pTask;

void SCH_Add(void(*), int, int, int);
void SCH_Update();
void SCH_Dispatch();
void SCH_Delete(int);
void SCH_Init();

#endif /* INC_SCHEDULER_H_ */
