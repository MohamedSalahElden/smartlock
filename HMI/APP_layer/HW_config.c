/*
 * HW_config.c
 *
 *  Created on: Feb 5, 2020
 *      Author: SALAH
 */

#include "HMI_utility_functions.h"

CHconfig_t buzzer = {portD , pin7 , output , none};
uartConfig_t uart = {asynchronous , Disabled , _1bit , _8bit , UARTrising , 9600};
EINT_t downbutton = {E_INT1 , falling , internal_pullup , movedown};
EINT_t upbutton = {E_INT0 , falling , internal_pullup , moveup};
EINT_t selectbutton = {E_INT2 , falling , internal_pullup , select};



