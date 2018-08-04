/*
 * keypad.h
 *
 *  Created on: Jul 28, 2018
 *      Author: Dell
 */

#ifndef HAL_KEYPAD_H_
#define HAL_KEYPAD_H_

#include "../hal/dio/DIO.h"

typedef struct {
	enum_port_base_t n3Port;
	enum_port_base_t n4Port; //lower
	u8 b0, b1, b2;
} gcfg_keypad_t;

void keypad_init(gcfg_keypad_t * keypad);
void keypad_dispatch(gcfg_keypad_t * keypad);
u8 keypad_get_key(gcfg_keypad_t * keypad);

#endif /* HAL_KEYPAD_H_ */
