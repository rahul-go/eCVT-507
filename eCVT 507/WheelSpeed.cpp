//*****************************************************************************
/**	@file		WheelSpeed.cpp
 *	@brief		Source code for a class that implements a hall effect sensor to
 *				measure wheel speed.
 *	@details	This class allows the user to implement a hall effect sensor to
 *				meausre wheel speed. It relies on the user to set up an
 *				interrupt service routine to call the calculate function on the
 *				rising or falling edge of the signal from a hall effect sensor
 *				measuring wheel speed.
 *
 *	@author		KC Egger, Rahul Goyal, Alexandros Petrakis
 *
 *  @date 2019-12-09 */
//*****************************************************************************

#include "WheelSpeed.h"
#include <stdint.h>
#include "TC_Config.h"

const uint32_t TIMEOUT = 1000000;

/** @brief		Constructor which creates and initializes a wheel speed object.
 *  @details	This constructor creates an wheel speed object with the given
 *				number of triggers. It saves the number of triggers and
 *				initializes the "previous" and "current" times.
 *  @param		The number of triggers per wheel revolution.
 */
WheelSpeed::WheelSpeed(uint8_t triggers) {
	// Initialize variables
	this->triggers = triggers;
	prevTime = micros();
	currTime = micros();
}

/** @brief		Update the current time and previous time to calculate the
 *				wheel speed.
 *  @details	This function stores the "current" time as the previous time
 *				and assign the current time to current time. These values can
 *				be used to calculate the wheel speed, but this calculation is
 *				left until the get() function is called to minimize the time
 *				spent in the interrupt service routing.
 */
void WheelSpeed::calc() {
	prevTime = currTime;
	currTime = micros();
}

/** @brief		Return the wheel speed in rotations per second.
 *  @details	This function calculates the wheel speed using the stored
 *				previous time and stored current time. The time between
 *				triggers is multipled by the number of triggers to calculate
 *				the time required for one revolution in microseconds. The
 *				constant 1E6 is divided by this time to get rotations per
 *				second.
 *  @param		The number of triggers per wheel revolution.
 *	@return		The wheel speed in rotations per second as a float.
 */
float WheelSpeed::get() {
	if (micros() - prevTime >= TIMEOUT) {
		return 0;
	}
	return (float)1000000 / ((currTime - prevTime) * triggers);		// Rotations per Second (RPS)
	// return (float)60000000 / ((currTime - prevTime) * triggers);	// Rotations per Minute (RPM)
}