/*
 * hal_UART.c
 *
 *  Created on: Jul 28, 2018
 *      Author: Dell
 */
#include "hal_UART.h"

void USART_Init(unsigned int baud) {
	/* Set baud rate */
	UBRRH = (unsigned char) (baud >> 8);
	UBRRL = (unsigned char) baud;
	/* Enable receiver and transmitter */
	UCSRB = (1 << RXEN) | (1 << TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1 << URSEL) | (1 << USBS) | (3 << UCSZ0);
}
void USART_Transmit(unsigned char data) {
	/* Wait for empty transmit buffer */
	while (!(UCSRA & (1 << UDRE)))
		;
	/* Put data into buffer, sends the data */
	UDR = data;
}
void USART_Transmit9(unsigned int data) {
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE))) )
	;
	/* Copy 9th bit to TXB8 */
	UCSRB &= ~(1 << TXB8);
	if (data & 0x0100)
		UCSRB |= (1 << TXB8);
	/* Put data into buffer, sends the data */
	UDR = data;
}
unsigned char USART_Receive(void) {
	/* Wait for data to be received */
	while (!(UCSRA & (1 << RXC)))
		;
	/* Get and return received data from buffer */
	return UDR;
}
unsigned int USART_Receive9(void) {
	unsigned char status, resh, resl;
	/* Wait for data to be received */
	while (!(UCSRA & (1 << RXC)))
		;
	/* Get status and 9th bit, then data */
	/* from buffer */
	status = UCSRA;
	resh = UCSRB;
	resl = UDR;
	/* If error, return -1 */
	if (status & (1 << FE) | (1 << DOR) | (1 << PE))
		return -1;
	/* Filter the 9th bit, then return */
	resh = (resh >> 1) & 0x01;
	return ((resh << 8) | resl);
}
void USART_Flush(void) {
	unsigned char dummy;
	while (UCSRA & (1 << RXC))
		dummy = UDR;
}
