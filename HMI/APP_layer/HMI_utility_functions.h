/*
 * HMI_utility_functions.h
 *
 *  Created on: Feb 1, 2020
 *      Author: SALAH
 */

#ifndef APP_LAYER_HMI_UTILITY_FUNCTIONS_H_
#define APP_LAYER_HMI_UTILITY_FUNCTIONS_H_
/*--------------------------hardware abstraction layer modules ----------------------------------------------------------*/
#include "../HWAL/lcd_module/lcd.h"
#include "../HWAL/keypad_module/keypad.h"

/*--------------------------microcontroller abstraction layer modules ----------------------------------------------------------*/
#include "../MCAL/uart_module/uart.h"
#include "../MCAL/external_interrupt/external_interrupt.h"
#include "../MCAL/dio_module/dio.h"

#define LIST_SIZE 6			/*defines the number of elements in the main menu list*/

/*---------------------------requests from controller to HMI ----------------------------------------------------------*/
#define ACK_MSG 				'a'			/*defines the ACK message sent to the controller after every message*/
#define MAIN_MENU_MSG 			'M'			/*defines the main menu message display request sent from controller to HMI*/
#define FIRST_RUN 				'f'			/*defines the first welcome message display request sent from controller to HMI*/
#define NEW_PASS_MGS 			's'			/*defines the set new password message display request sent from controller to HMI*/
#define REPEATE_PASS_MSG 		'r'			/*defines the repeat message display request sent from controller to HMI*/
#define PASSWORD_MATCH 			'm'			/*defines the password matching message display request sent from controller to HMI*/
#define NO_MATCH 				'n'			/*defines the no match message display request sent from controller to HMI*/
#define PASS_UPDATED_MSG 		'p'			/*defines the password updated message display request sent from controller to HMI*/
#define OLD_PASS_MSG			'o'			/*defines the enter old password message display request sent from controller to HMI*/
#define ENTER_PASS_MSG			'g'			/*defines the enter password message display request sent from controller to HMI*/
#define ALARM_MSG				'x'			/*defines the alarm message display request sent from controller to HMI*/

/*---------------------------requests from HMI to controller ----------------------------------------------------------*/
#define UPDATE_PASSWORD_REQ		't'			/*defines the request from HMI(user) to the controller asking to update password*/
#define	UNLOCK_REQ				'u'			/*defines the request from HMI(user) to the controller asking to unlock door*/
#define LOCK_REQ				'c'			/*defines the request from HMI(user) to the controller asking to lock door*/
#define SET_OPEN_TIME_REQ		'v'			/*defines the request from HMI(user) to the controller asking to set the door open delay*/

/*---------------------------hardware configuration ----------------------------------------------------------------*/
extern CHconfig_t buzzer ;			/*buzzer HW configuration as a GPIO PIN configuration*/
extern uartConfig_t uart;			/*UART configuration*/
extern EINT_t downbutton;			/*external interrupt down button configuration*/
extern EINT_t upbutton;				/*external interrupt up button configuration*/
extern EINT_t selectbutton ;		/*external interrupt select button configuration*/


/*********************************************************************************************************************************
 * Description : the move down function handles the interrupt caused by down button
 * it's responsible to move the arrow down , updating the menu to select the write window to display
 ********************************************************************************************************************************* */
void movedown(void);
/*********************************************************************************************************************************
 * Description : the move up function handles the interrupt caused by up button
 * it's responsible to move the arrow up , updating the menu to select the write window to display
 ********************************************************************************************************************************* */
void moveup(void);
/********************************************************************************************************************************
 * Description : the select function handles the interrupt caused by select button
 * it's responsible to send a request to the controller
 * the controller is then send a message as a response to that request
 ********************************************************************************************************************************* */
void select(void);
/********************************************************************************************************************************
 * Description : display alarm message in case of break , as a response to alarm message from the controller to HMI
 ********************************************************************************************************************************* */
void HMI_alarm(void);
/********************************************************************************************************************************
 * Description : this function responsible ask the user to enter 5 number password as a response to
 *  old password MSG
 *  repeat password MSG
 *  new password MSG
 *  Enter password MSG
 *  sent from the controller to HMI
 ********************************************************************************************************************************* */
void HMI_askForPassword(uint8 * message);
/********************************************************************************************************************************
 * Description : this function responsible to move the arrow to match the choice the user select
 ********************************************************************************************************************************* */
void HMI_moveArrow(uint8 pos);
/********************************************************************************************************************************
 * Description : this function responsible display the main menu on the LCD with respect to the display window , page number
 * arrow position
 ********************************************************************************************************************************* */
void HMI_displayMainMenu(void);
/********************************************************************************************************************************
 * Description : this function responsible display a first time message as a response to that the controller did not find
 * a password in the external EEPROM or it is the first time to operate after installation
 ********************************************************************************************************************************* */
void HMI_firstTimeMSG(void);
/********************************************************************************************************************************
 * Description : this function responsible display a error message as a response to that the controller find no match between
 * the entered password and the stored password
 * the old password and the stored password
 * the new password and the repeater password
 ********************************************************************************************************************************* */
void HMI_matchError(void);
/********************************************************************************************************************************
 * Description : this function responsible display a success message as a response to that the controller find a match between
 * the entered password and the stored password
 ********************************************************************************************************************************* */
void HMI_success(void);
/********************************************************************************************************************************
 * Description : this function responsible display a update success message as a response to that the controller updates the password
 * Stored in the EEPROM with a new one
 ********************************************************************************************************************************* */
void HMI_updated(void);


#endif /* APP_LAYER_HMI_UTILITY_FUNCTIONS_H_ */
