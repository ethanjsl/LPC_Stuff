/**********************************************************************************
 * Filename:		PWM.h
 * Author:			Ethan Lyons
 * Creation Date:	22.02.1993
 * Description:		Header file for PWM.c
 */
#ifndef PWM_H_
#define PWM_H_

void PWM_init(void);
void PWM_start(void);
void PWM_stop(void);
void TIMER32_0_IRQHandler(void);



#endif /* PWM_H_ */
