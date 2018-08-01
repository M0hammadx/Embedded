/*
 * hal_timer.h
 *
 *  Created on: Jul 20, 2018
 *      Author: hossam.adel
 */

#ifndef HAL_TIMER_H_
#define HAL_TIMER_H_
#include <avr/io.h>
#include "../common.h"
#include "hal_system_errors.h"
#include "iom32.h"

typedef enum {
	TIMER_0, TIMER_1, TIMER_2,
} genum_inst_timer_t;

typedef enum {
	WITHOUT_PRESACLER = 0x1, PRESCALER_8,
#ifdef TIMER2
	PRESCALER_32,
#endif
	PRESCALER_64,
#ifdef TIMER2
	PRESCALER_128,
#endif
	PRESCALER_256, PRESCALER_1024,
#ifndef TIMER2
	EXTERNAL_CLOCK = 0x6,
#endif

} genum_freq_timer_t;

typedef enum {
	NORMAL_MODE, CTC_MODE = 2,
} genum_fun_timer_t;

typedef enum {
	NORMAL_COM, TOGGLE, CLEAR, SET,
} genum_com_timer_t;

typedef enum {
	ON_OVERFLOW, ON_COMPARE,
} genum_int_timer_t;

typedef struct {
	genum_inst_timer_t ins_timer;
	genum_freq_timer_t freq;
	genum_fun_timer_t timer_fun;
	genum_com_timer_t com;
	genum_int_timer_t interrupt;
	void (*func)(void);
} gcfg_hal_timer_t;

s8 hal_init_timer(gcfg_hal_timer_t * obj);

s8 hal_read_timer(gcfg_hal_timer_t * obj, u8 * res);

s8 hal_is_timer_finish(gcfg_hal_timer_t * obj, bool_t * res);

s8 hal_update_timer(gcfg_hal_timer_t * obj, u8 value);

s8 hal_update_cmp_timer(gcfg_hal_timer_t * obj, u8 value);

s8 hal_deinit_timer(gcfg_hal_timer_t * obj);

#endif /* HAL_TIMER_H_ */
