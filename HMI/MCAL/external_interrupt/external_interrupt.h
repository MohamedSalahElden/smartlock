/*
 * external_int_0.h
 *
 *  Created on: Jan 7, 2020
 *      Author: SALAH
 */

#ifndef INT0_INT1_H_
#define INT0_INT1_H_


#include "../../utility_header/common_macros.h"
#include "../../utility_header/micro_config.h"
#include "../../utility_header/std_types.h"
#include "../dio_module/dio.h"
#include "externalINT_REG.h"
/*--------- ADC working modes ---------------- */
#ifndef NULL
#define NULL ((void *)0)
#endif


typedef enum{
	low_level , any , falling , rising
}senseControl_t;
typedef enum{
	E_INT0 , E_INT1 , E_INT2
}EINT_ch_t;


typedef struct{
	EINT_ch_t ch;
	senseControl_t INT_SC;
	internal_resistor_t internal_resistor;
	void (*INT_handler)(void);
}EINT_t;

void EINT_init(const EINT_t *EINT_config);
void EINT_changeSenseControl(const EINT_t *EINT_config , senseControl_t EINT_SC);
void EINT_DeInit(const EINT_t *EINT_config);



#endif /* INT0_INT1_H_ */
