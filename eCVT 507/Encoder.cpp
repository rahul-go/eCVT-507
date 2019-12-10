//*****************************************************************************
/**	@file		Encoder.cpp
 *	@brief		Source code for a class that implements an encoder.
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

#include "Encoder.h"
#include <stdint.h>
#include "IO_Config.h"
#include "TC_Config.h"
#include "Pin.h"

/** @brief		Constructor which creates and initializes an encoder object.
 *  @details	This constructor creates an encoder object with the given pins.
 *				It saves the pins and sets the pins for input. It sets QDPH0
 *				and QDPH1 sening level. It sets up the event system depending
 *				on the encoder. Future updates will allow for the the timer
 *				and event channel to be chosen independently by the user via
 *				parameters in the constructor.
 *  @param		ENC_A The first signal pin of the encoder.
 *	@param		ENC_B The second signal pin of the encoder.
 */
Encoder::Encoder(Pin ENC_A, Pin ENC_B) {

	this->ENC_A = ENC_A;
	this->ENC_B = ENC_B;

	// Port Setup
	ENC_A.PORT->DIRCLR = (ENC_A.PIN_BM | ENC_B.PIN_BM);

	/* Set QDPH0 and QDPH1 sensing level. */
	PORTCFG.MPCMASK |= (ENC_A.PIN_BM);
	PORTCFG.MPCMASK |= (ENC_B.PIN_BM);
	ENC_A.PORT->PIN0CTRL = (ENC_A.PORT->PIN0CTRL & ~PORT_ISC_gm) | PORT_ISC_LEVEL_gc;

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

/** @brief		Return the encoder position.
 *  @details	This function retrieves the timer count and returns it as an
 *				unsigned 16-bit number representing the encoder position.
 *  @return		The encoder position in ticks as an unsigned 16-bit number.
 */
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

/** @brief		Zero the encoder position.
 *  @details	This function sets the timer count representing the encoder
 *				position to zero.
 */
void Encoder::zero() {
	// Primary Encoder
	if (ENC_A.PIN_BM == P_ENC_A.PIN_BM) {
		TCD0.CNT = 0;
	}
	// Secondary Encoder
	if (ENC_A.PIN_BM == S_ENC_A.PIN_BM) {
		TCD1.CNT = 0;
	}
}