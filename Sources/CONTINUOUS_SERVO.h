#ifndef CONTINUOUS_SERVO_H
#define CONTINUOUS_SERVO_H

#include "SERVO.h"

class CONTINUOUS_SERVO: public SERVO
{
private:
  int speed;          // Desired speed in percentage

  // Private method to set the servomotor parameters  
  virtual void InitContinuousServo();

public:
  SERVO Servo;

  // Overload constructor with PWM pin
  CONTINUOUS_SERVO(PWM);

  // Overload constructor with PWM pin, min and max pulse width in ns
  CONTINUOUS_SERVO(PWM, int, int);

  // Interface method to set the speed
  virtual void SetSpeed (int);
  
  // Destructor
  ~CONTINUOUS_SERVO();
};

#endif // CONTINUOUS_SERVO_H
