/*
 *	Encoder.h - Library header for encoder.
 *	Created by Rahul Goyal, July 1, 2019.
 *	Released to Cal Poly Baja SAE. ;)
 */

#ifndef Encoder_h
#define Encoder_h

#include <stdint.h>

class Encoder {

	public:
		// Constructor
		Encoder(Pin ENC_A, Pin ENC_B);

		// Methods
		uint16_t read();
		void zero();

	private:

};

#endif