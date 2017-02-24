/**********************************************************************************
 * Filename:		localInput.c
 * Author:			Ethan Lyons
 * Creation Date:	21.02.1993
 * Description:		Handles the local Input (GPIO) and passes the relevant info
 * 					onto Lights.c.
 */
#include "driver_config.h"
#include "localInput.h"
#include "Lights.h"
#include "ADC.h"
#include "PWM.h"
void localInput_init(void){
	NVIC_EnableIRQ(EINT3_IRQn);
	NVIC_SetPriority(EINT3_IRQn,1);

	LPC_IOCON->PIO3_0 |= (0x02<<3);	//enable internal pullups
	LPC_IOCON->PIO3_1 |= (0x02<<3);	//enable internal pullups

	LPC_GPIO3->IBE |= 0x02;			//enable interrupt on both edges of PIO3,1
	LPC_GPIO3->IE |= 0x03;			//enable interrupt mask for PIO3,0 and PIO3,1

	LPC_SYSCON->SYSAHBCLKCTRL |= (0x01<<6);
	NVIC_EnableIRQ(EINT3_IRQn);
}

void PIOINT3_IRQHandler(void){
	if (LPC_GPIO3->MIS & 0x01){
			volatile uint32_t i;
			if (LightsGetStatus()){
				LightsOff();
			}
			else{
				LightsOn(ADCRead(0)*9.766);
			}
			for (i=858992;i>0;i--){};
		}
		if (LPC_GPIO3->MIS & 0x02){
			//uint32_t butVal = GPIOGetValue(3,1);
			if(LPC_GPIO3->DATA &= 0x02){
				LightsOff();
			}
			else{
				LightsOn(ADCRead(0)*9.766);
			}
		}
		LPC_GPIO3->IC |=0x3;
}
