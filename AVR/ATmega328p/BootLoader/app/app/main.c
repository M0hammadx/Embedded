/*
* app.c
*
* Created: 3/10/2019 12:33:02 AM
* Author : mh-sh
*/
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
void WDT_reset();
ISR(PCINT0_vect)
{
	WDT_reset();
}
int main(void)
{
//	_delay_ms(150);//debounce
	DDRB &= ~(1 << DDB0);
	
	PCMSK0 |= (1<<PCINT0);
	PCICR |= (1<<PCIE0);
	//sei();
	
	DDRB |= (1 << DDB1);
	while (1)
	{
		if((PINB & (1 << PINB0))==0){
			WDT_reset();
		}
		//PORTB = (1 << PORTB5);
		//_delay_ms(100);
		PORTB = (1 << PORTB1);//rly nigga?
		//_delay_ms(100);
	}
}

void WDT_reset(){
	//sei();
	cli();
	wdt_enable(WDTO_15MS);
	while (1);
}