/*
* TimerMangUnit.c
*
* Created: 7/14/2018 11:02:20 AM
*  Author: Dell
*/


#include <avr/io.h>

#include "TMU.h"

void function1(void * pv){
	DDRA=1;
	PORTA^=1;
}
void function2(void * pv){
	DDRB=1;
	PORTB^=1;
}
void function3(void * pv){
	DDRC=1;
	PORTC^=1;
}
int main(void)
{
	Timer_OBJ obj1,obj2,obj3;
	TMU_init(0,5,0);
	
	TMU_addTimer(&obj1,100,PERIODIC,function1);
	TMU_addTimer(&obj2,50,PERIODIC,function2);
	TMU_addTimer(&obj3,50,PERIODIC,function3);
	
	//TMU_removeTimer(&obj1);
	
	while(1)
	{
		TMU_Dispatch();
		//TODO:: Please write your application code
	}
}