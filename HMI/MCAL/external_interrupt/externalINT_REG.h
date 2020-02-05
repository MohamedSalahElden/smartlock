/*
 * externalINT_REG.h
 *
 *  Created on: Jan 27, 2020
 *      Author: SALAH
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_EXTERNALINT_REG_H_
#define MCAL_EXTERNAL_INTERRUPT_EXTERNALINT_REG_H_

#include "../../utility_header/std_types.h"

typedef struct {
	uint8 :5;
	uint8 _INT2 :1;
	uint8 _INT0 :1;
	uint8 _INT1 :1;
}GICR_t	 ;
typedef struct {
	uint8 :5;
	uint8 _INTF2 :1;
	uint8 _INTF0 :1;
	uint8 _INTF1 :1;
}GIFR_t  ;
typedef struct {
	uint8 _ISC0 : 2;
	uint8 _ISC1 : 2;
}MCUCR_t ;
typedef struct {
	uint8 :6;
	uint8 _ISC2 : 1;
}MCUCSR_t;



#define _GICR	 (*(volatile GICR_t	  * const ) (0X5B) )
#define _GIFR    (*(volatile GIFR_t   * const ) (0X5A) )
#define _MCUCR   (*(volatile MCUCR_t  * const ) (0X55) )
#define _MCUCSR  (*(volatile MCUCSR_t * const ) (0X54) )


#endif /* MCAL_EXTERNAL_INTERRUPT_EXTERNALINT_REG_H_ */
