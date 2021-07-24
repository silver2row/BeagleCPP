#ifndef Servo_H
#define Servo_H

#include "PWM.h"

/* The standard period of 20ms to control any servo */
const int ServoPeriod = 20000000;

class Servo : public PWM
{
private:
  PWM pwmPin;
  int angle;              // Desired angle in degrees
  int minimumPulseWidth;  // Minimum pulse width in ns
  int maximumPulseWidth;  // Minimum pulse width in ns

  // Set the Servo period for the PWM pin  
  virtual void InitServo();

public:

  // Overload constructor
  Servo(PWM);

  // Overload constructor with min and max pulse width in ns
  Servo(PWM, int, int);

  // Accessor method the minimum pulse width
  virtual int GetMinimumPulseWidth();

  // Accessor method the maximum pulse width
  virtual int GetMaximumPulseWidth();

  // Interface method to drive the motor 
  virtual void SetAngle (int);
  
  // Destructor
  ~Servo();
};

#endif // Servo_H
