/*
 * Lights.c
 *
 *  Created on: 15 Feb 2017
 *      Author: ethan
 */
#include "driver_config.h"

#include "Lights.h"
#include "gpio.h"
#include "adc.h"
#include "timer32.h"

void Lights_init(){
	//GPIO
	GPIOInit();

	NVIC_EnableIRQ(EINT3_IRQn);
	NVIC_SetPriority(EINT3_IRQn,1);

	LPC_IOCON->PIO3_0 |= (0x02<<3);	//enable pullups
	LPC_IOCON->PIO3_1 |= (0x02<<3);	//enable pullups

	LPC_GPIO3->IBE |= 0x02;			//enable interrupt on both edges of PIO3,1
	LPC_GPIO3->IE |= 0x03;			//enable interrupt mask for PIO3,0 and PIO3,1

	//ADC
	ADCInit(240000);

	//Timer32
	init_timer32(0,0);

	LPC_TMR32B0->MR0 = (ADCRead(0)*9.766);
	//enable_timer32(0);

	GPIOSetDir(1,6,1);
	GPIOSetValue(1,6,0);

}

void LightsOn(){
	//LPC_TMR32B0->MR0 = (ADCRead(0)*9.766);
	//enable_timer32(0);
	LPC_IOCON->PIO1_6 |= 0x02;
	enable_timer32(0);
	LightStatus=1;
}

void LightsOff(){
	//disable_timer32(0);
	//reset_timer32(0);
	LPC_IOCON->PIO1_6 &= ~0x07;
	disable_timer32(0);
	LightStatus=0;

}

void PIOINT3_IRQHandler(void){
	if (LPC_GPIO3->MIS & 0x01){
		volatile uint32_t i;
		if (LightStatus){
			LightsOff();
		}
		else{
			LightsOn();
		}
		for (i=858992;i>0;i--){};
	}
	if (LPC_GPIO3->MIS & 0x02){
		uint32_t butVal = GPIOGetValue(3,1);
		if (butVal==1){
			LightsOff();
		}
		else{
			LightsOn();
		}
	}
	LPC_GPIO3->IC |=0x3;
}
