#ifndef L298N_H
#define L298N_H

#include <vector>
#include "DCMOTOR.h"

class L298N
{
private:
  bool motorAisUsed;
  bool motorBisUsed;

public:
  DCMotor MotorA;
  DCMotor MotorB;

  // No-args default constructor
  L298N();

  // Overload constructor from one DCMotor object
  L298N(DCMotor&);

  // Overload constructor from DCMotor objects
  L298N(DCMotor&, DCMotor&);

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
  virtual ~L298N();
};

/******************************************************************************
PUBLIC FUNCTIONS TO RUN ONLY MOTOR OBJECTS
******************************************************************************/
void Forward (std::vector <L298N *>, int speed, int duration = 0, STOPMODE = idle);
void Backward (std::vector <L298N *>, int speed, int duration = 0, STOPMODE = idle);
void Brake (std::vector <L298N *>);
void Idle (std::vector <L298N *>);

#endif // L298N_H