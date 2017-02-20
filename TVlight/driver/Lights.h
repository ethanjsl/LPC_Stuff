/*
 * Lights.h
 *
 *  Created on: 15 Feb 2017
 *      Author: ethan
 */

#ifndef LIGHTS_H_
#define LIGHTS_H_

uint32_t LightStatus;

void Lights_init();
void LightsOn();
void LightsOff();

void PIOINT3_IRQHandler(void);

#endif /* LIGHTS_H_ */
