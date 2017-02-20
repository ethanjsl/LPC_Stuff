/******************************************************************************
** file name:			timer32.c
**
** Descriptions:		Hardware specific functions relating to timer 32.
** 						To be used in any project. Changes are to be made to 
**						the current project only.
**
** Author:				Ethan Lyons, Fr. Sauter AG Basel
**
** Date created:		21.09.2015
**
******************************************************************************/

#include "driver_config.h"
#if CONFIG_ENABLE_DRIVER_TIMER32==1
#include "timer32.h"
#include "gpio.h"
#include "adc.h"

volatile uint32_t timer32_0_period = 0;

volatile uint32_t timer32_0_counter = 0;
volatile uint32_t timer32_0_capture = 0;

volatile uint32_t timer32_1_period = 0;

volatile uint32_t timer32_1_counter = 0;
volatile uint32_t timer32_1_capture = 0;

uint32_t time0=150, time1=1;
uint32_t cycle0=0, cycle1=0;


#endif


void (*callback)(void) = 0;


void timer32_register_callback(void(*cb)(void)){
	callback = cb;
}

/******************************************************************************
** Function name:		init_timer32
**
** Descriptions:		Initialize timer, set timer interval, reset timer,
**						install timer interrupt handler
**
** parameters:			timer number and timer interval
** Returned value:		None
**
******************************************************************************/
void init_timer32(uint8_t timer_num, uint32_t TimerInterval)
{
  if ( timer_num == 0 )
  {
    /* Some of the I/O pins need to be carefully planned if
    you use below module because JTAG and TIMER CAP/MAT pins are muxed. */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);
    LPC_IOCON->PIO1_5 &= ~0x07;	/*  Timer0_32 I/O config */
    LPC_IOCON->PIO1_5 |= 0x02;	/* Timer0_32 CAP0 */
    LPC_IOCON->PIO1_6 &= ~0x07;
    //LPC_IOCON->PIO1_6 |= 0x02;	/* Timer0_32 MAT0 */
    LPC_IOCON->PIO1_7 &= ~0x07;
    LPC_IOCON->PIO1_7 |= 0x02;	/* Timer0_32 MAT1 */
    LPC_IOCON->PIO0_1 &= ~0x07;
    LPC_IOCON->PIO0_1 |= 0x02;	/* Timer0_32 MAT2 */
#ifdef __JTAG_DISABLED
    LPC_IOCON->JTAG_TDI_PIO0_11 &= ~0x07;
    LPC_IOCON->JTAG_TDI_PIO0_11 |= 0x03;	/* Timer0_32 MAT3 */
#endif

    timer32_0_counter = 0;
    timer32_0_capture = 0;

    LPC_TMR32B0->MR0 = TimerInterval;
    LPC_TMR32B0->MR3=10000;
#if TIMER_MATCH
	LPC_TMR32B0->EMR &= ~(0xFF<<4);
	LPC_TMR32B0->EMR |= ((0x3<<4)|(0x3<<6)|(0x3<<8)|(0x3<<10));	/* MR0/1/2/3 Toggle */
#else
	/* Capture 0 on rising edge, interrupt enable. */
	LPC_TMR32B0->CCR = (0x1<<0)|(0x1<<2);
#endif
    //LPC_TMR32B0->MCR = 3;			/* Interrupt and Reset on MR0 */
	LPC_TMR32B0->MCR &= 0x7FF;
	LPC_TMR32B0->MCR |= ((0x01<<9)|(0x01<<10)/*|(0x01<<11)*/);

	LPC_TMR32B0->PWMC |=0x01;

    /* Enable the TIMER0 Interrupt */
    NVIC_EnableIRQ(TIMER_32_0_IRQn);
    NVIC_SetPriority(TIMER_32_0_IRQn, 2);

  }
  else if ( timer_num == 1 )
  {
    /* Some of the I/O pins need to be clearfully planned if
    you use below module because JTAG and TIMER CAP/MAT pins are muxed. */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<10);
#ifdef __JTAG_DISABLED
    LPC_IOCON->JTAG_TMS_PIO1_0  &= ~0x07;	/*  Timer1_32 I/O config */
    LPC_IOCON->JTAG_TMS_PIO1_0  |= 0x03;	/* Timer1_32 CAP0 */
    LPC_IOCON->JTAG_TDO_PIO1_1  &= ~0x07;
    LPC_IOCON->JTAG_TDO_PIO1_1  |= 0x03;	/* Timer1_32 MAT0 */
    LPC_IOCON->JTAG_nTRST_PIO1_2 &= ~0x07;
    LPC_IOCON->JTAG_nTRST_PIO1_2 |= 0x03;	/* Timer1_32 MAT1 */
    LPC_IOCON->ARM_SWDIO_PIO1_3  &= ~0x07;
    LPC_IOCON->ARM_SWDIO_PIO1_3  |= 0x03;	/* Timer1_32 MAT2 */
#endif
    LPC_IOCON->PIO1_4 &= ~0x07;
    LPC_IOCON->PIO1_4 |= 0x02;		/* Timer0_32 MAT3 */

#if CONFIG_TIMER32_DEFAULT_TIMER32_1_IRQHANDLER==1
    timer32_1_counter = 0;
    timer32_1_capture = 0;
#endif //TIMER32_1_DEFAULT_HANDLER

    LPC_TMR32B1->MR0 = TimerInterval;
#if TIMER_MATCH
	LPC_TMR32B1->EMR &= ~(0xFF<<4);
	LPC_TMR32B1->EMR |= ((0x3<<4)|(0x3<<6)|(0x3<<8)|(0x3<<10));	/* MR0/1/2 Toggle */
#else
	/* Capture 0 on rising edge, interrupt enable. */
	LPC_TMR32B1->CCR = (0x1<<0)|(0x1<<2);
#endif
    LPC_TMR32B1->MCR = 3;			/* Interrupt and Reset on MR0 */

#if CONFIG_TIMER32_DEFAULT_TIMER32_1_IRQHANDLER==1
    /* Enable the TIMER1 Interrupt */
    NVIC_EnableIRQ(TIMER_32_1_IRQn);
    NVIC_SetPriority(TIMER_32_1_IRQn, 1);
#endif
  }
  return;
}

/******************************************************************************
** Function name:		enable_timer32
**
** Descriptions:		enables timer
**
** parameters:			timer number
**
** Returned value:		None
**
******************************************************************************/
void enable_timer32(uint8_t timer_num)
{
  if ( timer_num == 0 )
  {
    LPC_TMR32B0->TCR = 1;
  }
  else
  {
    LPC_TMR32B1->TCR = 1;
  }
  return;
}

/******************************************************************************
** Function name:		disable_timer32
**
** Descriptions:		disables timer
**
** parameters:			timer number
**
** Returned value:		None
**
******************************************************************************/
void disable_timer32(uint8_t timer_num)
{
  if ( timer_num == 0 )
  {
    LPC_TMR32B0->TCR = 0;
  }
  else
  {
    LPC_TMR32B1->TCR = 0;
  }
  return;
}

/******************************************************************************
** Function name:		reset_timer32
**
** Descriptions:		resets timer
**
** parameters:			timer number
**
** Returned value:		None
**
******************************************************************************/
void reset_timer32(uint8_t timer_num)
{
  volatile uint32_t regVal;

  if ( timer_num == 0 )
  {
    regVal = LPC_TMR32B0->TCR;
    regVal |= 0x02;
    LPC_TMR32B0->TCR = regVal;
  }
  else
  {
    regVal = LPC_TMR32B1->TCR;
    regVal |= 0x02;
    LPC_TMR32B1->TCR = regVal;
  }
  return;
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
void TIMER32_0_IRQHandler(void)
{
	uint32_t ADCVal=ADCRead(0);
	LPC_TMR32B0->MR0=ADCVal*9.766;
	//enable_timer32(0);
  if ( LPC_TMR32B0->IR & 0x01 )
  {
	LPC_TMR32B0->IR = 1;		/* clear interrupt flag */

	}
/*  if (GPIOGetValue(1,9)){
	  GPIOSetValue(1,9,0);
  }
  else {
	  GPIOSetValue(1,9,1);
  }*/
  GPIOSetValue(2,0,0);

}

/******************************************************************************
** Function name:		TIMER32_1_IRQHandler
**
** Descriptions:		interrupt handler for timer32 1
**
** parameters:			none
**
** Returned value:		None
**
******************************************************************************/
void TIMER32_1_IRQHandler (void)
{
	GPIOSetValue(0,7,1);
	if (LPC_TMR32B1->IR & 0x01)
	{
		LPC_TMR32B1->IR=1;

	}
	GPIOSetValue(0,7,0);
}

/******************************************************************************
** Function name:		timer32_setMatch
**
** Descriptions:		sets the match register of the selected timer32
**
** parameters:			timer number, match time in us
**
** Returned value:		None
**
******************************************************************************/
void timer32_setMatch(uint8_t timer_num, uint32_t match_in_us){
	uint32_t matchVal=0;

	//matchVal=match_in_us*(SystemCoreClock/1000000);
	matchVal=match_in_us;
	if (timer_num==0){
		LPC_TMR32B0->MR0=matchVal;
	}

	if (timer_num==1){
		LPC_TMR32B1->MR0=matchVal;
	}

}

/******************************************************************************
** Function name:		timer32_delay_us
**
** Descriptions:		delay function using timer32 1
**
** parameters:			time in us
**
** Returned value:		None
**
******************************************************************************/
void timer32_delay_us(uint32_t time_in_us){
	/* setup timer #1 for delay */
	    LPC_TMR32B1->TCR = 0x02;		/* reset timer */
	    LPC_TMR32B1->PR  = 0x00;		/* set prescaler to zero */
	    LPC_TMR32B1->MR0 = time_in_us * ((SystemCoreClock/(LPC_TMR32B0->PR+1)) / 1000000);
	    LPC_TMR32B1->IR  = 0xff;		/* reset all interrrupts */
	    LPC_TMR32B1->MCR = 0x04;		/* stop timer on match */
	    LPC_TMR32B1->TCR = 0x01;		/* start timer */

	    /* wait until delay time has elapsed */
	    while (LPC_TMR32B1->TCR & 0x01);
}
