/*
 * eCVT.ino - Main code to control eCVT.
 * Created by Rahul Goyal, July 1, 2019.
 * Released to Cal Poly Baja SAE. ;)
 */

// #define DEBUG 1

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "IO_Config.h"
#include "TC_Config.h"
#include "Pin.h"

#include "PIDController.h"
#include "Motor.h"
#include "Encoder.h"
#include "EngineSpeed.h"
#include "WheelSpeed.h"



/* ** SYSTEM ** */
const uint16_t ENGAGE_SPEED = 2800;
const uint16_t SHIFT_SPEED  = 3400;

const uint16_t SHEAVE_OFFSET = 0;

// PID Controllers
PIDController ePID(1, 1, 0);
PIDController pPID(0.01, 0, 0);
PIDController sPID(0.01, 0, 0);

// Hall Effect Sensors
EngineSpeed engineSpeed(8);
WheelSpeed rWheelsSpeed(8);

// Motors
Motor pMot(P_MOT_INA, P_MOT_INB, P_MOT_PWM);
Motor sMot(S_MOT_INA, S_MOT_INB, S_MOT_PWM);

// Encoders
Encoder pEnc(P_ENC_A, P_ENC_B);
Encoder sEnc(S_ENC_A, S_ENC_B);

// Calibration
// const uint16_t CALIBRATION_DELAY = 1000;	// Milliseconds (ms)
// uint32_t pCalTime, sCalTime;				// Milliseconds (ms)
const uint32_t CALIBRATION_DELAY = 1000000;	// Microseconds (us)
uint32_t pCalTime, sCalTime;				// Microseconds (us)



/* ** FINITE STATE MACHINE ** */

// Timer
const uint16_t CONTROLLER_SPEED = 10000;	// Microseconds (us)

// Inter-Communication Variables
bool run;
bool eCalc, pCalc, sCalc;
uint16_t pTicks, sTicks;

// Initialize Task States
uint8_t eState = 0;
uint8_t pState = 0;
uint8_t sState = 0;



/* **LOOKUP TABLES** */

uint16_t pRatioToTicks(float ratio) {
	// 1% ratio increments
	static const uint16_t pLookup[] = {15919,15563,15217,14878,14548,14226,13913,13607,13308,13017,12734,12457,12188,11925,11669,11419,11176,10938,10707,10481,10260,10045,9835,9631,9431,9236,9045,8859,8677,8500,8326,8157,7991,7829,7671,7516,7365,7217,7072,6930,6791,6655,6522,6392,6265,6140,6017,5897,5780,5665,5552,5441,5332,5226,5121,5019,4918,4820,4723,4628,4534,4443,4353,4264,4177,4092,4008,3925,3844,3765,3686,3609,3534,3459,3386,3314,3243,3173,3104,3037,2970,2905,2840,2777,2714,2653,2592,2532,2473,2415,2358,2302,2246,2191,2137,2084,2032,1980,1929,1879,1829};
	if (ratio < 0) { return pLookup[0]; } else if (ratio > 100) { return pLookup[100]; }
	return pLookup[(uint8_t)ratio];
}

uint16_t sRatioToTicks(float ratio) {
	// 1% ratio increments
	static const uint16_t sLookup[] = {0,386,756,1111,1452,1780,2096,2399,2690,2970,3240,3500,3751,3992,4225,4449,4665,4874,5076,5271,5459,5641,5818,5988,6153,6313,6467,6617,6763,6904,7040,7173,7302,7427,7548,7666,7781,7893,8001,8107,8210,8310,8407,8502,8594,8685,8773,8858,8942,9023,9103,9181,9257,9331,9403,9474,9543,9611,9677,9742,9805,9867,9928,9987,10045,10102,10157,10212,10266,10318,10369,10420,10469,10517,10565,10612,10657,10702,10746,10789,10832,10874,10915,10955,10994,11033,11071,11109,11146,11182,11218,11253,11287,11321,11354,11387,11419,11451,11483,11513,11544};
	if (ratio < 0) { return sLookup[0]; } else if (ratio > 100) { return sLookup[100]; }
	return sLookup[(uint8_t)ratio];
}



/* **INTERRUPT SERVICE ROUTINES** */

ISR(PORTE_INT0_vect) { engineSpeed.calc(); }
ISR(PORTE_INT1_vect) { rWheelsSpeed.calc(); }
	
ISR(TCE0_CCA_vect) {
	eCalc = true;
	pCalc = true;
	sCalc = true;
	TCC0.CCA += CONTROLLER_SPEED;
}



/* **TASKS** */

void eCVT() {
	// Debugging
	//#ifdef DEBUG
	//Serial.print("eState: ");
	//Serial.println(eState);
	//#endif

	switch (eState) {

		// INITIALIZE
		case 0:

			// PID Controller Setup
			ePID.setSetpoint(SHIFT_SPEED);
			ePID.setLoSat(0);
			ePID.setHiSat(100);
			ePID.reset();

			// Run
			run = true;

			// State Changes
			eState = 1;
			return;

		// DISENGAGED
		case 1:
			pTicks = 0;
			sTicks = sRatioToTicks(100);

			// State Changes
			if (engineSpeed.get() > ENGAGE_SPEED && run) {
				ePID.reset();
				eState = 2;
			}
			return;

		// ENGAGED, PID CONTROLLER - REST
		case 2:
			// State Changes
			if (engineSpeed.get() < ENGAGE_SPEED || !run) {
				eState = 1;
			} else if (eCalc) {
				eState = 3;
			}
			return;

		// ENGAGED, PID CONTROLLER - UPDATE
		case 3:
			ePID.calc(engineSpeed.get());
			pTicks = pRatioToTicks(ePID.get());
			sTicks = sRatioToTicks(ePID.get());

			//// Debugging
			//#ifdef DEBUG
			//Serial.print("ePID: ");
			//Serial.println(ePID.get());
			//#endif

			// State Changes
			eCalc = false;
			eState = 2;
			return;
	}
}



void primary() {
	// // Debugging
	// #ifdef DEBUG
	// Serial.print("pState: ");
	// Serial.println(pState);
	// #endif
	
	switch (pState) {
		// INITIALIZE
		case 0:
			// Setup Motor
			pMot.init();

			// Setup PID Controller
			pPID.setLoSat(-100);
			pPID.setHiSat( 100);
			pMot.setDutyCycle(0);

			// State Changes
			pState = 1;
			return;

		// CALIBRATE - OPEN SHEAVES
		case 1:
			pMot.setDutyCycle(-5);
			pCalTime = micros();
			// State Changes
			pState = 2;
			return;

		// CALIBRATE - ZERO ENCODER
		case 2:
			if (micros() - pCalTime > CALIBRATION_DELAY) {
				pEnc.zero();

				// State Changes
				pState = 3;
			}
			return;

		// P-ONLY CONTROLLER - REST
		case 3:
			// State Changes
			if (pCalc) {
				pState = 4;
			}

		// P-ONLY CONTROLLER - UPDATE
		case 4:
			pPID.setSetpoint(pTicks);
			pPID.calc(pEnc.read());
			pMot.setDutyCycle(pPID.get());

			// // Debugging
			// #ifdef DEBUG
			// Serial.print("pPID: ");
			// Serial.println(pPID.get());
			// #endif

			// State Changes
			pCalc = false;
			pState = 3;
	}
}



void secondary() {
	// // Debugging
	// #ifdef DEBUG
	// Serial.print("sState: ");
	// Serial.println(sState);
	// Serial.println(sEnc.read());
	// #endif
	
	switch (sState) {
		// INITIALIZE
		case 0:
			// Setup Motor
			sMot.init();

			// Setup PID Controller
			sPID.setLoSat(-100);
			sPID.setHiSat( 100);
			sMot.setDutyCycle(0);

			// State Changes
			sState = 1;
			return;

		// CALIBRATE - OPEN SHEAVES
		case 1:
			sMot.setDutyCycle(-5);
			sCalTime = micros();
			// State Changes
			sState = 2;
			return;

		// CALIBRATE - ZERO ENCODER
		case 2:
			if (micros() - sCalTime > CALIBRATION_DELAY) {
				sEnc.zero();

				// State Changes
				sState = 3;
			}
			return;

		// P-ONLY CONTROLLER - REST
		case 3:
			// State Changes
			if (sCalc) {
				sState = 4;
			}

		// P-ONLY CONTROLLER - UPDATE
		case 4:
			sPID.setSetpoint(sTicks);
			sPID.calc(sEnc.read());
			sMot.setDutyCycle(sPID.get());

			// // Debugging
			// #ifdef DEBUG
			// Serial.print("sPID: ");
			// Serial.println(sPID.get());
			// #endif

			// State Changes
			sCalc = false;
			sState = 3;
	}
}



/* ** MAIN ** */
int main(void) {

	// // Serial Monitor
	// #ifdef DEBUG
	// Serial.begin(9600);
	// #endif
	
	/* ** INPUT/OUTPUT CONFIGURATIONS ** */
	IO_Init();
	 // ** TIMER/COUNTER CONFIGURATIONS ** 
	TC_Init();

	pMot.init();
	pMot.setDutyCycle(30);

	while (true) {
		//eCVT();
		//primary();
		//secondary();
	}

}