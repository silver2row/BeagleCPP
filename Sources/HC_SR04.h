#ifndef HC_SR04_H
#define HC_SR04_H

#include "GPIO.h"
#include "GPI.h"

class HC_SR04 : public GPIO, public GPI
{
private:
  GPIO triggerPin;
  GPI echoPin;
  double soundSpeed;
  double timeTravel;
  double distanceCm;

public:

  // Overload constructor
  HC_SR04(GPIO, GPI);

  void PulseIn(); 

  double measureDistanceCm();

  // Destructor
  ~HC_SR04();
};

#endif // HC-SR04_H
