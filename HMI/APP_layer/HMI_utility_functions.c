/*
 * set_password.c
 *
 *  Created on: Jan 30, 2020
 *      Author: SALAH
 */



#include "HMI_utility_functions.h"
volatile uint8 pos = 1;


void movedown(void){
	pos++;
	if(pos > 3){
		pos = 3;
	}
	HMI_moveArrow(pos);
	DIO_writeChannel(&buzzer , 1);
	_delay_ms(50);
	DIO_writeChannel(&buzzer , 0);
}
void moveup(void){
	pos--;
	if(pos < 1){
		pos = 1;
	}
	HMI_moveArrow(pos);
	DIO_writeChannel(&buzzer , 1);
	_delay_ms(50);
	DIO_writeChannel(&buzzer , 0);
}

void select(void){
	switch(pos){
	case 1:
		UART_transmit('u');
		break;
	case 2:
		UART_transmit('t');
		break;
	case 3:
		UART_transmit('c');
		break;
	}
	DIO_writeChannel(&buzzer , 1);
	_delay_ms(50);
	DIO_writeChannel(&buzzer , 0);
}

void HMI_alarm(void){
	LCD_clearScreen();
	LCD_displayString("lw msktak");
	LCD_goTo(1,0);
	LCD_displayString("H........");
}
void HMI_getOldPassword(void){
	uint8 i = 0;
	uint8 pass[5];
	LCD_clearScreen();
	LCD_displayString("old password");
	LCD_goTo(2,4);
	while(i<5){
		pass[i] = KEYPAD_getCharacter();
		LCD_characterDisplay('*');
		DIO_writeChannel(&buzzer , 1);
		_delay_ms(50);
		DIO_writeChannel(&buzzer , 0);
		i++;
		while(!KEYPAD_keyRelaesed());
	}
	UART_transmitString(pass , 5);
}


void HMI_getpassword(void){
	uint8 i = 0;
	uint8 pass[5];
	LCD_clearScreen();
	LCD_displayString("enter password");
	LCD_goTo(2,4);
	while(i<5){
		pass[i] = KEYPAD_getCharacter();
		LCD_characterDisplay('*');
		DIO_writeChannel(&buzzer , 1);
		_delay_ms(50);
		DIO_writeChannel(&buzzer , 0);
		i++;
		while(!KEYPAD_keyRelaesed());
	}
	UART_transmitString(pass , 5);
}


void HMI_moveArrow(uint8 pos){
	if((pos>3) && (pos<1)){
		return;
	}
	LCD_goTo(1,0);
	LCD_displayString("  ");
	LCD_goTo(2,0);
	LCD_displayString("  ");
	LCD_goTo(3,0);
	LCD_displayString("  ");
	LCD_goTo(pos,0);
	LCD_displayString("->");
}



void HMI_displayMainMenu(void){
	LCD_clearScreen();
	LCD_goTo(0,0);
	LCD_displayString("select :");
	LCD_goTo(1,3);
	LCD_displayString("unlock door");
	LCD_goTo(2,3);
	LCD_displayString("reset pass");
	LCD_goTo(3,3);
	LCD_displayString("close door");
	//	_delay_ms(100);
}



void HMI_firstTimeMSG(void){
	LCD_clearScreen();
	LCD_displayString("welcome");
	LCD_goTo(1,0);
	LCD_displayString("yasta");
	LCD_goTo(2,6);
	LCD_displayString(":)");
}




uint8 HMI_set_password(void){
	uint8 i = 0;
	uint8 pass[5];
	LCD_clearScreen();
	LCD_displayString("new password");
	LCD_goTo(2,4);
	while(i<5){
		pass[i] = KEYPAD_getCharacter();
		LCD_characterDisplay('*');
		DIO_writeChannel(&buzzer , 1);
		_delay_ms(50);
		DIO_writeChannel(&buzzer , 0);
		i++;
		while(!KEYPAD_keyRelaesed());
	}
	UART_transmitString(pass , 5);
}

uint8 HMI_repeat_password(void){
	uint8 i = 0;
	uint8 pass[5];
	LCD_clearScreen();
	LCD_displayString("repeat password");
	LCD_goTo(2,4);
	while(i<5){
		pass[i] = KEYPAD_getCharacter();
		LCD_characterDisplay('*');
		DIO_writeChannel(&buzzer , 1);
		_delay_ms(50);
		DIO_writeChannel(&buzzer , 0);
		i++;
		while(!KEYPAD_keyRelaesed());
	}
	UART_transmitString(pass , 5);
}


void HMI_matchError(void){
	LCD_clearScreen();
	LCD_displayString("no matching");
}


void HMI_success(void){
	LCD_clearScreen();
	LCD_displayString("password");
	LCD_goTo(1,0);
	LCD_displayString("accepted");
}

void HMI_updated(void){
	LCD_clearScreen();
	LCD_displayString("password");
	LCD_goTo(1,0);
	LCD_displayString("updated");
	LCD_goTo(2,0);
	LCD_displayString("successfully");
}
