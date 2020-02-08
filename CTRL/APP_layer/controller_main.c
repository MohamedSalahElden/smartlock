/*
 * controller_main.c
 *
 *  Created on: Jan 26, 2020
 *      Author: SALAH
 */

#include "controller_utility_functions.h"


int main(void){
	/*------------------------------hardware initialization --------------------------------------*/
	UART_init(&uart);			/*initialize UART baudrate , mode */
	MOTOR_init(&motor1);		/*initialize motor pins */
	DIO_initChannel(&alarm);	/*initialize GPIO pin connected to the alarm buzzer*/

	SREG |= (1<<7);			/*enable global interrupt*/

	/*------------------------------check if this is the first run of system----------------------*/
	if(CONT_firstRunCheck()){
		CONT_setPassword();			/*set new password to the system*/
	}

	/*-------------------------------send message to the HMI to display the main menu --------------*/
	CONT_sendMSG(MAIN_MENU_MSG);

	while(1){					/*forever loop*/
		switch(recieved_data){				/*check the messages sent by the HMI*/
		/*---------------------------------ACK ------------------------------------------------------------------------------------------*/
		case ACK_MSG:			/*if the message is ACK message no action is taken*/
			break;
		/*---------------------------------unlock-----------------------------------------------------------------------------------------*/
		case UNLOCK_REQ:		/*if HMI wants to unlock the door this routine is executed*/
			if(CONT_getAndCompPassword(ENTER_PASS_MSG)){	/*wait for password and compare it with the stored one*/
				CONT_sendMSG(MAIN_MENU_MSG);		/*send message to HMI to display the main menu*/
				CONT_opendoor();					/*unlock the door*/
			}
			else{							/*this section is executed when user enter a wrong password 3 times*/
				CONT_startAlarm();			/*start alarm*/
				CONT_sendMSG(ALARM_MSG);	/*send message to HMI to display the main menu*/
			}
			recieved_data = 0x00;			/*clear the deceived UART data for the next iteration*/
			break;

		/*---------------------------------update password--------------------------------------------------------------------------------*/
		case UPDATE_PASSWORD_REQ:			/*this routine will be executed when user is tends to change password*/
			if(CONT_getAndCompPassword(OLD_PASS_MSG)){	/*wait for a 5 number password and compare it with the stored password*/
				CONT_setPassword();				/*enter the set password routine*/
				CONT_sendMSG(MAIN_MENU_MSG);	/*send message to HMI to display the main menu*/
			}
			else{							/*this section is executed when user enter a wrong password 3 times*/
				CONT_startAlarm();			/*start alarm*/
				CONT_sendMSG(ALARM_MSG);	/*send message to HMI to display the main menu*/
			}
			recieved_data = 0x00;			/*clear the deceived UART data for the next iteration*/
			break;
		/*---------------------------------lock door---------------------------------------------*/
		case LOCK_REQ:						/*this routine is executed as a responce to a lock request from the user (HMI)*/
			CONT_closedoor();				/*close the door  --- no password is nedded for this operation*/
			CONT_sendMSG(MAIN_MENU_MSG);	/*send message to HMI to display the main menu*/
			recieved_data = 0x00;			/*clear the deceived UART data for the next iteration*/
			break;
		/*---------------------------------default-----------------------------------------------------------------------------------------*/
		default:			/*in case if error (any other message has been send) no action*/
			break;
		}
		/*---------------------------------------------------------------------------------------------------------------------------------*/
	}
	return 0;
}

