/*
 * eeprom.h
 *
 *  Created on: Jan 23, 2020
 *      Author: SALAH
 */

#ifndef EEPROM_H_
#define EEPROM_H_


#include "../../utility_header/common_macros.h"
#include "../../utility_header/micro_config.h"
#include "../../utility_header/std_types.h"



void EEPROM_init(void);
uint8 EEPROM_writeData(uint16 addr , uint8* data , uint16 size);
uint8 EEPROM_readData(uint16 addr , uint8* recieved_data , uint8 size);
#endif /* EEPROM_H_ */
