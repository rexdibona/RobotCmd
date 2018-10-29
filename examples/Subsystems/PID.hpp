/*
 * PID subsystem
 *
 * This creates a pid controller.
 * It is run as an adhoc command (It adds itself)
 * This allows the PID loops to run without manually adding them as commands.
 *
 */

#ifndef	_PID_HPP
#define	_PID_HPP
#include "RobotCmd.hpp"
#include "PidReader.hpp"
#include "PidWriter.hpp"


class PID: public RobotCmd {
private:
	unsigned long _interval = 0;
	unsigned long _next;
	PidReader *_r = null;
	PidWriter *_w = null;
	float _p, _i, _d, _f;
	float _setPoint, _integral, _previousErr;

	PID::PID(float p, float i, float d, PidReader *r, PidWriter *w, unsigned long interval) {
		_f = 0;
		_p = p;
		_i = i;
		_d = d;
		_interval = interval;
		_r = r;
		_w = w;
		_integral = 0;
		_next = millis() + _interval;
		this->_active = false;
		RobotRunner::Instance()->adhoc(this);
	}

	PID *setSetPoint(float setPoint) {
		_setPoint = setPoint;
		this->_active = false;
		_integral = 0;
		_previousErr = _r->getPID() - setPoint;
		return this;
	}

	void initialise() {}
	void end() {}

	bool execute() {
		if (_next < millis()) {
			float newErr = _r->getValue() - setPoint;
			_integral = _integral +  newErr * _interval / 1000;
			float derivative = (newErr - curErr) * 1000 / interval;
			float output = _p * newErr + _i * _integral + _d * derivative + _f;
			_w->setPID(output);
			_previousErr = newErr;
			_next += _interval;
		}
		return false;
	}
};

#endif	// PID.hpp
