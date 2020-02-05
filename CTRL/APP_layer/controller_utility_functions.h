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

void motorTimerInterruptHandler(void);
void keepOpeninterruptHandler(void);
void motorTimerInterruptHandler(void);
void alarminterruptHandler(void);

void  CONT_opendoor		(void);
void  CONT_closedoor	(void);
void  CONT_keepOpen		(void);
void  CONT_opendoor		(void);
uint8 CONT_getAndCompPassword(char msg);
void  CONT_setPassword	(void);
void  CONT_sendMSG		(uint8 msg);
uint8 CONT_firstRunCheck(void);
void  CONT_getPassword	(uint8 * pass , uint8 msg);
uint8 CONT_password_match(uint8 * pass1 , uint8 * pass2);
void  CONT_updatePassword(uint8 * pass);


#endif /* APP_LAYER_CONTROLLER_UTILITY_FUNCTIONS_H_ */
