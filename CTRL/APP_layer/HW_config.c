/*
 * HW_config.c
 *
 *  Created on: Feb 5, 2020
 *      Author: SALAH
 */

#include "controller_utility_functions.h"

/***********************************************************************************/
motorConfig_t motor1 = {
		.motorPIN0 = {
				.PORT 				= portB ,
				.channel_num 		= pin0 ,
				.direction 			= output ,
				.internal_resistor 	= none
		} ,
		.motorPIN1 = {
				.PORT 				= portB ,
				.channel_num 		= pin1 ,
				.direction 			= output ,
				.internal_resistor 	= none
		} ,
		.enablePIN = OC2 ,
		.direction = CW
};
/***********************************************************************************/
timerConfig_t motortimer = {
		.timerNUM 				= timer1,
		.timer_mode 			= compare,
		.timer_prescaler 		= CLK_256,
		.SCValue				= 31250,
		.CallbackfunctionPtr 	= motorTimerInterruptHandler
};
/***********************************************************************************/
timerConfig_t keepOpenTimer = {
		.timerNUM 				= timer1,
		.timer_mode 			= compare,
		.timer_prescaler 		= CLK_256,
		.SCValue				= 31250,
		.CallbackfunctionPtr 	= keepOpeninterruptHandler
};
/***********************************************************************************/
timerConfig_t alarmTimer = {
		.timerNUM 				= timer1,
		.timer_mode 			= compare,
		.timer_prescaler 		= CLK_256,
		.SCValue				= 31250,
		.CallbackfunctionPtr 	= alarminterruptHandler
};
/***********************************************************************************/
uartConfig_t uart = {
		.mode 		= asynchronous ,
		.parity 	= Disabled ,
		.stop_num 	= _1bit ,
		.char_size 	= _8bit ,
		.polarity 	= UARTrising ,
		.baudrate 	= 9600
};
/***********************************************************************************/
CHconfig_t alarm = {
		.PORT 				= portA ,
		.channel_num 		= pin7 ,
		.direction 			= output ,
		.internal_resistor 	= none
};



