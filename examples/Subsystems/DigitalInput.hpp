/*
 * This is a wrapper around a digital input.
 * It can be used as an Event for a trigger if necessary
 *
 * It will return true of false
 */
#ifndef	_DIGITALINPUT_HPP
#define	_DIGITALINPUT_HPP
#include "Event.hpp"

class DigitalInput: public Event {
private:
	int _pin;

public:
	DigitalInput::DigitalInput(int pin) {
		_pin = pin;
		pinMode(_pin, OUTPUT);
	}

	bool
	getValue(bool value) {
		return digitalRead(_pin);
	}
};

#endif // DigitalInput.hpp
