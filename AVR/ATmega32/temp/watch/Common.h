/*
 * common.h
 *
 *  Created on: Aug 1, 2018
 *      Author: mh-sh
 */

#ifndef COMMON_H_
#define COMMON_H_

#define f_speed (1000000) //user set it here todo ecu config

#define ECU_FREQ ((long long) f_speed)
#define SFR_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr))
#define SFR_WORD(mem_addr) (*(volatile uint16_t *)(mem_addr))
#define SFR_DWORD(mem_addr) (*(volatile uint32_t *)(mem_addr))

typedef enum {
	E_FALSE = 0, E_TRUE,
} tenum_bool;

#define NULL ((void *)0)
typedef tenum_bool bool_t;
typedef signed char s8;
typedef short int s16;
typedef long int s32;

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;

#endif /* COMMON_H_ */
