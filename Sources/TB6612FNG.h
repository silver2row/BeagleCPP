#ifndef TB6612FNG_H
#define TB6612FNG_H

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
  
public:

  // Overload constructor
  TB6612FNG(GPIO, GPIO, GPIO, PWM, bool);

  // Destructor
  ~TB6612FNG();
};

#endif // HC-SR04_H
