/*
 *	IOConfig.h - Library header for input/output configuration.
 *	Created by KC Egger and Rahul Goyal, November 1, 2019.
 *	Released to Cal Poly Baja SAE. ;)
 */

#ifndef IO_Config_h
#define IO_Config_h

#include <avr/io.h>
#include "Pin.h"

/* ** WIRING ** */

// Hall Effect Sensors
static Pin ENGINE_SPEED_PIN  = {PORTE, PIN0_bm};
static Pin RWHEELS_SPEED_PIN = {PORTE, PIN1_bm};

// Primary
const Pin P_MOT_INA = {PORTA, PIN0_bm};
const Pin P_MOT_INB = {PORTA, PIN1_bm};
const Pin P_MOT_PWM = {PORTE, PIN2_bm};
const Pin P_ENC_A = {PORTA, PIN4_bm};
const Pin P_ENC_B = {PORTA, PIN5_bm};

// Secondary
const Pin S_MOT_INA = {PORTA, PIN2_bm};
const Pin S_MOT_INB = {PORTA, PIN3_bm};
const Pin S_MOT_PWM = {PORTE, PIN3_bm};
const Pin S_ENC_A = {PORTA, PIN6_bm};
const Pin S_ENC_B = {PORTA, PIN7_bm};

void IO_Init();

#endif