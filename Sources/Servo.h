#ifndef Servo_H
#define Servo_H

#include "PWM.h"

/* The standard period of 20ms to control any servo */
const int ServoPeriod = 20000000;

class Servo : public PWM
{
private:
  PWM pwmPin;
  int minimumPulseWidth;  // Minimum pulse width in ns
  int maximumPulseWidth;  // Minimum pulse width in ns
  int angle;              // Desired angle in degrees
  int speed;              // Desired speed in percentage for a continuos servo

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

  // Interface method to set the angle 
  virtual void SetAngle (int);

  // Interface method to set the speed for a continuos servo 
  virtual void SetSpeed (int);
  
  // Destructor
  ~Servo();
};

#endif // Servo_H
