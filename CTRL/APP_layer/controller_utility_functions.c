/*
 * set_password.c
 *
 *  Created on: Jan 30, 2020
 *      Author: SALAH
 */

#include "controller_utility_functions.h"


static uint8 door_state = 0;

void motorTimerInterruptHandler(void){
	static uint8 counter = 0;
	counter++;
	DDRA = 0xFF;
	PORTA ^= (2<<0);
	if(counter > MOTOR_ON_TIME){
		MOTOR_stop(&motor1);
		TIMER_stop(&motortimer);
		counter = 0;
		if(door_state == 1){
			CONT_keepOpen();
		}
	}
}


void keepOpeninterruptHandler(void){
	static uint8 counter = 0;
	counter++;
	DDRA = 0xFF;
	PORTA ^= (1<<0);
	if(counter > KEEP_OPEN_TIME){
		TIMER_stop(&keepOpenTimer);
		counter = 0;
		CONT_closedoor();
	}
}

void alarminterruptHandler(void){
	static uint8 counter = 0;
	counter++;
	DDRA = 0xFF;
	PORTA ^= (1<<0);
	if(counter > ALARM_TIME){
		TIMER_stop(&alarmTimer);
		UART_transmit(MAIN_MENU_MSG);
		counter = 0;
		DIO_writeChannel(&alarm , 0);
	}
}

void CONT_opendoor(void){
	if(door_state == 1)
		return;
	MOTOR_changeDirection(&motor1 , CW);
	TIMER_start(&motortimer);
	MOTOR_start(&motor1 , 250);
	door_state = 1;
}

void CONT_closedoor(void){
	if(door_state == 0)
		return;
	MOTOR_changeDirection(&motor1 , CCW);
	TIMER_start(&motortimer);
	MOTOR_start(&motor1 , 250);
	door_state = 0;
}

void CONT_keepOpen(void){
	TIMER_start(&keepOpenTimer);
}

void CONT_startAlarm(){
	DIO_writeChannel(&alarm , 1);
	TIMER_start(&alarmTimer);
}

uint8 CONT_getAndCompPassword(char msg){

	uint8 password[5]= {0};
	uint8 storedpassword[5] = {0};
	uint8 counter = 0;

	EEPROM_readData(0x00 , &storedpassword[0] , 1);
	EEPROM_readData(0x01 , &storedpassword[1] , 1);
	EEPROM_readData(0x02 , &storedpassword[2] , 1);
	EEPROM_readData(0x03 , &storedpassword[3] , 1);
	EEPROM_readData(0x04 , &storedpassword[4] , 1);

	for(counter=0 ; counter<3 ; counter++){
		CONT_getPassword(password , msg);
		if (CONT_password_match(password , storedpassword)){
			return 1;	/*password match*/
		}
	}
	return 0;	/*no matching*/
}

void CONT_setPassword(void){
	uint8 password[5] = {0};
	uint8 repeated[5] = {0};
	do{
		CONT_getPassword(password , NEW_PASS_MGS);
		CONT_getPassword(repeated , REPEATE_PASS_MSG);
	}while(!CONT_password_match(password , repeated));
	CONT_updatePassword(password);
	CONT_sendMSG(MAIN_MENU_MSG);
}


void CONT_sendMSG(uint8 msg){
	recieved_data = 0x00;
	while(recieved_data != ACK_MSG){
		UART_transmit(msg);
		_delay_ms(1000);
	}
}


uint8 CONT_firstRunCheck(void){
	uint8 first_EEPROM_Byte = 0;
	EEPROM_readData(0x00 , &first_EEPROM_Byte , 1);
	if(first_EEPROM_Byte == 0xFF){
		CONT_sendMSG(FIRST_RUN);
		_delay_ms(1000);
		return 1; /*this is first time run*/
	}
	return 0;	/*this is not the first time run*/
}

void CONT_getPassword(uint8 * pass , uint8 msg){
	CONT_sendMSG(msg);
	SREG &= ~(1<<7);
	UART_receiveString(pass , 5);
	SREG |= (1<<7);
}


uint8 CONT_password_match(uint8 * pass1 , uint8 * pass2){
	uint8 i=0;
	uint8 check[5];
	for(i=0 ; i<5 ; i++){
		if(pass1[i] != pass2[i]){
			CONT_sendMSG(NO_MATCH);
			_delay_ms(1000);
			return 0;
		}
	}
	//	UART_transmit(PASSWORD_MATCH);
	//	_delay_ms(1000);
	return 1;
}

void CONT_updatePassword(uint8 * pass){
	EEPROM_writeData(0x00 , pass , 5);
	CONT_sendMSG(PASS_UPDATED_MSG);
	_delay_ms(1000);
	recieved_data = 0x00;
}
