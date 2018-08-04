/*
 * com.h
 *
 *  Created on: Aug 4, 2018
 *      Author: Dell
 */

#ifndef SERVICE_COM_H_
#define SERVICE_COM_H_

#include "../HAL/UART/USART.h"

#define Frame__max_size 100
#define Header_max_size 3
#define RX_data_max_size Frame__max_size-Header_max_size-2

typedef enum {
	Idle, Receive_header, Receive_byte, Receive_complete
} RX_state;

typedef struct {
	u8 cmd;
	u8 size[2];
	u8 data[Frame__max_size - (1 + 2 + 2)];
	u8 cs[2];
} gcfg_Frame;

void RX_com_dispatch();

#endif /* SERVICE_COM_H_  */
