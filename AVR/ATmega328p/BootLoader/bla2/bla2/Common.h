/*
 * common.h
 *
 *  Created on: Aug 1, 2018
 *      Author: mh-sh
 */

#ifndef COMMON_H_
#define COMMON_H_

#define Mhz 1000000UL
#define F_CPU 1*Mhz

typedef enum {
	E_FALSE = 0, E_TRUE,
} tenum_bool;

#define NULL ((void *)0)
typedef tenum_bool bool_t;
typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned short int s16;
typedef unsigned long int u32;
typedef unsigned long int s32;

#ifndef _SFR_BYTE
#define _SFR_BYTE(mem_addr) (*(volatile u8 *)(mem_addr))
#define _SFR_WORD(mem_addr) (*(volatile u16 *)(mem_addr))
#define _SFR_DWORD(mem_addr) (*(volatile u32 *)(mem_addr))
#endif

#endif /* COMMON_H_ */
