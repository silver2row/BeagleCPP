#ifndef HC_SR04_H
#define HC_SR04_H

#include "GPIO.h"

class HC_SR04 : public GPIO 
{
private:
  GPIO triggerPin;
  GPIO echoPin;
  double soundSpeed;
  double timeTravel;

  // Initialize the GPIO pin with the data provided by the constructor
  void InitSensor();

public:
  double distanceCm;

  // Overload constructor
  HC_SR04(GPIO, GPIO);

  int MeasureDistanceCm();

  // Destructor
  ~HC_SR04();
};

#endif // HC-SR04_H
