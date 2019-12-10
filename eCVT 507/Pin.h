//*****************************************************************************
/**	@file		Pin.h
 *	@brief		Header for a struct that implements a pin.
 *	@details	This struct allows the user to implement a pin containing
 *				information about the pin's port and number.
 *
 *	@author		KC Egger, Rahul Goyal, Alexandros Petrakis
 *
 *  @date 2019-12-09 */
//*****************************************************************************

#ifndef Pin_h
#define Pin_h

#include <avr/io.h>

struct Pin {
	PORT_t *PORT;
	uint8_t PIN_BM;
};

#endif