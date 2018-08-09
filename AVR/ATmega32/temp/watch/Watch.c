/*
 * Watch.c
 *
 * Created: 7/16/2018 1:24:37 PM
 *  Author: mh-sh
 */

#include <avr/io.h>

#include "SERVICE/TMU.h"
#include "SERVICE/seven_seg.h"
#include "SERVICE/lcd.h"
#include "SERVICE/keypad.h"
#include "SERVICE/TMU.h"
#include "SERVICE/seven_seg.h"
#include "SERVICE/lcd.h"
#include "SERVICE/keypad.h"
#include "SERVICE/com.h"

#include "stdio.h"
#include "HAL/UART/UART.h"

int currSec = 1, currMin = 10;
u8 secID1, secID10, minID1, minID10;

void function1(void * pv) {
	seven_seg_display(secID1, currSec % 10);
	if (currSec >= 59)
		currMin++, currSec = 0;

	currSec++;
}
void function2(void * pv) {

	seven_seg_display(secID10, currSec / 10);

}
void function3(void * pv) {
	seven_seg_display(minID1, currMin % 10);
	seven_seg_display(minID10, currMin++ / 10);

}
gcfg_lcd_t lcd;
void tx(u8* Rx_data) {
//	DIO_write_pin(BASE_B, 0, !DIO_read_pin(BASE_B, 0));
	DIO_set_pin(BASE_A, 0);
//	lcd_send_data(&lcd, 'x');
//	sei();
}
u8 flag;
void rx() {
	flag = 1;
	DIO_write_pin(BASE_A, 1, !DIO_read_pin(BASE_A, 1));
//	((void (*)()) tx)(); WOW !!!
//	UART_sendByte(0, 3);
//	DIO_set_pin(BASE_A, 1);
//	sei();

}
int main(void) {
//	u8 arr[] = { 1, 2, 3, 4, 5, 6, 7 };
	UART_init(UART0, 9600);
	DIO_init_port_output(BASE_A, 0x3);
	UART_addISR(0, USART_RXC, rx);
//	UART_sendByte(0, 3);
//	RX_com_init();
//	RX_com_receive(tx);
//	UART_sendByte(0, 'x');

//	UART_sendPacket(0, arr, 7);
//	UART_addISR(UART0, USART_RXC, rx); //working
//	UART_addISR(UART0, USART_TXC, tx); // not working somehow

//	DIO_init_port_input(BASE_B, 0x4);

//	Timer_OBJ obj1, obj2, obj3;
//	TMU_init(0, 5, 0);
//	seven_seg_init(BASE_C, COMMON_CATHOD, &secID1);
//	seven_seg_init(BASE_D, COMMON_CATHOD, &secID10);
//
//	seven_seg_init(BASE_A, COMMON_CATHOD, &minID1);
//	seven_seg_init(BASE_B, COMMON_CATHOD, &minID10);
//
//	TMU_addTimer(&obj1, 500, PERIODIC, function1);
//	TMU_addTimer(&obj2, 5000, PERIODIC, function2);
//	TMU_addTimer(&obj3, 10000, PERIODIC, function3);

//	u8 key = 0;
//	char str[2];
//	gcfg_keypad_t keypad = { BASE_C, BASE_C };
//	keypad_init(&keypad);

#define debug
#ifdef debug
	lcd.RS = 7;
	lcd.RW = 6;
	lcd.EN = 5;
	lcd.controlPort = BASE_A;
	lcd.dataPort = BASE_B;
	lcd.nbit = n4BIT_MODE;
	lcd_init(&lcd);
	lcd_gotoxy(&lcd, 1, 1);

//	lcd_send_data(&lcd, '0' + 1);
//	lcd_print(&lcd, "xxxx xxxx");
//	lcd_gotoxy(&lcd, 1, 2);
//	lcd_print(&lcd, "yyyy yyyy");
#endif

//	u8 i = 0;
//	while (i < 7) {
//		UART_sendByte(0, arr[i++]);
////		if (UART_readByte(0) == (u8) 0)
////			rx();
//		lcd_send_data(&lcd, '0' + RX_com_dispatch());
//		RX_com_dispatch();
//	}

	while (1) {
//		UART_sendByte(0, 3);
//		if (flag)
//			UART_sendByte(0, 3), flag = 0;
//		if (RX_com_dispatch())
//			rx();
//		lcd_send_data(&lcd, '0' + RX_com_dispatch());
		lcd_send_data(&lcd, '0' + flag | (UCSRA & (1 << RXC)));

//		UART_sendByte(0, 3);
//		lcd_send_data(&lcd, '0' + UART_readByte(0));
//		if (UART_readByte(0) == 3)
//			rx();

//		if ((key = keypad_get_key(&keypad)) != 0) {
//			sprintf(str, "%x", key);
//			lcd_print(&lcd, str);
//			sprintf(str, "%x", DIO_read_port(BASE_C, 0xf));
//			lcd_print(&lcd, str);
//			key = 0;
//		}
//		keypad_dispatch(&keypad);
//		TMU_Dispatch();
	}
}

