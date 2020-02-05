/*
 * timer.c
 *
 *  Created on: Jan 5, 2020
 *      Author: mohamed salah-el-den
 *
 */

#include "timer.h"
/*---------------------------------------------------------------------------
 * these global variables is used store the address of user funtion to be
 * called when an interrupt event happen
 *--------------------------------------------------------------------------- */
static volatile void (*g_timer0compare)  (void) = NULL;
static volatile void (*g_timer1compare)  (void) = NULL;
static volatile void (*g_timer2compare)  (void) = NULL;
static volatile void (*g_timer0overflow) (void) = NULL;
static volatile void (*g_timer1overflow) (void) = NULL;
static volatile void (*g_timer2overflow) (void) = NULL;

/*---------------------------------------------------------------------------
 * these variables is used to reload the timer counter register at interrupt
 *--------------------------------------------------------------------------- */
static volatile uint16 timer0_Reload ;
static volatile uint16 timer1_Reload ;
static volatile uint16 timer2_Reload ;

/* ---------------------------------------------------------------------------------------------------------------------
 * function name : TIMER_stop
 * arguments : structure of type timerConfig_t contains
 * 				{timerNUM , timer_mode , timer_prescaler , compareValue , CallbackfunctionPtr}
 *
 * Description : this function responsible to configure the timer with it's prescaler , call back function
 * 					timer mode either compare or overflow and the compare value in case of compare mode
 * 					compare value dosent matter in case of ovdrflow mode
 * ---------------------------------------------------------------------------------------------------------------------*/

void TIMER_start(const timerConfig_t * timerConfig){
	switch(timerConfig->timerNUM){
	/*-------------------------------------------------------------------------------------------------------------------
	 * 											timer 0 configuration
	 * -----------------------------------------------------------------------------------------------------------------*/
	case timer0:
		_TCCR0._FOC0 = 1;						/*this bit is set at non PWM mode*/
		_TCCR0._COM0 = 0;						/*disable output compare pin */
		_TCNT0 = 0;								/*clear timer 0 data register*/
		if(timerConfig->timer_mode == overflow){
			_TCCR0._WGM01 = 0;							/*configure timer 0 to overflow mode*/
			_TCCR0._WGM00 = 0;
			_TIMSK._TOIE0 = 1;							/*enable timer 0 over flow interrupt request generation*/
			_TIMSK._OCIE0 = 0;							/*disable timer 0 compare interrupt request generation*/
			_TCNT0 = timerConfig->SCValue;				/*load timer counter register with the initial value*/
			timer0_Reload = timerConfig->SCValue;		/*this value will be used later in ISR*/
			g_timer0overflow = (volatile void(*)(void))timerConfig->CallbackfunctionPtr;	/*configure the call back function address*/
		}
		else if(timerConfig->timer_mode == compare){
			_TCCR0._WGM01 = 1;					/*configure timer 0 to compare mode*/
			_TCCR0._WGM00 = 0;
			_TCNT0 = 0;							/*clear timer 0 data register*/
			_OCR0 = timerConfig->SCValue;		/*set the compare register to compare value*/
			_TIMSK._TOIE0 = 0;					/*disable timer 0 over flow interrupt request generation*/
			_TIMSK._OCIE0 = 1;					/*enable timer 0 compare interrupt request generation*/
			g_timer0compare = (volatile void(*)(void))timerConfig->CallbackfunctionPtr;
		}
		_TCCR0._CS0 = timerConfig->timer_prescaler; /*configure prescaler for timer 0 and start counting*/
		break;
		/*-------------------------------------------------------------------------------------------------------------------
		 * 											timer 1 configuration
		 * -----------------------------------------------------------------------------------------------------------------*/
	case timer1:
		_TCCR1A._COM1A = 0;
		_TCCR1A._COM1B = 0;
		_TCCR1A._FOC1A = 1;
		_TCCR1A._FOC1B = 1;
		_TCCR1B._ICES1 = 0;
		_TCCR1B._ICNC1 = 0;
		if(timerConfig->timer_mode == overflow){
			_TCCR1A._WGM10_1 = 0;
			_TCCR1B._WGM12_3 = 0;
			_TIMSK._TOIE1 = 1;
			_TIMSK._OCIE1A = 0;
			_TCNT1 = timerConfig->SCValue;
			timer1_Reload = timerConfig->SCValue;
			g_timer1overflow = (volatile void(*)(void))timerConfig->CallbackfunctionPtr;
		}
		else if(timerConfig->timer_mode == compare){
			_TCCR1A._WGM10_1 =  0;
			_TCCR1B._WGM12_3  = 1;
			_TIMSK._TOIE1  = 0;
			_TIMSK._OCIE1A = 1;
			_TCNT1 = 0;
			_OCR1A = timerConfig->SCValue;
			g_timer1compare = (volatile void(*)(void))timerConfig->CallbackfunctionPtr;
		}
		_TCCR1B._CS1 = timerConfig->timer_prescaler;
		break;
	/*-------------------------------------------------------------------------------------------------------------------
	 * 											timer 2 configuration
	 * -----------------------------------------------------------------------------------------------------------------*/
	case timer2:
		_TCCR2._FOC2 = 1;						/*this bit is set at non PWM mode*/
		_TCCR2._COM2 = 0;
		if(timerConfig->timer_mode == overflow){
			_TCCR2._WGM21 = 0;					/*configure timer 0 to overflow mode*/
			_TCCR2._WGM20 = 0;
			_TIMSK._TOIE2 = 1;					/*enable timer 0 over flow interrupt request generation*/
			_TIMSK._OCIE2 = 0;					/*disable timer 0 compare interrupt request generation*/
			_TCNT2 = timerConfig->SCValue;
			timer2_Reload = timerConfig->SCValue;
			g_timer2overflow = (volatile void(*)(void))timerConfig->CallbackfunctionPtr;
		}
		else if(timerConfig->timer_mode == compare){
			_TCCR2._WGM21 = 1;					/*configure timer 0 to compare mode*/
			_TCCR2._WGM20 = 0;
			_TCNT2 = 0;							/*clear timer 0 data register*/
			_OCR2 = timerConfig->SCValue;		/*set the compare register to compare value*/
			_TIMSK._TOIE2 = 0;					/*disable timer 0 over flow interrupt request generation*/
			_TIMSK._OCIE2 = 1;					/*enable timer 0 compare interrupt request generation*/
			g_timer2compare = (volatile void(*)(void))timerConfig->CallbackfunctionPtr;
		}
		_TCCR2._CS2 = timerConfig->timer_prescaler; /*configure prescaler for timer 0 and start counting*/
		break;
	}
}


/*----------------------------------------------------------------------------------------------------------------
 * function name : TIMER_stop
 * arguments : structure of type timerConfig_t contains
 * 				{timerNUM , timer_mode , timer_prescaler , compareValue , CallbackfunctionPtr}
 *
 * Description : this function responsible to stop the timer by disable it's clock
 * --------------------------------------------------------------------------------------------------------------*/
void TIMER_stop(const timerConfig_t * timerConfig){
	switch(timerConfig->timerNUM){
	case timer0:
		_TCCR0._CS0 = 0; /*remove clock and disable timer */
		break;
	case timer1:
		_TCCR1B._CS1 = 0;/*remove clock and disable timer */
		break;
	case timer2:
		_TCCR2._CS2 = 0; /*remove clock and disable timer */
		break;
	}
}

/*----------------------------timer interrupt service routine -----------------------------*/

ISR(TIMER0_OVF_vect){
	_TCNT0 = timer0_Reload ;
	if(g_timer0overflow != NULL){
		(*g_timer0overflow)();
	}
}

ISR(TIMER0_COMP_vect){
	if(g_timer0compare != NULL){
		(*g_timer0compare)();
	}
}


ISR(TIMER1_OVF_vect){
	_TCNT1 = timer1_Reload ;
	if(g_timer1overflow != NULL){
		(*g_timer1overflow)();
	}
}

ISR(TIMER1_COMPA_vect){
	if(g_timer1compare != NULL){
		(*g_timer1compare)();
	}
}

ISR(TIMER2_OVF_vect){
	_TCNT2 = timer2_Reload ;
	if(g_timer2overflow != NULL){
		(*g_timer2overflow)();
	}
}
ISR(TIMER2_COMP_vect){
	if(g_timer2compare != NULL){
		(*g_timer2compare)();
	}
}
