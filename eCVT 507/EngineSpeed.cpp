//*****************************************************************************
/**	@file		EngineSpeed.cpp
 *	@brief		Source code for a class that implements a hall effect sensor to
 *				measure engine speed.
 *	@details	This class allows the user to implement a hall effect sensor to
 *				meausre engine speed. It relies on the user to set up an
 *				interrupt service routine to call the calculate function on the
 *				rising or falling edge of the signal from a hall effect sensor
 *				measuring engine speed. The engine speed is similar to the
 *				wheel speed library but also averages the thermodynamic cycle
 *				of a four-stroke engine (that is, it averages every two
 *				revolutions) to reduce the noise of the output signal.
 *
 *	@author		KC Egger, Rahul Goyal, Alexandros Petrakis
 *
 *  @date 2019-12-09 */
//*****************************************************************************

#include "EngineSpeed.h"
#include <stdint.h>
#include "TC_Config.h"

const uint32_t TIMEOUT = 1000000;

/** @brief		Constructor which creates and initializes an engine speed
 *				object.
 *  @details	This constructor creates an wheel speed object with the given
 *				number of triggers. It saves the number of triggers and
 *				initializes the "previous" and "current" times.
 *  @param		triggers The number of triggers per revolution of the wheel.
 */
EngineSpeed::EngineSpeed(uint8_t triggers) {
	// Initialize variables
	this->triggers = triggers;
	for (uint8_t i = 0; i < triggers; i++) {
		prevTime[i] = micros();
	}
	currTime = micros();
}

/** @brief		Update the current time and previous time to calculate the
 *				engine speed.
 *  @details	This function stores the "current" time as the previous time
 *				and assign the current time to current time. These values can
 *				be used to calculate the wheel speed, but this calculation is
 *				left until the get() function is called to minimize the time
 *				spent in the interrupt service routing. The previous time is
 *				stored to the respective trigger position, then the position
 *				is incremented. If the position increases to a number greater
 *				than the number of triggers, the position is reset to zero.
 */
void EngineSpeed::calc() {
	prevTime[pos] = currTime;
	currTime = micros();
	// Increment position
	pos++;
	if (pos >= triggers) {
		pos = 0;
	}
}

/** @brief		Return the engine speed in rotations per second.
 *  @details	This function calculates the wheel speed using the stored
 *				previous time and stored current time. The time between
 *				triggers is multipled by the number of triggers to calculate
 *				the time required for one revolution in microseconds. The
 *				constant 1E6 is divided by this time to get rotations per
 *				second. The previous time retrieved is from the current
 *				trigger position.
 *	@return		The wheel speed in rotations per second as a float.
 */
uint16_t EngineSpeed::get() {
	if (micros() - prevTime[pos] >= TIMEOUT) {
		return 0;
	}
	// return 2000000 / (currTime - prevTime[pos]);	// Rotations per Second (RPS)
	return 120000000 / (currTime - prevTime[pos]);	// Rotations per Minute (RPM)
}