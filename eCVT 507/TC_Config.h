//*****************************************************************************
/**	@file		TC_Config.h
 *	@brief		Source code for a header that implements the timer/counter
 *				configuration.
 *	@details	This library allows the user to configure the timers/counters
 *				in one place. System time is retrieved using the micros()
 *				function, meant to simulate the function on the Arduino but
 *				with 1us precision. PWM duty cycle is written on Timer E0 using
 *				the analogWrite() function, meant to simulate the function on
 *				the Arduino. Future updates will allow for the timer and event
 *				channel to be chosen independently by the user via parameters
 *				in the constructor.
 *
 *	@author		KC Egger, Rahul Goyal, Alexandros Petrakis
 *
 *  @date 2019-12-09 */
//*****************************************************************************

#ifndef TC_Config_h
#define TC_Config_h

#include <avr/io.h>
#include <stdint.h>
#include "IO_Config.h"
#include "Pin.h"

void TC_Init();
uint32_t micros();
void analogWrite(Pin pin, uint8_t value);

#endif