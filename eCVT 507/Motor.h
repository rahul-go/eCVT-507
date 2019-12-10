//*****************************************************************************
/**	@file		Motor.h
 *	@brief		Header for a class that implements a motor.
 *	@details	This class allows the user to implement a motor. The motor will
 *				respond to a duty cycle between -100 and 100, with a duty cycle
 *				of 0 causing the motor to coast regardless of direction. Each
 *				motor object of this class can controlled independently.
 *
 *	@author		KC Egger, Rahul Goyal, Alexandros Petrakis
 *
 *  @date 2019-12-09 */
//*****************************************************************************

#ifndef Motor_h
#define Motor_h

#include <stdint.h>
#include "avr/io.h"
#include "Pin.h"


/**	@brief		Class that implements a motor.
 *	@details	This class allows the user to implement a motor. The motor will
 *				respond to a duty cycle between -100 and 100, with a duty cycle
 *				of 0 causing the motor to coast regardless of direction. Each
 *				motor object of this class can controlled independently.
 */
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