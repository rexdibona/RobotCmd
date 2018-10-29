/*
 * Event
 *
 * An event is anything that can return true of false.
 * It is used for responder actions. It must be supertyped to the actual
 * type that has an event() method.
 * The event method is a boolean that returns either true or false
 */

#ifndef _EVENT_HPP
#define _EVENT_HPP

class Event {
public:
	/**
	* The event() method retuns a boolean that is true if the event has occurred.
	*/
	virtual bool getValue() = 0;
};

#endif /* Event.hpp */
