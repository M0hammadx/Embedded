/*
 * com.c
 *
 *  Created on: Aug 4, 2018
 *      Author: Dell
 */
#include "com.h"
#include "../SERVICE/lcd.h"
static RX_state gRX_state;
static TX_state gTX_state;

static u8 RX_DataLock = 0;
//static u8 TX_DataLock = 0;
static u8 RX_main_frame_current_idx;
static u8 TX_main_frame_current_idx;
static gcfg_Frame RX_main_frame;
static u8 RX_flag_data_received; //flag , 1 > data received
static u8 TX_flag_data_received; //flag , 1 > data received
void (*RX_hook_receive_complete)(u8* Rx_data);

static void RX_com_reset() {
	RX_DataLock = 0;
	gRX_state = RX_IDLE;
	RX_main_frame_current_idx = 0;
}
static void TX_com_callback() {
	TX_flag_data_received = 1;

	if (TX_main_frame_current_idx < TX_data_max_size) {
		gTX_state = SENDING_BYTE_COMPLETE;
		TX_main_frame_current_idx++;
	}

}
static void RX_com_callback() {
	RX_flag_data_received = 1;

	if (!RX_DataLock && RX_main_frame_current_idx < RX_data_max_size)
		RX_main_frame.data[RX_main_frame_current_idx++] = UART_dataReady(0);

}
u16 chech_sum(u8*arr, u16 n) {
	u32 temp = 0;
	u32 mod = ((u32) 1 << 16) - 1;
	for (u16 i = 0; i < n; i++) {
		temp += arr[i];
		temp %= mod;
	}
	return (u16) temp;
}
void RX_com_init() {
	RX_com_reset();
	UART_init(0, 9600);
	UART_addISR(0, USART_RXC, RX_com_callback);
}
void RX_com_receive(void (*hook)(u8* Rx_data)) {
	RX_hook_receive_complete = hook;
}
//callback with functionality

//void RX_get_data() {
//
//}
//u8 RX_is_data_ready() {
//
//}

//todo if not idle
u8 RX_check_header() { //todo chech header
	return 1;
}

RX_state RX_com_dispatch() {
	if (RX_flag_data_received) {

		switch (gRX_state) {

		case RX_IDLE: {
			if (RX_main_frame_current_idx > Header_size) {
				if (RX_check_header()) {
					gRX_state = RECEIVE_BYTE;
					RX_DataLock = 1;
				} else {
					RX_com_reset();
				}

			} else {
				gRX_state = RECEIVE_HEADER;
			}
			break;
		}

		case RECEIVE_HEADER: {
			if (RX_main_frame_current_idx > Header_size) {
				if (RX_check_header()) {
					gRX_state = RECEIVE_BYTE;
					RX_DataLock = 1;
				} else {
					RX_com_reset();
				}
			}
			break;
		}

		case RECEIVE_BYTE: {
			if (RX_main_frame_current_idx >= RX_main_frame.size + 1) { //todo not >=
				gRX_state = RECEIVE_COMPLETE; //todo chech sum
			}
			break;
		}

		case RECEIVE_COMPLETE: {
			RX_hook_receive_complete(RX_main_frame.data);
			break;
		}

		}
	}
	return RX_flag_data_received;
}

