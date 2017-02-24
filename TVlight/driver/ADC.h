/**********************************************************************************
 * Filename:		ADC.h
 * Author:			Ethan Lyons
 * Creation Date:	21.02.1993
 * Description:		Header file for ADC.c
 */

#ifndef ADC_H_
#define ADC_H_


#include "driver_config.h"

#define ADC_OFFSET	0x10
#define ADC_INDEX	4
#define ADC_DONE 	0x80000000
#define ADC_OVERRUN	0x40000000
#define ADC_ADINT	0x00010000
#define ADC_NUM		8			//for LPC11xx
#define ADC_CLK		240000		//Set to 2.4MHz

extern volatile uint32_t ADCValue[ADC_NUM];
extern void ADC_init(uint32_t ADC_Clk);
extern uint32_t ADCRead(uint32_t channelNum);

#endif /* ADC_H_ */
