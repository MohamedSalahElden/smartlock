/*
 * eeprom.c
 *
 *  Created on: Jan 23, 2020
 *      Author: SALAH
 */


#include "../../MCAL/i2c/i2c.h"
#include "eeprom.h"


void EEPROM_init(void){
	TWIconfig_t I2C_EEPROM_config= {2 , PRE_1 , 0xAA};
	TWI_init(&I2C_EEPROM_config);
}
uint8 EEPROM_writeData(uint16 addr , uint8* data , uint16 size){

	uint16 devAddress = (0b10100000 & 0xF1) | (uint8)((addr & 0x700) >> 7);
	uint8 i = 0;
	TWI_start();
	TWI_write(devAddress);
	TWI_write((addr & 0xFF));
	for(i=0 ; i<size ; i++){
		TWI_write(data[i]);
	}
	TWI_stop();

}
uint8 EEPROM_readData(uint16 addr , uint8* recieved_data , uint8 size){
	uint8 i;

	TWI_start();
	TWI_write((0b10100000 & 0xF0) | (uint8)((addr & 0x700) >> 7));
	TWI_write((uint8)addr);

	TWI_start();
	TWI_write((0b10100001 & 0xF1) | (uint8)((addr & 0x700) >> 7));
	for(i=0 ; i<size-1 ; i++){
		recieved_data[i] = TWI_readWithACK();
	}
	recieved_data[0] = TWI_readWithNACK();
	TWI_stop();

}
