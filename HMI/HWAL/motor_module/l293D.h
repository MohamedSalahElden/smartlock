/*
 * l293D.h
 *
 *  Created on: Jan 7, 2020
 *      Author: SALAH
 */

#ifndef L293D_H_
#define L293D_H_

#include "../../utility_header/common_macros.h"
#include "../../utility_header/micro_config.h"
#include "../../utility_header/std_types.h"
#include "../../MCAL/PWM_module/pwm.h"

typedef enum{
	CW , CCW
}motorDir;


typedef struct{
	CHconfig_t motorPIN0;
	CHconfig_t motorPIN1;
	e_pwmChannel enablePIN;
	motorDir direction;
}motorConfig_t;

void MOTOR_init(motorConfig_t * motorConfig);
void MOTOR_start(motorConfig_t * motorConfig , uint8 speed);
void MOTOR_stop(motorConfig_t * motorConfig);
void MOTOR_changeDirection(motorConfig_t * motorConfig , motorDir direction);

#endif /* L293D_H_ */
