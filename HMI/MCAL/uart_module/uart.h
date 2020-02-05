/*
 * uart.h
 *
 *  Created on: Jan 29, 2020
 *      Author: SALAH
 */

#ifndef MCAL_UART_MODULE_UART_H_
#define MCAL_UART_MODULE_UART_H_

#include "../../utility_header/common_macros.h"
#include "../../utility_header/micro_config.h"
#include "../../utility_header/std_types.h"
#include "uartREG.h"

extern volatile uint8 recieved_data ;

#ifndef NULL
#define NULL (void*)(0)
#endif
typedef enum{
	asynchronous , synchronous
}uartMode_t;

typedef enum{
	Disabled , Even=2 , Odd
}parityMode_t;

typedef enum{
	_1bit , _2bit
}stopBitNUM_t;

typedef enum{
	_5bit , _6bit , _7bit , _8bit
}charSize_t;

typedef enum{
	UARTrising , UARTfalling
}clockPolarity_t;

typedef struct{
	uartMode_t mode;
	parityMode_t parity;
	stopBitNUM_t stop_num;
	charSize_t char_size;
	clockPolarity_t polarity;
	uint16 baudrate;
}uartConfig_t;


void UART_init(uartConfig_t * uartConfig);
void UART_transmit(uint8 data);
uint8 UART_receive(void);
void UART_transmitString(uint8* data , uint8 size);
void UART_receiveString(uint8 * rec_data , uint8 size);
void UART_setcallback(void (*a_callback)(void));
#endif /* MCAL_UART_MODULE_UART_H_ */
