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

  // Getter to let know if the  MotorA is used
  virtual bool GetMotorAisUsed();

  //Getter to let know if the  MotorB is used
  virtual bool GetMotorBisUsed(); 

  // Destructor
  virtual ~L298N();
};

#endif // L298N_H