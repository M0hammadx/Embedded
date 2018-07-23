/*
 * hal_timer.h
 *
 *  Created on: Jul 20, 2018
 *      Author: hossam.adel
 */

#ifndef HAL_TIMER_H_
#define HAL_TIMER_H_

#include "../common.h"

typedef enum {
	TIMER_0,
	TIMER_1,
	TIMER_2,
}genum_inst_timer_t;

typedef enum {
	WITHOUT_PRESACLER = 0x1,
	PRESCALER_8 ,
	PRESCALER_64,
#ifdef TIMER2
	PRESCALER_128,
#endif
	PRESCALER_256,
	PRESCALER_1024,
	EXTERNAL_CLOCK = 0x6,
}genum_freq_timer_t;

typedef enum {
	CTC_MODE,
	NORMAL_MODE,
}genum_fun_timer_t;


typedef struct {
	genum_inst_timer_t ins_timer;
	genum_freq_timer_t freq;
	genum_fun_timer_t timer_fun;
	/*INT handler*/
}gcfg_hal_timer_t;

ecore_s8 hal_init_timer(gcfg_hal_timer_t * obj);

ecore_s8 hal_read_timer(gcfg_hal_timer_t * obj);

ecore_s8 hal_is_timer_finish(gcfg_hal_timer_t * obj , bool_t * res);

ecore_s8 hal_update_timer(gcfg_hal_timer_t * obj , ecore_u8 value);

ecore_s8 hal_update_cmp_timer(gcfg_hal_timer_t * obj , ecore_u8 value);

ecore_s8 hal_deinit_timer(gcfg_hal_timer_t * obj);



#endif /* HAL_TIMER_H_ */
