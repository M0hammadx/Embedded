/*
 * lcd.h
 *
 *  Created on: Jul 28, 2018
 *      Author: Dell
 */

#ifndef HAL_LCD_H_
#define HAL_LCD_H_
#include "hal/hal_DIO.h"
#include <util/delay.h>

typedef enum {
	n4BIT_MODE, n8BIT_MODE
} genum_nBit_mode_t;

typedef struct {
	genum_nBit_mode_t nbit;
	enum_port_base_t controlPort; //upper
	enum_port_base_t dataPort; //lower
	u8 RS, RW, EN;
} gcfg_lcd_t;

void lcd_init(gcfg_lcd_t* lcd);
void lcd_send_command(gcfg_lcd_t * lcd, u8 cmd);
void lcd_send_data(gcfg_lcd_t * lcd, u8 data);
void lcd_gotoxy(gcfg_lcd_t * lcd, u8 x, u8 y);
void lcd_print(gcfg_lcd_t * lcd, char * str);
void lcd_clear();
void lcd_off();
void lcd_deinit();
#endif /* HAL_LCD_H_ */
