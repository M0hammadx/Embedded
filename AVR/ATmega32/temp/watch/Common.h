/*
 * common.h
 *
 *  Created on: Jun 23, 2018
 *      Author: hossam.adel
 */

#ifndef COMMON_H_
#define COMMON_H_

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
