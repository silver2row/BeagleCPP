#ifndef SG90_H
#define SG90_H

#include "PWM.h"

/* The numeric mode for ACTION on the motor: e.g. 0/1 for Brake/Stop */
const int SG90Period = 20000000;

class SG90 : public PWM
{
private:
  PWM pwmPin;
  int angle;              // Desired angle in degrees
  int minimumPulseWidth;  // Minimum pulse width in ns
  int maximumPulseWidth;  // Minimum pulse width in ns

public:

  // Overload constructor
  SG90(PWM);

  // Overload constructor with min and max pulse width in ns
  SG90(PWM, int, int);

  // Accessor method the minimum pulse width
  virtual int GetMinimumPulseWidth();

  // Accessor method the maximum pulse width
  virtual int GetMaximumPulseWidth();

  // Interface method to drive the motor 
  virtual void SetAngle (int);
  
  // Destructor
  ~SG90();
};

#endif // SG90_H
