/*
 * keypad.c
 *
 *  Created on: Aug 1, 2018
 *      Author: mh-sh
 */
#include "keypad.h"
static u8 last_click;
void keypad_init(gcfg_keypad_t * keypad) {
	DIO_init_port_output(keypad->n3Port,
			(1 << keypad->b0) | (1 << keypad->b1) | (1 << keypad->b2));
	DIO_set_port(keypad->n3Port,
			(1 << keypad->b0) | (1 << keypad->b1) | (1 << keypad->b2));
	DIO_init_port_input(keypad->n4Port, 0xF);
}
static void read_input(gcfg_keypad_t * keypad) {
	u8 temp;
	DIO_clear_port(keypad->n4Port, 0xF);
	DIO_set_pin(keypad->n3Port, keypad->b0);
	if (DIO_read_port(keypad->n4Port, 0xF))
		temp = 1;
	else {
		DIO_clear_pin(keypad->n3Port, keypad->b0);
		DIO_set_pin(keypad->n3Port, keypad->b1);
		if (DIO_read_port(keypad->n4Port, 0xF))
			temp = 2;
		else {
			DIO_clear_pin(keypad->n3Port, keypad->b1);
			temp = 3;
		}
	}
	if (DIO_read_pin(keypad->n4Port, 0)) {
		last_click = 1 * temp;
	} else if (DIO_read_pin(keypad->n4Port, 1)) {
		last_click = 2 * temp;
	} else if (DIO_read_pin(keypad->n4Port, 2)) {
		last_click = 3 * temp;
	} else if (DIO_read_pin(keypad->n4Port, 3)) {
		last_click = 4 * temp;
	}
}
void keypad_dispatch(gcfg_keypad_t * keypad) {
	if (DIO_read_port(keypad->n4Port, 0xF)) {
		read_input(keypad);
	}
}
u8 keypad_get_key(gcfg_keypad_t * keypad) {
	u8 temp = last_click;
	last_click = 0;
	return temp;
}
