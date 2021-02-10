#ifndef HC_SR04_H
#define HC_SR04_H

#include "GPIO.h"
#include "RAINBOWCOLORS.h"

class HC_SR04 : public GPIO
{
private:
  GPIO triggerPin;
  GPIO echoPin;
  double soundSpeed;
  double timeTravel;
  double distanceCm;
  
public:

  // Overload constructor
  HC_SR04(int, int);

  void test();

  double PulseIn(); 

  double measureDistanceCm();

  // Destructor
  ~HC_SR04();
};

#endif // HC-SR04_H
