//*****************************************************************************
/**	@file		PIDController.h
 *	@brief		Header for a class that implements a PID Controller.
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

#ifndef PIDController_h
#define PIDController_h

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