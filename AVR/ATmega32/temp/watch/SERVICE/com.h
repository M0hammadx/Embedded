/*
 * com.h
 *
 *  Created on: Aug 4, 2018
 *      Author: Dell
 */

#ifndef SERVICE_COM_H_
#define SERVICE_COM_H_

#include "../HAL/UART/UART.h"

#define Frame__size 100
#define Header_size 3
#define CS_size 3
#define RX_data_max_size (Frame__size-Header_size-2)

typedef enum {
	Idle, Receive_header, Receive_byte, Receive_complete
} RX_state;

typedef struct {
	u8 cmd;
	u8 size[2];
	u8 data[Frame__size - (1 + 2 + 2)];
	u8 cs[CS_size];
} gcfg_Frame;

void RX_com_dispatch();

#endif /* SERVICE_COM_H_  */
