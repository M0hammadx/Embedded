/*
 * seven_seg.h
 *
 *  Created on: Jul 7, 2018
 *      Author: hossam.adel
 */

#ifndef SEVEN_SEG_H_
#define SEVEN_SEG_H_
#include "common.h"

#define MAX_NUMBER_OF_HANDLERS 2

typedef enum{
	INVALID_MIN_INDEX=0x2F,
	BASE_D = 0x30,
	BASE_C = 0x33,
	BASE_B = 0x36,
	BASE_A = 0x39,
	INVALID_MAX_INDEX,
}enum_port_base_t;

typedef enum{
	COMMON_ANOD,
	COMMON_CATHOD
}enum_seven_seg_type_t;

bool_t seven_seg_init(enum_port_base_t port_base ,enum_seven_seg_type_t seven_seg_type, ecore_u8 * handler );
bool_t seven_seg_display(ecore_u8 handler , ecore_u8 dis_no);
bool_t seven_seg_reset(ecore_u8 handler);
bool_t seven_seg_deinit(ecore_u8 handler);

#endif /* SEVEN_SEG_H_ */
