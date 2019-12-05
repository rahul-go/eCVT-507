/*
 *	Motor.h - Library header for motors (adapted from DualVNH5019MotorShield library).
 *	Created by Rahul Goyal, July 1 2019.
 *	Released to Cal Poly Baja SAE. ;)
 */

#ifndef Motor_h
#define Motor_h

#include <stdint.h>
#include "avr/io.h"
#include "Pin.h"

class Motor {

	public:
		// Constructor
		Motor(Pin INA, Pin INB, Pin PWM);

		// Methods
		void init();
		void setDutyCycle(int8_t dutyCycle);

	private:
		Pin INA;
		Pin INB;
		Pin PWM;
		bool negative;
};

#endif