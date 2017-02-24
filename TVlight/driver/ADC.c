/**********************************************************************************
 * Filename:		ADC.c
 * Author:			Ethan Lyons
 * Creation Date:	21.02.1993
 * Description:		Handles the ADC Hardware on the LPC1114 with specific code for
 * 					the TVLight project.
 */
#include "driver_config.h"
#include "ADC.h"

volatile uint32_t ADCValue[ADC_NUM];

void ADC_init(uint32_t ADC_Clk){

	//Disable Power Down bit for the ADC H/W
	LPC_SYSCON->PDRUNCFG &= ~(0x01<<4);

	//Enable AHB Clock for the ADC H/W
	LPC_SYSCON->SYSAHBCLKCTRL |= (0x01<<13);

	//Clear the ADCValue Array. As only ADC0 is in use, we only need to clear its Value
	ADCValue[0]=0x00;

	//Set ADC0 Pin for ADC Mode.
	LPC_IOCON->R_PIO0_11 &= ~0x8F;
	LPC_IOCON->R_PIO0_11 |= 0x02;

	//Set the ADC Clock. should not succeed 4.5MHz. Current value: ?MHz
	LPC_ADC->CR =((SystemCoreClock/LPC_SYSCON->SYSAHBCLKDIV)/ADC_Clk-1)<<8;
}

uint32_t ADCRead(uint32_t channelNum){
	uint32_t regVal, ADC_Data;

	//Start ADC convert
	LPC_ADC->CR &= 0xFFFFFF00;
	LPC_ADC->CR |= (1<<24) | 1;

	//Read ADC results
	while(1){
		regVal=*(volatile unsigned long *)(LPC_ADC_BASE + ADC_OFFSET + ADC_INDEX * 0);
		if (regVal&ADC_DONE){
			break;
		}
	}
	LPC_ADC->CR &=0xF8FFFFFF;	//Stop ADC immediately
		if (regVal & ADC_OVERRUN){ //save data when not overrun, otherwise return 0
			return(0);
		}
		ADC_Data=(regVal>>6)&0x3FF;
		return(ADC_Data);	//Return ADC value
}
