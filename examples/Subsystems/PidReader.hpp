/*
 * This is an abstract class for use in the PID loop.
 * This class must be overloaded to define float getPID()
 */
#ifndef	_PIDREADER_HPP
#define	_PIDREADER_HPP

class PidReader {
private:
	PidReader::PidReader() {}

public:
	float getValue() = 0;
};

#endif // PidReader.hpp
