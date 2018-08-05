/*
 * lcd.h
 *
 *  Created on: Jul 28, 2018
 *      Author: Dell
 */

#ifndef HAL_LCD_H_
#define HAL_LCD_H_

#include <util/delay.h>
#include "../HAL/DIO/DIO.h"

typedef enum {
	n4BIT_MODE = 1, n8BIT_MODE
} genum_nBit_mode_t;

typedef struct {
	genum_nBit_mode_t nbit;
	enum_port_base_t dataPort; //upper
	enum_port_base_t controlPort;
	u8 RS, RW, EN;
} gcfg_lcd_t;

void lcd_init(gcfg_lcd_t* lcd);
void lcd_send_command(gcfg_lcd_t * lcd, u8 cmd);
void lcd_send_data(gcfg_lcd_t * lcd, u8 data);
void lcd_gotoxy(gcfg_lcd_t * lcd, u8 x, u8 y);
void lcd_print(gcfg_lcd_t * lcd, char * str);
void lcd_clear(gcfg_lcd_t * lcd);
void lcd_off();
void lcd_deinit(gcfg_lcd_t * lcd);
#endif /* HAL_LCD_H_ */
