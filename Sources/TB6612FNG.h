#ifndef TB6612FNG_H
#define TB6612FNG_H

#include <vector>
#include "DCMOTOR.h"

class TB6612FNG
{
private:
  GPIO standByPin;
  bool motorAisUsed;
  bool motorBisUsed;

public:
  DCMotor MotorA;
  DCMotor MotorB;

  // No-args default constructor
  TB6612FNG();

  // Overload constructor from one DCMotor object
  TB6612FNG(DCMotor&, GPIO);

  // Overload constructor from DCMotor objects
  TB6612FNG(DCMotor&, DCMotor&, GPIO);

  // Interface method to activate the module
  virtual void Activate ();

  // Interface method to deactivate the module
  virtual void Deactivate ();

  // Interface method to brake the both motors
  virtual void Brake();

  // Interface method to idle the both motors
  virtual void Idle(); 

  // Interface method to drive both motors forward 
  virtual void Forward (int speed, int duration = 0, STOPMODE action = idle);

  // Interface method to drive both motors backward 
  virtual void Backward (int speed, int duration = 0, STOPMODE action = idle);

  // Interface method to drive in opposite direction both motors 
  virtual void TurnLeft (int speed, int duration = 0, STOPMODE action = idle);

  // Interface method to drive in the another opposite direction both motors 
  virtual void TurnRight(int speed, int duration = 0, STOPMODE action = idle);

  // Destructor
  virtual ~TB6612FNG();
};

/******************************************************************************
PUBLIC FUNCTIONS TO RUN ONLY MOTOR OBJECTS
******************************************************************************/

void Forward (std::vector <TB6612FNG *>, int);
void Forward (std::vector <TB6612FNG *>, int, int, STOPMODE);
void Backward (std::vector <TB6612FNG *>, int);
void Backward (std::vector <TB6612FNG *>, int, int, STOPMODE);
void Brake (std::vector <TB6612FNG *>);
void Idle (std::vector <TB6612FNG *>);

#endif // TB6612FNG_H