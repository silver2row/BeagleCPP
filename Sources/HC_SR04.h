#ifndef HC_SR04_H
#define HC_SR04_H

#include <iostream>
#include <chrono> // chrono::milliseconds()
#include <sstream> //stringstream
#include <iomanip> //setprecision()
#include <list>
#include <future>

#include "GPIO.h"

class HC_SR04 : public GPIO 
{
private:
  GPIO triggerPin;
  GPIO echoPin;
  double soundSpeed;
  double offset;

  // Initialize the GPIO pin with the data provided by the constructor
  void InitSensor();

  // Private method to count the pulse duration
  double CountPulseDuration();

  // Private method to count the pulse duration
  double MakeGetPulseDuration();

public:

  // No-args default constructor
  HC_SR04();

  // Overload constructor with trigger and echo pins
  HC_SR04(GPIO, GPIO);

  // Overload constructor with temperature for sound speed correction
  HC_SR04 (GPIO, GPIO, double, double); 

  // Public method to get and calculate the distance
  virtual double MeasureDistanceCm();

  // Public method to get, calculate and filter the distance
  virtual double MeasureDistanceCmWithMedian(int windowSize = 5);

  

  // Destructor
  ~HC_SR04();
};

#endif // HC-SR04_H
