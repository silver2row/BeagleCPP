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
  int averagePulseWidth;  // Average pulse width in ns
  int maximumPulseWidth;  // Maximun pulse width in ns
  int angle;          // Desired angle in degrees
  int speed;          // Desired speed in percentage for a continuos servo

  // Set the Servo period for the PWM pin  
  virtual void InitServo();

public:
  // Default constructor
  Servo();

  // Overload constructor
  Servo(PWM);

  // Overload constructor with min and max pulse width in ns
  Servo(PWM, int, int);

  // Accessor method to get the minimum pulse width
  virtual int GetMinimumPulseWidth();

  // Accessor method to get the maximum pulse width
  virtual int GetMaximumPulseWidth();

  // Accessor method to get the average pulse width
  virtual int GetAveragePulseWidth();

  // Interface method to set the angle 
  virtual void SetAngle (int);

  // Interface method to set the speed for a continuous servo 
  virtual void SetSpeed (int);
  
  // Destructor
  ~Servo();
};

#endif // Servo_H
