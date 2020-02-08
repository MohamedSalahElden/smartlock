/*
 * set_password.c
 *
 *  Created on: Jan 30, 2020
 *      Author: SALAH
 */


#include "HMI_utility_functions.h"



/*-----------------------------------main menu list -----------------------------------*/

/*
 * position value determine the position of the arrow
 * the choice to be selected
 */
static volatile uint8 pos = 1;
/*
 * page variable determine the window to display choices on the LCD
 * page = 0 displays [choice 1 , 2 , 3]
 * page = 1 displays [choice 2 , 3 , 4]
 * page = 2 displays [choice 3 , 4 , 5] and so on
 * */
static volatile uint8 page = 0;
/*
 * structure to define the list type which contains
 * name of the list choice
 * msg to be sent to controller when this choice is selected
 * */
typedef struct {
	char *name;
	char msg;
}list_type;
/*
 * array of list choices defines the names and msg's
 * future options is set to test the page and window displaying functions
 * */
static list_type list[LIST_SIZE] = {
		{"open door" , UNLOCK_REQ},
		{"close door"  , LOCK_REQ},
		{"reset password"  , UPDATE_PASSWORD_REQ},
		{"future option"  , '\0'},
		{"future option"  , '\0'},
		{"future option"  , '\0'}
};
/*********************************************************************************************************************************
 * Description : the move down function handles the interrupt caused by down button
 * it's responsible to move the arrow down , updating the menu to select the write window to display
 ********************************************************************************************************************************* */
void movedown(void){
	if(pos >= LIST_SIZE){	/*termination condition*/
		return;				/*return if user keep pushing down button while the arrow on the last choice  */
	}
	pos++;					/*move the position value to the next choice*/
	if(pos > 3){			/*if the position exceeds window [window is 3 choices] then the next page is to be displayed*/
		page ++;
	}
	HMI_displayMainMenu();			/*display the main menu with arrow on position and the desired page*/
	DIO_writeChannel(&buzzer , 1);	/*peep with the buzzer to indicate a click of down button*/
	_delay_ms(50);
	DIO_writeChannel(&buzzer , 0);
}
/*********************************************************************************************************************************
 * Description : the move up function handles the interrupt caused by up button
 * it's responsible to move the arrow up , updating the menu to select the write window to display
 ********************************************************************************************************************************* */
void moveup(void){
	if(pos <= 1){		/*termination condition*/
		return;			/*return if user keep pushing up button while the arrow on the first choice  */
	}
	pos--;				/*move the position value to the precious choice*/
	if(pos < page+1 ){	/*if the position exceeds window [window is 3 choices] then the previous page is to be displayed*/
		page --;
	}
	HMI_displayMainMenu();			/*display the main menu with arrow on position and the desired page*/
	DIO_writeChannel(&buzzer , 1);	/*peep with the buzzer to indicate a click of down button*/
	_delay_ms(50);
	DIO_writeChannel(&buzzer , 0);
}
/********************************************************************************************************************************
 * Description : the select function handles the interrupt caused by select button
 * it's responsible to send a request to the controller
 * the controller is then send a message as a response to that request
 ********************************************************************************************************************************* */
void select(void){
	UART_transmit(list[pos-1].msg);		/*send the request character via UART */
	DIO_writeChannel(&buzzer , 1);		/*peep with the buzzer to indicate a click of select button*/
	_delay_ms(50);
	DIO_writeChannel(&buzzer , 0);
}
/********************************************************************************************************************************
 * Description : display alarm message in case of break , as a responce to alarm message from the controller to HMI
 ********************************************************************************************************************************* */
void HMI_alarm(void){
	LCD_clearScreen();
	LCD_displayString("lw msktak");
	LCD_goTo(1,0);
	LCD_displayString("H........");
}
/********************************************************************************************************************************
 * Description : this function responsible ask the user to enter 5 number password as a responce to
 *  old password msg
 *  repeat password msg
 *  new passowrd msg
 *  enetr password msg
 *  sent from the controller to HMI
 ********************************************************************************************************************************* */
void HMI_askForPassword(uint8 * message){
	uint8 i = 0;							/*variable to loop untill get the 5 numbers*/
	uint8 pass[5];							/*array to store the 5 character password*/
	LCD_clearScreen();
	LCD_displayString(message);				/*print on the screen a msg*/
	LCD_goTo(2,4);
	while(i<5){								/*loop untill you get the 5 numbers*/
		pass[i] = KEYPAD_getCharacter();	/*get character from keypad and store it in tha password array*/
		LCD_characterDisplay('*');			/*display the charcter as '*' to hide the password*/
		DIO_writeChannel(&buzzer , 1);		/*peep with the buzzer to indicate a click of keypad button*/
		_delay_ms(50);
		DIO_writeChannel(&buzzer , 0);
		i++;								/*increase the position of the next embty location in the password array*/
		while(!KEYPAD_keyRelaesed());		/*bussy loop , do nothing until the button is released*/
	}
	UART_transmitString(pass , 5);			/*transmit the 5 character password to the controller */
}
/********************************************************************************************************************************
 * Description : this function responsible to move the arrow to match the choise the user select
 ********************************************************************************************************************************* */
void HMI_moveArrow(uint8 pos){
	if((pos>3) && (pos<1)){			/*terminate if the position will exceed the LCD limitation*/
		return;
	}
	LCD_goTo(1,0);					/*clear all positions of arrow to display it in the desired position*/
	LCD_displayString("  ");
	LCD_goTo(2,0);
	LCD_displayString("  ");
	LCD_goTo(3,0);
	LCD_displayString("  ");
	if(pos >3){						/*in case the displayed page is not 0 */
		LCD_goTo(pos-page,0);		/*the arrow will remains at the 3rd location and the choices will move up*/
		LCD_displayString("->");
	}
	else{
		LCD_goTo(pos,0);			/*in case of the first page the arrow will move and the choices will remain at it's location */
		LCD_displayString("->");
	}
}
/********************************************************************************************************************************
 * Description : this function responsible display the main menu on the LCD with respect to the display window , page number
 * arrow position
 ********************************************************************************************************************************* */
void HMI_displayMainMenu(void){
	uint8 i = 0;					/*variable to loop through the list elements*/
	LCD_clearScreen();				/*clear the screen to start new display*/
	LCD_goTo(0,0);
	LCD_displayString("select :");	/*display the list title*/
	for(i=0 ; i<3 ; i++){			/*loop through the list elements [choices]*/
		LCD_goTo(i+1,2);			/*start peinting the choice name from coulomn 2 to leave space for the arrow and at the next row*/
		LCD_displayString(list[page+i].name);	/*print the  choice name at it's row*/
	}
	LCD_goTo(0,15);					/*location on the LCD to display the choice number (just for testing)*/
	LCD_displayNumber(pos);			/*display the choice number*/
	HMI_moveArrow(pos-page);		/*display the arrow at the current selected choice location*/
}
/********************************************************************************************************************************
 * Description : this function responsible display a fisrt time message as a responce to that the controller did not find
 * a password in the external EEPROM or it is the first time to operate after installation
 ********************************************************************************************************************************* */
void HMI_firstTimeMSG(void){
	LCD_clearScreen();
	LCD_displayString("welcome");
	LCD_goTo(1,0);
	LCD_displayString("yasta");
	LCD_goTo(2,6);
	LCD_displayString(":)");
}
/********************************************************************************************************************************
 * Description : this function responsible display a error message as a responce to that the controller find no match between
 * the entered password and the stored password
 * the old password and the stored password
 * the new password and the repeater password
 ********************************************************************************************************************************* */
void HMI_matchError(void){
	LCD_clearScreen();
	LCD_displayString("no matching");
}
/********************************************************************************************************************************
 * Description : this function responsible display a success message as a responce to that the controller find a match between
 * the enetred password and the stored password
 ********************************************************************************************************************************* */
void HMI_success(void){
	LCD_clearScreen();
	LCD_displayString("password");
	LCD_goTo(1,0);
	LCD_displayString("accepted");
}
/********************************************************************************************************************************
 * Description : this function responsible display a update success message as a responce to that the controller updates the password
 * stord in the eeprom with a new one
 ********************************************************************************************************************************* */
void HMI_updated(void){
	LCD_clearScreen();
	LCD_displayString("password");
	LCD_goTo(1,0);
	LCD_displayString("updated");
	LCD_goTo(2,0);
	LCD_displayString("successfully");
}
