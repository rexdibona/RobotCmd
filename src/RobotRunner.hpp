/*
 * Robot executer
 *
 * This code will execute  all the RobotCmd structs added.
 * Initially they are added inactive, the first is made active and we start running them.
 *
 * Sadly, we run through a linked list of all RobotCmd each loop to see which are active.
 * But given we generally have only a few commands this n^2 should not become burdensome.
 * If it does a smarter algorithm is required.
 *
 */
#ifndef _ROBOTRUNNER_HPP
#define _ROBOTRUNNER_HPP
#include <RobotCmd.hpp>		// we need the RobotCmd structures that we utilise.

class RobotRunner {
public:
	RobotCmd *_base;	// normal command structures
	RobotCmd *_adhoc;	// adhoc commands, just added as a command.
	
	RobotRunner::RobotRunner()
	{
		_base = NULL;	// initialise it!
		_adhoc = TriggerMonitor::Instance();
	}

	RobotRunner *
	RobotRunner::adhoc(RobotCmd *newRC) {
		if (newRC == NULL) return;	// all done
		_adhoc = newRC->setNext(_adhoc);
		add(newRC->_sibling);	// should always be NULL
		add(newRC->_child);	// should always be NULL
		return this;
	}

	RobotRunner *
	RobotRunner::add(RobotCmd *newRC) {
		if (newRC == NULL) return;	// all done
		_base = newRC->setNext(_base);
		add(newRC->_sibling);
		add(newRC->_child);
		return this;
	}

	void
	RobotRunner::setParallelActive(RobotCmd *setRC) {
		while (setRC != NULL) {
			setRC->initialise();
			setRC->_active = true;
			setRC = setRC->_sibling;
		}
	}

	void
	RobotRunner::update() {
		RobotCmd *ptr;

		for (ptr = _base; ptr != NULL; ptr = ptr->_next) {
			if (ptr->_active == false) {
				continue;
			}
			if (ptr->execute()) {
				ptr->end();
				ptr->_active = false;
				setParallelActive(ptr->_child);
			}
		}
		for (ptr = _adhoc; ptr != NULL; ptr = ptr->_next) {
			if (ptr->_active == false) {
				continue;
			}
			if (ptr->execute()) {
				ptr->end();
				ptr->_active = false;
				setParallelActive(ptr->_child);
			}
		}
	}
};

#endif /* RobotRunner.hpp */
