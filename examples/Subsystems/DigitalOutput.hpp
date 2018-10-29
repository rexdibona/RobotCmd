/*
 * This is a wrapper around a digital output.
 * It can be set to high or Low.
 */

#ifndef	_DIGITALOUTPUT_HPP
#define	_DIGITALOUTPUT_HPP

class DigitalOutput {
private:
	int _pin;

public:
	DigitalOutput::DigitalOutput(int pin) {
		_pin = pin;
		pinMode(_pin, OUTPUT);
	}

	void
	setValue(bool value) {
		digitalWrite(_pin, value);
	}
};

#endif	// DigitalOutput.hpp
