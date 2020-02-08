/*
 * HW_config.c
 *
 *  Created on: Feb 5, 2020
 *      Author: SALAH
 */

#include "HMI_utility_functions.h"
/*----------------------------------------------------------------
 * buzzer hardware configuration
 *---------------------------------------------------------------- */
CHconfig_t buzzer = {
		.PORT 				=  portD ,
		.channel_num 		= pin7 ,
		.direction 			= output ,
		.internal_resistor 	= none
};
/*----------------------------------------------------------------
 * UART peripheral configuration
 *---------------------------------------------------------------- */
uartConfig_t uart = {
		.mode 		= asynchronous ,
		.parity 	= Disabled ,
		.stop_num 	= _1bit ,
		.char_size 	= _8bit ,
		.polarity 	= UARTrising ,
		.baudrate 	= 9600
};
/*----------------------------------------------------------------
 * down button external interrupt  hardware configuration
 *------------------------------------------------------------- */
EINT_t downbutton = {
		.ch = E_INT1 ,
		.INT_SC = falling ,
		.internal_resistor = internal_pullup ,
		.INT_handler = movedown
};
/*----------------------------------------------------------------
 * up button external interrupt  hardware configuration
 *------------------------------------------------------------- */
EINT_t upbutton = {
		.ch = E_INT0 ,
		.INT_SC = falling ,
		.internal_resistor = internal_pullup ,
		.INT_handler = moveup
};
/*----------------------------------------------------------------
 * select button external interrupt  hardware configuration
 *------------------------------------------------------------- */
EINT_t selectbutton = {
		.ch = E_INT2 ,
		.INT_SC = falling ,
		.internal_resistor = internal_pullup ,
		.INT_handler = select
};



