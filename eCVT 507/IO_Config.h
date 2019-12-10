//*****************************************************************************
/**	@file		IO_Config.h
 *	@brief		Header for a library that implements the input/output
 *				configuration.
 *	@details	This library allows the user to configure the inputs/outputs
 *				in one place. The library assigns ports and pin numbers via Pin
 *				objects to each input/output. Additionally, the library sets up
 *				interrupts for the engine speed and rear wheel speed hall
 *				effect sensors.
 *
 *	@author		KC Egger, Rahul Goyal, Alexandros Petrakis
 *
 *  @date 2019-12-09 */
//*****************************************************************************

#ifndef IO_Config_h
#define IO_Config_h

#include <avr/io.h>
#include "Pin.h"

/* ** WIRING ** */

// Hall Effect Sensors
static Pin ENGINE_SPEED_PIN  = {&PORTE, PIN0_bm};
static Pin RWHEELS_SPEED_PIN = {&PORTE, PIN1_bm};

// Primary
const Pin P_MOT_INA = {&PORTA, PIN0_bm};
const Pin P_MOT_INB = {&PORTA, PIN1_bm};
const Pin P_MOT_PWM = {&PORTE, PIN2_bm};
const Pin P_ENC_A = {&PORTA, PIN4_bm};
const Pin P_ENC_B = {&PORTA, PIN5_bm};

// Secondary
const Pin S_MOT_INA = {&PORTA, PIN2_bm};
const Pin S_MOT_INB = {&PORTA, PIN3_bm};
const Pin S_MOT_PWM = {&PORTE, PIN3_bm};
const Pin S_ENC_A = {&PORTA, PIN6_bm};
const Pin S_ENC_B = {&PORTA, PIN7_bm};

void IO_Init();

#endif