/*
 *	WheelSpeed.cpp - Library for measuring wheel speed.
 *	Created by Rahul Goyal, July 1 2019.
 *	Released to Cal Poly Baja SAE. ;)
 */

#include "WheelSpeed.h"
#include <stdint.h>
#include "../Time/Time.h"

Time time;
const uint32_t TIMEOUT = 1000000;

// Constructor
WheelSpeed::WheelSpeed(uint8_t triggers) {
	// Initialize variables
	this->triggers = triggers;
	prevTime = time.micros();
	currTime = time.micros();
}

void WheelSpeed::calc() {
	prevTime = currTime;
	currTime = time.micros();
}

float WheelSpeed::get() {
	if (time.micros() - prevTime >= TIMEOUT) {
		return 0;
	}
	return (float)1000000 / ((currTime - prevTime) * triggers);		// Rotations per Second (RPS)
	// return (float)60000000 / ((currTime - prevTime) * triggers);	// Rotations per Minute (RPM)
}