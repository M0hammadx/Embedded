/*
 * hal_DIO.h
 *
 *  Created on: Jul 28, 2018
 *      Author: Dell
 */

#ifndef HAL_HAL_DIO_H_
#define HAL_HAL_DIO_H_

#include "../../Common.h"

typedef enum {
	INVALID_MIN_INDEX = 0x2F,
	BASE_D = 0x30,
	BASE_C = 0x33,
	BASE_B = 0x36,
	BASE_A = 0x39,
	INVALID_MAX_INDEX,
} enum_port_base_t;

void DIO_init_port_output(enum_port_base_t port_base, u8 port_mask);
void DIO_init_port_input(enum_port_base_t port_base, u8 port_mask);

void DIO_write_port(enum_port_base_t port_base, u8 port_mask, u8 data);
void DIO_write_pin(enum_port_base_t port_base, u8 pin_no, bool_t data);

void DIO_set_port(enum_port_base_t port_base, u8 port_mask);
void DIO_clear_port(enum_port_base_t port_base, u8 port_mask);
void DIO_set_pin(enum_port_base_t port_base, u8 pin_no);
void DIO_clear_pin(enum_port_base_t port_base, u8 pin_no);

u8 DIO_read_port(enum_port_base_t port_base, u8 port_mask);
u8 DIO_read_pin(enum_port_base_t port_base, u8 pin_no);

void DIO_PullUp_port(enum_port_base_t port_base, u8 port_mask);
void DIO_PullUp_pin(enum_port_base_t port_base, u8 pin_no);

void DIO_deinit_port(enum_port_base_t port_base, u8 port_mask);

#endif /* HAL_HAL_DIO_H_ */
