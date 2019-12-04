/*
 *	EngineSpeed.cpp - Library for measuring engine speed.
 *	Created by Rahul Goyal, July 1 2019.
 *	Released to Cal Poly Baja SAE. ;)
 */

#include "EngineSpeed.h"
#include <stdint.h>
#include "../Time/Time.h"

Time time;
const uint32_t TIMEOUT = 1000000;

// Constructor
EngineSpeed::EngineSpeed(uint8_t triggers) {
	// Initialize variables
	this->triggers = triggers;
	for (uint8_t i = 0; i < triggers; i++) {
		prevTime[i] = time.micros();
	}
	currTime = time.micros();
}

void EngineSpeed::calc() {
	prevTime[pos] = currTime;
	currTime = time.micros();
	// Increment position
	pos++;
	if (pos >= triggers) {
		pos = 0;
	}
}

uint16_t EngineSpeed::get() {
	if (time.micros() - prevTime[pos] >= TIMEOUT) {
		return 0;
	}
	// return 2000000 / (currTime - prevTime[pos]);	// Rotations per Second (RPS)
	return 120000000 / (currTime - prevTime[pos]);	// Rotations per Minute (RPM)
}