/*
 * Robot command structure class
 *
 * This is used to daisy chain commands that can be executed either in series, or in parallel.
 */

#ifndef _ROBOTCMD_HPP
#define _ROBOTCMD_HPP

class RobotCmd {
public:
	bool _active;		// whether this command is active
	RobotCmd *_next;	// full list of all commands in system
	RobotCmd *_child;	// next serial command
	RobotCmd *_sibling;	// next parallel command

	RobotCmd::RobotCmd() {
		_active = false;
		_next = NULL;
		_child = NULL;
		_sibling = NULL;
	}

	virtual void initialise() = 0;

	virtual bool execute() = 0;

	virtual void end() = 0;

	virtual void cancel() = 0;

	/*
	 * Framework functions.
	 * These should not be overridden by derived classes
	 */

	/*
	 * Set the next value to that specified.
	 * The caller has to ensure we are not losing information.
	 */
	RobotCmd *
	RobotCmd::setNext(RobotCmd *newRC) {
		_next = newRC;
		return this;
	}

	/*
	 * add a command as a sequential command.
	 * We walk to the end of the list before we add it.
	 */
	RobotCmd *
	RobotCmd::addSequential(RobotCmd *newRC) {
		if (_child == NULL) {
			_child = newRC;
		} else {
			_child->addSequential(newRC);
		}
		return this;
	}

	/*
	 * add a command as a parallel command.
	 * We walk to the end of the list before we add it.
	 */
	RobotCmd *
	RobotCmd::addParallel(RobotCmd *newRC) {
		if (_sibling == NULL) {
			_sibling = newRC;
		} else {
			_sibling->addParallel(newRC);
		}
		return this;
	}

	/*
	 * start this command running.
	 * If the command is not active we run its initialise() method, then
	 * set the active flag.
	 */

	RobotCmd *
	RobotCmd::start() {
		if (_active == false) {
			this->initialise();
			_active = true;
		}
		return this;
	}

	RobotCmd *
	RobotCmd::stop() {
		if (_active) {
			this->cancel();
			this->end();
			_active = false;
		}
		return this;
	}
};

#endif /* RobotCmd.hpp */
