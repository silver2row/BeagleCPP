#include <iostream>
#include <chrono> // chrono::milliseconds()

#include "HC_SR04.h"

// Overload Constructor with trigger and echo pins
HC_SR04::HC_SR04(GPIO newTriggerPin, GPIO newEchoPin) :
        triggerPin(newTriggerPin), echoPin(newEchoPin) { 
  soundSpeed = 343.0 * 100; // Units in cm/s

  InitSensor();
  std::cout << RainbowText("HC-SR04: Trigger and Echo pins created", "Light Green") << std::endl;
}

// Overload Constructor with temperature for sound speed correction 
HC_SR04::HC_SR04(GPIO newTriggerPin, GPIO newEchoPin, double temperature) :
        triggerPin(newTriggerPin), echoPin(newEchoPin) { 
  this->soundSpeed = 33130 + 60.6 * temperature; // Units in cm/s and ºC

  InitSensor();
  std::cout << RainbowText("HC-SR04: Trigger and Echo pins created", "Light Green") << std::endl;
}

// Private method to initialize the Pins
void HC_SR04::InitSensor() {
  // Set the right modes for the pins
  triggerPin.SetMode(OUTPUT);
  echoPin.SetMode(INPUT);

  // Security before start the readings
  triggerPin.DigitalWrite(LOW);
  Delayms(500);
}
/*
  Private method to count the pulse duration
  @return double: The duration of pulse in seconds
*/
double HC_SR04::PulseDuration() {
  auto pulseStart = std::chrono::steady_clock::now();
  auto pulseEnd = std::chrono::steady_clock::now();

  while (echoPin.DigitalRead() == LOW) {
    pulseStart = std::chrono::steady_clock::now();
  }
    
  while (echoPin.DigitalRead() == HIGH) {
    pulseEnd = std::chrono::steady_clock::now();
  }
  
  std::chrono::duration<double> duration = (pulseEnd-pulseStart);
  return duration.count();
}

/*
  Public method to calculate the distance
  @return double: the measured distance in cm
*/
double HC_SR04::MeasureDistanceCm() {
  // Send the pulse and keep it for at least 5ms in HIGH state
  triggerPin.DigitalWrite(HIGH);
  Delayms(5);
  triggerPin.DigitalWrite(LOW);

  double distanceCm = this->PulseDuration() * soundSpeed / 2.0;
  
  if (distanceCm == 0 || distanceCm > 400) {
    return -1.0;
  }
  else { 
    return distanceCm;
  } 
}

// Destructor
HC_SR04::~HC_SR04() {}
