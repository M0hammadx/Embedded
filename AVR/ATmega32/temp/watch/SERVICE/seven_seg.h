/*
 * seven_seg.h
 *
 *  Created on: Jul 7, 2018
 *      Author: hossam.adel
 */

#ifndef SEVEN_SEG_H_
#define SEVEN_SEG_H_

#include "../common.h"
#include "../HAL/DIO/DIO.h"

#define MAX_NUMBER_OF_HANDLERS 4

typedef enum {
	COMMON_ANOD, COMMON_CATHOD
} enum_seven_seg_type_t;

bool_t seven_seg_init(enum_port_base_t port_base,
		enum_seven_seg_type_t seven_seg_type, u8 * handler);
bool_t seven_seg_display(u8 handler, u8 dis_no);
bool_t seven_seg_reset(u8 handler);
bool_t seven_seg_deinit(u8 handler);

#endif /* SEVEN_SEG_H_ */
