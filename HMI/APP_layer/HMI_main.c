/*
 * main.c
 *
 *  Created on: Jan 26, 2020
 *      Author: SALAH
 */


#include "HMI_utility_functions.h"

/************************************************************************************************************************************
 * the uartMsgInetrruptHandler function is executed every time the UART module recieves message from controller
 * it's responsible to interpret the controller message and execute the desired action according to the controller request
 *********************************************************************************************************************************** */
void uartMsgInetrruptHandler(void){
	switch (recieved_data){
	case NEW_PASS_MGS:		UART_transmit(ACK_MSG);		HMI_askForPassword("new password");		break;
	case REPEATE_PASS_MSG:	UART_transmit(ACK_MSG);		HMI_askForPassword("repeat password");	break;
	case NO_MATCH:			UART_transmit(ACK_MSG);		HMI_matchError();						break;
	case PASSWORD_MATCH:	UART_transmit(ACK_MSG);		HMI_success();							break;
	case PASS_UPDATED_MSG:	UART_transmit(ACK_MSG);		HMI_updated();							break;
	case FIRST_RUN:			UART_transmit(ACK_MSG);		HMI_firstTimeMSG();						break;
	case ENTER_PASS_MSG:	UART_transmit(ACK_MSG);		HMI_askForPassword("enter password");	break;
	case OLD_PASS_MSG:		UART_transmit(ACK_MSG);		HMI_askForPassword("old password");		break;
	case ALARM_MSG:			UART_transmit(ACK_MSG);		HMI_alarm();							break;
	case MAIN_MENU_MSG:		UART_transmit(ACK_MSG);		HMI_displayMainMenu();					break;
	default :	break;
	}
}
/************************************************************************************************************************************
 *
 * 												  main function
 *
 *********************************************************************************************************************************** */
int main(void){
	/*--------------------------initialize modules -----------------------------------------*/
	DIO_initChannel(&buzzer);		/*initialize GPIO config for peep buzzer*/

	EINT_init(&downbutton);			/*initialize external interrupt config for down button*/
	EINT_init(&upbutton);			/*initialize external interrupt config for up button*/
	EINT_init(&selectbutton);		/*initialize external interrupt config for select button*/

	LCD_init();						/*initialize LCD */

	UART_init(&uart);							/*initialize UART module*/
	UART_setcallback(uartMsgInetrruptHandler);	/*set the callback function for UART*/

	SREG |= (1<<7);					/*enable global interrupt */

	while(1);			/*bussy loop*/
	return 0;
}

