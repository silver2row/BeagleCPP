#ifndef SERVO_H
#define SERVO_H

#include "PWM.h"

/* The standard period of 20ms to control any servo */
const int ServoPeriod = 20000000;

class SERVO : public PWM
{
private:
  // Declare POSITION_SERVO class as friend to allow access to private date members
  friend class POSITION_SERVO;

  // Declare CONTINUOUS_SERVO class as friend to allow access to private date members
  friend class CONTINUOUS_SERVO;

  PWM pwmPin;
  int minimumPulseWidth;  // Minimum pulse width in ns
  int averagePulseWidth;  // Average pulse width in ns
  int maximumPulseWidth;  // Maximun pulse width in ns

  // Set the Servo period for the PWM pin  
  virtual void InitServo();

public:
  // Default constructor
  SERVO();

  // Overload constructor
  SERVO(PWM);

  // Overload constructor with min and max pulse width in ns
  SERVO(PWM, int, int);

  // Accessor method to get the minimum pulse width
  virtual int GetMinimumPulseWidth();

  // Accessor method to get the maximum pulse width
  virtual int GetMaximumPulseWidth();

  // Accessor method to get the average pulse width
  virtual int GetAveragePulseWidth();

  // Destructor
  ~SERVO();
};

#endif // SERVO_H
