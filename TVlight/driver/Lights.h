/**********************************************************************************
 * Filename:		Lights.h
 * Author:			Ethan Lyons
 * Creation Date:	21.02.1993
 * Description:		Header file for Lights.c
 */

#ifndef LIGHTS_H_
#define LIGHTS_H_

void Lights_init();
void LightsOn(uint32_t level);
void LightsOff();
void LightsSetLevel(uint32_t level);
uint32_t LightsGetLevel();
uint32_t LightsGetStatus();


#endif /* LIGHTS_H_ */
