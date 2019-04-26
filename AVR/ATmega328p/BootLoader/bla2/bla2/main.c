/*
* bla.c
*
* Created: 3/7/2019 12:12:15 AM
* Author : mh-sh
*/
#define Mhz 1000000UL
#define F_CPU 1*Mhz
#include "UART/UART.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/boot.h>
#include <avr/lock.h>
#include <avr/sfr_defs.h>
#include <avr/eeprom.h>

#include <inttypes.h>
#include <avr/pgmspace.h>

#define APP_RECEIVE_END 0xFF
#define APP_RECEIVE_START_SIZE 3
#define APP_TEMP_RAM_START_POS 0x200

typedef union {
	uint8_t  *bptr;
	uint16_t *wptr;
	uint16_t word;
	uint8_t bytes[2];
} addr16_t;

void WDT_reset();
void CleanBL();
void run_app();
void boot_program_page (uint32_t page, uint8_t *buf);
void boot_program_page_size (uint32_t page, uint8_t *buf,uint8_t pSize);
void pageR(uint32_t page, uint8_t *buf);

//asm pos
extern uint8_t RAM_READ_BYTE(uint16_t);
extern void RAM_WRITE_BYTE(uint16_t,uint8_t);
extern void BL_CPY_RAM_FLASH(uint16_t,uint16_t,uint16_t);
extern void BL_CPY_EE_FLASH(uint16_t,uint16_t,uint16_t);
extern void Write_page(uint16_t,uint16_t);
extern uint8_t EE_READ_BYTE(uint16_t);
extern uint8_t ret_one(void);
extern void JUMP0000(void);
extern void Erase_buff_page(uint16_t);
extern void Fill_buff_page(uint16_t,uint16_t);
extern void Write_buff_page(uint16_t);

int RX_byte_idx = 0;
uint8_t AppRamAvailable=0,AppFlashAvailable=0,ReceivingApp=0,ReceivingHeader=0; //states
uint8_t APP_RECEIVE_HEADER[APP_RECEIVE_START_SIZE]={0x55,0x66,0x77},receive_header_idx=0;
void rx(u8 data) { //TODO this should be moved out of the ISR 
	//eeprom_write_byte((uint8_t *)(RX_byte_idx), data);
	if(ReceivingApp&&data==APP_RECEIVE_END){
		ReceivingApp=0,AppRamAvailable=1;
		return;
	}
	if(receive_header_idx==0&&data==APP_RECEIVE_HEADER[0]){
		ReceivingHeader=1;
		receive_header_idx=1;
		return;
	}
	if(receive_header_idx>0&&receive_header_idx<APP_RECEIVE_START_SIZE){
		if(data!=APP_RECEIVE_HEADER[receive_header_idx++]){
			receive_header_idx=0;
		}
		return;
	}
	if(!ReceivingApp&&receive_header_idx==APP_RECEIVE_START_SIZE){
		ReceivingApp=1;
		RX_byte_idx=0;
	}
	if(ReceivingApp){
		RAM_WRITE_BYTE(APP_TEMP_RAM_START_POS+(RX_byte_idx), data);
		RX_byte_idx++;
	}
}
u16 data;
u8 temp;
u16 i;
u8 lastEE;
void BL_Flash_App(u16 flash_adr, u16 eeprom_adr, u16 code_size) {
	for ( i = 0; i < code_size; i += 2) {
		data=0;
		data&=0;
		data&=lastEE;
		temp=EE_READ_BYTE(eeprom_adr + i);
		data =temp<<8;
		//data<<=8;
		temp=EE_READ_BYTE(eeprom_adr + i + 1);
		data &=0xff;
		data &=0xff;
		data &=0xff;
		data =data&0xff;
		
		data |= temp;
		lastEE=data;
		Write_page(flash_adr + i, data);
	}
}
void BL_Flash_AppR(u16 flash_adr, u16 eeprom_adr, u16 code_size) {
	for ( i = 0; i < code_size; i += 2) {
		data=0;
		data&=0;
		data&=lastEE;
		temp=RAM_READ_BYTE(eeprom_adr + i);
		data =temp<<8;
		//data<<=8;
		temp=RAM_READ_BYTE(eeprom_adr + i + 1);
		data &=0xff;
		data &=0xff;
		data &=0xff;
		data =data&0xff;
		
		data |= temp;
		lastEE=data;
		Write_page(flash_adr + i, data);
	}
}

uint8_t x=0x55;
uint8_t xarr[]={0x55,0x66};
int main(void) {
	
	
	//for (i = 0; i < 128; i+=2)
	//{
	//Fill_buff_page(0x00+i,0x5566);
	//}
	//
	//
	//Write_buff_page(0x00);
	//
	//for (x = 0; x < 128;x+=2)
	//{
	//Fill_buff_page(0x100+x,0x1122);
	//}
	//Write_buff_page(0x100);
	//
	//
	//Erase_buff_page(0x00);
	//
	//Fill_buff_page(0x00+0,0x5566);
	//Fill_buff_page(0x00+02,0x5566);
	//Fill_buff_page(0x00+04,0x5566);
	//
	//
	//Write_buff_page(0x00);
	
	_delay_ms(150);//debounce
	
	//CLKPR = (1 << CLKPCE); // Enable change of CLKPS bits
	//CLKPR = 0x00; //no prescaler
	//asm("jmp 0000");
	
	//boot_program_page(0x0,xarr);
	//JUMP0000();
	//eeprom_write_byte(0x10, 0x55);
	//Write_page();
	
	MCUCR = (1<<IVCE);
	MCUCR = (1<<IVSEL);
	DDRB &= ~(1 << DDB0);
	DDRB |= (1 << DDB1);
	//DDRC = 0xFF;
	PCMSK0 |= (1<<PCINT0);
	PCICR |= (1<<PCIE0);

	UART_init(0, 2400);
	UART_addISR(0, UART_RX, rx);
	sei();
	//pageR(0, &xarr);
	
	Write_page(0x0,0x3344);
	Erase_buff_page(0x04);
	//Write_page(0x4,0x4433);
	//for (;x<16;x++)
	//{
	////Write_page(x,0x5555);
	//rx(x);
	//}
	//BL_Flash_App(0,0,RX_byte_idx);
	//x=EE_READ_BYTE(0x7788);
	//BL_CPY_EE_FLASH(0,0,x);
	//RAM_WRITE_BYTE(0x102,0x55);
	//BL_Flash_AppR(0,0x100,x);
	//BL_CPY_RAM_FLASH(0,0x10c,x);
	//Write_page(0x5,0x3344);
	//RAM_WRITE_BYTE(0x102,0x55);
	//x=ret_one();
	//boot_page_erase_safe(0x2000);
	//boot_page_fill_safe(0x2000,0x5555);
	//boot_page_write_safe(0x2000);
	
	
	//SPMCSR=(1<<SELFPRGEN)|(1<<PGWRT);
	
	
	
	//asm("jmp 0x3800");
	
	
	//boot_rww_enable ();
	//PORTB |= (1 << PORTB1);
	if(pgm_read_byte(0x0000)!=0xff){
		AppRamAvailable=1;
	}
	//if(EE_READ_BYTE(0x10)==0x55){
	//PORTB |= (1 << PORTB1);
	//}
	
	while(1) {
		if(AppRamAvailable){
			BL_CPY_RAM_FLASH(0,APP_TEMP_RAM_START_POS,RX_byte_idx);
			AppFlashAvailable=1;
			AppRamAvailable=0;
		}
		//PORTC = RX_byte_idx;
		//if((PINB & (1 << PINB0))==1){
		////PORTB &= ~(1 << DDB1); //run off
		////PORTB = (1 << PORTB1);
		////run_app();
		//}
		//else{
		//PORTB = (0 << PORTB1);
		////PORTB |= (1 << PORTB1); //run on
		//}
		
		//PORTB = (1 << PORTB1);
		//_delay_ms(1000);
		//PORTB = (0 << PORTB1);
		//_delay_ms(1000);
	}
	return 0;
}

ISR(PCINT0_vect)
{
	//x=1;
	//PORTB = (1 << PORTB1);
	//PORTB &= ~(1 << DDB1); //run off
	if(AppFlashAvailable&&!ReceivingApp)
		run_app();
}

void WDT_reset(){
	//sei();
	cli();
	wdt_enable(WDTO_15MS);
	while (1);
}
void CleanBL(){
	DDRB =0;
	PCMSK2 =0;
	PCICR =0;
}
void run_app(){
	CleanBL();
	
	//for (uint8_t i=0; i<404; i+=2)
	//{
	//page(i,appCode+i);
	//}
	//
	//boot_rww_enable ();
	
	//boot_program_page(0,appCode);
	// Put interrupts back in app land
	MCUCR= (1<<IVCE);
	MCUCR = 0;
	
	// Run the application
	asm("jmp 0000");
}
//void write_program_full(uint32_t page, uint8_t *buf,uint8_t pSize){
//while (pSize-128>=0)
//{
//boot_program_page (page, appCode);
//}
//}

void pageR(uint32_t page, uint8_t *buf){
	boot_page_erase(page);
	boot_spm_busy_wait ();
	uint16_t w = *buf++;
	w += (*buf++) << 8;
	boot_page_fill(page,w);
	boot_page_write(page);
	boot_spm_busy_wait ();
}
void boot_program_page_size (uint32_t page, uint8_t *buf,uint8_t pSize)
{
	uint16_t i;
	uint8_t sreg;
	// Disable interrupts.
	sreg = SREG;
	cli();
	eeprom_busy_wait ();
	boot_page_erase (page);
	boot_spm_busy_wait ();      // Wait until the memory is erased.
	for (i=0; i<pSize; i+=2)
	{
		// Set up little-endian word.
		uint16_t w = *buf++;
		w += (*buf++) << 8;
		
		boot_page_fill (page + i, w);
	}
	boot_page_write (page);     // Store buffer in flash page.
	boot_spm_busy_wait();       // Wait until the memory is written.
	// Reenable RWW-section again. We need this if we want to jump back
	// to the application after bootloading.
	boot_rww_enable ();
	// Re-enable interrupts (if they were ever enabled).
	sei();
	SREG = sreg;
}
void boot_program_page (uint32_t page, uint8_t *buf)
{
	
	boot_rww_enable ();
	
	uint16_t i;
	uint8_t sreg;
	// Disable interrupts.
	sreg = SREG;
	cli();
	eeprom_busy_wait ();
	boot_page_erase (page);
	boot_spm_busy_wait ();      // Wait until the memory is erased.
	for (i=0; i<SPM_PAGESIZE; i+=2)
	{
		// Set up little-endian word.
		uint16_t w = *buf++;
		w += (*buf++) << 8;
		
		boot_page_fill (page + i, w);
	}
	boot_page_write (page);     // Store buffer in flash page.
	boot_spm_busy_wait();       // Wait until the memory is written.
	// Reenable RWW-section again. We need this if we want to jump back
	// to the application after bootloading.
	boot_rww_enable ();
	// Re-enable interrupts (if they were ever enabled).
	sei();
	SREG = sreg;
}