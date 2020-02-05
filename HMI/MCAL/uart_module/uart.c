/*
 * uart.c
 *
 *  Created on: Jan 29, 2020
 *      Author: SALAH
 */

#include "uart.h"

volatile uint8 recieved_data ;
volatile void(*g_callback)(void) = NULL;


void UART_init(uartConfig_t * uartConfig){

	uint16 baudrate_reg = 0;
	if(uartConfig->mode == asynchronous){
		baudrate_reg = ((F_CPU / (16UL * (uartConfig->baudrate))) - 1);
	}
	else if(uartConfig->mode == synchronous){
		baudrate_reg = (uint16)((F_CPU / (2.0 * uartConfig->baudrate)) - 1);
	}

	_UCSRB._TXEN = 1;	/*Receiver enabled*/
	_UCSRB._RXEN = 1;	/*transmitter enabled*/

	_UCSRB._UCSZ2 = 0;	/*Character size will not be 9*/

	_UCSRC._URSEL 	= 1;						/*this bit set to one to allow accessing to UCSRC */
	_UCSRC._UMSEL 	= uartConfig->mode ;		/*configure the mode of UART*/
	_UCSRC._UPM 	= uartConfig->parity ;		/*configure the parity bits type */
	_UCSRC._USBS 	= uartConfig->stop_num;		/*configure the number of stop bits*/
	_UCSRC._UCSZ1_0 = uartConfig->char_size;	/*configure the character size*/
	_UCSRC._UCPOL 	= uartConfig->polarity ;	/*configure the polarity*/

	_UCSRB._RXCIE 	= 1;	/*enable receiving interrupt*/

	_UCSRC._URSEL = 0;								/*this bit set to zero to allow accessing to UBRR */
	_UBRRH._UBRR = (uint8)((baudrate_reg) >> 8);	/*configure the most 4 bits of UBRR*/
	_UBRRL = baudrate_reg;					/*configure the least 8 bits of UBRR register*/


}
void UART_transmit(uint8 data){
//	while(!_UCSRA._UDRE);	/*wait until the the register is empty*/
	while(BIT_IS_CLEAR(UCSRA , UDRE)) ;
	_UDR = data;			/*send the data*/
}
uint8 UART_receive(void){
	while(!_UCSRA._RXC);	/*wait until the receiving operation completes*/
	return _UDR;			/*return the received data*/
}


void UART_transmitString(uint8* data , uint8 size){
	uint8 i = 0;
	while(i<size){
		UART_transmit(data[i]);
		i++;
	}
}
void UART_receiveString(uint8 * rec_data , uint8 size){
	uint8 i = 0;
	while(i<size){
		rec_data[i] = UART_receive();
		i++;
	}
}

void UART_setcallback(void (*a_callback)(void)){
	g_callback = (volatile void *)a_callback;
}

ISR(USART_RXC_vect){
	recieved_data = _UDR;
	if(g_callback != NULL){
		(*g_callback)();
	}
}











