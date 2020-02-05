/*
 * i2c.c
 *
 *  Created on: Jan 22, 2020
 *      Author: SALAH
 */
#include "i2c.h"

void TWI_init(TWIconfig_t * TWIconfig){
	/*
	 * TWCR ---------------- page 180
	 * bit	name 	value 	description
	 * 7 	TWINT 	1		(HW flag) clear by writing 1
	 * 6	TWEA	0		will be enabled in TWI_readWithACK & disabled in TWI_readWithNACK
	 * 5	TWSTA	0		will be enabled in TWI_start to send start bit
	 * 4	TWSTO	0		will be enabled in TWI_stop to release the bus to another master
	 * 3	TWWC	-		write collision flag (HW flag)
	 * 2	TWEN	1		enables the TWI module
	 * 1	reserved
	 * 0	TWIE	0		TWI module interrupt enable (we will use polling)
	 */
	TWBR = TWIconfig->bitRate ;
	TWCR = (1<<TWINT) | (1<<TWEN); /*clear the interrupt flag & enable the TWI module*/
	TWSR = (TWSR & 0xFC) | (TWIconfig->preScaller & 0x03); /*set the prescaler */
	TWAR = (TWIconfig->deviceAddress)<<1;	/*set the slave address (shift is used because the 7 bit address 7-1)*/
}
void TWI_start(void){
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA); /*clear the interrupt flag & enable the TWI module & set the start bit condition*/
	while(BIT_IS_CLEAR(TWCR , TWINT));	/*busy loop until finishing sending the start bit*/
}
void TWI_stop(void){
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO); /*clear the interrupt flag & enable the TWI module & set the stop bit condition*/
}
void TWI_write(uint8 data){
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN); /*clear the interrupt flag & enable the TWI module*/
	while(BIT_IS_CLEAR(TWCR , TWINT));	/*busy loop until finishing sending data*/
}
uint8 TWI_readWithACK(void){
	TWCR = (1 << TWINT) | (1 << TWEN) | (1<<TWEA); /*clear the interrupt flag & enable the TWI module & enable replying with ACK*/
	while(BIT_IS_CLEAR(TWCR , TWINT));	/*busy loop until finishing receiving data*/
	return TWDR; /*read data*/
}
uint8 TWI_readWithNACK(void){
	TWCR = (1 << TWINT) | (1 << TWEN); /*clear the interrupt flag & enable the TWI module*/
	while(BIT_IS_CLEAR(TWCR , TWINT));	/*busy loop until finishing recieving data*/
	return TWDR;
}
uint8 TWI_getStatus(void){
	return (TWSR & 0xF8); /*masking the most five bits that represents the TWI status*/
}
