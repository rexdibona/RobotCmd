/*
 * Robot Responder.
 * This class allows us to configure responses to various types of
 * external events.
 *
 * We take an event and a command and a rule. When that event occurs then the rule takes place.
 *
 * An event can be superclassed to allow anything that can be a boolean be an event.
 * Rules are first true, first false, or while true.
 *
 * So, we can 'onTrue', 'onFalse' and 'whileTrue'
 *
 */

#ifndef _TRIGGER_HPP
#define _TRIGGER_HPP
#include "Event.hpp"

class Trigger {
public:
	Event *_ep;		// event we are monitoring
	RobotCmd *_onTrue_cmd;
	RobotCmd *_onFalse_cmd;
	RobotCmd *_whileTrue_cmd;
	bool _active;
	Trigger *_next;		// for chaining in TriggerMonitor

	RobotResponder::RobotResponder(Event *ep) {
		_ep = ep;
		_cmd = NULL;
		_active = false;
		_next = NULL;
		TriggerMonitor::Instance()->addTrigger(this);
	}

	RobotResponder *
	onTrue(RobotCmd *cmd) {
		_onTrue_cmd = cmd;
		return this;

	RobotResponder *
	onFalse(RobotCmd *cmd) {
		_onFalse_cmd = cmd;
		return this;

	RobotResponder *
	whileTrue(RobotCmd *cmd) {
		_whileTrue_cmd = cmd;
		return this;
	}
	
	/*
	 * Check the event, and schedule a command to execute
	 * as appropriately
	 */
	void
	update() {
		bool temp = _ep->event();
		if (temp) {
			if (_whileTrue_cmd != NULL) {
				_whileTrue_cmd->start();
			}
			if (_active == false && _onTrue_cmd != NULL) {
				_onTrue_cmd->start();
			}
		} else if (_active == true && _onFalse_cmd != NULL) {
			_onFalse_cmd->start();
		}
		_active = temp;
	}
};

#endif /* Triger.hpp */
