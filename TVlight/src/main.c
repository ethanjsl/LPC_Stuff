/******************************************************************************
** file name:			main.c
**
** Descriptions:		main program.
**
** Author:				Ethan Lyons, Fr. Sauter AG Basel
**
** Date created:		21.09.2015
**
** Date edited:			18.12.2015
**
** Edited because:		Changes were made to make it a general main.c file.
**						To be used as an empty Project.
**
******************************************************************************/

#include "driver_config.h"
#include "target_config.h"

#include "../driver/gpio.h"

#include <stdio.h>
#include "../driver/timer32.h"
#include "../driver/adc.h"
#include "../driver/Lights.h"

/* Main Program */

int main (void){
	//Lights
	Lights_init();
	//LightsOn();
	//GPIO
	//GPIOInit();

	//ADC
	//ADCInit(240000);
  
	//Other peripherals
	
	//GPIO Setup
	//GPIOSetDir(3,0,0);
	//GPIOSetDir(3,1,1);
	
	//Timer32B0
	//init_timer32(0,0);
/*	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);
	LPC_IOCON->PIO1_5 &= ~0x07;	//Timer0_32 I/O config
	LPC_IOCON->PIO1_5 |= 0x02;	//Timer0_32 CAP0
	LPC_IOCON->PIO1_6 &= ~0x07;
	LPC_IOCON->PIO1_6 |= 0x02;	//Timer0_32 MAT0
	LPC_IOCON->PIO1_7 &= ~0x07;
	LPC_IOCON->PIO1_7 |= 0x02;	//Timer0_32 MAT1
	LPC_IOCON->PIO0_1 &= ~0x07;
	LPC_IOCON->PIO0_1 |= 0x02;	//Timer0_32 MAT2

    //timer32_0_counter = 0;
    //timer32_0_capture = 0;

    LPC_TMR32B0->MR3 = 1000;

	LPC_TMR32B0->EMR &= ~(0xFF<<4);
	//LPC_TMR32B0->EMR |= ((0x2<<4)|(0x3<<6)|(0x3<<8)|(0x3<<10));	//MR0/1/2/3 Toggle

    //LPC_TMR32B0->MCR = 3;			//Interrupt and Reset on MR0
	LPC_TMR32B0->MCR &= ~0x7FF;
    LPC_TMR32B0->MCR |= (0x1<<10);

    LPC_TMR32B0->PWMC |= 0x01;

    // Enable the TIMER0 Interrupt
    NVIC_EnableIRQ(TIMER_32_0_IRQn);
    NVIC_SetPriority(TIMER_32_0_IRQn, 2);*/

   // LPC_TMR32B0->MR0 = 7500;

    //enable_timer32(0);

	while (1){ /* Loop forever */
	

	}
}
