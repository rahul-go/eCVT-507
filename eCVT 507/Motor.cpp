//*****************************************************************************
/**	@file		Motor.cpp
 *	@brief		Source code for a class that implements a motor.
 *	@details	This class allows the user to implement a motor. The motor will
 *				respond to a duty cycle between -100 and 100, with a duty cycle
 *				of 0 causing the motor to coast regardless of direction. Each
 *				motor object of this class can controlled independently.
 *
 *	@author		KC Egger, Rahul Goyal, Alexandros Petrakis
 *
 *  @date 2019-12-09 */
//*****************************************************************************

#include "Motor.h"
#include "avr/io.h"
#include <stdint.h>
#include "TC_Config.h"
#include "Pin.h"

/** @brief		Constructor which creates and initializes a motor object.
 *  @details	This constructor creates a motor object with the given pins.
 *  @param		INA The first direction pin of the motor driver.
 *	@param		INB The second direction pin of the motor driver.
 *	@param		PWM The duty cycle pin of the motor driver.
 */
Motor::Motor(Pin INA, Pin INB, Pin PWM) {
	this->INA = INA;
	this->INB = INB;
	this->PWM = PWM;
}

/** @brief		Configures the pins.
 *  @details	This function configures the direction pins (that is, INA and
 *				INB) and duty cycle pin (that is, PWM) as output pins.
 */
void Motor::init() {
	INA.PORT->DIRSET = INA.PIN_BM | INB.PIN_BM;
	PWM.PORT->DIRSET = PWM.PIN_BM;
}

/** @brief		Sets the duty cycle.
 *  @details	This function takes a duty cycle between -100 and 100 to write
 *				as a PWM signal to the motor driver. It automatically writes to
 *				the direction pins depending on the sign of the duty cycle and
 *				scales the absolute value of the provided duty cycle to the PWM
 *				pin.
 *  @param		dutyCycle the duty cycle the motor is set to 
 */
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
	analogWrite(PWM, dutyCycle);

	// Coast (indpendent of direction)
	if (dutyCycle == 0) {
		INA.PORT->OUTCLR = INA.PIN_BM;
		INB.PORT->OUTCLR = INB.PIN_BM;
	// Negative
	} else if (negative) {
		INA.PORT->OUTCLR = INA.PIN_BM;
		INB.PORT->OUTSET = INB.PIN_BM;
	// Positive
	} else {
		INA.PORT->OUTSET = INA.PIN_BM;
		INB.PORT->OUTCLR = INB.PIN_BM;
	}
}