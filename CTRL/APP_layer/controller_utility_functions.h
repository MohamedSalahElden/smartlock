/*
 * controller_utility_functions.h
 *
 *  Created on: Feb 1, 2020
 *      Author: SALAH
 */

#ifndef APP_LAYER_CONTROLLER_UTILITY_FUNCTIONS_H_
#define APP_LAYER_CONTROLLER_UTILITY_FUNCTIONS_H_

#include "../MCAL/dio_module/dio.h"
#include "../MCAL/uart_module/uart.h"
#include "../MCAL/timer_module/timer.h"

#include "../HWAL/motor_module/l293D.h"
#include "../HWAL/eeprom_module/eeprom.h"


#define ACK_MSG 				'a'
#define MAIN_MENU_MSG 			'M'
#define FIRST_RUN 				'f'
#define NEW_PASS_MGS 			's'
#define REPEATE_PASS_MSG 		'r'
#define PASSWORD_MATCH 			'm'
#define NO_MATCH 				'n'
#define PASS_UPDATED_MSG 		'p'
#define OLD_PASS_MSG			'o'
#define ENTER_PASS_MSG			'g'
#define UPDATE_PASSWORD_REQ		't'
#define	UNLOCK_REQ				'u'
#define LOCK_REQ				'c'
#define ALARM_MSG				'x'
#define SET_OPEN_TIME_REQ		'v'

#define KEEP_OPEN_TIME 5
#define MOTOR_ON_TIME 2
#define ALARM_TIME 60

extern CHconfig_t 		alarm ;
extern uint8 			keep_open_duration;
extern motorConfig_t 	motor1 ;
extern timerConfig_t 	motortimer;
extern timerConfig_t 	keepOpenTimer;
extern uartConfig_t 	uart ;
extern timerConfig_t 	alarmTimer ;


/********************************************************************************************************************************
 * Description : this function is a callback function to handle the time of motor rotating before it stops
 * this function is caller every 1 second by the timer interrupt event
 ********************************************************************************************************************************* */
void motorTimerInterruptHandler(void);
/********************************************************************************************************************************
 * Description : this function is a callback function to handle the opening time between opening the door and close it untill the
 * object pass
 * this function is callback function for timer interrupt that is called every 1 second according to timer configuration
 ********************************************************************************************************************************* */
void keepOpeninterruptHandler(void);
/********************************************************************************************************************************
 * Description : this function is a callback function to handle the alarm
 * this function is callback function for timer interrupt that is called every 1 second according to timer configuration
 ********************************************************************************************************************************* */
void alarminterruptHandler(void);
/********************************************************************************************************************************
 * Description : this function responsible for opening the door as a response of user password matches the stored password
 * this function open the door
 * change the state of the door to open
 * start a timer to keep rotating the motor for specific amount of time
 ********************************************************************************************************************************* */
void CONT_opendoor(void);
/********************************************************************************************************************************
 * Description : this function responsible for closing the door as a response of a timer interrupt is called afer a MOTOR_ON_TIME
 * and the door is opened
 ********************************************************************************************************************************* */
void CONT_closedoor(void);
/********************************************************************************************************************************
 * Description : this function responsible keeping the door opened for a specific amount for time
 * this function configure a timer with a keepOpeninterruptHandler to keep the motor stopped until KEEP_OPEN_TIME is elapsed and
 * start the close door routine
 ********************************************************************************************************************************* */
void CONT_keepOpen(void);
/********************************************************************************************************************************
 * Description : this function responsible to start the alarm and configure a timer to stop it after ALARM_TIME is elapsed
 ********************************************************************************************************************************* */
void CONT_startAlarm();
/********************************************************************************************************************************
 * Description : this function responsible for
 * 1- read the strored password form EEPORM
 * 2- wait for the user to enter a 5 number password
 * 3- compare the entered password with the stored one
 * 4- return 1 if password is match the stored one
 * 5- return 0 if password didnt match for 3 times
 ********************************************************************************************************************************* */
uint8 CONT_getAndCompPassword(char msg);
/********************************************************************************************************************************
 * Description : this function responsible for updating the stored EEPROM locations with a new password as a response of
 * updating password request form the user (req sent form HMI to controller)
 * or a first run operation that is no password is stored in the EEPROM
 ********************************************************************************************************************************* */
void CONT_setPassword(void);
/********************************************************************************************************************************
 * Description : this function responsible sending messages to HMI and wait for ACK message to ensure the system synchronization
 ********************************************************************************************************************************* */
void CONT_sendMSG(uint8 msg);
/********************************************************************************************************************************
 * Description : this function responsible check the EEPROM , if password exists
 * the function return 0 so this is not the first run of the sytem
 * the function returns 1 if no password exist and the EEPROM is set to it's default values
 ********************************************************************************************************************************* */
uint8 CONT_firstRunCheck(void);
/********************************************************************************************************************************
 * Description : this function responsible for get a password form the user for
 * get old password while updating password
 * get password while opne door
 ********************************************************************************************************************************* */
void CONT_getPassword(uint8 * pass , uint8 msg);
/********************************************************************************************************************************
 * Description : this function responsible compare two passwords for
 * 1- comparing old password with the stored one in case of set new password
 * 2- entered password with the stored one in case of open door
 * 3- new password with reentered password in case of new password
 ********************************************************************************************************************************* */
uint8 CONT_password_match(uint8 * pass1 , uint8 * pass2);
/********************************************************************************************************************************
 * Description : this function responsible for updating the EEPROM locations with a password
 ********************************************************************************************************************************* */
void CONT_updatePassword(uint8 * pass);


#endif /* APP_LAYER_CONTROLLER_UTILITY_FUNCTIONS_H_ */
