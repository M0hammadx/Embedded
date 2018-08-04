/*
 * keypad.c
 *
 *  Created on: Aug 1, 2018
 *      Author: mh-sh
 */
#include "keypad.h"
static u8 chars[4][4] = { { 7, 8, 9, '/' }, { 4, 5, 6, '*' }, { 1, 2, 3, '-' },
		{ 'O', 0, '=', '+' } };
static u8 last_click = 0;
void keypad_init(gcfg_keypad_t * keypad) {

	DIO_init_port_input(keypad->n4Port_left, 0xF0);
	DIO_set_port(keypad->n4Port_left, 0xF0);

	DIO_init_port_input(keypad->n4Port_bot, 0xF);
}
static void read_input(gcfg_keypad_t * keypad) {
	u8 temp = 0;
//	DIO_clear_port(keypad->n4Port_left, 0xF0);

	for (u8 i = 4; i < 8; i++) {
		DIO_clear_port(keypad->n4Port_left, 0xF0);
//		DIO_set_pin(keypad->n4Port_left, i);
		if (DIO_read_port(keypad->n4Port_bot, 0xF)) {
			temp = i - 3;
			break;
		}
	}

//	for (u8 i = 0; i < 4; i++) {
//		if (DIO_read_pin(keypad->n4Port_bot, i)) {
//			last_click = (i + 1) * temp;
//			break;
//		}
//	}
	last_click = temp;

	DIO_set_port(keypad->n4Port_left, 0xF0);
}
void keypad_dispatch(gcfg_keypad_t * keypad) {
	if (DIO_read_port(keypad->n4Port_bot, 0xF)) {
		read_input(keypad);
	}
}
u8 keypad_get_key(gcfg_keypad_t * keypad) {
	u8 temp = last_click;
	last_click = 0;
	return temp;
}
