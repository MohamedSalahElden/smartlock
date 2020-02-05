/*
 * dio.h
 *
 *  Created on: Jan 26, 2020
 *      Author: SALAH
 */

#ifndef DIO_H_
#define DIO_H_

#include "../../utility_header/common_macros.h"
#include "../../utility_header/micro_config.h"
#include "../../utility_header/std_types.h"


#ifndef HIGH
#define HIGH 1
#endif
#ifndef LOW
#define LOW 1
#endif


/*--------------------enums to configure a GPIO pin ---------------------*/
typedef enum{none   , internal_pullup}internal_resistor_t;   			/*use none in case of no internal resistance is used*/
typedef enum{input , output }direction_t;
typedef enum{pin0  , pin1, pin2, pin3, pin4, pin5, pin6, pin7}PINnum_t;
typedef enum{portA , portB , portC , portD}PORT_t;

typedef struct{
	PORT_t PORT;							/*port name to be configured [portA , portB , portC , portD]*/
	PINnum_t channel_num;					/*specific pin in this port [pin0  , pin1, pin2, pin3, pin4, pin5, pin6, pin7]*/
	direction_t direction;					/*configure the direction of pin [input , output]*/
	internal_resistor_t internal_resistor;	/*configure the internal connection of pin [none  , internal_pullup]*/
}CHconfig_t;

typedef struct{
	PORT_t PORT;							/*port name to be configured [portA , portB , portC , portD]*/
	uint8 mask;					/*specific pin in this port [pin0  , pin1, pin2, pin3, pin4, pin5, pin6, pin7]*/
	direction_t direction;					/*configure the direction of pin [input , output]*/
	internal_resistor_t internal_resistor;	/*configure the internal connection of pin [none  , internal_pullup]*/
}PORTconfig_t;
/*
 * Description : configure the channel's direction , pull up / down
 * */
void  DIO_initChannel(const CHconfig_t * pin_config);
/*
 * Description : write a digital value to a channel
 *
 * */
void DIO_writeChannel(const CHconfig_t * pin_config , uint8 value);
/*
 * Description : the read channel function returns either 0 or 1 representing the digital
 * value exist on the pin
 * */
uint8 DIO_readChannel(const CHconfig_t * pin_config);
/*
 * Description : the init port function initializes a specific port to it's configuration
 * selected in port_config strcuture
 * note that the port_config is masked by the mask member , that mean any write operation on
 * the port would affect only the masked bits leaving all other bits un changed
 * */
void  DIO_initPort(const PORTconfig_t * port_config);
/*
 * Description : the write port function write a specific value to the port in case of output port
 * note that the port_config is masked by the mask member , that mean any write operation on
 * the port would affect only the masked bits leaving all other bits unchanged
 * */
void DIO_writePort(const PORTconfig_t * port_config , uint8 value);
void DIO_PORTDirection(const PORTconfig_t * port_config , uint8 direction);

uint8 DIO_readPort(const PORTconfig_t * port_config);

#endif /* DIO_H_ */
