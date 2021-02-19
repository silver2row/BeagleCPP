#ifndef TB6612FNG_H
#define TB6612FNG_H

#include <vector>
#include <thread>

#include "GPIO.h"
#include "PWM.h"

class TB6612FNG : public GPIO, public PWM
{
private:
  GPIO input1Pin;
  GPIO input2Pin;
  GPIO standByPin;
  PWM pwmPin;
  bool swapSpin;
  int swapSpinMotor;
  const int maxSpeed = 100;

  // Helper method to set CW the direction of motor rotation 
  virtual void SetCWMode();
  
  // Helper method to set CCW the direction of motor rotation 
  virtual void SetCCWMode();
  
public:

  // Overload constructor WITHOUT standby pin
  TB6612FNG(GPIO, GPIO, PWM, bool);

  // Overload constructor WITH standby pin
  TB6612FNG(GPIO, GPIO, PWM, bool, GPIO);

  // Interface method to set the rotation speed
  virtual void SetSpeed(int);

  // Interface method to drive the motor 
  virtual void Drive (int);

  // Overloaded interface method to drive the motor during a certain time 
  virtual void MakeDrive (int, int);

  // Interface method to set the standby mode in the motor
  virtual void SetStandByMode();

  // Interface method to stop the motor
  virtual void StopMode();

  // Interface method to do a short brake on the motor
  virtual void ShortBrakeMode();  

  // Destructor
  ~TB6612FNG();
};

#endif // HC-SR04_H
