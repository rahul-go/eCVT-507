//*****************************************************************************
/**	@file		TC_Config.cpp
 *	@brief		Source code for a library that implements the timer/counter
 *				configuration.
 *	@details	This library allows the user to configure the timers/counters
 *				in one place. System time is retrieved using the micros()
 *				function, meant to simulate the function on the Arduino but
 *				with 1us precision. PWM duty cycle is written on Timer E0 using
 *				the analogWrite() function, meant to simulate the function on
 *				the Arduino. Future updates will allow for the timer and event
 *				channel to be chosen independently by the user via parameters
 *				in the constructor.
 *
 *	@author		KC Egger, Rahul Goyal, Alexandros Petrakis
 *
 *  @date 2019-12-09 */
//*****************************************************************************

#include "TC_Config.h"
#include <avr/io.h>
#include <stdint.h>
#include "IO_Config.h"
#include "Pin.h"

/** @brief		Sets up the timer configuration.
 *  @details	This function sets up the system clock timer, timer interrupt,
 *				encoder counters, and PWM output.
 */
void TC_Init(){
	// micros() Initialization
	/* Use peripheral clock prescaler 16 as input for event channel 0. */
	EVSYS_CH0MUX = EVSYS_CHMUX_PRESCALER_16_gc;
	/* Use event channel 0 as clock source for TCC0. */
	TCC0_CTRLA = (TCC0_CTRLA & ~TC0_CLKSEL_gm) | TC_CLKSEL_EVCH0_gc;
	/* Use TCC0 overflow as input for event channel 1. */
	EVSYS_CH1MUX = EVSYS_CHMUX_TCC0_OVF_gc;	
	/* Use event channel 1 as clock source for TCC1. */
	TCC1_CTRLA = (TCC1_CTRLA & ~TC1_CLKSEL_gm) | TC_CLKSEL_EVCH1_gc;

	// // Timer Interrupt Initialization (old implementation)
	// /* Initialize period register of the timer/counter. */
	// TCD0.PER = 0x4E20;
	// /* Set levels for overflow interrupt. */
	// TCD0.INTCTRLA = TC_OVFINTLVL_MED_gc;
	// /* Start the timer/counter and enable interrupts. */
	// TCD0.CTRLA = TC_CLKSEL_DIV8_gc;

	// Timer Interrupt Initialization
	/* Enable Compare channel A. */
	TCC0_CTRLB |= TC0_CCAEN_bm;
	/* Set level for compare channel interrupt. */
	TCC0_INTCTRLB = TC_CCAINTLVL_HI_gc;

	// Encoder Initialization
	/* Configure TC as a quadrature counter. */
	TCD0_CTRLD = (uint8_t) TC_EVACT_QDEC_gc | EVSYS_CH2MUX;
	// TCD0.PER = (3584 * 4) - 1;
	TCD0_CTRLA = TC_CLKSEL_DIV1_gc;	 
	/* Configure TC as a quadrature counter. */
	TCD1_CTRLD = (uint8_t) TC_EVACT_QDEC_gc | EVSYS_CH3MUX;
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

/** @brief		Returns the system time.
 *  @details	This function concatenates the values of two 16-bit timers to
 *				return the system time as a 32-bit timer.
 *	@return		The system time in microseconds as an unsigned 32-bit number.
 */
uint32_t micros() {
	return ((uint32_t)TCC1_CNT << 16) | TCC0_CNT;
}

/** @brief		Returns the system time.
 *  @details	This function concatenates the values of two 16-bit timers to
 *				return the system time as a 32-bit timer.
 *	@param		The pin to write the PWM duty cycle to.
 *	@param		The duty cycle to write, between -100 and 100.
 */
void analogWrite(Pin pin, uint8_t dutyCycle) {
	// Primary Motor
	if (pin.PIN_BM == P_MOT_PWM.PIN_BM) {
		TCE0_CCC = ((uint16_t)dutyCycle) * 200;
	}
	// Secondary Motor
	if (pin.PIN_BM == S_MOT_PWM.PIN_BM) {
		TCE0_CCD = ((uint16_t)dutyCycle) * 200;
	}
}
