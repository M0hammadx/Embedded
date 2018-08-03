/*
 * E2PROM.h
 *
 *  Created on: Aug 3, 2018
 *      Author: Dell
 */

#ifndef ECU_E2PROM_H_
#define ECU_E2PROM_H_

#include "../../Common.h"
#include "../../HAL/I2C/I2C.h"

void E2PROM_init();
void E2PROM_write_byte();
void E2PROM_write_byteArray();
void E2PROM_read_byte();
void E2PROM_read_byteArray();

#endif /* ECU_E2PROM_H_ */
