/*
* TMU.h
*
*  Created on: Jul 14, 2018
*      Author: Dell
*/

#ifndef TMU_H_
#define TMU_H_
#define Max_TIMERS_NO 3
#include "Common.h"
#include <avr/io.h>

#define  F_CPU 1
#include <util/delay.h>
#include <avr/interrupt.h>
#include <inttypes.h>

typedef enum {
	ONE_SHOT, PERIODIC
} TIMER_TYPE;

typedef struct {
	u16 Period;
	short remTime;
	TIMER_TYPE TimerType;
	void (*cb)(void * pv);
} Timer_OBJ;

typedef enum {
	ALL_IS_WELL, HARDWARE_TIMER_BUSY, MAX_TIMERS_REACHED,Object_NOT_FOUND, UNEXPECTED_ERROR
} TMU_Erors;

TMU_Erors TMU_init(u8 hardwareTimerNo, u16 resolution, u8*ID);
TMU_Erors TMU_addTimer(Timer_OBJ* timerObj, u16 timePeriod, TIMER_TYPE TimerType,void (*cb)(void * pv));
TMU_Erors TMU_removeTimer(Timer_OBJ *timerObj);
TMU_Erors TMU_Dispatch();
TMU_Erors TMU_deinit();

#endif /* TMU_H_ */
