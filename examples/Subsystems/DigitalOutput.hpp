/*
 * This is a wrapper around a digital output.
 * It can be set to high or Low.
 */
class DigitalOutput {
private:
	int _pin;

public:
	DigitalOutput::DigitalOutput(int pin) {
		_pin = pin;
		pinMode(_pin, OUTPUT);
	}

	void
	setOutput(bool value) {
		digitalWrite(_pin, value);
	}
};
