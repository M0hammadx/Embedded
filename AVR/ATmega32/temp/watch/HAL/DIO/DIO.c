/*
 * hal_DIO.c
 *
 *  Created on: Aug 1, 2018
 *      Author: mh-sh
 */

#include "DIO.h"

void DIO_init_port_output(enum_port_base_t port_base, u8 port_mask) {
	*(volatile u8*) (port_base + 1) |= port_mask;
}
void DIO_init_port_input(enum_port_base_t port_base, u8 port_mask) {
	*(volatile u8*) (port_base + 1) &= ~port_mask;
}

void DIO_write_port(enum_port_base_t port_base, u8 port_mask, u8 data) {
	*(volatile u8*) (port_base + 2) &= ~(port_mask);
	*(volatile u8*) (port_base + 2) |= data & (port_mask);
}
void DIO_write_pin(enum_port_base_t port_base, u8 pin_no, bool_t data) {
	*(volatile u8*) (port_base + 2) &= ~(1 << pin_no);
	*(volatile u8*) (port_base + 2) |= data << pin_no;
}

void DIO_set_port(enum_port_base_t port_base, u8 port_mask) {
	*(volatile u8*) (port_base + 2) |= port_mask;
}
void DIO_clear_port(enum_port_base_t port_base, u8 port_mask) {
	*(volatile u8*) (port_base + 2) &= ~port_mask;
}
void DIO_set_pin(enum_port_base_t port_base, u8 pin_no) {
	*(volatile u8*) (port_base + 2) |= 1 << pin_no;
}
void DIO_clear_pin(enum_port_base_t port_base, u8 pin_no) {
	*(volatile u8*) (port_base + 2) &= ~(1 << pin_no);
}

u8 DIO_read_port(enum_port_base_t port_base, u8 port_mask) {
	return ((*(volatile u8*) (port_base)) & (port_mask));
}
u8 DIO_read_pin(enum_port_base_t port_base, u8 pin_no) {
	return ((*(volatile u8*) (port_base)) & (1 << pin_no));
}

void DIO_PullUp_port(enum_port_base_t port_base, u8 port_mask) {
	*(volatile u8*) (port_base + 2) |= port_mask;
}
void DIO_PullUp_pin(enum_port_base_t port_base, u8 pin_no) {
	*(volatile u8*) (port_base + 2) |= 1 << pin_no;
}

void DIO_deinit_port(enum_port_base_t port_base, u8 port_mask) { //todo
	DIO_clear_port(port_base, port_mask);
}
