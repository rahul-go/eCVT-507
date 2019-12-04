/*
 *	Motor.cpp - Library for motors (adapted from DualVNH5019MotorShield library).
 *	Created by Rahul Goyal, July 1 2019.
 *	Released to Cal Poly Baja SAE. ;)
 */

// #include <Arduino.h>
#include <stdint.h>
#include "Motor.h"
#include "../Pin.h"

// Constructor
Motor::Motor(Pin INA, Pin INB, Pin PWM) {
	this->INA = INA;
	this->INB = INB;
	this->PWM = PWM;
}

void Motor::init() {
	// pinMode(INA, OUTPUT);
	// pinMode(INB, OUTPUT);
	// pinMode(PWM, OUTPUT);
	INA.PORT.DIR |= INA.PIN_BM;
	INB.PORT.DIR |= INB.PIN_BM;
	PWM.PORT.DIR |= PWM.PIN_BM;
}

void Motor::setDutyCycle(int8_t dutyCycle) {
	// Normalize duty cycle, determine direction
	if (dutyCycle < 0) {
		dutyCycle *= -1;
		negative = true;
	} else {
		negative = false;
	}

	// Saturate duty cycle
	if (dutyCycle > 100) {
		dutyCycle = 100;
	}

	// Write PWM, scale 100 to 255
	analogWrite(PWM, dutyCycle * 255 / 100);

	// Coast (indpendent of direction)
	if (dutyCycle == 0) {
		// digitalWrite(INA, LOW);
		// digitalWrite(INB, LOW);
		INA.PORT.OUTCLR = INA.PIN_BM;
		INB.PORT.OUTCLR = INB.PIN_BM;
	// Negative
	} else if (negative) {
		// digitalWrite(INA, LOW);
		// digitalWrite(INB, HIGH);
		INA.PORT.OUTCLR = INA.PIN_BM;
		INB.PORT.OUTSET = INB.PIN_BM;
	// Positive
	} else {
		// digitalWrite(INA, HIGH);
		// digitalWrite(INB, LOW);
		INA.PORT.OUTSET = INA.PIN_BM;
		INB.PORT.OUTCLR = INB.PIN_BM;
	}
}