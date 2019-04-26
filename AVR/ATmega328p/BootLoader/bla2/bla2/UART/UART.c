/*
 * USART.c
 *
 *  Created on: Aug 1, 2018
 *      Author: mh-sh
 */

#include "UART.h"


typedef void (*USART_RX_fptr)(u8);
typedef void (*USART_TX_fptr)();

USART_RX_fptr ISR_USART_RX_CB;
USART_TX_fptr ISR_USART_TX_CB;

ISR(USART_UDRE_vect) {

}
ISR(USART_RX_vect) {
	if (ISR_USART_RX_CB)
		ISR_USART_RX_CB(UDR0);
}
ISR(USART_TX_vect) {
	if (ISR_USART_TX_CB)
		ISR_USART_TX_CB();
}
void UART_addISR(UART_NUM_t UART, UART_INTERRUPT_t ISR_type, void (*ISR_CB)()) {

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)

	if (ISR_type == UART_RX) {
		ISR_USART_RX_CB = (USART_RX_fptr) ISR_CB;
		UCSR0B |= (1 << RXCIE0);
	} else if (ISR_type == UART_TX) {
		ISR_USART_TX_CB = (USART_TX_fptr) ISR_CB;
		UCSR0B |= (1 << TXCIE0);
	}
#endif

}

void UART_init(UART_NUM_t UART, u32 BAUD_RATE) {
	//calc baudRate
//	u16 UBRR_16Bit = round(((F_CPU / 16 + BAUD_RATE / 2) / BAUD_RATE - 1));
//	u16 UBRR_16Bit = round((F_CPU / BAUD_RATE / 16 - 1));
	u16 UBRR_16Bit = round((F_CPU / (16 * BAUD_RATE) - 1));
#ifdef __AVR_ATmega128__
	if(bootuart == 1) {
		UBRR0L = (uint8_t)(F_CPU/(BAUD_RATE*16L)-1);
		UBRR0H = (F_CPU/(BAUD_RATE*16L)-1) >> 8;
		UCSR0A = 0x00;
		UCSR0C = 0x06;
		UCSR0B = _BV(TXEN0)|_BV(RXEN0);
	}
	if(bootuart == 2) {
		UBRR1L = (uint8_t)(F_CPU/(BAUD_RATE*16L)-1);
		UBRR1H = (F_CPU/(BAUD_RATE*16L)-1) >> 8;
		UCSR1A = 0x00;
		UCSR1C = 0x06;
		UCSR1B = _BV(TXEN1)|_BV(RXEN1);
	}
#elif defined __AVR_ATmega163__
	UBRR = (uint8_t)(F_CPU/(BAUD_RATE*16L)-1);
	UBRRHI = (F_CPU/(BAUD_RATE*16L)-1) >> 8;
	UCSRA = 0x00;
	UCSRB = _BV(TXEN)|_BV(RXEN);
#elif defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)

	UBRR0H = UBRR_16Bit >> 8;
	UBRR0L = UBRR_16Bit;

	//UBRR0L = (uint8_t)(F_CPU/(BAUD_RATE*16L)-1);
	//UBRR0H = (F_CPU/(BAUD_RATE*16L)-1) >> 8;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);  //8-bit - 1stop - no parity
#elif defined __AVR_ATmega8__
			/* m8 */
			UBRRH = (((F_CPU/BAUD_RATE)/16)-1)>>8; // set baud rate
			UBRRL = (((F_CPU/BAUD_RATE)/16)-1);
			UCSRB = (1<<RXEN)|(1<<TXEN);// enable Rx & Tx
			UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);// config USART; 8N1
#else
			/* m16,m32,m169,m8515,m8535 */
			UBRRL = (uint8_t)(F_CPU/(BAUD_RATE*16L)-1);
			UBRRH = (F_CPU/(BAUD_RATE*16L)-1) >> 8;
			UCSRA = 0x00;
			UCSRC = 0x06;
			UCSRB = _BV(TXEN)|_BV(RXEN);
#endif
}

UARTError_t UART_getError(UART_NUM_t UART) {
	UARTError_t ret_error = NO_ERROR;
#ifdef __AVR_ATmega32__
	if (UCSRA & ((1 << FE) | (1 << DOR) | (1 << PE))) {
		if (UCSRA & (1 << FE)) {
			ret_error = Framing_Error;
		} else if (UCSRA & (1 << DOR)) {
			ret_error = Overrun_Error;
		} else if (UCSRA & (1 << PE)) {
			ret_error = Parity_Error;
		}
	}
#endif
	return ret_error;

}

u8 UART_readByte(UART_NUM_t UART) { //Blocking
#ifdef __AVR_ATmega32__
while (!(UCSRA & (1 << RXC)));
return UDR;
#elif defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
	/* Wait for data to be received */
	while (!(UCSR0A & (1 << RXC0)))
		;
	/* Get and return received data from buffer */
	return UDR0;
#endif

}
//#ifdef __AVR_ATmega32__
//
//#elif defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
//
//#endif
void UART_sendByte(UART_NUM_t UART, u8 data) { //Blocking
#ifdef __AVR_ATmega32__

while (!(UCSRA & (1 << UDRE)))
;

UDR = Chr;
#elif defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
	/* Wait for empty transmit buffer */
	while (!( UCSR0A & (1 << UDRE0)))
		;
	/* Put data into buffer, sends the data */
	UDR0 = data;
#endif
}

void UART_sendString(UART_NUM_t UART, char *String) {
	u8 i = 0;
	while (String[i] != '\0') {
		UART_sendByte(UART, String[i++]);
	}
}

void UART_sendPacket(UART_NUM_t UART, char A[], u8 N) {
	u8 i = 0;
	while (i < N) {
		UART_sendByte(UART, A[i++]);
	}

}
u8 UART_dataReady(UART_NUM_t UART) {
#ifdef __AVR_ATmega32__
	return (UCSRA & (1 << RXC));
#elif defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
	return (UCSR0A & (1 << RXC0));
#else
	return 0;
#endif
}

void UART_Flush(void) {
	UART_readByte(0);
}

void UART_deinit(UART_NUM_t UART) {
#ifdef __AVR_ATmega32__
	UBRRH = 0;
	UBRRL = 0;
	UCSRB = 0;
	UCSRC = 0;
#elif defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
	UBRR0H = 0;
	UBRR0L = 0;
	UCSR0B = 0;
	UCSR0C = 0;
#endif
	ISR_USART_RX_CB = 0;
	ISR_USART_TX_CB = 0;
}
