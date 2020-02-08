/*
 * controller_utility_functions.c
 *
 *  Created on: Jan 30, 2020
 *      Author: SALAH
 */

#include "controller_utility_functions.h"

/********************************************************************
 * door state variable is used to store the current door state
 * 1 = open
 * 0 = closed
 * ********************************************************************/
static uint8 door_state = 0;

/********************************************************************************************************************************
 * Description : this function is a callback function to handle the time of motor rotating before it stops
 * this function is caller every 1 second by the timer interrupt event
 ********************************************************************************************************************************* */
void motorTimerInterruptHandler(void){
	static uint8 counter = 0;			/*variable to be incremented every one second according to timer configuration*/
	counter++;							/*increase the counter every second (every time that function is called by timer)*/
	DDRA = 0xFF;						/*turn on led test just to indicate that the timer us up and running*/
	PORTA ^= (2<<0);					/*toggle led test */
	if(counter > MOTOR_ON_TIME){		/*this block is executed after MOTOR_ON_TIME seconds that indicates the motor rotates for a specific number of seconds*/
		MOTOR_stop(&motor1);			/*stop the motor form rotating*/
		TIMER_stop(&motortimer);		/*stop the timer form counting to disable calling this interrupt handler */
		counter = 0;					/*reset the counter variable for the next time the timer is activated again*/
		if(door_state == 1){			/*this section is executed only when the door is open */
			CONT_keepOpen();			/*a keep door open timer is activated to keep the motor off and don't close the door until object pass*/
		}
	}
}
/********************************************************************************************************************************
 * Description : this function is a callback function to handle the opening time between opening the door and close it untill the
 * object pass
 * this function is callback function for timer interrupt that is called every 1 second according to timer configuration
 ********************************************************************************************************************************* */
void keepOpeninterruptHandler(void){
	static uint8 counter = 0;			/*variable to be incremented every one second according to timer configuration*/
	counter++;							/*increase the counter every second (every time that function is called by timer)*/
	DDRA = 0xFF;						/*turn on led test just to indicate that the timer us up and running*/
	PORTA ^= (1<<0);					/*toggle led test */
	if(counter > KEEP_OPEN_TIME){		/*this block is executed after KEEP_OPEN_TIME elapse , that indicates that the door has been kept open for a specific amount of time*/
		TIMER_stop(&keepOpenTimer);		/*stop the timer to stop calling this interrupt handler */
		counter = 0;					/*reset the counter for the next time timer is activated*/
		CONT_closedoor();				/*close the door after the opening time has been elapsed*/
	}
}
/********************************************************************************************************************************
 * Description : this function is a callback function to handle the alarm
 * this function is callback function for timer interrupt that is called every 1 second according to timer configuration
 ********************************************************************************************************************************* */
void alarminterruptHandler(void){
	static uint8 counter = 0;			/*variable to be incremented every one second according to timer configuration*/
	counter++;							/*increase the counter every second (every time that function is called by timer)*/
	DDRA = 0xFF;						/*turn on led test just to indicate that the timer us up and running*/
	PORTA ^= (1<<0);					/*toggle led test */
	if(counter > ALARM_TIME){			/*this block is executed after ALARM_TIME elapse , that indicates timer buzzer has been peeping for a specific amount of time*/
		TIMER_stop(&alarmTimer);		/*stop the timer to stop calling this interrupt handler */
		UART_transmit(MAIN_MENU_MSG);	/*send the display message to HMI to display the main menu allowing the user to re use the system*/
		counter = 0;					/*reset the counter for the next time timer is activated*/
		DIO_writeChannel(&alarm , 0);	/*turn off the buzzer after the ALARM_TIME elapsed */
	}
}
/********************************************************************************************************************************
 * Description : this function responsible for opening the door as a response of user password matches the stored password
 * this function open the door
 * change the state of the door to open
 * start a timer to keep rotating the motor for specific amount of time
 ********************************************************************************************************************************* */
void CONT_opendoor(void){
	if(door_state == 1)						/*if the door is already opened preventing motor from rotating that may break the door or damage motor*/
		return;
	MOTOR_changeDirection(&motor1 , CW);	/*configure the motor rotation direction to rotate it clock wise (open rotation direction)*/
	TIMER_start(&motortimer);				/*start the timer to close the door after MOTOR_ON_TIME is elapsed */
	MOTOR_start(&motor1 , 250);				/*start the motor with a speed of 250/255 * 100 %*/
	door_state = 1;							/*change the door state to open*/
}
/********************************************************************************************************************************
 * Description : this function responsible for closing the door as a response of a timer interrupt is called afer a MOTOR_ON_TIME
 * and the door is opened
 ********************************************************************************************************************************* */
void CONT_closedoor(void){					/*if the door is already closed preventing motor from rotating that may break the door or damage motor*/
	if(door_state == 0)
		return;
	MOTOR_changeDirection(&motor1 , CCW);	/*configure the motor rotation direction to rotate it counter clock wise (close rotation direction)*/
	TIMER_start(&motortimer);				/*start the timer to close the door after MOTOR_ON_TIME is elapsed */
	MOTOR_start(&motor1 , 250);				/*start the motor with a speed of 250/255 * 100 %*/
	door_state = 0;							/*change the door state to close*/
}
/********************************************************************************************************************************
 * Description : this function responsible keeping the door opened for a specific amount for time
 * this function configure a timer with a keepOpeninterruptHandler to keep the motor stopped until KEEP_OPEN_TIME is elapsed and
 * start the close door routine
 ********************************************************************************************************************************* */
void CONT_keepOpen(void){
	TIMER_start(&keepOpenTimer);			/*start the keep open timer*/
}
/********************************************************************************************************************************
 * Description : this function responsible to start the alarm and configure a timer to stop it after ALARM_TIME is elapsed
 ********************************************************************************************************************************* */
void CONT_startAlarm(){
	DIO_writeChannel(&alarm , 1);			/*turn on the alarm*/
	TIMER_start(&alarmTimer);				/*start the alarm timer*/
}
/********************************************************************************************************************************
 * Description : this function responsible for
 * 1- read the strored password form EEPORM
 * 2- wait for the user to enter a 5 number password
 * 3- compare the entered password with the stored one
 * 4- return 1 if password is match the stored one
 * 5- return 0 if password didnt match for 3 times
 ********************************************************************************************************************************* */
uint8 CONT_getAndCompPassword(char msg){

	uint8 password[5]= {0};				/*array to store the user entered password*/
	uint8 storedpassword[5] = {0};		/*array to store the password read form EEPROM*/
	uint8 counter = 0;					/*counter to count how many times user entered wrong password if 3 alarm should start*/
	/*------------------------------------read password from EEPRM -----------------------------------------------------*/
	EEPROM_readData(0x00 , &storedpassword[0] , 1);				/*their is a run time error happens when reading the 5 memory location at one time*/
	EEPROM_readData(0x01 , &storedpassword[1] , 1);				/*so to solve it i read one location at a time*/
	EEPROM_readData(0x02 , &storedpassword[2] , 1);
	EEPROM_readData(0x03 , &storedpassword[3] , 1);
	EEPROM_readData(0x04 , &storedpassword[4] , 1);
	/*-----------------------------------ask for password for 3 times ----------------------------------------------------*/
	for(counter=0 ; counter<3 ; counter++){
		CONT_getPassword(password , msg);						/*ask HMI for display a specific message on the LCD and wait for 5 number password*/
		if (CONT_password_match(password , storedpassword)){	/*Check if the received  password matches the stored one*/
			return 1;					/*password match*/
		}
	}
	return 0;		/*no matching*/
}
/********************************************************************************************************************************
 * Description : this function responsible for updating the stored EEPROM locations with a new password as a response of
 * updating password request form the user (req sent form HMI to controller)
 * or a first run operation that is no password is stored in the EEPROM
 ********************************************************************************************************************************* */
void CONT_setPassword(void){
	uint8 password[5] = {0};		/*array to store the received user's password*/
	uint8 repeated[5] = {0};		/*array to store the reentered password*/
	do{						/*do for at least one time*/
		CONT_getPassword(password , NEW_PASS_MGS);			/*ask user to enter the new password*/
		CONT_getPassword(repeated , REPEATE_PASS_MSG);		/*ask user to repeat the preentered password*/
	}while(!CONT_password_match(password , repeated));		/*compare the two passwords if match exit the loop if no matching set the password again*/
	CONT_updatePassword(password);		/*in case of password match update the EEPROM location with the entered password*/
	CONT_sendMSG(MAIN_MENU_MSG);		/*send message to HMI to display the main menu*/
}
/********************************************************************************************************************************
 * Description : this function responsible sending messages to HMI and wait for ACK message to ensure the system synchronization
 ********************************************************************************************************************************* */
void CONT_sendMSG(uint8 msg){
	recieved_data = 0x00;		/*reset the received data variable , this variable is changes according to the data the UART received as an response for the UART interrupt action*/
	while(recieved_data != ACK_MSG){	/*loop while HMI is not ready (HMI don't send ACK message)*/
		UART_transmit(msg);				/*Transmit the message via UART channel*/
		_delay_ms(1000);				/*wait for a while before retransmit the message again */
	}
}
/********************************************************************************************************************************
 * Description : this function responsible check the EEPROM , if password exists
 * the function return 0 so this is not the first run of the sytem
 * the function returns 1 if no password exist and the EEPROM is set to it's default values
 ********************************************************************************************************************************* */
uint8 CONT_firstRunCheck(void){
	uint8 first_EEPROM_Byte = 0;		/*variable to store the first EEPROM location value*/
	EEPROM_readData(0x00 , &first_EEPROM_Byte , 1);  /*read the first memory location (byte) of the EEPROM*/
	if(first_EEPROM_Byte == 0xFF){			/*check if the value of this location is set to default value  (0XFF)*/
		CONT_sendMSG(FIRST_RUN);			/*send to HMI message to display a welcome message on the LCD screen*/
		_delay_ms(1000);					/*delay for a while to allow the user to read the message before sending the next message*/
		return 1; 				/*this is first time run*/
	}
	return 0;	/*this is not the first time run*/
}
/********************************************************************************************************************************
 * Description : this function responsible for get a password form the user for
 * get old password while updating password
 * get password while opne door
 ********************************************************************************************************************************* */
void CONT_getPassword(uint8 * pass , uint8 msg){
	CONT_sendMSG(msg);			/*send a specific message to the user (HMI) to display on the LCD a proper message describes what operation is running*/
	SREG &= ~(1<<7);			/*disable global interrupt to operate UART at polling */
	UART_receiveString(pass , 5);		/*wait for 5 numbers to be sent*/
	SREG |= (1<<7);				/*enable the global interrupt */
}
/********************************************************************************************************************************
 * Description : this function responsible compare two passwords for
 * 1- comparing old password with the stored one in case of set new password
 * 2- entered password with the stored one in case of open door
 * 3- new password with reentered password in case of new password
 ********************************************************************************************************************************* */
uint8 CONT_password_match(uint8 * pass1 , uint8 * pass2){
	uint8 i=0;						/*counter to loop through the password elements*/
	for(i=0 ; i<5 ; i++){			/*loop through the 5 numbers in each array*/
		if(pass1[i] != pass2[i]){	/*compare each element*/
			CONT_sendMSG(NO_MATCH);	/*if no matching send to HMI a NO_MATCH message to display on the LCD no matching message*/
			_delay_ms(1000);		/*delay for a while to allow the user to read the message displayed*/
			return 0;				/*return 0 means no matching*/
		}
	}
	return 1;		/*returning 1 means password match */
}
/********************************************************************************************************************************
 * Description : this function responsible for updating the EEPROM locations with a password
 ********************************************************************************************************************************* */
void CONT_updatePassword(uint8 * pass){
	EEPROM_writeData(0x00 , pass , 5);	/*write the first 5 locations in EEPROM with the 5 numbers */
	CONT_sendMSG(PASS_UPDATED_MSG);		/*send a message to the HMI to display "password updated successfully message " */
	_delay_ms(1000);					/*delay for a while to allow the user to read the message*/
	recieved_data = 0x00;				/*reset the received UART byte*/
}
