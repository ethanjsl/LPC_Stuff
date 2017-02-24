/**********************************************************************************
 * Filename:		localInput.h
 * Author:			Ethan Lyons
 * Creation Date:	21.02.1993
 * Description:		Header file for localInput.c
 */
#ifndef LOCALINPUT_H_
#define LOCALINPUT_H_

#define PORT0	0
#define PORT1	1
#define PORT2	2
#define PORT3	3
static LPC_GPIO_TypeDef (* const LPC_GPIO[4])={ LPC_GPIO0, LPC_GPIO1, LPC_GPIO2, LPC_GPIO3 };
void localInput_init(void);
void PIOINT3_IRQHandler(void);
#endif /* LOCALINPUT_H_ */
