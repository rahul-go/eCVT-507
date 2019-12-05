/*
 *	TCConfig.cpp - Library for timer/counter configuration.
 *	Created by KC Egger and Rahul Goyal, November 1, 2019.
 *	Released to Cal Poly Baja SAE. ;)
 */

#include "TC_Config.h"
#include <avr/io.h>
#include <stdint.h>
#include "IO_Config.h"
#include "Pin.h"

void TC_Init(){
	// micros() Initialization
	/* Use peripheral clock prescaler 16 as input for event channel 0. */
	EVSYS.CH0MUX = EVSYS_CHMUX_PRESCALER_16_gc;
	/* Use event channel 0 as clock source for TCC0. */
	TCC0.CTRLA = (TCC0.CTRLA & ~TC0_CLKSEL_gm) | TC_CLKSEL_EVCH0_gc;
	/* Use TCC0 overflow as input for event channel 1. */
	EVSYS.CH1MUX = EVSYS_CHMUX_TCC0_OVF_gc;	
	/* Use event channel 1 as clock source for TCC1. */
	TCC1.CTRLA = (TCC1.CTRLA & ~TC1_CLKSEL_gm) | TC_CLKSEL_EVCH1_gc;

	// // Timer Interrupt Initialization (old implementation)
	// /* Initialize period register of the timer/counter. */
	// TCD0.PER = 0x4E20;
	// /* Set levels for overflow interrupt. */
	// TCD0.INTCTRLA = TC_OVFINTLVL_MED_gc;
	// /* Start the timer/counter and enable interrupts. */
	// TCD0.CTRLA = TC_CLKSEL_DIV8_gc;

	// Timer Interrupt Initialization
	/* Enable Compare channel A. */
	TCC0.CTRLB |= TC0_CCAEN_bm;
	/* Set level for compare channel interrupt. */
	TCC0.INTCTRLB = TC_CCAINTLVL_MED_gc;

	// Encoder Initialization
	/* Configure TC as a quadrature counter. */
	TCD0_CTRLD = (uint8_t) TC_EVACT_QDEC_gc | EVSYS.CH2MUX;
	// TCD0.PER = (3584 * 4) - 1;
	TCD0_CTRLA = TC_CLKSEL_DIV1_gc;	 
	/* Configure TC as a quadrature counter. */
	TCD1_CTRLD = (uint8_t) TC_EVACT_QDEC_gc | EVSYS.CH3MUX;
	// TCD1.PER = (3584 * 4) - 1;
	TCD1_CTRLA = TC_CLKSEL_DIV1_gc;

	// PWM Output Initialization
	/* Set the TC period. */
	TCE0_PER = 20000;
	/* Configure the TC for single slope mode. */
	TCE0_CTRLB |= TC_WGMODE_SINGLESLOPE_gc;
	/* Enable Compare channel C and D. */
	TCE0_CTRLB |= TC0_CCCEN_bm;
	TCE0_CTRLB |= TC0_CCDEN_bm;
	/* Start timer by selecting a clock source. */
	TCE0_CTRLA = (TCE0_CTRLA & ~TC0_CLKSEL_gm) | TC_CLKSEL_DIV1_gc;
}

uint32_t micros() {
	return ((uint32_t)TCC1.CNT << 16) | TCC0.CNT;
}

void analogWrite(Pin pin, uint8_t dutyCycle) {
	// Primary Motor
	if (pin.PIN_BM == P_MOT_PWM.PIN_BM) {
		TCE0_CCC = 12000;
	}
	// Secondary Motor
	if (pin.PIN_BM == S_MOT_PWM.PIN_BM) {
		TCE0_CCD = 12000;
	}
}

