/*
 * HMI_utility_functions.h
 *
 *  Created on: Feb 1, 2020
 *      Author: SALAH
 */

#ifndef APP_LAYER_HMI_UTILITY_FUNCTIONS_H_
#define APP_LAYER_HMI_UTILITY_FUNCTIONS_H_

#include "../HWAL/lcd_module/lcd.h"
#include "../HWAL/keypad_module/keypad.h"
#include "../MCAL/uart_module/uart.h"

#include "../MCAL/external_interrupt/external_interrupt.h"
#include "../MCAL/dio_module/dio.h"

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

extern CHconfig_t buzzer ;
extern uartConfig_t uart;
extern EINT_t downbutton;
extern EINT_t upbutton;
extern EINT_t selectbutton ;
extern volatile uint8 pos;

void movedown(void);
void moveup(void);
void select(void);
void HMI_alarm(void);
void HMI_getOldPassword(void);
void HMI_moveArrow(uint8 pos);
void HMI_displayMainMenu(void);
void HMI_firstTimeMSG(void);
uint8 HMI_set_password(void);
uint8 HMI_repeat_password(void);
void HMI_matchError(void);
void HMI_success(void);
void HMI_updated(void);
#endif /* APP_LAYER_HMI_UTILITY_FUNCTIONS_H_ */
