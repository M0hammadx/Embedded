/*
 * seven_seg.c
 *
 *  Created on: Jul 7, 2018
 *      Author: hossam.adel
 */
#include "common.h"
#include "seven_seg.h"

typedef struct {
	enum_port_base_t enum_base_port;
	enum_seven_seg_type_t enum_type;
} str_seven_seg_info_t;

static str_seven_seg_info_t ga_seven_handlers[MAX_NUMBER_OF_HANDLERS];

static const ecore_u8 pattern[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };

static ecore_u8 handler_counter = 0;

bool_t seven_seg_init(enum_port_base_t port_base,
		enum_seven_seg_type_t seven_seg_type, ecore_u8 * handler) {
	bool_t b_ret_val = E_TRUE;

	ecore_u8 idx = 0;
	for (; idx < MAX_NUMBER_OF_HANDLERS; idx++) {
		if (ga_seven_handlers[idx].enum_base_port == 0)
			break;
	}

	if ((port_base < INVALID_MAX_INDEX) && (port_base > INVALID_MIN_INDEX)
			&& (handler != NULL)) {
		if (handler_counter < MAX_NUMBER_OF_HANDLERS) {
			*(volatile ecore_u8*) (port_base + 1) |= 0x7f;
			ga_seven_handlers[idx].enum_base_port = port_base;
			ga_seven_handlers[idx].enum_type = seven_seg_type;
			*handler = idx;
			handler_counter++;
		} else {
			b_ret_val = E_FALSE;
		}
	} else {
		b_ret_val = E_FALSE;
	}

	return b_ret_val;
}

bool_t seven_seg_display(ecore_u8 handler, ecore_u8 dis_no) {
	bool_t b_ret_val = E_TRUE;
	if ((handler < MAX_NUMBER_OF_HANDLERS) && (dis_no < 10)) {
		if (ga_seven_handlers[handler].enum_base_port != 0) {
			if (ga_seven_handlers[handler].enum_type == COMMON_CATHOD) {
				*(volatile ecore_u8*) (ga_seven_handlers[handler].enum_base_port
				+ 2) &= ~(0x7f);
				*(volatile ecore_u8*) (ga_seven_handlers[handler].enum_base_port
						+ 2) |= pattern[dis_no];
			} else if (ga_seven_handlers[handler].enum_type == COMMON_ANOD) {
				*(volatile ecore_u8*) (ga_seven_handlers[handler].enum_base_port
				+ 2) |= 0x7f;
				*(volatile ecore_u8*) (ga_seven_handlers[handler].enum_base_port
						+ 2) &= ~pattern[dis_no];
			} else {
				/*invalid parameter*/
				b_ret_val = E_FALSE;
			}
		} else {
			/*module not init*/
			b_ret_val = E_FALSE;
		}
	} else {
		b_ret_val = E_FALSE;
	}
	return b_ret_val;
}

bool_t seven_seg_reset(ecore_u8 handler) {
	bool_t b_ret_val = E_TRUE;
	if ((handler < MAX_NUMBER_OF_HANDLERS)) {
		if (ga_seven_handlers[handler].enum_base_port != 0) {
			if (ga_seven_handlers[handler].enum_type == COMMON_CATHOD) {
				*(volatile ecore_u8*) (ga_seven_handlers[handler].enum_base_port
				+ 2) &= ~(0x7f);
				*(volatile ecore_u8*) (ga_seven_handlers[handler].enum_base_port
						+ 2) |= pattern[0];
			} else if (ga_seven_handlers[handler].enum_type == COMMON_ANOD) {
				*(volatile ecore_u8*) (ga_seven_handlers[handler].enum_base_port
				+ 2) |= 0x7f;
				*(volatile ecore_u8*) (ga_seven_handlers[handler].enum_base_port
						+ 2) &= ~pattern[0];
			} else {
				/*invalid parameter*/
				b_ret_val = E_FALSE;
			}
		} else {
			/*module not init*/
			b_ret_val = E_FALSE;
		}
	} else {
		b_ret_val = E_FALSE;
	}
	return b_ret_val;
}

bool_t seven_seg_deinit(ecore_u8 handler) {
	bool_t b_ret_val = E_TRUE;
	if ((handler < MAX_NUMBER_OF_HANDLERS)) {
		if (ga_seven_handlers[handler].enum_base_port != 0) {
			if (ga_seven_handlers[handler].enum_type == COMMON_CATHOD) {
				*(volatile ecore_u8*) (ga_seven_handlers[handler].enum_base_port
						+ 2) &= ~(0x7f);
				ga_seven_handlers[handler].enum_base_port = 0;
			} else if (ga_seven_handlers[handler].enum_type == COMMON_ANOD) {
				*(volatile ecore_u8*) (ga_seven_handlers[handler].enum_base_port
						+ 2) |= 0x7f;
				ga_seven_handlers[handler].enum_base_port = 0;
			} else {
				/*invalid parameter*/
				b_ret_val = E_FALSE;
			}
		} else {
			/*module not init*/
			b_ret_val = E_FALSE;
		}
	} else {
		b_ret_val = E_FALSE;
	}
	return b_ret_val;
}

