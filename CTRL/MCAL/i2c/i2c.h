/*
 * i2c.h
 *
 *  Created on: Jan 22, 2020
 *      Author: SALAH
 */

#ifndef I2C_H_
#define I2C_H_

#include "../../utility_header/common_macros.h"
#include "../../utility_header/micro_config.h"
#include "../../utility_header/std_types.h"


typedef enum{PRE_1 , PRE_4 , PRE_16 , PRE_64}i2cPreScaler_t;
typedef struct{
	/*--------------------------------------------------------------
	 * bit rate of i2c module is calculated from an equation in page (178)
	 * 	--->SCL frequency = (CPU Clock frequency) / (16 + 2*TWBR * (4^TWPS))
	 * 		where TWBR is the bit rate
	 * 			  TWPS is prescaler
	 * --------------------------------------------------------------*/
	uint8 bitRate;
	/*--------------------------------------------------------------
	 * prescaler could be [PRE_1 , PRE_4 , PRE_16 , PRE_64]
	 * --------------------------------------------------------------*/
	i2cPreScaler_t preScaller;
	/*--------------------------------------------------------------
	 * the slave address of the device runs that code 0 ~ 127
	 * --------------------------------------------------------------*/
	uint8 deviceAddress;
}TWIconfig_t;

void TWI_init(TWIconfig_t * TWIconfig);
void TWI_start(void);
void TWI_stop(void);
void TWI_write(uint8 data);
uint8 TWI_readWithACK(void);
uint8 TWI_readWithNACK(void);
uint8 TWI_getStatus(void);

#endif /* I2C_H_ */
