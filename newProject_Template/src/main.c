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

/* Main Program */

int main (void){
	//GPIO
	GPIOInit();
  
	//Other peripherals
	
	
	while (1){ /* Loop forever */
	
		
	}
}
