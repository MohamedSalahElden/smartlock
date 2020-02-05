/*
 * dio.c
 *
 *  Created on: Jan 26, 2020
 *      Author: SALAH
 */

#include "dio.h"

void  DIO_initChannel(const CHconfig_t * pin_config){
	switch (pin_config->PORT){
	case portA:			/*configure pin in port A*/
		WRITE_BIT(DDRA , pin_config->channel_num , pin_config->direction); 				/*configure direction of pin either input or output*/
		WRITE_BIT(PORTA , pin_config->channel_num , pin_config->internal_resistor);		/*configure the internal resistor connection [none , internal_pullup]*/
		break;
	case portB:
		WRITE_BIT(DDRB , pin_config->channel_num , pin_config->direction);
		WRITE_BIT(PORTB , pin_config->channel_num , pin_config->internal_resistor);
		break;
	case portC:
		WRITE_BIT(DDRC , pin_config->channel_num , pin_config->direction);
		WRITE_BIT(PORTC , pin_config->channel_num , pin_config->internal_resistor);
		break;
	case portD:
		WRITE_BIT(DDRD , pin_config->channel_num , pin_config->direction);
		WRITE_BIT(PORTD , pin_config->channel_num , pin_config->internal_resistor);
		break;
	default:
		return;
		break;
	}
}
void  DIO_writeChannel(const CHconfig_t * pin_config , uint8 value){
	if(pin_config->direction == input){
		return ;
	}
	switch (pin_config->PORT){
	case portA:
		WRITE_BIT(PORTA , pin_config->channel_num , value);
		break;
	case portB:
		WRITE_BIT(PORTB , pin_config->channel_num , value);
		break;
	case portC:
		WRITE_BIT(PORTC , pin_config->channel_num , value);
		break;
	case portD:
		WRITE_BIT(PORTD , pin_config->channel_num , value);
		break;
	}
}
uint8 DIO_readChannel(const CHconfig_t * pin_config){
	switch (pin_config->PORT){
	case portA:
		return READ_BIT(PINA , pin_config->channel_num );
		break;
	case portB:
		return READ_BIT(PINB , pin_config->channel_num );
		break;
	case portC:
		return READ_BIT(PINC , pin_config->channel_num );
		break;
	case portD:
		return READ_BIT(PIND , pin_config->channel_num );
		break;
	}
	return 0;
}



void  DIO_initPort(const PORTconfig_t * port_config){
	switch (port_config->PORT){
	case portA:
		DDRA  = (DDRA & ~(port_config->mask)) | ((port_config->direction * 255)         & port_config->mask);
		PORTA = (PORTA & ~(port_config->mask)) | ((port_config->internal_resistor * 255) & port_config->mask);
		break;
	case portB:
		DDRB  = (DDRB & ~(port_config->mask)) | ((port_config->direction * 255)         & port_config->mask);
		PORTB = (PORTB & ~(port_config->mask)) | ((port_config->internal_resistor * 255) & port_config->mask);
		break;
	case portC:
		DDRC  = (DDRC & ~(port_config->mask)) | ((port_config->direction * 255)         & port_config->mask);
		PORTC = (PORTC & ~(port_config->mask)) | ((port_config->internal_resistor * 255) & port_config->mask);
		break;
	case portD:
		DDRD  = (DDRD & ~(port_config->mask)) | ((port_config->direction * 255)         & port_config->mask);
		PORTD = (PORTD & ~(port_config->mask)) | ((port_config->internal_resistor * 255) & port_config->mask);
		break;
	}
}
void DIO_writePort(const PORTconfig_t * port_config , uint8 value){
	switch (port_config->PORT){
	case portA:
		PORTA = (PORTA & ~(port_config->mask)) | ((value) & port_config->mask);
		break;
	case portB:
		PORTB = (PORTB & ~(port_config->mask)) | ((value) & port_config->mask);
		break;
	case portC:
		PORTC = (PORTC & ~(port_config->mask)) | ((value) & port_config->mask);
		break;
	case portD:
		PORTD = (PORTD & ~(port_config->mask)) | ((value) & port_config->mask);
		break;
	}
}

void DIO_PORTDirection(const PORTconfig_t * port_config , uint8 direction){
	switch (port_config->PORT){
	case portA:
		DDRA = (DDRA & ~(port_config->mask)) | ((direction) & port_config->mask);
		break;
	case portB:
		DDRB = (DDRB & ~(port_config->mask)) | ((direction) & port_config->mask);
		break;
	case portC:
		DDRC = (DDRC & ~(port_config->mask)) | ((direction) & port_config->mask);
		break;
	case portD:
		DDRD = (DDRD & ~(port_config->mask)) | ((direction) & port_config->mask);
		break;
	}
}

uint8 DIO_readPort(const PORTconfig_t * port_config){
	switch (port_config->PORT){
	case portA:
		return PINA & port_config->mask;
		break;
	case portB:
		return PINB & port_config->mask;
		break;
	case portC:
		return PINC & port_config->mask;
		break;
	case portD:
		return PIND & port_config->mask;
		break;
	}
	return 0;
}
