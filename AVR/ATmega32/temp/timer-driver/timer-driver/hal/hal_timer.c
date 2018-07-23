
#include "hal_system_errors.h"
#include "hal_timer.h"
#include "../common.h"

ecore_s8 hal_init_timer(gcfg_hal_timer_t * obj)
{

	ecore_s8 ret_val = E_OK;
	if(obj != NULL)
	{
		if(obj->freq && obj->ins_timer && obj->timer_fun)
		{
			switch (obj->ins_timer){
				case TIMER_0:
					TCCR0|=((obj->timer_fun)/2)<<6;
					TCCR0|=((obj->timer_fun)%2)<<3;
					TCCR0|=(obj->freq);					
				break;
				case TIMER_1:
					
				break;
				case TIMER_2:
					TCCR2|=((obj->timer_fun)/2)<<6;
					TCCR2|=((obj->timer_fun)%2)<<3;
					TCCR2|=(obj->freq);
					
				break;
			}
		}
		else
		{
			ret_val = INVALID_ARG;
		}
	}
	else
	{
		ret_val = INVALID_ARG;
	}
}

ecore_s8 hal_read_timer(gcfg_hal_timer_t * obj)
{
}

ecore_s8 hal_is_timer_finish(gcfg_hal_timer_t * obj , bool_t * res)
{
}

ecore_s8 hal_update_timer(gcfg_hal_timer_t * obj , ecore_u8 value)
{
}

ecore_s8 hal_update_cmp_timer(gcfg_hal_timer_t * obj , ecore_u8 value)
{
}

ecore_s8 hal_deinit_timer(gcfg_hal_timer_t * obj)
{
}
