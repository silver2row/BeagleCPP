#include <iostream>

#include "DCMOTOR_UTILS.h"

/******************************************************************************
PUBLIC FUNCTIONS TO RUN ONLY DC MOTOR MODULES OBJECTS
******************************************************************************/
/*
  Function to drive FORWARD a robot with ANY number of Module drivers 
  during certain time
  @param std::vector<Module *>: The vector of pointers to Module objects  
  @param int speed: The desired speed (0,100). It set up the correct value if the user enters 
                    a negative value.
  @param int duration:  The desired duration in milliseconds with 0 as 
                        default value
  @param STOPMODE action <brake / idle>:  Action on the motor after driving it with 
                                        <idle> as default action.  
*/
template <typename Module>
void Forward (std::vector<Module *> vectorOfModules, int speed, int duration, STOPMODE action)
{
  if (speed < 0)
    speed *= -1;

  for (auto module : vectorOfModules)
  {
    if (module->GetMotorAisUsed())
      module->MotorA.Drive(speed);
    if (module->GetMotorBisUsed())
      module->MotorB.Drive(speed);
  }

  if (duration > 0)
  {
    DelayMilliseconds(duration);
    
    if (action == idle)
      Idle(vectorOfModules);
    else
      Brake(vectorOfModules);
  }
}

/*
  Function to drive BACKWARD a robot with ANY number of Module drivers 
  during certain time
  @param std::vector<Module *>: The vector of pointers to Module objects
  @param int speed: The desired speed (-100,0). It set up the correct value if
                    the user enters a positive value.
  @param int duration:  The desired duration in milliseconds with 0 as 
                        default value
  @param STOPMODE action <brake / idle>:  Action on the motor after driving it with 
                                        <idle> as default action. 
*/
template <typename Module>
void Backward (std::vector<Module *> vectorOfModules, int speed, int duration, STOPMODE action)
{
  if (speed > 0)
    speed *= -1;

  for (auto module : vectorOfModules)
  {
    if (module->GetMotorAisUsed())
      module->MotorA.Drive(speed);
    if (module->GetMotorBisUsed())
      module->MotorB.Drive(speed);
  }

  if (duration > 0)
  {
    DelayMilliseconds(duration);
    
    if (action == idle)
      Idle(vectorOfModules);
    else
      Brake(vectorOfModules);
  }
}

/*
  Function to BRAKE a robot with ANY number of motors
  @param std::vector<Module *>: The vector of pointers to Module objects
*/
template <typename Module>
void Brake (std::vector<Module *> vectorOfModules)
{
  for (auto module : vectorOfModules)
    module->Brake();
}

/*
  Function to IDLE a robot with ANY number of motors
  @param std::vector<Module *>: The vector of pointers to Module objects 
*/
template <typename Module>
void Idle (std::vector<Module *> vectorOfModules)
{
  for (auto module : vectorOfModules)
    module->Idle();
}