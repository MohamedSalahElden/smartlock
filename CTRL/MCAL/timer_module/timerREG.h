/*
 * timerREG.h
 *
 *  Created on: Jan 27, 2020
 *      Author: SALAH
 */

#ifndef MCAL_TIMER_MODULE_TIMERREG_H_
#define MCAL_TIMER_MODULE_TIMERREG_H_

#include "../../utility_header/std_types.h"
/*----------------------------------------------------------------------
 * Definitions of types to be used with timer registers
 *---------------------------------------------------------------------- */
typedef struct {
	uint8 	_TOIE0		:1;		/*timer0 overflow interrupt enable*/
	uint8 	_OCIE0		:1;		/*timer0 output compare interrupt enable*/
	uint8	_TOIE1		:1;		/*timer1 overflow interrupt enable*/
	uint8	_OCIE1B		:1;		/*timer1 output compare B interrupt enable*/
	uint8	_OCIE1A		:1;		/*timer1 output compare A interrupt enable*/
	uint8	_TICIE1		:1;		/*timer1 input capture interrupt enable*/
	uint8 	_TOIE2		:1;		/*timer2 overflow interrupt enable*/
	uint8 	_OCIE2 		:1;		/*timer2 output compare interrupt enable*/
}TIMSK_t	;
typedef struct {
	uint8	_TOV0	:1;
	uint8	_OCF0	:1;
	uint8	_TOV1	:1;
	uint8	_OCF1B	:1;
	uint8	_OCF1A	:1;
	uint8	_ICF1	:1;
	uint8	_TOV2	:1;
	uint8	_OCF2    :1;
}TIFR_t     ;
typedef struct {
	uint8	_CS0	:3;
	uint8	_WGM01	:1;
	uint8	_COM0	:2;
	uint8	_WGM00	:1;
	uint8	_FOC0   :1;
}TCCR0_t    ;
typedef struct {
	uint8	_WGM10_1	:2;
	uint8	_FOC1B	:1;
	uint8	_FOC1A	:1;
	uint8	_COM1B	:2;
	uint8	_COM1A	:2;

}TCCR1A_t   ;
typedef struct {
	uint8	_CS1	:3;
	uint8	_WGM12_3	:2;
	uint8		    :1;
	uint8	_ICES1	:1;
	uint8	_ICNC1   :1;
}TCCR1B_t   ;
typedef struct {
	uint8	_CS2		:3;
	uint8	_WGM21	:1;
	uint8	_COM2	:2;
	uint8	_WGM20	:1;
	uint8	_FOC2    :1;
}TCCR2_t    ;

/*----------------------------timers registers addresses ----------------------------*/
#define 	_OCR0        ( *(volatile 	uint8	 * const)(0X5C) )
#define 	_TIMSK       ( *(volatile 	TIMSK_t	 * const)(0X59) )
#define 	_TIFR        ( *(volatile 	TIFR_t	 * const)(0X58) )
#define 	_TCCR0       ( *(volatile 	TCCR0_t	 * const)(0X53) )
#define 	_TCNT0       ( *(volatile 	uint8	 * const)(0X52) )
#define 	_TCCR1A      ( *(volatile 	TCCR1A_t * const)(0X4F) )
#define 	_TCCR1B      ( *(volatile 	TCCR1B_t * const)(0X4E) )
#define 	_TCNT1       ( *(volatile 	uint16	 * const)(0X4C) )
#define 	_OCR1A       ( *(volatile 	uint16	 * const)(0X4A) )
#define 	_OCR1B       ( *(volatile 	uint16	 * const)(0X48) )
#define 	_ICR1        ( *(volatile 	uint16	 * const)(0X46) )
#define 	_TCCR2       ( *(volatile 	TCCR2_t	 * const)(0X45) )
#define 	_TCNT2       ( *(volatile 	uint8	 * const)(0X44) )
#define 	_OCR2		 ( *(volatile 	uint8	 * const)(0X43) )



#endif /* MCAL_TIMER_MODULE_TIMERREG_H_ */

