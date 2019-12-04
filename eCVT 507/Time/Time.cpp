/*
 *	Time.cpp - Library for time.
 *	Created by Rahul Goyal, July 1 2019.
 *	Released to Cal Poly Baja SAE. ;)
 */

#include "Time.h"
#include <avr/io.h>
#include <stdint.h>

// Constructor
Time::Time() {
	
	/* Use peripheral clock prescaler 4 as input for event channel 0. */
	EVSYS.CH0MUX = EVSYS_CHMUX_PRESCALER_16_gc;
	/* Use event channel 0 as clock source for TCC0. */
	TCC0.CTRLA = (TCC0.CTRLA & ~TC0_CLKSEL_gm) | TC_CLKSEL_EVCH0_gc;

	/* Use TCC0 overflow as input for event channel 1. */
	EVSYS.CH1MUX = EVSYS_CHMUX_TCC0_OVF_gc;	
	/* Use event channel 1 as clock source for TCC1. */
	TCC1.CTRLA = (TCC1.CTRLA & ~TC1_CLKSEL_gm) | TC_CLKSEL_EVCH1_gc;

}

uint32_t Time::micros() {
	return ((uint32_t)TCC1.CNT << 16) | TCC0.CNT;
}