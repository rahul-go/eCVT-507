/*
 *	PIDController.cpp - Library header for PID controller.
 *	Created by Rahul Goyal, July 1 2019.
 *	Released to Cal Poly Baja SAE. ;)
 */

#ifndef PIDController_h
#define PIDController_h

// #include <Arduino.h>
#include <stdint.h>

class PIDController {

	public:
		// Constructor
		PIDController(float Kp, float Ki, float Kd);

		// Methods
		void setKp(float Kp);
		void setKi(float Ki);
		void setKd(float Kd);
		void setSetpoint(int32_t setpoint);
		void setLoSat(int8_t loSat);
		void setHiSat(int8_t hiSat);

		void calc(int32_t measurement);
		float get();
		void reset();

	private:
		int32_t setpoint = 0;
		int32_t prev = 0;
		int32_t error = 0;
		int32_t integral = 0;
		int32_t derivative = 0;

		int8_t loSat = 0;
		int8_t hiSat = 0;
		bool saturated;

		float Kp;
		float Ki;
		float Kd;

		float output = 0;
};

#endif