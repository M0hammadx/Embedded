/*
 * lcd.c
 *
 *  Created on: Aug 1, 2018
 *      Author: mh-sh
 */

#include "lcd.h"

void lcd_init(gcfg_lcd_t * lcd) {

	if (lcd->nbit == n4BIT_MODE) {
		DIO_init_port_output(lcd->controlPort, 0xF0);
		DIO_init_port_output(lcd->dataPort, 0xF0);
	} else if (lcd->nbit == n8BIT_MODE) {
		DIO_init_port_output(lcd->controlPort, 0xFF);
		DIO_init_port_output(lcd->dataPort, 0xFF);
	} else {
		// todo error
	}
	DIO_clear_pin(lcd->controlPort, (lcd->EN));
	_delay_us(2000);
	if (lcd->nbit == n4BIT_MODE) {

		lcd_send_command(lcd, 0x33); //vodoo
		lcd_send_command(lcd, 0x32); //vodoo
		lcd_send_command(lcd, 0x2C); //2 line , 5*11, 4bit
	} else if (lcd->nbit == n8BIT_MODE) {
		lcd_send_command(lcd, 0x3C); //2 line , 5*11, 8bit
	}

	lcd_send_command(lcd, 0x0E); //cursor on
	lcd_send_command(lcd, 0x06); //shift right
	lcd_send_command(lcd, 0x01); //clear
	_delay_us(2000);

}
void lcd_send_command(gcfg_lcd_t * lcd, u8 cmd) {
	DIO_clear_pin(lcd->controlPort, (lcd->RS));
	DIO_clear_pin(lcd->controlPort, (lcd->RW));

	if (lcd->nbit == n4BIT_MODE) {
		DIO_write_port(lcd->dataPort, 0xF0, (cmd & 0xF0));
		DIO_set_pin(lcd->controlPort, (lcd->EN));
		_delay_us(1);
		DIO_clear_pin(lcd->controlPort, (lcd->EN));
		_delay_us(100);
		DIO_write_port(lcd->dataPort, 0xF0, (cmd & 0xF) << 4);
	} else if (lcd->nbit == n8BIT_MODE) {
		DIO_write_port(lcd->dataPort, 0xFF, cmd);
	} else {
		// todo error
	}
	DIO_set_pin(lcd->controlPort, (lcd->EN));
	_delay_us(1);
	DIO_clear_pin(lcd->controlPort, (lcd->EN));
	_delay_us(100);
}
void lcd_send_data(gcfg_lcd_t * lcd, u8 data) {
	DIO_set_pin(lcd->controlPort, (lcd->RS));
	DIO_clear_pin(lcd->controlPort, (lcd->RW));

	if (lcd->nbit == n4BIT_MODE) {
		DIO_write_port(lcd->dataPort, 0xF0, (data & 0xF0));
		DIO_set_pin(lcd->controlPort, (lcd->EN));
		_delay_us(1);
		DIO_clear_pin(lcd->controlPort, (lcd->EN));
		_delay_us(100);
		DIO_write_port(lcd->dataPort, 0xF0, (data & 0xF) << 4);
	} else if (lcd->nbit == n8BIT_MODE) {
		DIO_write_port(lcd->dataPort, 0xFF, data);
	} else {
		// todo error
	}
	DIO_set_pin(lcd->controlPort, (lcd->EN));
	_delay_us(1);
	DIO_clear_pin(lcd->controlPort, (lcd->EN));
	_delay_us(100);
}

static const u8 firstCharAdr[] = { 0x80, 0xC0 };
void lcd_gotoxy(gcfg_lcd_t * lcd, u8 x, u8 y) {
//	if (x > 0&&) todo
	//00-27h , 40h-67h

	lcd_send_command(lcd, firstCharAdr[y - 1] + x - 1);
}
void lcd_print(gcfg_lcd_t * lcd, char * str) {
	u8 i = 0;
	while (str[i] != '\0')
		lcd_send_data(lcd, str[i++]);
}
void lcd_clear(gcfg_lcd_t * lcd) {
	lcd_send_command(lcd, 0x01); //clear
	_delay_us(2000);
}
void lcd_deinit(gcfg_lcd_t * lcd) {
	if (lcd->nbit == n4BIT_MODE) {
		DIO_deinit_port(lcd->dataPort, 0xF0);
	} else if (lcd->nbit == n8BIT_MODE) {
		DIO_deinit_port(lcd->dataPort, 0xFF);
	} else {
		// todo error
	}
	DIO_deinit_port(lcd->controlPort,
			(1 << (lcd->EN)) | (1 << (lcd->RS)) | (1 << (lcd->RW)));
	lcd->controlPort = 0;
	lcd->dataPort = 0;
	lcd->nbit = 0;

}
