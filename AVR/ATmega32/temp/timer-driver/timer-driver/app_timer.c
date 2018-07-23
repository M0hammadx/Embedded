/*
 ============================================================================
 Name        : hal_timer.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "hal/hal_timer.h"
#include "hal/hal_system_errors.h"
#include <avr/io.h>

int main(void) {
	gcfg_hal_timer_t my_timer =
	{
			TIMER_0,
			WITHOUT_PRESACLER,
			NORMAL_MODE,
	};

	gcfg_hal_timer_t my_timer2 =
	{
			.ins_timer =  TIMER_0,
			.freq = WITHOUT_PRESACLER,
			.timer_fun = NORMAL_MODE,
	};

	hal_init_timer(&my_timer);

	while(1){
		
	}
	return 0;
}
