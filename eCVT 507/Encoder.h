//*****************************************************************************
/**	@file		Encoder.h
 *	@brief		Header for a class that implements an encoder.
 *	@details	This class allows the user to implement an encoder on either
 *				Timer D0, Event Channel 2 or Timer D1, Event Channel 3. Future
 *				updates will allow for the timer and event channel to be chosen
 *				independently by the user via parameters in the constructor.
 *				Each encoder object of this class can read from and written to
 *				independently.
 *
 *	@author		KC Egger, Rahul Goyal, Alexandros Petrakis
 *
 *  @date 2019-12-09 */
//*****************************************************************************

#ifndef Encoder_h
#define Encoder_h

#include <stdint.h>
#include "Pin.h"

class Encoder {

	public:
		// Constructor
		Encoder(Pin ENC_A, Pin ENC_B);

		// Methods
		uint16_t read();
		void zero();

	private:
		/**	User input of the first encoder pin.
	 	*	@param that_clod The first encoder pin.
	 	*/
		Pin ENC_A;
		/**	User input of the second encoder pin.
	 	*	@param that_clod The second encoder pin.
	 	*/
		Pin ENC_B;

};

#endif