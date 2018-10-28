/*
 * A subsystem is a wrapper class around a piece of hardware functionality.
 * It generally holds the state about a piece of hardware, and is used to manipulate the state of the hardware.
 *
 * Each piece of hardware should have its own subsystem class.
 *
 * This is a wrapper around a digital output for a LED
 */
class SubsystemLED {
private:
	int _pin;

public:
	SubsystemLED::SubsystemLED(int pin) {
		_pin = pin;
		pinMode(_pin, OUTPUT);
	}

	void
	setLED(bool value) {
		digitalWrite(_pin, value);
	}
};
