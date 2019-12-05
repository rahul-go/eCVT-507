/*
 *	IOConfig.h - Library for input/output configuration.
 *	Created by KC Egger and Rahul Goyal, November 1, 2019.
 *	Released to Cal Poly Baja SAE. ;)
 */

#include "IO_Config.h"
#include <avr/io.h>
#include "Pin.h"

void IO_Init() {

	/* ** INPUT/OUTPUT CONFIGURATION ** */
	// Engine Speed Setup
	ENGINE_SPEED_PIN.PORT.INTCTRL = (ENGINE_SPEED_PIN.PORT.INTCTRL & ~PORT_INT0LVL_gm) | PORT_INT0LVL_MED_gc;
	ENGINE_SPEED_PIN.PORT.INT0MASK = ENGINE_SPEED_PIN.PIN_BM;

	// Rear Wheel Speed Setup
	RWHEELS_SPEED_PIN.PORT.INTCTRL = (RWHEELS_SPEED_PIN.PORT.INTCTRL & ~PORT_INT1LVL_gm) | PORT_INT0LVL_MED_gc;
	RWHEELS_SPEED_PIN.PORT.INT1MASK = RWHEELS_SPEED_PIN.PIN_BM;

	// Primary Motor Setup
	/* Handled in Motor files. */

	// Primary Encoder Setup
	/* Handled in Encoder files. */

	// Secondary Motor Setup
	/* Handled in Motor files. */

	// Secondary Encoder Setup
	/* Handled in Encoder files. */

}