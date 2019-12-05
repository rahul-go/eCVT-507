/*
 *	TCConfig.h - Library header for timer/counter configuration.
 *	Created by KC Egger and Rahul Goyal, November 1, 2019.
 *	Released to Cal Poly Baja SAE. ;)
 */

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