/*
 *	Encoder.cpp - Library for encoder.
 *	Created by Rahul Goyal, July 1 2019.
 *	Released to Cal Poly Baja SAE. ;)
 */

#include "Encoder.h"
#include <stdint.h>
#include "IO_Config.h"
#include "TC_Config.h"
#include "Pin.h"

// Constructor
Encoder::Encoder(Pin ENC_A, Pin ENC_B) {

	this->ENC_A = ENC_A;
	this->ENC_B = ENC_B;

	// Port Setup
	ENC_A.PORT->DIRCLR = (ENC_A.PIN_BM | ENC_B.PIN_BM);

	/* Set QDPH0 and QDPH1 sensing level. */
	PORTCFG.MPCMASK |= (ENC_A.PIN_BM);
	PORTCFG.MPCMASK |= (ENC_B.PIN_BM);
	ENC_A.PORT->PIN0CTRL = (ENC_A.PORT->PIN0CTRL & ~PORT_ISC_gm) | PORT_ISC_LEVEL_gc
	                  | (false ? PORT_INVEN_bm : 0);

	// Event System Setup
    uint8_t pin = 0;
    uint8_t pin_bm = ENC_A.PIN_BM;
    while (pin_bm) {
    	pin_bm >>= 1;
    	pin++;
    }
	// Primary Encoder
	if (ENC_A.PIN_BM == P_ENC_A.PIN_BM) {
		EVSYS.CH2MUX = pin;
		EVSYS.CH2CTRL = EVSYS_QDEN_bm | EVSYS_DIGFILT_2SAMPLES_gc;
	}
	// Secondary Encoder
	if (ENC_A.PIN_BM == S_ENC_A.PIN_BM) {
		EVSYS.CH3MUX = pin;
		EVSYS.CH3CTRL = EVSYS_QDEN_bm | EVSYS_DIGFILT_2SAMPLES_gc;
	}
	
	// TC Setup
	/* Handled in TC_Config files. */

}

uint16_t Encoder::read() {
	// Primary Encoder
	if (ENC_A.PIN_BM == P_ENC_A.PIN_BM) {
		return TCD0.CNT;
	}
	// Secondary Encoder
	if (ENC_A.PIN_BM == S_ENC_A.PIN_BM) {
		return TCD1.CNT;
	}
}

void Encoder::zero() {

}