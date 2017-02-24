/**********************************************************************************
 * Filename:		Lights.c
 * Author:			Ethan Lyons
 * Creation Date:	21.02.1993
 * Description:		Controls the Lights (On/Off, Brightness) for the TVLight project.
 */
#include "driver_config.h"

#include "Lights.h"
//#include "gpio.h"
#include "ADC.h"
#include "PWM.h"

uint32_t LightStatus;
uint32_t LightLevel;

void Lights_init(){
	//GPIO
	//GPIOInit();

	LPC_TMR32B0->MR0 = (ADCRead(0)*9.766);
	//enable_timer32(0);

	LPC_GPIO1->DIR |= 0x01<<6;

	LPC_GPIO1->MASKED_ACCESS[0x01<<6]=(0<<6);
	//GPIOSetDir(1,6,1);
	//GPIOSetValue(1,6,0);

}

void LightsOn(uint32_t level){
	LightLevel=level;
	LPC_TMR32B0->MR0 = LightLevel;
	LPC_IOCON->PIO1_6 |= 0x02;
	PWM_start;
	LightStatus=1;
}

void LightsOff(){
	//disable_timer32(0);
	//reset_timer32(0);
	LPC_IOCON->PIO1_6 &= ~0x07;
	PWM_stop();
	LightStatus=0;

}

uint32_t LightsGetStatus(void){
	return LightStatus;
}
