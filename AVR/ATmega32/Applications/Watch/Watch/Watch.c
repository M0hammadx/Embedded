/*
 * Watch.c
 *
 * Created: 7/16/2018 1:24:37 PM
 *  Author: mh-sh
 */ 


#include <avr/io.h>
#include "TMU.h"
#include "seven_seg.h"

int curr;
u8 id1,id10;

void function1(void * pv){
	seven_seg_display(id1,curr%10);
	seven_seg_display(id10,curr++/10);
	
}
int main(void)
{
	
	Timer_OBJ obj1;
	TMU_init(0,5,0);
	seven_seg_init(BASE_C,COMMON_CATHOD,&id1);
	seven_seg_init(BASE_D,COMMON_CATHOD,&id10);
	TMU_addTimer(&obj1,1000,PERIODIC,function1);
	
    while(1)
    {
		TMU_Dispatch();
        //TODO:: Please write your application code 
    }
}