/*
 * timer.h
 *
 *  Created on: Jan 5, 2020
 *      Author: mohamed salah
 */

#ifndef TIMER_H_
#define TIMER_H_

#ifndef NULL
#define NULL ((void *)0)
#endif
/*-----------------------------------------------include utility files---------------------------------------------*/

#include "../../utility_header/common_macros.h"
#include "../../utility_header/micro_config.h"
#include "../../utility_header/std_types.h"
#include "timerREG.h"

/*------------------------------------------------data type definitions-----------------------------------------------*/

#ifndef PRESCALER
#define PRESCALER
typedef enum {CLK_OFF , CLK_1 , CLK_8 , CLK_64 , CLK_256 , CLK_1024 , EX_T1_FALLING , EX_T1_RISING}prescaler;
#endif
typedef enum {overflow , compare }mode;
typedef enum {timer0 , timer1 , timer2}timerNUM_t;

typedef struct {
	/**************************************************************************************
	 * timer number specifies which timer will be configured
	 * it can be one of these values [timer0 , timer1 , timer2]
	 **************************************************************************************/
	timerNUM_t timerNUM;
	/**************************************************************************************
	 * timer can operate at [overflow , compare] modes
	 **************************************************************************************/
	mode timer_mode;
	/**************************************************************************************
	 * pre scaler value configure the frequency of timer = freq of CPU / prescaler
	 * [CLK_OFF , CLK_1 , CLK_8 , CLK_64 , CLK_256 , CLK_1024 , EX_T1_FALLING , EX_T1_RISING]
	 * selecting [CLK_OFF] will stop the timer
	 **************************************************************************************/
	prescaler timer_prescaler;
	/**************************************************************************************
	 * start or compare value in case of
	 * 1- overflow mode this value is loaded into timer counter to start form
	 * 2- compare mode timer always starts from 0 and interrupt at this value
	 **************************************************************************************/
	uint16 SCValue;
	/**************************************************************************************
	 * a pointer to function points to function to be called when interrupt request happen
	 **************************************************************************************/
	void (*CallbackfunctionPtr)(void);
}timerConfig_t;

/*--------------------------------------------------function prototypes----------------------------------------------*/

void TIMER_start(const timerConfig_t * timerConfig);
void TIMER_stop(const timerConfig_t * timerConfig);


#endif /* TIMER1_H_ */
