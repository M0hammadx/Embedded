/*
 * I2C.h
 *
 *  Created on: Aug 3, 2018
 *      Author: Dell
 */

#ifndef DEBUG_HAL_I2C_I2C_H_
#define DEBUG_HAL_I2C_I2C_H_

#include "../../Common.h"
#include <avr/io.h>

void I2C_init(u32 SCL_freq);
void I2C_master_send();
void I2C_master_recieve();
void I2C_slave_send();
void I2C_slave_recieve();

#endif /* DEBUG_HAL_I2C_I2C_H_ */
