/*
 * This is an abstract class for use in the PID loop.
 * This class must be overloaded to define setPID(float value)
 */
#ifndef	_PIDWRITER_HPP
#define	_PIDWRITER_HPP

class PidWriter {
private:
	PidWriter::PidWriter() {}

public:
	void setValue(float value) = 0;
};

#endif // PidWriter.hpp
