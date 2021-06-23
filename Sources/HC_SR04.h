#ifndef HC_SR04_H
#define HC_SR04_H

#include "GPIO.h"

class HC_SR04 : public GPIO 
{
private:
  GPIO triggerPin;
  GPIO echoPin;
  double soundSpeed;

  // Initialize the GPIO pin with the data provided by the constructor
  void InitSensor();

  // Private method to count the pulse duration
  double PulseDuration();

public:

  // Overload constructor with trigger and echo pins
  HC_SR04(GPIO, GPIO);

  // Overload constructor with temperature for sound speed correction
  HC_SR04 (GPIO, GPIO, double); 

  // Public method to calculate the distance
  double MeasureDistanceCm();

  // Destructor
  ~HC_SR04();
};

#endif // HC-SR04_H
