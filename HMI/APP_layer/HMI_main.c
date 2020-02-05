/*
 * main.c
 *
 *  Created on: Jan 26, 2020
 *      Author: SALAH
 */


#include "HMI_utility_functions.h"


void uartMsgInetrruptHandler(void){
	switch (recieved_data){
	case NEW_PASS_MGS:				/*set new password*/
		UART_transmit(ACK_MSG);
		HMI_set_password();
		break;
	case REPEATE_PASS_MSG:			/*repeat password*/
		UART_transmit(ACK_MSG);
		HMI_repeat_password();
		break;
	case NO_MATCH:					/*matching error*/
		UART_transmit(ACK_MSG);
		HMI_matchError();
		break;
	case PASSWORD_MATCH:			/*password matching*/
		UART_transmit(ACK_MSG);
		HMI_success();
		break;
	case PASS_UPDATED_MSG:			/*password updated*/
		UART_transmit(ACK_MSG);
		HMI_updated();
		break;
	case FIRST_RUN:					/*first time msg*/
		UART_transmit(ACK_MSG);
		HMI_firstTimeMSG();
		break;
	case MAIN_MENU_MSG:				/*main menu*/
		UART_transmit(ACK_MSG);
		HMI_displayMainMenu();
		pos = 1;
		HMI_moveArrow(pos);
		break;
	case ENTER_PASS_MSG:			/*get password*/
		UART_transmit(ACK_MSG);
		HMI_getpassword();
		break;
	case OLD_PASS_MSG:				/*get old password*/
		UART_transmit(ACK_MSG);
		HMI_getOldPassword();
		break;
	case ALARM_MSG:					/*display alarm msg*/
		UART_transmit(ACK_MSG);
		HMI_alarm();
		break;
	default :
		break;
	}
}

int main(void){
	DIO_initChannel(&buzzer);
	EINT_init(&downbutton);
	EINT_init(&upbutton);
	EINT_init(&selectbutton);
	LCD_init();
	UART_init(&uart);
	UART_setcallback(uartMsgInetrruptHandler);
	SREG |= (1<<7);
	while(1);
	return 0;
}

