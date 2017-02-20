/******************************************************************************
** file name:			timer32.h
**
** Descriptions:		header file for timer32.c. Contains all function
** 						prototypes relating to timer32.c.
**
** Author:				Ethan Lyons, Fr. Sauter AG Basel
**
** Date created:		21.09.2015
**
******************************************************************************/

#ifndef TIMER32_H_
#define TIMER32_H_
#if CONFIG_ENABLE_DRIVER_TIMER32==1

#define TIME_INTERVAL	(SystemCoreClock/100000 - 1)
/* depending on the SystemFrequency and SystemAHBFrequency setting,
if SystemFrequency = 60Mhz, SystemAHBFrequency = 1/4 SystemAHBFrequency,
10mSec = 150.000-1 counts */

#define Null 0

uint32_t timer1_increments;

void (*callback)(void);
void timer32_register_callback( void (*cb) (void) );
void init_timer32(uint8_t timer_num, uint32_t timerInterval);
void enable_timer32(uint8_t timer_num);
void disable_timer32(uint8_t timer_num);
void reset_timer32(uint8_t timer_num);
void TIMER32_0_IRQHandler(void);
void TIMER32_1_IRQHandler(void);
void timer32_setMatch(uint8_t timer_num, uint32_t match_in_us);
void timer32_delay_us(uint32_t time_in_us);


#endif
#endif /* TIMER32_H_ */
