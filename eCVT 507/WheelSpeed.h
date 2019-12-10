//*****************************************************************************
/**	@file		WheelSpeed.h
 *	@brief		Header for a class that implements a hall effect sensor to
 *				measure wheel speed.
 *	@details	This class allows the user to implement a hall effect sensor to
 *				meausre wheel speed. It relies on the user to set up an
 *				interrupt service routine to call the calculate function on the
 *				rising or falling edge of the signal from a hall effect sensor
 *				measuring wheel speed.
 *
 *	@author		KC Egger, Rahul Goyal, Alexandros Petrakis
 *
 *  @date 2019-12-09 */
//*****************************************************************************

#ifndef WheelSpeed_h
#define WheelSpeed_h

#include <stdint.h>
#include "TC_Config.h"

/**	@brief		Header for a class that implements a hall effect sensor to
 *				measure wheel speed.
 *	@details	This class allows the user to implement a hall effect sensor to
 *				meausre wheel speed. It relies on the user to set up an
 *				interrupt service routine to call the calculate function on the
 *				rising or falling edge of the signal from a hall effect sensor
 *				measuring wheel speed.
 */
class WheelSpeed {

	public:
		// Constructor
		WheelSpeed(uint8_t triggers);

		// Methods
		void calc();
		float get();

	private:
		uint8_t triggers;
		
		volatile uint32_t prevTime;
		volatile uint32_t currTime;
};

#endif