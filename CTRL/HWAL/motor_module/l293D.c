/*
 * l293D.c
 *
 *  Created on: Jan 7, 2020
 *      Author: SALAH
 */
#include "../../MCAL/dio_module/dio.h"
#include "l293D.h"



void MOTOR_init(motorConfig_t * motorConfig){
	DIO_initChannel(&motorConfig->motorPIN0);
	DIO_initChannel(&motorConfig->motorPIN1);
	if(motorConfig->direction == CW){
		DIO_writeChannel(&motorConfig->motorPIN0 , 1);
		DIO_writeChannel(&motorConfig->motorPIN1 , 0);
	}
	else if(motorConfig->direction == CCW){
		DIO_writeChannel(&motorConfig->motorPIN0 , 0);
		DIO_writeChannel(&motorConfig->motorPIN1 , 1);

	}
}


void MOTOR_start(motorConfig_t * motorConfig , uint8 speed){
	s_pwmConfig motor = {motorConfig->enablePIN , CLK_8 , 255 , speed , non_inverting};
	PWM_start(&motor);
}

void MOTOR_stop(motorConfig_t * motorConfig){
	PWM_stop(motorConfig->enablePIN);
}



void MOTOR_changeDirection(motorConfig_t * motorConfig , motorDir direction){
	if(direction == CW){
		DIO_writeChannel(&motorConfig->motorPIN0 , 1);
		DIO_writeChannel(&motorConfig->motorPIN1 , 0);
	}
	else if(direction == CCW){
		DIO_writeChannel(&motorConfig->motorPIN0 , 0);
		DIO_writeChannel(&motorConfig->motorPIN1 , 1);

	}
}
