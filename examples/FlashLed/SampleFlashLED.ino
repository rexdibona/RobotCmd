/*
 * Sample robot command structure.
 * The robot in this case consists of two instances of the LED subsystem, and two instances of the flash LED command.
 */
#include "RobotCmd.hpp"
#include "RobotRunner.hpp"
#include "RobotFlashLed.hpp"

RobotRunner *cmds;

int led1 = 5;
int led2 = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  
  cmds = new RobotRunner();     // create an execution environment
  RobotFlashLed *rfl = new RobotFlashLed(new SubsystemLED(led1), 500);
  rfl->addParallel(new RobotFlashLed(new SubsystemLED(led2), 300));
  
  cmds->add(rfl);
  cmds->setParallelActive(rfl);
}

void loop() {
  // put your main code here, to run repeatedly:
  cmds->update();   // run robot commands
}

