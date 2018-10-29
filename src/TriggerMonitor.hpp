/*
 * TriggerMonitor is the class that runs all the triggers.
 * It is built as a command that never dies, so that we can run it from
 * RobotRunner as an adhoc command.
 * 
 * When run it will call the update(0 method of all registered triggers.
 *
 */

#ifndef	_TRIGGERMONITOR_HPP
#define	_TRIGGERMONITOR_HPP
#include "RobotCmd.hpp"
#include "Trigger.hpp"


class TriggerMonitor {
	private:
	Trigger *_triggerBase = NULL;
	TriggerMonitor() {
		_triggerBase = NULL;
	};

	public:
	static TriggerMonitor& Instance() {
		static TriggerMonitor singleton;
		return singleton;
	}

	void
	addTrigger(Trigger *tp) {
		tp->_next = _triggerBase;
		_triggerBase = tp;
	}

	update() {
		Trigger *tp;

		for (tp = _triggerBase; tp != NULL; tp = tp->_next) {
			tp->update();
		}
	}
};	


#endif	/* TriggerMonitor.hpp */
