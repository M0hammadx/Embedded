#include "timer.h"



void (*t0_isr[TIMER0_HANDLERS_MAX_COUNT])(),
		(*t1_isr[TIMER1_HANDLERS_MAX_COUNT])(),
		(*t2_isr[TIMER2_HANDLERS_MAX_COUNT])();

//ISR(TIMER0_COMP_vect) {
//
//	if (t0_isr)
//		t0_isr();
//}
//
//ISR(TIMER0_OVF_vect) {
//
//	if (t0_isr)
//		t0_isr();
//}

void TIMER0_COMP_vect() {

	for (u8 i = 0; i < TIMER0_HANDLERS_MAX_COUNT; i++)
		if (t0_isr[i])
			t0_isr[i]();
}
void TIMER2_COMP_vect() {
	for (u8 i = 0; i < TIMER2_HANDLERS_MAX_COUNT; i++)
		if (t2_isr[i])
			t2_isr[i]();
}

s8 hal_init_timer(gcfg_hal_timer_t * obj) {
	s8 ret_val = E_OK;
	if (obj != NULL) {
//		if (obj->freq && obj->ins_timer && obj->timer_fun) {
		switch (obj->ins_timer) {
		case TIMER_0:
			TCCR0 |= ((obj->timer_fun) / 2) << 6;
			TCCR0 |= ((obj->timer_fun) % 2) << 3;
			TCCR0 |= (obj->freq);
			TCCR0 |= (obj->com) << 4;
			TIMSK |= (1 << (obj->interrupt));
			TIFR |= (1 << (obj->interrupt));
			for (u8 i = 0; i < TIMER0_HANDLERS_MAX_COUNT; i++)
				if (!t0_isr[i])
					t0_isr[i] = obj->func;
			break;
		case TIMER_1:

			break;
		case TIMER_2:
			TCCR2 |= ((obj->timer_fun) / 2) << 6;
			TCCR2 |= ((obj->timer_fun) % 2) << 3;
			TCCR2 |= (obj->freq);
			TCCR2 |= (obj->com) << 4;
			TIMSK |= (1 << (obj->interrupt + 6));
			TIFR |= (1 << (obj->interrupt + 6));

			for (u8 i = 0; i < TIMER2_HANDLERS_MAX_COUNT; i++)
				if (!t2_isr[i])
					t2_isr[i] = obj->func;
			break;
		}

//		} else {
//			ret_val = INVALID_ARG;
//		}
	} else {
		ret_val = INVALID_ARG;
	}
	return ret_val;
}

s8 hal_read_timer(gcfg_hal_timer_t * obj, u8 * res) {
	s8 ret_val = E_OK;
	if (obj != NULL) {
//		if (obj->freq && obj->ins_timer && obj->timer_fun) {
		switch (obj->ins_timer) {
		case TIMER_0:
			*res = TCNT0;
			break;
		case TIMER_1:

			break;
		case TIMER_2:
			*res = TCNT2;
			break;
		}
//		} else {
//			ret_val = INVALID_ARG;
//		}
	} else {
		ret_val = INVALID_ARG;
	}
	return ret_val;
}

s8 hal_update_timer(gcfg_hal_timer_t * obj, u8 value) {
	s8 ret_val = E_OK;
	if (obj != NULL) {
//		if (obj->freq && obj->ins_timer && obj->timer_fun) {
		switch (obj->ins_timer) {
		case TIMER_0:
			TCNT0 = value;
			break;
		case TIMER_1:

			break;
		case TIMER_2:
			TCNT2 = value;
			break;
		}
//		} else {
//			ret_val = INVALID_ARG;
//		}
	} else {
		ret_val = INVALID_ARG;
	}
	return ret_val;
}

s8 hal_is_timer_finish(gcfg_hal_timer_t * obj, bool_t * res) {
	s8 ret_val = E_OK;
	if (obj != NULL) {
//		if (obj->freq && obj->ins_timer && obj->timer_fun) {
		switch (obj->ins_timer) {
		case TIMER_0:
			*res = (TIFR & ~(1 << (obj->interrupt))) > 0;
			if (*res)
				TIFR |= (1 << (obj->interrupt));
			break;
		case TIMER_1:

			break;
		case TIMER_2:
			*res = (TIFR & ~(1 << (obj->interrupt + 6))) > 0;
			if (*res)
				TIFR |= (1 << (obj->interrupt + 6));
			break;
		}
//		} else {
//			ret_val = INVALID_ARG;
//		}
	} else {
		ret_val = INVALID_ARG;
	}
	return ret_val;
}

s8 hal_update_cmp_timer(gcfg_hal_timer_t * obj, u8 value) {
	s8 ret_val = E_OK;
	if (obj != NULL) {
//		if (obj->freq && obj->ins_timer && obj->timer_fun) {
		switch (obj->ins_timer) {
		case TIMER_0:
			OCR0 = value;
			break;
		case TIMER_1:

			break;
		case TIMER_2:
			OCR2 = value;
			break;
		}
//		} else {
//			ret_val = INVALID_ARG;
//		}
	} else {
		ret_val = INVALID_ARG;
	}
	return ret_val;
}

s8 hal_deinit_timer(gcfg_hal_timer_t * obj) {
	s8 ret_val = E_OK;
	if (obj != NULL) {
//		if (obj->freq && obj->ins_timer && obj->timer_fun) {
		switch (obj->ins_timer) {
		case TIMER_0:
			TCCR0 = 0;
			TIMSK &= ~(1 << (obj->interrupt));
			TIFR &= ~(1 << (obj->interrupt));
			break;
		case TIMER_1:

			break;
		case TIMER_2:
			TCCR2 = 0;
			TIMSK &= ~(1 << (obj->interrupt + 6));
			TIFR &= ~(1 << (obj->interrupt + 6));
			break;
		}
		for (u8 i = 0; i < TIMER0_HANDLERS_MAX_COUNT; i++)
			t0_isr[i] = 0;
		for (u8 i = 0; i < TIMER2_HANDLERS_MAX_COUNT; i++)
			t2_isr[i] = 0;
//		} else {
//			ret_val = INVALID_ARG;
//		}
	} else {
		ret_val = INVALID_ARG;
	}
	return ret_val;
}
