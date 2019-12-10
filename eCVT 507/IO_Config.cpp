//*****************************************************************************
/**	@file		IO_Config.cpp
 *	@brief		Source code for a library that implements the input/output
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

#include "IO_Config.h"
#include <avr/io.h>
#include "Pin.h"

/** @brief		Sets up the engine speed and wheel speed interrupt pins.
 *  @details	This function sets up the engine speed and wheel speed for
 *				interrupt functionality.
 */
void IO_Init() {

	/* ** INPUT/OUTPUT CONFIGURATION ** */
	// Engine Speed Setup
	ENGINE_SPEED_PIN.PORT->INTCTRL = (ENGINE_SPEED_PIN.PORT->INTCTRL & ~PORT_INT0LVL_gm) | PORT_INT0LVL_MED_gc;
	ENGINE_SPEED_PIN.PORT->INT0MASK = ENGINE_SPEED_PIN.PIN_BM;

	// Rear Wheel Speed Setup
	RWHEELS_SPEED_PIN.PORT->INTCTRL = (RWHEELS_SPEED_PIN.PORT->INTCTRL & ~PORT_INT1LVL_gm) | PORT_INT0LVL_MED_gc;
	RWHEELS_SPEED_PIN.PORT->INT1MASK = RWHEELS_SPEED_PIN.PIN_BM;

	// Primary Motor Setup
	/* Handled in Motor files. */

	// Primary Encoder Setup
	/* Handled in Encoder files. */

	// Secondary Motor Setup
	/* Handled in Motor files. */

	// Secondary Encoder Setup
	/* Handled in Encoder files. */

}