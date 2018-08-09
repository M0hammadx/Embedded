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
#define CS_size 2
#define RX_data_max_size (Frame__size-Header_size-2)
#define TX_data_max_size RX_data_max_size

typedef enum {
	RX_IDLE, RECEIVE_HEADER, RECEIVE_BYTE, RECEIVE_COMPLETE,
} RX_state;

typedef enum {
	TX_IDLE, SENDING_HEADER, SENDING_BYTE, SENDING_BYTE_COMPLETE,
} TX_state;

typedef struct {
	u8 cmd;
	u16 size;
	u8 data[Frame__size - (1 + 2 + 2)];
	u16 cs;
} gcfg_Frame;

void RX_com_init();
void RX_com_receive(void (*hook)(u8* Rx_data));
RX_state RX_com_dispatch();

#endif /* SERVICE_COM_H_  */
