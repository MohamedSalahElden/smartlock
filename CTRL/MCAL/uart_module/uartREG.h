/*
 * uartREG.h
 *
 *  Created on: Jan 29, 2020
 *      Author: SALAH
 */

#ifndef MCAL_UART_MODULE_UARTREG_H_
#define MCAL_UART_MODULE_UARTREG_H_

#include "../../utility_header/std_types.h"


typedef struct {
	uint8 	_UBRR 	: 	4 	;
	uint8			:	3 	;
	uint8	_URSEL	:	1 	;	/*Register Select*/
}UBRRH_t;
typedef struct {
	uint8	_UCPOL	:	1 	;	/*clock polarity */
	uint8	_UCSZ1_0:	1 	;	/*character size*/
	uint8	_USBS	:	1 	;	/*stop bit select*/
	uint8	_UPM	:	2 	;	/*Parity mode*/
	uint8	_UMSEL	:	1 	;	/*USART mode select*/
	uint8	_URSEL	:	1 	;	/*register select*/
}UCSRC_t;
typedef struct {
	uint8	_TXB8	:	1	;	/*Transmit data bit 8*/
	uint8	_RXB8	:	1	;	/*Receive data bit 8*/
	uint8	_UCSZ2	:	1	;	/*Character size*/
	uint8	_TXEN	:	1	;	/*transmitter enable*/
	uint8	_RXEN	:	1	;	/*Receiver enable*/
	uint8	_UDRIE	:	1	;	/*USART data register empty interrupt enable*/
	uint8	_TXCIE	:	1	;	/*Transition complete interrupt enable*/
	uint8	_RXCIE	:	1	;	/*Receive complete interrupt enable*/
}UCSRB_t;
typedef struct {
	uint8	_MPCM	:	1	;	/*multiprocessor communication mode*/
	uint8	_U2X	:	1	;	/*double the UART transmission speed*/
	uint8	_PE		:	1	;	/*parity error*/
	uint8	_DOR	:	1	;	/*data over run*/
	uint8	_FE		:	1	;	/*frame error (error in start or stop bit) */
	uint8	_UDRE	:	1	;	/*UART data register is empty flag*/
	uint8	_TXC	:	1	;	/*Transmit complete flag*/
	uint8	_RXC	:	1	;	/*Receive complete flag*/
}UCSRA_t;


#define _UBRRH		(*(volatile UBRRH_t	 * const)(0X40))
#define _UCSRC		(*(volatile UCSRC_t	 * const)(0X40))
#define _UDR		(*(volatile uint8	 * const)(0X2C))
#define _UCSRA		(*(volatile UCSRA_t	 * const)(0X2B))
#define _UCSRB		(*(volatile UCSRB_t	 * const)(0X2A))
#define _UBRRL		(*(volatile uint8	 * const)(0X29))

#endif /* MCAL_UART_MODULE_UARTREG_H_ */
