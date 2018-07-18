/*
 * Watch.c
 *
 * Created: 7/16/2018 1:24:37 PM
 *  Author: mh-sh
 */ 


#include <avr/io.h>
#include "TMU.h"
#include "seven_seg.h"

int currSec=1,currMin=10;
u8 secID1,secID10,minID1,minID10;

void function1(void * pv){
	seven_seg_display(secID1,currSec%10);
	if(currSec>=19)currMin++,currSec=0;
	
	currSec++;
}
void function2(void * pv){
	
	seven_seg_display(secID10,currSec/10);
	
}
void function3(void * pv){
	seven_seg_display(minID1,currMin%10);
	seven_seg_display(minID10,currMin++/10);
	
}

int main(void)
{
	
	Timer_OBJ obj1,obj2,obj3;
	TMU_init(0,5,0);
	seven_seg_init(BASE_C,COMMON_CATHOD,&secID1);
	seven_seg_init(BASE_D,COMMON_CATHOD,&secID10);
	
	seven_seg_init(BASE_A,COMMON_CATHOD,&minID1);
	seven_seg_init(BASE_B,COMMON_CATHOD,&minID10);
	
	TMU_addTimer(&obj1,500,PERIODIC,function1);
	TMU_addTimer(&obj2,5000,PERIODIC,function2);
	TMU_addTimer(&obj3,10000,PERIODIC,function3);
	
    while(1)
    {
		TMU_Dispatch();
        //TODO:: Please write your application code 
    }
}