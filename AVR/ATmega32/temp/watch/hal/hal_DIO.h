/*
 * hal_DIO.h
 *
 *  Created on: Jul 28, 2018
 *      Author: Dell
 */

#ifndef HAL_HAL_DIO_H_
#define HAL_HAL_DIO_H_

typedef enum {
	INVALID_MIN_INDEX = 0x2F,
	BASE_D = 0x30,
	BASE_C = 0x33,
	BASE_B = 0x36,
	BASE_A = 0x39,
	INVALID_MAX_INDEX,
} enum_port_base_t;

void hal_init_port_output(enum_port_base_t port_base, u8 port_mask);
void hal_init_port_input(enum_port_base_t port_base, u8 port_mask);
void hal_set_port(enum_port_base_t port_base, u8 port_mask);
void hal_clear_port(enum_port_base_t port_base, u8 port_mask);
void hal_set_port(enum_port_base_t port_base, u8 pin_no);
void hal_clear_port(enum_port_base_t port_base, u8 pin_no);
void hal_deinit_port(enum_port_base_t port_base, u8 port_mask);
#endif /* HAL_HAL_DIO_H_ */
