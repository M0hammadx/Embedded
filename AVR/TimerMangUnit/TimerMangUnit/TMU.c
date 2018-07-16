/*
* TMU.c
*
*  Created on: Jul 14, 2018
*      Author: Dell
*/
#include "TMU.h"

static Timer_OBJ * Timer_Objects[Max_TIMERS_NO];
static u32 timerResolution;
static u8 timerCount;


void TIMER0_COMP_vect() {
for (int i = 0; i < Max_TIMERS_NO; i++) {
	if (Timer_Objects[i]) {
		Timer_Objects[i]->remTime--;
	}
	
}
	
	
	TIFR |=1;
	TCNT0=0;
	OCR0=78;
	sei();
}

TMU_Erors TMU_init(u8 hardwareTimerNo, u16 resolution, u8*ID) {
	TMU_Erors ret_error = ALL_IS_WELL;
	timerResolution = resolution;

	TCCR0=0b00000011;
	TCNT0=0;
	OCR0=78;
	TIMSK=1<<1;
	TIFR |=1;
	sei();	
	return ret_error;
}

TMU_Erors TMU_addTimer(Timer_OBJ *timerObj, u16 timePeriod, TIMER_TYPE TimerType,
void (*cb)(void * pv)) {
cli();
	TMU_Erors ret_error = ALL_IS_WELL;

	if (timerCount < Max_TIMERS_NO) {
		timerObj->TimerType = TimerType;
		timerObj->cb = cb;
		timerObj->Period = timePeriod / timerResolution;
		timerObj->remTime=timerObj->Period;
		timerCount++;

		for (int i = 0; i < Max_TIMERS_NO; i++) {
			if (!Timer_Objects[i]) {
				Timer_Objects[i] = timerObj;
				break;
			}
		}
		} else {
		//error
		ret_error = MAX_TIMERS_REACHED;
	}
sei();
	return ret_error;

}
TMU_Erors TMU_removeTimer(Timer_OBJ* timerObj) {
	TMU_Erors ret_error = ALL_IS_WELL;
	cli();
	int found = 0;
	timerCount--;
	for (int i = 0; i < Max_TIMERS_NO; i++) {
		if (Timer_Objects[i] == timerObj) {
			Timer_Objects[i] = 0;
			found = 1;
			break;
		}
	}
sei();
	if (!found)
	ret_error = Object_NOT_FOUND;
	
	return ret_error;

}
TMU_Erors TMU_Dispatch() {
	TMU_Erors ret_error = ALL_IS_WELL;
cli();
	for (int i = 0; i < Max_TIMERS_NO; i++) {
		if(Timer_Objects[i])
			if ((Timer_Objects[i]->remTime)<=0) {
				Timer_Objects[i]->cb(0);
				if (Timer_Objects[i]->TimerType == ONE_SHOT){
					timerCount--;
					Timer_Objects[i]->cb=0;
					Timer_Objects[i] = 0;
				}else{
					Timer_Objects[i]->remTime+=Timer_Objects[i]->Period;
				}
			}
	}
	sei();
	return ret_error;

}
TMU_Erors TMU_deinit() {
	TMU_Erors ret_error = ALL_IS_WELL;
	cli();
	TCCR0=0b00000000;
	for (int i = 0; i < Max_TIMERS_NO; i++) {
		Timer_Objects[i] = 0;
	}
	sei();
	return ret_error;

}

