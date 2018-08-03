/*
 * common.h
 *
 *  Created on: Aug 1, 2018
 *      Author: mh-sh
 */

#ifndef COMMON_H_
#define COMMON_H_

#define ECU_FREQ 1000000

typedef enum {
	E_FALSE = 0, E_TRUE,
} tenum_bool;

#define NULL ((void *)0)
typedef tenum_bool bool_t;
typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;

#endif /* COMMON_H_ */
