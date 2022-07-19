#ifndef POSITION_SERVO_H
#define POSITION_SERVO_H

#include "SERVO.h"

class POSITION_SERVO
{
private:
  int angle;          // Desired angle in degrees

  // Private method to set the servomotor parameters  
  virtual void InitPositionServo();

public:
  SERVO Servo;

  // No-args default constructor
  POSITION_SERVO ();

  // Overload constructor with PWM pin
  POSITION_SERVO(PWM);

  // Overload constructor with PWM pin, min and max pulse width in ns
  POSITION_SERVO(PWM, int, int);

  // Interface method to set the angle 
  virtual void SetAngle (int);
  
  // Destructor
  ~POSITION_SERVO();
};

#endif // POSITION_SERVO_H
