/*
 * Watch.c
 *
 * Created: 7/16/2018 1:24:37 PM
 *  Author: mh-sh
 */

#include <avr/io.h>
<<<<<<< HEAD
#include "SERVICE/TMU.h"
#include "SERVICE/seven_seg.h"
#include "hal/dio/DIO.h"
#include "SERVICE/lcd.h"
#include "SERVICE/keypad.h"
=======
#include "service/TMU.h"
#include "service/seven_seg.h"
#include "hal/dio/DIO.h"
#include "service/lcd.h"
#include "service/keypad.h"
>>>>>>> 4dc176ffe1bb20ece6c6e4ada9dacf7df24a391d
#include "stdio.h"
#include "HAL/UART/USART.h"

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
void tx() {
	DIO_write_pin(BASE_B, 0, !DIO_read_pin(BASE_B, 0));
//	sei();
}
void rx() {
	DIO_write_pin(BASE_B, 1, !DIO_read_pin(BASE_B, 1));
//	sei();

}
int main(void) {
	UART_init(UART0, 9600);

<<<<<<< HEAD
	UART_addISR(UART0, USART_RXC, rx); //working
	UART_addISR(UART0, USART_TXC, tx); // not working somehow

	DIO_init_port_output(BASE_B, 0x3);
	DIO_init_port_input(BASE_B, 0x4);

=======
>>>>>>> 4dc176ffe1bb20ece6c6e4ada9dacf7df24a391d
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

<<<<<<< HEAD
//	u8 key = 0;
//	char str[2];
//	gcfg_keypad_t keypad = { BASE_C, BASE_C, 0, 1, 2 };
//	keypad_init(&keypad);
//	gcfg_lcd_t lcd;
//	lcd.RS = 7;
//	lcd.RW = 6;
//	lcd.EN = 5;
//	lcd.controlPort = BASE_A;
//	lcd.dataPort = BASE_B;
//	lcd.nbit = n4BIT_MODE;
//	lcd_init(&lcd);
//	lcd_gotoxy(&lcd, 1, 1);
//	lcd_print(&lcd, "xxxx xxxx");
//	lcd_gotoxy(&lcd, 1, 2);
//	lcd_print(&lcd, "yyyy yyyy");
	if (UCSRA & (1 << 6)) {
		tx();
	}
	while (1) {
	UART_sendByte(UART0, 'a');
	UART_Flush();
//		if (DIO_read_pin(BASE_B, 2)) {
//			UART_sendByte(UART0, 'a');
//			rx();
//		}
//		if (UART_readByte(UART0) == 'a') {
//		}
//		keypad_dispatch(&keypad);
//		if ((key = keypad_get_key(&keypad)) != 0) {
//			sprintf(str, "%d", key);
//			lcd_print(&lcd, str);
//
//		}

//		TMU_Dispatch();

=======
	u8 key = 0;
	char str[2];
	gcfg_keypad_t keypad = { BASE_C, BASE_C };
	keypad_init(&keypad);
	gcfg_lcd_t lcd;
	lcd.RS = 7;
	lcd.RW = 6;
	lcd.EN = 5;
	lcd.controlPort = BASE_A;
	lcd.dataPort = BASE_B;
	lcd.nbit = n4BIT_MODE;
	lcd_init(&lcd);
	lcd_gotoxy(&lcd, 1, 1);
	lcd_print(&lcd, "xxxx xxxx");
//	sprintf(str, "%x", DIO_read_port(BASE_C, 0xf));
//	lcd_print(&lcd, str);
	lcd_gotoxy(&lcd, 1, 2);
	lcd_print(&lcd, "yyyy yyyy");
	while (1) {
		keypad_dispatch(&keypad);
		if ((key = keypad_get_key(&keypad)) != 0) {
			sprintf(str, "%x", key);
			lcd_print(&lcd, str);
			sprintf(str, "%x", DIO_read_port(BASE_C, 0xf));
			lcd_print(&lcd, str);
			key = 0;
		}

//		TMU_Dispatch();
>>>>>>> 4dc176ffe1bb20ece6c6e4ada9dacf7df24a391d
//		UART_sendByte(UART0, 'a');
//		if (UART_readByte(UART0) == 'a') {
//			DIO_write_pin(BASE_B, 0, !DIO_read_pin(BASE_B, 0));
//		}
	}
}
