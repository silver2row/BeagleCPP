#ifndef TB6612FNG_H
#define TB6612FNG_H

#include <vector>
#include "DCMOTOR.h"

class TB6612FNG
{
private:
  GPIO standByPin;

public:
  DCMotor MotorA;
  DCMotor MotorB;

  // Overload constructor from pins
  TB6612FNG(GPIO, GPIO, PWM, GPIO, bool = false);

  // Overload constructor from pins
  TB6612FNG(GPIO, GPIO, PWM, GPIO, GPIO, PWM, GPIO, bool = false, bool = false);

  // Overload constructor from one DCMotor object
  TB6612FNG(DCMotor&, GPIO);

  // Overload constructor from DCMotor objects
  TB6612FNG(DCMotor&, DCMotor&, GPIO);

  // Interface method to activate the module
  virtual void Activate ();

  // Interface method to deactivate the module
  virtual void Deactivate (); 

  // Interface method to drive both motors forward
  virtual void Forward (int);

  // Interface method to drive both motors forward during certain time with <stop> as a default action. 
  virtual void Forward (int, int, ACTION = stop);

  // Interface method to drive  both motors backward
  virtual void Backward (int);

  // Interface method to drive both motors backward during certain time with <stop> as a default action. 
  virtual void Backward (int, int, ACTION = stop);

  // Interface method to drive in opposite direction both motors
  virtual void TurnLeft (int);

  // Interface method to drive in opposite direction both motors during certain time with <stop> as a default action. 
  virtual void TurnLeft (int, int, ACTION = stop);

  // Interface method to drive in the another opposite direction both motors
  virtual void TurnRight (int);

  // Interface method to drive in the another opposite direction both motors during certain time with <stop> as a default action. 
  virtual void TurnRight(int, int, ACTION = stop);

  // Interface method to brake the both motors
  virtual void Brake();

  // Destructor
  virtual ~TB6612FNG();
};

/******************************************************************************
PUBLIC FUNCTIONS TO RUN ONLY MOTOR OBJECTS
******************************************************************************/

void Forward (std::vector <DCMotor *>, int);
void Forward (std::vector <DCMotor *>, int, int, ACTION);
void Backward (std::vector <DCMotor *>, int);
void Backward (std::vector <DCMotor *>, int, int, ACTION);
void Brake (std::vector <DCMotor *>);

#endif // TB6612FNG_H