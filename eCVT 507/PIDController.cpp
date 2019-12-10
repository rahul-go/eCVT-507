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

// Constructor
PIDController::PIDController(float Kp, float Ki, float Kd) {
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
}

// Mutator Methods
void PIDController::setKp(float Kp) { this->Kp = Kp; }
void PIDController::setKi(float Ki) { this->Ki = Ki; }
void PIDController::setKd(float Kd) { this->Kd = Kd; }

// Mutator Methods
void PIDController::setSetpoint(int32_t setpoint) { this->setpoint = setpoint; }
void PIDController::setLoSat(int8_t loSat) { this->loSat = loSat; }
void PIDController::setHiSat(int8_t hiSat) { this->hiSat = hiSat; }

// Interrupt Service Routine Method
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

// Get output
float PIDController::get() {
	// Calculate output
	output = Kp * error + Ki * integral + Kd * derivative;
	// Test if saturated
	saturated = output < loSat || output > hiSat;
	// Return output
	return output;
}

// Reset integral and derivative
void PIDController::reset() {
	integral = 0;
	derivative = 0;
}