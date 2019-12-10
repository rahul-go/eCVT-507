//*****************************************************************************
/**	@file		PIDController.cpp
 *	@brief		Source code for a class that implements a PID Controller.
 *	@details	This class allows the user to implement a PID Controller. It is
 *				given a setpoint, low saturation, high saturation, and Kp, Ki,
 *				and Kd gain values. In addition to providing PID output, the
 *				class accounts for integral windup by disabling the integral
 *				term if the output is determined as saturated. The class can
 *				also serve as a P-Only, PI, or PD controller by setting the
 *				appropriate gains to 0, although this does result in some
 *				unnecessary calculations.
 *
 *	@author		KC Egger, Rahul Goyal, Alexandros Petrakis
 *
 *  @date 2019-12-09 */
//*****************************************************************************

#include "PIDController.h"
#include <stdint.h>

/** @brief		Constructor which creates and initializes a motor object.
 *  @details	This constructor creates a PID controller object with a given
 *				proportional gain, integral gain, and derivative gain. If a
 *				P-Only, PI, or PD controller is desired, set the other gains
 *				to zero. 
 *  @param		Kp The proportional gain for the controller.
 *	@param		Ki The integral gain for the controller.
 *	@param		Kd The derivative gain for the controller.
 */
PIDController::PIDController(float Kp, float Ki, float Kd) {
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
}

/** @brief		Updates the proportional gain.
 *  @details	This function updates the proportional gain to a new value
 *				during use.
 *  @param		Kp The new proportional gain for the controller.
 */
void PIDController::setKp(float Kp) { this->Kp = Kp; }
/** @brief		Updates the integral gain.
 *  @details	This function updates the integral gain to a new value during
 *				use.
 *  @param		Ki The new integral gain for the controller.
 */
void PIDController::setKi(float Ki) { this->Ki = Ki; }
/** @brief		Updates the derivative gain.
 *  @details	This function updates the derivative gain to a new value
 *				during use.
 *  @param		Kd The new derivative gain for the controller.
 */
void PIDController::setKd(float Kd) { this->Kd = Kd; }

// Mutator Methods
/** @brief		Updates the setpoint.
 *  @details	This function updates the setpoint to a new value during use.
 *  @param		setpoint The new proportional gain for the controller.
 */
void PIDController::setSetpoint(int32_t setpoint) { this->setpoint = setpoint; }
/** @brief		Updates the low saturation limit.
 *  @details	This function updates the low saturation limit to a new value
 *				during use.
 *  @param		loSat The new low saturation limit for the controller.
 */
void PIDController::setLoSat(int8_t loSat) { this->loSat = loSat; }
/** @brief		Updates the high saturation limit.
 *  @details	This function updates the high saturation limit to a new value
 *				during use.
 *  @param		hiSat The new high saturation limit for the controller.
 */
void PIDController::setHiSat(int8_t hiSat) { this->hiSat = hiSat; }

/** @brief		Update the previous error, the error, the integral, and the derivative.
 *  @details	This function updates the previous error, the error, the integral, and
 *				the derivative values. These values can be used to calculate the
 *				PID output and saturation status, but this calculation is left
 *				until the get() function is called to minimize the time spent
 *				in the interrupt service routine.
 */
void PIDController::calc(int32_t measurement) {
	// Store previous error
	prev = error;
	// P
	error = setpoint - measurement;
	// I
	if (!saturated) {
		integral += error;
	}
	// D
	derivative = error - prev;
}

/** @brief		Update the saturation status and return the PID output.
 *  @details	This function calculatest the PID output. It then compares the
 *				calculated output to the low saturation limit and the high
 *				saturation limit. If the PID output is outside of the
 *				saturation limits, the saturation status is set to true, else
 *				it is set to false. The PID output is then returned.
 *  @return		get The PID output as a float.
 */
float PIDController::get() {
	// Calculate output
	output = Kp * error + Ki * integral + Kd * derivative;
	// Test if saturated
	saturated = output < loSat || output > hiSat;
	// Return output
	return output;
}

/** @brief		Reset the calculated integral and derivative to zero.
 *  @details	This function resets the calculated integral and derivative
 *				to zero so that the PID controller can be re-entered without
 *				an affect from old data.
 */void PIDController::reset() {
	integral = 0;
	derivative = 0;
}