/**********************************************************************************
 * Filename:		PWM.c
 * Author:			Ethan Lyons
 * Creation Date:	22.02.1993
 * Description:		Handles the PWM Hardware on Timer32_0 and includes the ISR.
 */
#include "driver_config.h"
#include "PWM.h"
#include "ADC.h"

/******************************************************************************
** Function name:		PWM_init
**
** Descriptions:		Initialization of the PWM H/W. Using PIO1_6 as the output
** 						(linked to MR0) and using MR3 as the reset register.
** 						For more details on the PWM H/W, see UM10398.pdf page 373.
**
** parameters:			none
**
** Returned value:		None
**
******************************************************************************/
void PWM_init(void){
	LPC_SYSCON->SYSAHBCLKCTRL |= (0x01<<9);
	LPC_IOCON->PIO1_6 |= ~0x07;

	LPC_TMR32B0->MCR &= ~0x7FF;
	LPC_TMR32B0->MCR |= ((0x01<<9)|(0x01<<10));

	LPC_TMR32B0->PWMC |= 0x01;

	NVIC_EnableIRQ(TIMER_32_0_IRQn);
	NVIC_SetPriority(TIMER_32_0_IRQn,2);
}

/******************************************************************************
** Function name:		PWM_start
**
** Descriptions:		starts Timer32B0 -> starts the PWM-Signal
**
** parameters:			None
**
** Returned value:		None
**
******************************************************************************/
void PWM_start(void){
	LPC_TMR32B0->TCR=1;
}

/******************************************************************************
** Function name:		PWM_stop
**
** Descriptions:		stops Timer32B0 -> stops the PWM-Signal
**
** parameters:			None
**
** Returned value:		None
**
******************************************************************************/
void PWM_stop(void){
	LPC_TMR32B0->TCR=0;
}

/******************************************************************************
** Function name:		TIMER32_0_IRQHandler
**
** Descriptions:		interrupt handler for timer32 0
**
** parameters:			none
**
** Returned value:		None
**
******************************************************************************/
void TIMER32_0_IRQHandler(void){
	uint32_t ADCVal=ADCRead(0);
	LPC_TMR32B0->MR0=ADCVal*9.766;
	if (LPC_TMR32B0->IR*0x01){LPC_TMR32B0->IR=0x01;}
}
