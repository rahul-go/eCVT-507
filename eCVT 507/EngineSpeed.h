//*****************************************************************************
/**	@file		EngineSpeed.h
 *	@brief		Header for a class that implements a hall effect sensor to
 *				measure engine speed.
 *	@details	This class allows the user to implement a hall effect sensor to
 *				meausre engine speed. It relies on the user to set up an
 *				interrupt service routine to call the calculate function on the
 *				rising or falling edge of the signal from a hall effect sensor
 *				measuring engine speed. The engine speed is similar to the
 *				wheel speed library but also averages the thermodynamic cycle
 *				of a four-stroke engine (that is, it averages every two
 *				revolutions) to reduce the noise of the output signal.
 *
 *	@author		KC Egger, Rahul Goyal, Alexandros Petrakis
 *
 *  @date 2019-12-09 */
//*****************************************************************************

#ifndef EngineSpeed_h
#define EngineSpeed_h

#include <stdint.h>
#include "TC_Config.h"

/**	@brief		Header for a class that implements a hall effect sensor to
 *				measure engine speed.
 *	@details	This class allows the user to implement a hall effect sensor to
 *				meausre engine speed. It relies on the user to set up an
 *				interrupt service routine to call the calculate function on the
 *				rising or falling edge of the signal from a hall effect sensor
 *				measuring engine speed. The engine speed is similar to the
 *				wheel speed library but also averages the thermodynamic cycle
 *				of a four-stroke engine (that is, it averages every two
 *				revolutions) to reduce the noise of the output signal.
 */
class EngineSpeed {

	public:
		// Constructor
		EngineSpeed(uint8_t triggers);

		// Methods
		void calc();
		uint16_t get();

	private:
		uint8_t triggers;
		uint8_t pos = 0;

		volatile uint32_t prevTime[100];
		volatile uint32_t currTime;
};

#endif