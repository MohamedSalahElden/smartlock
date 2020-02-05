/*
 * INT0_INT1.c
 *
 *  Created on: Jan 7, 2020
 *      Author: SALAH
 */


#include "external_interrupt.h"



volatile static void (*g_INT0_functionPtr) (void) = NULL;
volatile static void (*g_INT1_functionPtr) (void) = NULL;
volatile static void (*g_INT2_functionPtr) (void) = NULL;

void EINT_init(const EINT_t *EINT_config){
	CHconfig_t EINT0_pin = {portD , pin2 , input , EINT_config->internal_resistor};
	CHconfig_t EINT1_pin = {portD , pin3 , input , EINT_config->internal_resistor};
	CHconfig_t EINT2_pin = {portB , pin2 , input , EINT_config->internal_resistor};
	switch(EINT_config->ch){
	case E_INT0:
		DIO_initChannel(&EINT0_pin);	/*configure pin as input and configure pull up / pull down resistor*/
		_MCUCR._ISC0 = EINT_config->INT_SC;
		_GICR._INT0 = 1;
		g_INT0_functionPtr = (volatile void(*)(void))EINT_config->INT_handler;
		break;
	case E_INT1:
		DIO_initChannel(&EINT1_pin);	/*configure pin as input and configure pull up / pull down resistor*/
		_MCUCR._ISC1 = EINT_config->INT_SC;
		_GICR._INT1 = 1;
		g_INT1_functionPtr = (volatile void(*)(void))EINT_config->INT_handler;
		break;
	case E_INT2:
		DIO_initChannel(&EINT2_pin);	/*configure pin as input and configure pull up / pull down resistor*/
		if((EINT_config->INT_SC != falling) | (EINT_config->INT_SC != rising)){
			_MCUCSR._ISC2 = 1;	/*1=rising*/
		}
		else{
			_MCUCSR._ISC2 = EINT_config->INT_SC-2; 	/*0=falling 1=rising*/
		}
		_GICR._INT2 = 1;	/*enable INT0 request*/
		g_INT2_functionPtr = (volatile void(*)(void))EINT_config->INT_handler;
		break;
	}
}
void EINT_changeSenseControl(const EINT_t *EINT_config , senseControl_t EINT_SC){
	switch(EINT_config->ch){
	case E_INT0:
		MCUCR  = (MCUCR & 0xFC) | (EINT_config->INT_SC & 0x03); 	/*set the interrupt sense control bits*/
		break;
	case E_INT1:
		MCUCR  = (MCUCR & 0xF3) | (EINT_config->INT_SC & 0x03)<<2; 	/*set the interrupt sense control bits*/
		break;
	case E_INT2:
		if((EINT_config->INT_SC != falling) | (EINT_config->INT_SC != rising)){
			MCUCSR  = (MCUCSR & 0xBF) | (1<<ISC2); 	/*1=rising*/
		}else{
			MCUCSR  = (MCUCSR & 0xBF) | ((EINT_config->INT_SC-2))<<6; 	/*0=falling 1=rising*/
		}
		break;
	}
}

ISR(INT0_vect){
	if(g_INT0_functionPtr != NULL){
		(*g_INT0_functionPtr)();
	}
}
ISR(INT1_vect){
	if(g_INT1_functionPtr != NULL){
		(*g_INT1_functionPtr)();
	}
}
ISR(INT2_vect){
	if(g_INT1_functionPtr != NULL){
		(*g_INT2_functionPtr)();
	}
}


