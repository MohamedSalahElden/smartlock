/*
 * main.c
 *
 *  Created on: Jan 26, 2020
 *      Author: SALAH
 */

#include "controller_utility_functions.h"


int main(void){
	UART_init(&uart);
	MOTOR_init(&motor1);
	DIO_initChannel(&alarm);

	SREG |= (1<<7);

	if(CONT_firstRunCheck()){
		CONT_setPassword();
	}
	CONT_sendMSG(MAIN_MENU_MSG);
	while(1){
		switch(recieved_data){
		case ACK_MSG:
			break;
		case UNLOCK_REQ:
			if(CONT_getAndCompPassword(ENTER_PASS_MSG)){
				CONT_sendMSG(MAIN_MENU_MSG);
				CONT_opendoor();
			}
			else{
				CONT_startAlarm();
				CONT_sendMSG(ALARM_MSG);
			}
			recieved_data = 0x00;
			break;
		case UPDATE_PASSWORD_REQ:
			if(CONT_getAndCompPassword(OLD_PASS_MSG)){
				CONT_setPassword();
				CONT_sendMSG(MAIN_MENU_MSG);
			}
			else{
				CONT_startAlarm();
				CONT_sendMSG(ALARM_MSG);

			}
			recieved_data = 0x00;
			break;
		case LOCK_REQ:
			CONT_closedoor();
			CONT_sendMSG(MAIN_MENU_MSG);
			recieved_data = 0x00;
			break;
		default:
			break;
		}
	}
	return 0;
}

