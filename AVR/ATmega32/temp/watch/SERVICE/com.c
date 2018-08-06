/*
 * com.c
 *
 *  Created on: Aug 4, 2018
 *      Author: Dell
 */
#include "com.h"

static RX_state gRX_state;

static u8 RX_DataLock = 0;
static u8 RX_main_frame_current_idx;
static gcfg_Frame RX_main_frame;
static u8 RX_flag_data_received; //flag , 1 > data received
void (*RX_hook_receive_complete)(u8* Rx_data);

static void RX_com_reset() {
	RX_DataLock = 0;
	gRX_state = Idle;
	RX_main_frame_current_idx = 0;
}
static void RX_com_callback() {
	RX_flag_data_received = 1;

	if (!RX_DataLock && RX_main_frame_current_idx < RX_data_max_size)
		RX_main_frame.data[RX_main_frame_current_idx++] = UART_dataReady(0);

}
void RX_com_init() {
	RX_com_reset();
	UART_init(0, 9600); //todo zabato ba3den , add intr
	UART_addISR(0, USART_RXC, &RX_com_callback);
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
u8 RX_check_header() {

}
//u8 RX_com_save_data(u8 from, u8 to) { // data swap
//	for (u8 i = from; i < to; i++) {
//		RX_main_frame[RX_main_frame_current_idx++] = RX_temp_buffer[i];
//	}
//}
void RX_com_dispatch() {
	if (RX_flag_data_received) {

		switch (gRX_state) {

		case Idle: {
			if (RX_main_frame_current_idx > Header_size) {
				if (RX_check_header()) {
					gRX_state = Receive_byte;
				} else {
					RX_com_reset();
				}

			} else {
				gRX_state = Receive_header;
			}
			break;
		}

		case Receive_header: {
			if (RX_main_frame_current_idx > Header_size) {
				gRX_state = Receive_byte;
				if (RX_check_header()) {
					RX_com_reset();
				} else {
					RX_com_reset();
				}
			}
			break;
		}

		case Receive_byte: {
			if (RX_main_frame_current_idx >= RX_data_max_size) { //todo not >=
				gRX_state = Receive_byte;
			}
			break;
		}

		case Receive_complete: {
			RX_hook_receive_complete(RX_main_frame.data);
			break;
		}

		}
	}
}

