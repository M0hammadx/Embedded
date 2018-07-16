/*
 * seven_seg.c
 *
 * Created: 7/13/2018 10:47:02 PM
 *  Author: mh-sh
 */ 


#include <avr/io.h>

#include "seven_seg.h"
int main(void)
{
	ecore_u8 id;
	
	seven_seg_init(BASE_C,COMMON_CATHOD,&id);
	seven_seg_display(id,9);
	//for(int i=0;i<80000;i++);
	seven_seg_display(id,5);
	//for(int i=0;i<20000;i++);
	seven_seg_reset(id);
	seven_seg_deinit(id);
	seven_seg_display(id,5);
    while(1)
    {
        //TODO:: Please write your application code 
    }
}